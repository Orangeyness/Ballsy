#include "ShutdownListener.h"

void ShutdownListener::Shutdown(EventQueueAccessor eQ)
{
    ALLEGRO_EVENT stopEvent;
    stopEvent.user.type = EVENT_LOOP_STOP;

    eQ.Talk(stopEvent);
}

void ShutdownListener::Pause(EventQueueAccessor eQ)
{
    ALLEGRO_EVENT event;
    event.user.type = EVENT_SCENE_PAUSE;

    eQ.Talk(event);
}

void ShutdownListener::Resume(EventQueueAccessor eQ)
{
    ALLEGRO_EVENT event;
    event.user.type = EVENT_SCENE_RESUME;

    eQ.Talk(event);
}

void ShutdownListener::SetupListen(EventQueueAccessor eQ)
{
    using namespace std::placeholders;

    EventCallBack shutdownCallBack = std::bind(&ShutdownListener::Shutdown, this, _2);
    EventCallBack pauseCallBack = std::bind(&ShutdownListener::Pause, this, _2);
    EventCallBack resumeCallBack = std::bind(&ShutdownListener::Resume, this, _2);

    eQ.ListenFor(GetEventId(ALLEGRO_EVENT_DISPLAY_CLOSE), shutdownCallBack);
    eQ.ListenFor(GetKeyboardEventId(ALLEGRO_EVENT_KEY_DOWN, ALLEGRO_KEY_ESCAPE), shutdownCallBack);
    eQ.ListenFor(GetKeyboardEventId(ALLEGRO_EVENT_KEY_DOWN, ALLEGRO_KEY_P), pauseCallBack);
    eQ.ListenFor(GetKeyboardEventId(ALLEGRO_EVENT_KEY_DOWN, ALLEGRO_KEY_R), resumeCallBack);
}
