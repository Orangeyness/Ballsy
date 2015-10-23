#ifndef H_EVENTS_SOURCE_GROUP
#define H_EVENTS_SOURCE_GROUP

#include "Events/EventCallBack.h"

#include <allegro5/allegro.h>
#include <map>

namespace Events
{
    class EventBoy;

    typedef void* SourceHandle;

    class SourceGroup
    {
        friend class EventBoy;

        private:
            ALLEGRO_EVENT_QUEUE* _eventQueue;
            std::multimap<SourceHandle, ALLEGRO_EVENT_SOURCE*> _sources;

        protected:
            void AddSource(SourceHandle handle, ALLEGRO_EVENT_SOURCE* source);
            void RemoveSource(SourceHandle handle, ALLEGRO_EVENT_SOURCE* source);
            void RemoveSource(SourceHandle handle);

        public:
            SourceGroup(ALLEGRO_EVENT_QUEUE* eventQueue);
    };
}

#endif
