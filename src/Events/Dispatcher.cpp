#include "Events/Dispatcher.h"
#include "Events/EventBoy.h"

#include <algorithm>

namespace Events
{
    Dispatcher::Dispatcher(DispatchFilter filter, bool allowedChildren)
        :   _filter(filter),
            _allowedChildren(allowedChildren)
    { }

    void Dispatcher::FireEvent(const ALLEGRO_EVENT& event, EventBoy boy)
    {
        for(auto const& entry : _listeners)
        {
            boy.ReBind(entry.Listener);
            entry.CallBack(event, boy);
        }

        if (!_allowedChildren)
            return;

        intptr_t key = _filter(event);

        // We have a child dispatcher to handle this event type
        auto childIter = _filteredDispatchers.find(key);
        if (childIter != _filteredDispatchers.end())
        {
            auto& childDispatcher = childIter->second;
            childDispatcher.FireEvent(event, boy);
            return;
        }
    }

    void Dispatcher::AddListener(ListenerHandle listener, EventCallBack callBack)
    {
        AddListenerEntry(ListenerEntry(listener, callBack));
    }

    void Dispatcher::AddListenerEntry(ListenerEntry listener)
    {
        _listeners.push_back(listener);
    }

    void Dispatcher::RemoveListenerLocal(ListenerHandle listener)
    {
        auto back = _listeners.end();
        for(auto it = _listeners.begin(); it != _listeners.end(); ++it)
        {
            auto entry = *it;

            if (entry.Listener == listener)
            {
                std::iter_swap(it--, --back);
                _listeners.pop_back();
            }
        }
    }

    void Dispatcher::RemoveListener(ListenerHandle listener)
    {
        RemoveListenerLocal(listener);

        for (auto& child : _filteredDispatchers)
        {
            child.second.RemoveListener(listener);
        }
    }

    Dispatcher& Dispatcher::Filter(intptr_t id)
    {
        auto entry = _filteredDispatchers.find(id);

        if (entry == _filteredDispatchers.end())
        {
            if (!_allowedChildren)
                throw TracedException("Enable to filter further");

            AddFilter(id, std::bind(NoChildrenFilter), false);
         
            entry = _filteredDispatchers.find(id);
        }

        return entry->second;
    }

    void Dispatcher::AddFilter(intptr_t id, DispatchFilter filter, bool allowedChildren)
    {
        bool hasFilter = _filteredDispatchers.count(id) > 0;

        if (hasFilter)
            throw TracedException("Filter already registered");

        if (!_allowedChildren)
            throw TracedException("Enable to filter further");

        // TODO: Use emplace to construct Dispatcher
        _filteredDispatchers.emplace(id, Dispatcher(filter, allowedChildren));
    }

    void Dispatcher::AddFilter(intptr_t id, DispatchFilter filter)
    {
        AddFilter(id, filter, true);
    }

    ListenerEntry::ListenerEntry
        (ListenerHandle listener, EventCallBack callBack)
        :   Listener(listener),
            CallBack(callBack)
    { }
}
