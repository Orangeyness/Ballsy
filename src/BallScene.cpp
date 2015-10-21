#include "BallScene.h"
#include "util/TracedException.h"

#include <allegro5/allegro_primitives.h>

BallScene::BallScene(int width, int height)
    : _width(width),
      _height(height)
{
    _timer = al_create_timer(ALLEGRO_BPS_TO_SECS(30));

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

void BallScene::SetEventLoop(EventLoopListenerAdder loop)
{
    using namespace std::placeholders;

    loop.ListenFor(ALLEGRO_EVENT_TIMER, std::bind(&BallScene::Update, this, _1));
    loop.ListenFor(EventTypes::RENDER_EVENT, std::bind(&BallScene::Render, this, _1));
}

ALLEGRO_EVENT_SOURCE* BallScene::GetEventSource() const
{
    return al_get_timer_event_source(_timer);
}

EventCallbackResult BallScene::Update(const ALLEGRO_EVENT& event)
{
    if (event.timer.source != _timer)
        return EventCallbackResult::NORMAL;   

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

    return EventCallbackResult::NEED_RENDER;
}

EventCallbackResult BallScene::Render(const ALLEGRO_EVENT& event)
{
    al_clear_to_color(al_map_rgb(200, 200, 200));

    for(const Ball& ball : _balls)
        al_draw_filled_circle(ball.x, ball.y, ball.radius, al_map_rgb(255, 0, 0));

    al_flip_display();

    return EventCallbackResult::NORMAL;
}
