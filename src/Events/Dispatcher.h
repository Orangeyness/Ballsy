#ifndef H_EVENTS_DISPATCHER
#define H_EVENTS_DISPATCHER

#include "Events/EventCallBack.h"
#include "Events/EventFilters.h"
#include "Util/TracedException.h"

#include <allegro5/allegro.h>

#include <functional>
#include <vector>
#include <map>

namespace Events
{
    class EventBoy;
    class ListenerEntry;

    // Hiding void* behind a typedef 
    // makes it fine right?
    typedef void* ListenerHandle;

    class Dispatcher
    {
        friend class DispatcherProxy;
        friend class EventQueue;

        private:
            std::vector<ListenerEntry> _listeners;
            std::map<intptr_t, Dispatcher> _filteredDispatchers;
            DispatchFilter _filter;
            bool _allowedChildren;

        protected:
            Dispatcher(DispatchFilter filter, bool allowedChildren);

            void FireEvent(const ALLEGRO_EVENT& event, EventBoy boy);

            void AddListener(ListenerHandle listener, EventCallBack callBack);

            void AddListenerEntry(ListenerEntry listener);

            void RemoveListenerLocal(ListenerHandle listener);

            void RemoveListener(ListenerHandle listener);

            void AddFilter(intptr_t id, DispatchFilter filter, bool allowedChildren);
        public:

            void AddFilter(intptr_t T, DispatchFilter filter);

            Dispatcher& Filter(intptr_t id);
    };

    class ListenerEntry
    {
        friend class Dispatcher;

        public:
            ListenerEntry(ListenerHandle listener, EventCallBack callBack);

        protected:
            ListenerHandle Listener;
            EventCallBack CallBack;
    };
}

#endif
