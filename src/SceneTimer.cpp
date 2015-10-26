#include "SceneTimer.h"

using namespace Events;
using namespace std::placeholders;

SceneTimer::SceneTimer(int fps, Events::EventCallBack updateCallBack)
    :   _updateCallBack(updateCallBack)
{
    _timer = al_create_timer(ALLEGRO_BPS_TO_SECS(40));

    if (_timer == nullptr)
        throw TracedException("Bad Timer");

    al_start_timer(_timer);
}

SceneTimer::~SceneTimer()
{
    al_destroy_timer(_timer);
}

void SceneTimer::OnPause()
{
    al_stop_timer(_timer);
}

void SceneTimer::OnResume()
{
    al_start_timer(_timer);
}

void SceneTimer::ConnectEvents(EventBoy e)
{
    e   .Listen(ALLEGRO_EVENT_TIMER)
        .Filter((intptr_t)_timer)
        .Do(_updateCallBack);

    // TODO: These two events to be filtered by timer
    e   .Listen(EVENT_SCENE_PAUSE)
        .Do(std::bind(&SceneTimer::OnPause, this));

    e   .Listen(EVENT_SCENE_RESUME)
        .Do(std::bind(&SceneTimer::OnResume, this));

    e   .TalkFrom(al_get_timer_event_source(_timer));
}

void SceneTimer::DisconnectEvents(EventBoy e)
{
    e   .Listen(ALLEGRO_EVENT_TIMER)
        .Filter((intptr_t)_timer)
        .Stop();

    e   .Listen(EVENT_SCENE_PAUSE)
        .Stop();

    e   .Listen(EVENT_SCENE_RESUME)
        .Stop();

    e   .StopTalking(al_get_timer_event_source(_timer));
}
