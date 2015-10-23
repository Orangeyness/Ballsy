#include "ShutdownListener.h"

#include <iostream>

using namespace Events;

void ShutdownListener::Shutdown(EventBoy& e)
{
    e.Talk(EVENT_LOOP_STOP);
}

void ShutdownListener::Pause(EventBoy& e)
{
    e.Talk(EVENT_SCENE_PAUSE);
}

void ShutdownListener::Resume(EventBoy& e)
{
    e.Talk(EVENT_SCENE_RESUME);
}

void ShutdownListener::Key(const ALLEGRO_EVENT& event)
{
    std::cout << event.keyboard.keycode << std::endl;
}

void ShutdownListener::ConnectEvents(EventBoy e)
{
    using namespace std::placeholders;

    EventCallBack shutdownCallBack = std::bind(&ShutdownListener::Shutdown, this, _2);
    EventCallBack pauseCallBack = std::bind(&ShutdownListener::Pause, this, _2);
    EventCallBack resumeCallBack = std::bind(&ShutdownListener::Resume, this, _2);
    EventCallBack keyCallBack = std::bind(&ShutdownListener::Key, this, _1);

    e   .Listen(ALLEGRO_EVENT_DISPLAY_CLOSE)
        .Do(shutdownCallBack);

    e   .Listen(ALLEGRO_EVENT_KEY_UP)
        .Filter(ALLEGRO_KEY_ESCAPE)
        .Do(shutdownCallBack);

    e   .Listen(ALLEGRO_EVENT_KEY_DOWN)
        .Filter(ALLEGRO_KEY_P)
        .Do(pauseCallBack);

    e   .Listen(ALLEGRO_EVENT_KEY_CHAR)
        .Filter(ALLEGRO_KEY_R)
        .Do(resumeCallBack);

    e   .Listen(ALLEGRO_EVENT_KEY_CHAR)
        .Do(keyCallBack);
}
