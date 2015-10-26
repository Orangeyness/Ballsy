#include "Events/UserEvents/BallCreation.h"

using Util::Vector2;

namespace Events
{
    namespace UserEvents
    {
        BallCreation::BallCreation(BallCreationState state, const Vector2& position)
            : EventReader(EventType)
        {
            _event.user.data1 = (intptr_t)state;
            _event.user.data2 = (intptr_t)position.X;
            _event.user.data3 = (intptr_t)position.Y;
        }

        BallCreation::BallCreation(const ALLEGRO_EVENT& event)
            : EventReader(event)
        { }

        BallCreationState BallCreation::GetState()
        {
            return (BallCreationState)_event.user.data1;
        }

        Vector2 BallCreation::GetPosition()
        {
            return Vector2((int)_event.user.data2, (int)_event.user.data3);
        }

        void BallCreation::DisposePayLoad()
        { }
    }
}
