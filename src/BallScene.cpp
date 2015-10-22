#include "BallScene.h"
#include "Util/TracedException.h"

#include <allegro5/allegro_primitives.h>

BallScene::BallScene(int width, int height)
    : _width(width),
      _height(height)
{
    _timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));

    if (_timer == nullptr)
        throw TracedException("Bad Timer");

    _balls[0].x = 50;
    _balls[0].y = 50;
    _balls[0].xspeed = 20;
    _balls[0].yspeed = 20;
    _balls[0].radius = 100;

    _balls[1].x = 200;
    _balls[1].y = 300;
    _balls[1].xspeed = 1.2;
    _balls[1].yspeed = 4;
    _balls[1].radius = 7;

    _balls[2].x = 300;
    _balls[2].y = 200;
    _balls[2].xspeed = 2;
    _balls[2].yspeed = -1;
    _balls[2].radius = 9;

    _balls[3].x = 100;
    _balls[3].y = 150;
    _balls[3].xspeed = 3;
    _balls[3].yspeed = 3;
    _balls[3].radius = 10;

    _balls[4].x = 300;
    _balls[4].y = 40;
    _balls[4].xspeed = 2;
    _balls[4].yspeed = 2;
    _balls[4].radius = 34;

    al_start_timer(_timer);

    _needRenderEvent.type = EVENT_LOOP_RENDER_NEEDED;
}

BallScene::~BallScene()
{
    al_destroy_timer(_timer);
}

void BallScene::SetupListen(EventQueueAccessor eQ)
{
    using namespace std::placeholders;

    eQ.ListenFor(GetTimerEventId(ALLEGRO_EVENT_TIMER, _timer), std::bind(&BallScene::OnUpdate, this, _2));
    eQ.ListenFor(GetEventId(EVENT_RENDER), std::bind(&BallScene::OnRender, this));
    eQ.ListenFor(GetEventId(EVENT_SCENE_PAUSE), std::bind(&BallScene::OnPause, this));
    eQ.ListenFor(GetEventId(EVENT_SCENE_RESUME), std::bind(&BallScene::OnResume, this));
}

void BallScene::SetupTalk(EventQueueAccessor eQ)
{
    eQ.TalkFrom(al_get_timer_event_source(_timer));
}

void BallScene::OnUpdate(EventQueueAccessor eQ)
{
    for(Ball& b : _balls)
    {
        b.x += b.xspeed;
        b.y += b.yspeed;

        if (b.x - b.radius < 0)
        {
            b.x = b.radius;
            b.xspeed = -b.xspeed;
        } else if (b.x + b.radius >= _width)
        {
            b.x = _width - 1 - b.radius;
            b.xspeed = -b.xspeed;
        }

        if (b.y - b.radius < 0)
        {
            b.y = b.radius;
            b.yspeed = -b.yspeed;
        } else if (b.y + b.radius >= _height)
        {
            b.y = _height - b.radius;
            b.yspeed = -b.yspeed;
        }
    }

    eQ.Talk(_needRenderEvent);
}

void BallScene::OnRender()
{
    al_clear_to_color(al_map_rgb(200, 200, 200));

    for(const Ball& ball : _balls)
        al_draw_filled_circle(ball.x, ball.y, ball.radius, al_map_rgb(255, 0, 0));

    al_flip_display();
}

void BallScene::OnPause()
{
    al_stop_timer(_timer);
}

void BallScene::OnResume()
{
    al_start_timer(_timer);
}
