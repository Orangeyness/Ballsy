#include <cstdlib>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#ifdef ANDROID
   #include "allegro5/allegro_android.h"
#endif

#include "Events/EventLoop.h"
#include "ShutdownListener.h"
#include "BallScene.h"
#include "Util/TracedException.h"

bool init_allegro()
{
    if (!al_init())
        return false;

    if (!al_init_image_addon())
        return false;

    if (!al_install_keyboard())
        return false;

    if (!al_install_mouse())
        return false;

    if (!al_init_primitives_addon())
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
        throw TracedException("Could not initialise Allegro");

#ifdef ANDROID
    ALLEGRO_MONITOR_INFO monitor_info;
    al_get_monitor_info(0, &monitor_info);

    int width = (monitor_info.x2 - monitor_info.x1); 
    int height = (monitor_info.y2 - monitor_info.x1);
#else
    int width = 405;
    int height = 720;
#endif

    auto display = al_create_display(width, height);

    if (display == nullptr)
        throw TracedException("Bad Display");

    BallScene ballScene(width, height);
    ShutdownListener shutdownListener;

    EventLoop gameLoop;
    gameLoop.RegisterSource(al_get_display_event_source(display));
    gameLoop.RegisterSource(al_get_keyboard_event_source());
    gameLoop.RegisterListener(shutdownListener);
    gameLoop.RegisterSource(ballScene);
    gameLoop.RegisterListener(ballScene);

    gameLoop.Run();

    al_destroy_display(display);

    return EXIT_SUCCESS;
}
