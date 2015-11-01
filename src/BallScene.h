#ifndef H_BALL_SCENE
#define H_BALL_SCENE

#include "Box2D/Box2D.h"

#include "Events/Events.h"
#include "Rendering/Viewport.h"
#include "Util/Vector2.h"

#include "SceneTimer.h"
#include "BallInputListener.h"

#include <allegro5/allegro.h>
#include <vector>

class BallScene
{
    private:
        const float PixelsPerMetre = 20;

        b2World _world;
        ALLEGRO_TIMER* _timer;
        Rendering::Viewport _viewport;
        BallInputListener _input;
        SceneTimer _updateTimer;
        b2Body* _creatingBall;

        b2Body* CreateBall(const Vector2& position, const Vector2& velocity, float radius, float density, float restitution);
        void OnRender();
        void OnUpdate(Events::EventBoy e);
        void OnInput(const ALLEGRO_EVENT& event);

        inline float PhysicalToScreen(float x);
        inline float ScreenToPhysical(float x); 

    public:
        BallScene(Rendering::Viewport viewport);

        void ConnectEvents(Events::EventBoy e);
};

/*
class BallContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* manifold);
};*/

inline float BallScene::PhysicalToScreen(float x)
{
    return x * PixelsPerMetre;
}

inline float BallScene::ScreenToPhysical(float x)
{
    return x / PixelsPerMetre;
}

#endif
