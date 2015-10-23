#ifndef H_EVENT_TYPES
#define H_EVENT_TYPES

#include <allegro5/allegro.h>

namespace Events
{
    const ALLEGRO_EVENT_TYPE EVENT_BASE                     = ALLEGRO_GET_EVENT_TYPE('R','L','B', 0);
    const ALLEGRO_EVENT_TYPE EVENT_RENDER                   = EVENT_BASE + 0;
    const ALLEGRO_EVENT_TYPE EVENT_LOOP_RENDER_NEEDED       = EVENT_BASE + 1;
    const ALLEGRO_EVENT_TYPE EVENT_LOOP_STOP                = EVENT_BASE + 2;

    const ALLEGRO_EVENT_TYPE EVENT_SCENE_PAUSE              = EVENT_BASE + 3;
    const ALLEGRO_EVENT_TYPE EVENT_SCENE_RESUME             = EVENT_BASE + 4;
}
#endif
