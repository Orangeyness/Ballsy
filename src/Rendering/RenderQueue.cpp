#include "Rendering/RenderQueue.h"

#include "Events/Events.h"
#include "Events/UserEvents/UserEvents.h"

using namespace Events;
using namespace Events::UserEvents;
using namespace std::placeholders;

namespace Rendering
{
    RenderQueue::RenderQueue()
    {
        _active = true;
        _dirty = false;
    }

    bool RenderQueue::NeedsRender()
    {
        return _active && _dirty;
    }

    void RenderQueue::Render()
    {
        for(const auto& rendererEntry : _renderers)
            rendererEntry.CallBack();
    }

    void RenderQueue::OnDirty()
    {
        _dirty = true;
    }

    void RenderQueue::OnActiveChange(bool val)
    {
        _active = val;
    }

    void RenderQueue::OnAddRenderer(const ALLEGRO_EVENT& event)
    {
        auto entry = RenderRegister(event).GetRenderEntry();
        
        _renderers.insert(entry);
    }

    void RenderQueue::OnRemoveRenderer(const ALLEGRO_EVENT& event)
    {
        auto id = RenderUnregister(event).GetHandle();

        auto iter = _renderers.begin();
        while(iter !=_renderers.end())
        {
            if (iter->Handle == id)
                _renderers.erase(++iter);
            else
                ++iter;
        }
    }

    void RenderQueue::ConnectEvents(EventBoy& e)
    {
        e   .Listen(RenderRegister::EventType)
            .Do(std::bind(&RenderQueue::OnAddRenderer, this, _1));

        e   .Listen(RenderUnregister::EventType)
            .Do(std::bind(&RenderQueue::OnRemoveRenderer, this, _1));

        e   .Listen(EVENT_RENDER_NEEDED)
            .Do(std::bind(&RenderQueue::OnDirty, this));

        e   .Listen(EVENT_RENDER_NOT_ALLOWED)
            .Do(std::bind(&RenderQueue::OnActiveChange, this, false));

        e   .Listen(EVENT_RENDER_ALLOWED)
            .Do(std::bind(&RenderQueue::OnActiveChange, this, true));
    }

    void RenderQueue::DisconnectEvents(EventBoy& e)
    {
        e   .Listen(RenderRegister::EventType).Stop();
        e   .Listen(RenderUnregister::EventType).Stop();
        e   .Listen(EVENT_RENDER_NEEDED).Stop();
        e   .Listen(EVENT_RENDER_NOT_ALLOWED).Stop();
        e   .Listen(EVENT_RENDER_ALLOWED).Stop();
    }

    RenderEntry::RenderEntry(RenderHandle handle, RenderCallBack callBack, int depth)
        :   Handle(handle),
            CallBack(callBack),
            Depth(depth)
    { }

    bool RenderEntryOrderer::operator() (const RenderEntry& left, const RenderEntry& right) const
    {
        return left.Depth < right.Depth;
    }
}
