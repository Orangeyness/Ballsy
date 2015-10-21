#include "ShutdownListener.h"

EventCallbackResult ShutdownListener::Shutdown(const ALLEGRO_EVENT& event)
{
    return EventCallbackResult::STOP_LOOP;
}

void ShutdownListener::SetEventLoop(EventLoopListenerAdder loop)
{
    using namespace std::placeholders;

    EventCallback shutdownCallback = std::bind(&ShutdownListener::Shutdown, this, _1);

    loop.ListenFor(ALLEGRO_EVENT_DISPLAY_CLOSE, shutdownCallback);
    loop.ListenFor(ALLEGRO_EVENT_KEY_DOWN, shutdownCallback);
}
