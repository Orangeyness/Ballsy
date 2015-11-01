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
    :   _world(b2Vec2(0.0f, 10.0f)),
        _viewport(viewport),
        _input(_viewport),
        _updateTimer(40, std::bind(&BallScene::OnUpdate, this, _2))
{
    Vector2 size = Vector2(_viewport.Size());
    size.X = ScreenToPhysical(size.X);
    size.Y = ScreenToPhysical(size.Y);

    b2Body* body;
    b2BodyDef bodyDef;
    b2EdgeShape edge;
    bodyDef.type = b2_staticBody;

    // Horizontal edge
    edge.Set( b2Vec2(-size.X, 0), b2Vec2(size.X, 0));

    // Top
    bodyDef.position.Set(size.X / 2, 0);
    body = _world.CreateBody(&bodyDef);
    body->CreateFixture(&edge, 1.0);

    // Bottom
    bodyDef.position.Set(size.X / 2, size.Y);
    body = _world.CreateBody(&bodyDef);
    body->CreateFixture(&edge, 1.0f);

    // vertical edge
    edge.Set( b2Vec2(0, -size.Y), b2Vec2(0, size.Y));

    // Left
    bodyDef.position.Set(0, size.Y / 2);
    body = _world.CreateBody(&bodyDef);
    body->CreateFixture(&edge, 1.0f);
    
    // Right 
    bodyDef.position.Set(size.X, size.Y / 2);
    body = _world.CreateBody(&bodyDef);
    body->CreateFixture(&edge, 1.0f);

    CreateBall(_viewport.Size() / 2, Vector2(10, 5), 10, 1, 1);
    CreateBall(Vector2(200, 200), Vector2(20, 20), 10, 1, 1);
}

b2Body* BallScene::CreateBall(const Vector2& position, const Vector2& velocity, float radius, float density, float restitution)
{
    b2Vec2 realPosition (ScreenToPhysical(position.X), ScreenToPhysical(position.Y));
    b2Vec2 realVelocity (velocity.X, velocity.Y);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(realPosition.x, realPosition.y);
    bodyDef.linearDamping = 0.0f;
    bodyDef.gravityScale = 0.0f;
    bodyDef.bullet = true;

    b2Body* body = _world.CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_p.Set(0, 0);
    circle.m_radius = ScreenToPhysical(radius);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = density;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = restitution;
    body->CreateFixture(&fixtureDef);

    body->ApplyLinearImpulse(realVelocity, body->GetWorldCenter(), true);

    return body;
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
    Vector2 position = params.GetPosition();

    switch(state)
    {
        case BallCreationState::STARTED:
            _creatingBall = CreateBall(position, Vector2(0, 0), 10, 1, 0);
            break;

        case BallCreationState::COMPLETED:
            _creatingBall->SetGravityScale(1);
            _creatingBall->SetAwake(true);
            _creatingBall = nullptr;
            break;

        case BallCreationState::MOVED:
        {
            b2Vec2 realPosition (ScreenToPhysical(position.X), ScreenToPhysical(position.Y));
            _creatingBall->SetTransform(realPosition, _creatingBall->GetAngle());
            break;
        }
    }
}

void BallScene::OnUpdate(EventBoy e)
{
    if (_creatingBall != nullptr)
    {
        b2Fixture* originalFixture = _creatingBall->GetFixtureList();
        b2CircleShape* originalCircle = (b2CircleShape*)originalFixture->GetShape();
        float currentRadius = originalCircle->m_radius;

        _creatingBall->DestroyFixture(originalFixture);

        b2CircleShape circle;
        circle.m_p.Set(0, 0);
        circle.m_radius = currentRadius + ScreenToPhysical(1);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.0f;
        fixtureDef.restitution = 0.0f;
        _creatingBall->CreateFixture(&fixtureDef);
    }

    float timeStep = 1.0f / 40.0f;
    int velocityIterations = 8;
    int positionIterations = 3;

    _world.Step(timeStep, velocityIterations, positionIterations);

    e.Talk(EVENT_RENDER_NEEDED);
}

void BallScene::OnRender()
{
    al_clear_to_color(al_map_rgb(255, 255, 255));

    _viewport.SetTransform();

    for ( b2Body* b = _world.GetBodyList(); b; b = b->GetNext())
    {
        b2Fixture* fixture = b->GetFixtureList();

        b2Shape::Type shapeType = fixture->GetType();
        if ( shapeType != b2Shape::e_circle)
            continue;

        b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();

        auto ballPos = b->GetPosition();

        float radius = PhysicalToScreen(circle->m_radius);
        float ballX = PhysicalToScreen(ballPos.x);
        float ballY = PhysicalToScreen(ballPos.y);
        al_draw_filled_circle(ballX, ballY, radius, al_map_rgb(255, 0, 0));
    }

    _viewport.UnsetTransform();

    al_flip_display();
}
