#include <iostream>
#include <cstdlib>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "util/TracedException.h"

bool init_allegro()
{
    if (!al_init())
        return false;

    if (!al_init_font_addon())
        return false;

    if (!al_init_image_addon())
        return false;

    if (!al_install_keyboard())
        return false;

    if (!al_install_mouse())
        return false;

    al_set_new_display_flags(ALLEGRO_OPENGL);
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_RENDER_METHOD, 1, ALLEGRO_SUGGEST);
    //al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_CAN_DRAW_INTO_BITMAP, 1, ALLEGRO_SUGGEST);

    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_VIDEO_BITMAP);

    return true;
}

int main(int argc, char** argv)
{
    if (!init_allegro())
        throw TracedException("Could not initalise Allegro");

    auto display = al_create_display(800, 600);
    auto timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
    auto eventQueue = al_create_event_queue();

    if (display == nullptr)
        throw TracedException("Bad Display");

    if (timer == nullptr)
        throw TracedException("Bad Timer");

    if (eventQueue == nullptr)
        throw TracedException("Bad EventQueue");

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    al_start_timer(timer);

    bool render = true;
    bool gameActive = true;
    while (gameActive)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                gameActive = false;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    gameActive = false;
                break;

            case ALLEGRO_EVENT_TIMER:
               render = true;
               break;               
        }

        if (render && al_is_event_queue_empty(eventQueue))
        {
            al_clear_to_color(al_map_rgb(255, 255, 255));

            al_draw_filled_circle(400, 300, 50, al_map_rgb(255, 0, 0));

            al_flip_display();
            render = false;
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return EXIT_SUCCESS;
}
