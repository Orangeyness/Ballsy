#ifndef H_BALL_INPUT_LISTENER
#define H_BALL_INPUT_LISTENER

#include "Events/Events.h"
#include "Events/UserEvents/BallCreation.h"
#include "Rendering/Viewport.h"

#include <allegro5/allegro.h>

using Events::UserEvents::BallCreationState;

class BallInputListener
{
    private:
        const Rendering::Viewport& _viewport;
        bool _inputActive;

        void OnInput(const ALLEGRO_EVENT& event, Events::EventBoy e, BallCreationState state);
        bool IsTouchEvent(const ALLEGRO_EVENT& event);

    public:
        BallInputListener(const Rendering::Viewport& viewport);

        void ConnectEvents(Events::EventBoy& e);
        void DisconnectEvents(Events::EventBoy& e);
};

#endif
