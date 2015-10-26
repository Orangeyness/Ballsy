#include "BallScene.h"
#include "Util/Vector2.h"
#include "Util/TracedException.h"
#include "Events/UserEvents/RenderRegister.h"
#include "Events/UserEvents/BallCreation.h"

#include <allegro5/allegro_primitives.h>

using namespace Events;
using namespace Rendering;
using namespace std::placeholders;

using Util::Vector2;
using Events::UserEvents::BallCreation;
using Events::UserEvents::BallCreationState;
using Events::UserEvents::RenderRegister;

BallScene::BallScene(Viewport viewport)
    :   _viewport(viewport),
        _input(_viewport),
        _updateTimer(40, std::bind(&BallScene::OnUpdate, this, _2)),
        _isCreatingBall(false)
{
    _creatingBall.speed.X = 4;
    _creatingBall.speed.Y = 3;
}

void BallScene::ConnectEvents(EventBoy e)
{
    e   .Register(_input);
    e   .Register(_updateTimer);

    e   .Listen(BallCreation::EventType)
        .Do(std::bind(&BallScene::OnInput, this, _1));

    e   .Talk(RenderRegister(this, std::bind(&BallScene::OnRender, this), 10));
}

void BallScene::OnInput(const ALLEGRO_EVENT& event)
{

    BallCreation params(event);
    BallCreationState state = params.GetState();
    _creatingBall.pos = params.GetPosition();
    UpdateBallPosition(_creatingBall, _viewport.Size());   

    switch(state)
    {
        case BallCreationState::STARTED:
            _isCreatingBall = true;
            _creatingBall.radius = 1;
            break;

        case BallCreationState::COMPLETED:
            _isCreatingBall = false;
            _balls.push_back(_creatingBall);
            break;

        default:
            break;
    }
}

void BallScene::OnUpdate(EventBoy e)
{
    if (_isCreatingBall)
        _creatingBall.radius += 1;

    auto size = _viewport.Size();

    for(Ball& b : _balls)
        UpdateBallPosition(b, size);

    e.Talk(EVENT_RENDER_NEEDED);
}

void BallScene::UpdateBallPosition(Ball& b, const Vector2& size)
{
    b.pos += b.speed;

    if (b.pos.X - b.radius < 0)
    {
        b.pos.X = b.radius;
        b.speed.X = -b.speed.X;
    } else if (b.pos.X + b.radius >= size.X)
    {
        b.pos.X = size.X - 1 - b.radius;
        b.speed.X = -b.speed.X;
    }

    if (b.pos.Y - b.radius < 0)
    {
        b.pos.Y = b.radius;
        b.speed.Y = -b.speed.Y;
    } else if (b.pos.Y + b.radius >= size.Y)
    {
        b.pos.Y = size.Y - b.radius;
        b.speed.Y = -b.speed.Y;
    }
}

void BallScene::OnRender()
{
    al_clear_to_color(al_map_rgb(255, 255, 255));

    _viewport.SetTransform();

    al_draw_filled_rectangle(0, 0, 1920, 1920, al_map_rgb(0, 200, 200));

    if (_isCreatingBall)
        al_draw_filled_circle(_creatingBall.pos.X, _creatingBall.pos.Y, _creatingBall.radius, al_map_rgb(0, 0, 255));

    for(const Ball& ball : _balls)
        al_draw_filled_circle(ball.pos.X, ball.pos.Y, ball.radius, al_map_rgb(255, 0, 0));

    _viewport.UnsetTransform();

    al_flip_display();
}
