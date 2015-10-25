#ifndef H_EVENTS_USER_EVENT_RENDER_REGISTER
#define H_EVENTS_USER_EVENT_RENDER_REGISTER

#include "Rendering/RenderQueue.h"
#include "Events/EventReader.h"
#include "Events/EventTypes.h"

#include <allegro5/allegro.h>

using namespace Rendering;

namespace Events
{
    namespace UserEvents
    {
        class RenderRegister : protected EventReader
        {
            public: 
                static const int EventType = EVENT_RENDER_REGISTER;

                RenderRegister(RenderHandle handle, RenderCallBack callBack, int depth);
                RenderRegister(const ALLEGRO_EVENT& event);
                RenderRegister(const RenderRegister& that) = delete;
                RenderRegister(RenderRegister&& that);
                RenderRegister& operator=(RenderRegister that);

                virtual ~RenderRegister();
                const RenderEntry& GetRenderEntry();
                void DisposePayLoad();

                using EventReader::Transmit;
        };

    }
}

#endif
