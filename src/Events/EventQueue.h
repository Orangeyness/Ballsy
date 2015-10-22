#ifndef H_EVENT_QUEUE
#define H_EVENT_QUEUE

#include "Events/EventTypes.h"
#include "Events/EventListenerEntry.h"
#include "Events/EventQueueAccessor.h"

#include <allegro5/allegro.h>
#include <unordered_map>

class EventQueue
{
    friend EventQueueAccessor;

    private:
        ALLEGRO_EVENT_QUEUE* _eventQueue;
        ALLEGRO_EVENT_SOURCE _eventSource;
        std::unordered_multimap<EventId, EventListenerEntry> _callBackMap;
        std::unordered_multimap<ListenerHandle, EventId> _listenerMap;
        std::unordered_multimap<ListenerHandle, ALLEGRO_EVENT_SOURCE*> _sourceMap;

        void HandleEvent(const ALLEGRO_EVENT& event);

        inline EventQueueAccessor GetAccessor(ListenerHandle target);

        template<typename T>
        inline EventQueueAccessor GetAccessor(T& target);

        template<typename T>
        inline EventQueueAccessor GetAccessor(T* target);

        bool DeregisterCallBack(ListenerHandle listener, EventId id);

    protected:
        void RegisterListener(EventListenerEntry entry);
        bool DeregisterListener(ListenerHandle listener, EventId id);
        bool DeregisterListener(ListenerHandle listener);

        void RegisterEventSource(ListenerHandle listener, ALLEGRO_EVENT_SOURCE* eventSource);
        bool DeregisterEventSource(ListenerHandle listener, ALLEGRO_EVENT_SOURCE* eventSource);
        bool DeregisterEventSource(ListenerHandle listener);

        void BroadcastEvent(ALLEGRO_EVENT& userEvent);

    public:
        EventQueue();
        ~EventQueue();
        
        void ProcessNextEvent();
        bool Empty();

        void RegisterSource(ALLEGRO_EVENT_SOURCE* eventSource);

        template<typename T>
        void RegisterSource(T& eventSource);
       
        template<typename T>
        void RegisterSource(T* eventSource);

        template<typename T>
        void RegisterListener(T& eventListener);

        template<typename T>
        void RegisterListener(T* eventListener);
};

inline EventQueueAccessor EventQueue::GetAccessor(ListenerHandle target)
{
    return EventQueueAccessor(this, target);
}

template<typename T>
inline EventQueueAccessor EventQueue::GetAccessor(T* target)
{
    return EventQueueAccessor(this, static_cast<ListenerHandle>(target));
}

template<typename T>
inline EventQueueAccessor EventQueue::GetAccessor(T& target)
{
    return EventQueueAccessor(this, static_cast<ListenerHandle>(&target));
}

template<typename T>
void EventQueue::RegisterSource(T& eventSource)
{
    eventSource.SetupTalk(GetAccessor(eventSource));
}

template<typename T>
void EventQueue::RegisterSource(T* eventSource)
{
    eventSource->SetupTalk(GetAccessor(eventSource));
}

template<typename T>
void EventQueue::RegisterListener(T& eventListener)
{
    eventListener.SetupListen(GetAccessor(eventListener));
}

template<typename T>
void EventQueue::RegisterListener(T* eventListener)
{
    eventListener->SetupListen(GetAccessor(eventListener));
}

#endif
