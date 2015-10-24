#include "BallScene.h"
#include "Util/TracedException.h"

#include <allegro5/allegro_primitives.h>

using namespace Events;

BallScene::BallScene(int width, int height)
    : _width(width),
      _height(height)
{
    _timer = al_create_timer(ALLEGRO_BPS_TO_SECS(20));

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
}

BallScene::~BallScene()
{
    al_destroy_timer(_timer);
}

void BallScene::ConnectEvents(EventBoy e)
{
    using namespace std::placeholders;

    e   .Listen(ALLEGRO_EVENT_TIMER)
        .Filter((intptr_t)_timer)
        .Do(std::bind(&BallScene::OnUpdate, this, _2));

    e   .Listen(EVENT_RENDER)
        .Do(std::bind(&BallScene::OnRender, this));

    e   .Listen(EVENT_SCENE_PAUSE)
        .Do(std::bind(&BallScene::OnPause, this));

    e   .Listen(EVENT_SCENE_RESUME)
        .Do(std::bind(&BallScene::OnResume, this));

    e   .TalkFrom(al_get_timer_event_source(_timer));
}

void BallScene::OnUpdate(EventBoy e)
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

    e.Talk(EVENT_RENDER_NEEDED);
}

#include <math.h>

void BallScene::OnRender()
{
    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_draw_filled_rectangle(0, 0, _width/2, _height/2, al_map_rgb(100, 0, 0));
    al_draw_filled_rectangle(_width/2, 0, _width, _height/2, al_map_rgb(0, 100, 0));
    al_draw_filled_rectangle(0, _height/2, _width/2, _height, al_map_rgb(0, 0, 100));
    al_draw_filled_rectangle(_width/2, _height/2, _width, _height, al_map_rgb(100, 100, 100));

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
