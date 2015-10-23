#include <cstdlib>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#ifdef ANDROID
   #include "allegro5/allegro_android.h"
#endif

#include "ShutdownListener.h"
#include "BallScene.h"
#include "Events/Events.h"
#include "Util/TracedException.h"

using namespace Events;
using namespace std::placeholders;

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

    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();

    EventLoop gameLoop (eventQueue, std::bind(EventTypeFilter, _1));

    auto& dispatcher = gameLoop.GetDispatcher();
    dispatcher.AddFilter(ALLEGRO_EVENT_KEY_DOWN, std::bind(KeyCodeFilter, _1));
    dispatcher.AddFilter(ALLEGRO_EVENT_KEY_UP, std::bind(KeyCodeFilter, _1));
    dispatcher.AddFilter(ALLEGRO_EVENT_KEY_CHAR, std::bind(KeyCodeFilter, _1));
    dispatcher.AddFilter(ALLEGRO_EVENT_TIMER, std::bind(TimerSourceFilter, _1));

    gameLoop.Register(al_get_display_event_source(display));
    gameLoop.Register(al_get_keyboard_event_source());
    gameLoop.Register(shutdownListener);
    gameLoop.Register(ballScene);

    gameLoop.Run();

    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);

    return EXIT_SUCCESS;
}
