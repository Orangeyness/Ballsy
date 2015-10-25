#ifndef H_EVENTS_EVENT_READER
#define H_EVENTS_EVENT_READER

#include <allegro5/allegro.h>

namespace Events
{
    class EventReader 
    {
        private:
            bool _ownsPayLoad;

            void InternalSetPayLoad(intptr_t ptr);
            intptr_t InternalGetPayLoad();

        protected:
            ALLEGRO_EVENT _event;

            EventReader(int eventType);
            EventReader(const ALLEGRO_EVENT& event);

            bool IsOwner();    
            bool HasPayLoad();
            bool ShouldDisposePayLoad();

            template<typename T>
            T* GetPayLoad();

            template<typename T>
            void SetPayLoad(T* t);

        public:
            void Transmit(ALLEGRO_EVENT_SOURCE* source);

            static void Dispose(const ALLEGRO_EVENT& event);

            void DisposePayLoad();
    };

    template<typename T>
    T* EventReader::GetPayLoad()
    {
        return (T*)(InternalGetPayLoad());
    }

    template<typename T>
    void EventReader::SetPayLoad(T* t)
    {
        InternalSetPayLoad((intptr_t) t);
    }
}


#endif
