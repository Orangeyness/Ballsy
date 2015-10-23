#include "Events/DispatcherProxy.h"

namespace Events
{
    DispatcherProxy::DispatcherProxy(Dispatcher* dispatcher, ListenerHandle listener)
        :   _dispatcher(dispatcher),
            _listener(listener)
    {
    }

    void DispatcherProxy::Do(EventCallBack event)
    {
        _dispatcher->AddListenerEntry(ListenerEntry(_listener, event));
    }

    void DispatcherProxy::Stop()
    {
        _dispatcher->RemoveListenerLocal(_listener);
    }

    void DispatcherProxy::StopAll()
    {
        _dispatcher->RemoveListenerLocal(_listener);
    }

    DispatcherProxy DispatcherProxy::Filter(intptr_t id) 
    {
        return DispatcherProxy(&(_dispatcher->Filter(id)), _listener);
    }
}
