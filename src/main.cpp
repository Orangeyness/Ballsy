#include <cstdlib>
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#ifdef ANDROID
   #include "allegro5/allegro_android.h"
#endif

#include "DisplayMan.h"
#include "ShutdownListener.h"
#include "BallScene.h"
#include "Events/Events.h"
#include "Util/TracedException.h"
#include "Util/Loggers/StreamLogger.h"
#include "Util/Loggers/AndroidLogger.h"

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

    Util::Loggers::AndroidLogger logger("Ballsy");
#else
    int width = 480;
    int height = 720;

    Util::Loggers::StreamLogger logger(std::cout);
#endif

    DisplayMan display(width, height);
    EventLogger eventLogger(logger);
    BallScene ballScene(width, height);
    ShutdownListener shutdownListener;

    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();

    EventLoop gameLoop (eventQueue, Events::Filters::EventType);

    auto& dispatcher = gameLoop.GetDispatcher();
    dispatcher.AddFilter(ALLEGRO_EVENT_KEY_DOWN, Events::Filters::KeyCode);
    dispatcher.AddFilter(ALLEGRO_EVENT_KEY_UP, Events::Filters::KeyCode);
    dispatcher.AddFilter(ALLEGRO_EVENT_KEY_CHAR, Events::Filters::KeyCode);
    dispatcher.AddFilter(ALLEGRO_EVENT_TIMER, Events::Filters::TimerSource);

    gameLoop.Register(display);
    gameLoop.Register(al_get_keyboard_event_source());
    gameLoop.Register(eventLogger);
    gameLoop.Register(shutdownListener);
    gameLoop.Register(ballScene);

    gameLoop.Run();

    al_destroy_event_queue(eventQueue);

    return EXIT_SUCCESS;
}
