#ifndef H_EVENT_CALL_BACK
#define H_EVENT_CALL_BACK

#include <allegro5/allegro.h>
#include <functional>

// Hiding void* behind a typedef 
// makes it fine right?
typedef void* ListenerHandle;

class EventQueueAccessor;

typedef std::function<void(const ALLEGRO_EVENT&, EventQueueAccessor)> EventCallBack;

#endif
