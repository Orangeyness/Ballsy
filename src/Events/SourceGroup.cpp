#include "Events/SourceGroup.h"

namespace Events
{
    SourceGroup::SourceGroup(ALLEGRO_EVENT_QUEUE* eventQueue)
        :   _eventQueue(eventQueue)
    { }

    void SourceGroup::AddSource(SourceHandle handle, ALLEGRO_EVENT_SOURCE* source)
    {
        _sources.emplace(handle, source);
        al_register_event_source(_eventQueue, source);
    }

    void SourceGroup::RemoveSource(SourceHandle handle, ALLEGRO_EVENT_SOURCE* source)
    {
        al_unregister_event_source(_eventQueue, source);

        auto sources = _sources.equal_range(handle);
        for (auto it = sources.first; it != sources.second; ++it)
        {
            ALLEGRO_EVENT_SOURCE* foundSource = it->second;
            if (foundSource == source)
            {
                _sources.erase(it);
                return;
            }
        }
    }

    void SourceGroup::RemoveSource(SourceHandle source)
    {
        auto sources = _sources.equal_range(source);
        for (auto it = sources.first; it != sources.second; ++it)
        {
            ALLEGRO_EVENT_SOURCE* foundSource = it->second;
            al_unregister_event_source(_eventQueue, foundSource);
        }

        _sources.erase(sources.first, sources.second);
    }
}
