#ifndef H_SHUTDOWN_LISTENER
#define H_SHUTDOWN_LISTENER

#include "Events/Events.h"
#include <allegro5/allegro.h>

class ShutdownListener
{
    private:
        void Shutdown(Events::EventBoy& e);
        void Pause(Events::EventBoy& e);
        void Resume(Events::EventBoy& e);
        void Key(const ALLEGRO_EVENT& event);

    public:
        void ConnectEvents(Events::EventBoy e);
};

#endif
