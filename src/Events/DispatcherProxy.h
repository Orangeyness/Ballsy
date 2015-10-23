#ifndef H_EVENTS_DISPATCHER_PROXY
#define H_EVENTS_DISPATCHER_PROXY

#include "Events/Dispatcher.h"

namespace Events
{
    class DispatcherProxy
    {
        friend class EventBoy;

        private:
            Dispatcher* _dispatcher;
            ListenerHandle _listener;

        protected:
            DispatcherProxy(Dispatcher* dispatcher, ListenerHandle listener);

        public:
            DispatcherProxy Filter(intptr_t id);

            void Do(EventCallBack event);
            void Stop();
            void StopAll();
    };
}

#endif
