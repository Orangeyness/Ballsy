#ifndef H_EVENTS_USER_EVENT_BALL_CREATION
#define H_EVENTS_USER_EVENT_BALL_CREATION

#include "Util/Vector2.h"
#include "Events/EventReader.h"
#include "Events/EventTypes.h"

#include <allegro5/allegro.h>

namespace Events
{
    namespace UserEvents
    {
        enum BallCreationState
        {
            STARTED,
            MOVED,
            COMPLETED
        };

        class BallCreation : protected EventReader
        {
            public: 
                static const int EventType = EVENT_BALL_CREATION;

                BallCreation(BallCreationState state, const Util::Vector2& position);
                BallCreation(const ALLEGRO_EVENT& event);

                Util::Vector2 GetPosition();
                BallCreationState GetState();
                void DisposePayLoad();

                using EventReader::Transmit;
        };
    }
} 


#endif
