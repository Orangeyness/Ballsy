#include "Events/UserEvents/RenderRegister.h"
#include "Util/TracedException.h"
#include <iostream>

using namespace Rendering;

namespace Events
{
    namespace UserEvents
    {
        RenderRegister::RenderRegister(RenderHandle handle, RenderCallBack callback, int depth)
            : EventReader(EventType)
        {
            SetPayLoad<RenderEntry>(new RenderEntry(handle, callback, depth));
        }

        RenderRegister::RenderRegister(const ALLEGRO_EVENT& event)
            : EventReader(event)
        {
        }

        RenderRegister::RenderRegister(RenderRegister&& that)
            : EventReader(EventType)
        {
            std::swap(_event, that._event);
        }

        RenderRegister& RenderRegister::operator=(RenderRegister that)
        {
            std::swap(_event, that._event);
            return *this;
        }

        RenderRegister::~RenderRegister()
        {
            if (ShouldDisposePayLoad())
            {
                std::cout << "DisposePayLoad on destructor" << std::endl;
                DisposePayLoad();
            }
        }

        void RenderRegister::DisposePayLoad()
        {
            std::cout << "RenderRegister::DisposePayLoad" << std::endl;

            delete GetPayLoad<RenderEntry>();

            EventReader::DisposePayLoad();
        }

        const RenderEntry& RenderRegister::GetRenderEntry()
        {
            if (!HasPayLoad())
                throw TracedException("Not payload");

            return *GetPayLoad<RenderEntry>();
        }

    }   
}
