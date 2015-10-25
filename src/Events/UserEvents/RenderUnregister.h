#ifndef H_EVENTS_USER_EVENT_RENDER_UNREGISTER
#define H_EVENTS_USER_EVENT_RENDER_UNREGISTER

#include "Rendering/RenderQueue.h"
#include "Events/EventReader.h"
#include "Events/EventTypes.h"

#include <allegro5/allegro.h>

using namespace Rendering;

namespace Events
{
    namespace UserEvents
    {
        class RenderUnregister : protected EventReader
        {
            public: 
                static const int EventType = EVENT_RENDER_UNREGISTER;

                RenderUnregister(RenderHandle renderer);
                RenderUnregister(const ALLEGRO_EVENT& event);

                RenderHandle GetHandle();
                void DisposePayLoad();

                using EventReader::Transmit;
        };

    }
}

#endif
