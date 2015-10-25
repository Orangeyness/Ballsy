#include "Events/UserEvents/RenderUnregister.h"

using namespace Rendering;

namespace Events
{
    namespace UserEvents
    {
        RenderUnregister::RenderUnregister(RenderHandle handle)
            : EventReader(EventType)
        {
            _event.user.data1 = (intptr_t)handle;
        }

        RenderUnregister::RenderUnregister(const ALLEGRO_EVENT& event)
            : EventReader(event)
        { }

        RenderHandle RenderUnregister::GetHandle()
        {
            return (RenderHandle)_event.user.data1;
        }

        void RenderUnregister::DisposePayLoad()
        { }
    }
}
