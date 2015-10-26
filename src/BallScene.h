#ifndef H_BALL_SCENE
#define H_BALL_SCENE

#include "Events/Events.h"
#include "Rendering/Viewport.h"
#include "Util/Vector2.h"

#include "SceneTimer.h"
#include "BallInputListener.h"

#include <allegro5/allegro.h>
#include <vector>

struct Ball
{
    Vector2 pos;
    Vector2 speed;
    float radius;
};

class BallScene
{
    private:
        ALLEGRO_TIMER* _timer;
        std::vector<Ball> _balls;
        Rendering::Viewport _viewport;
        BallInputListener _input;
        SceneTimer _updateTimer;
        Ball _creatingBall;
        bool _isCreatingBall;

        void OnRender();
        void OnUpdate(Events::EventBoy e);
        void OnInput(const ALLEGRO_EVENT& event);

        void UpdateBallPosition(Ball& b, const Util::Vector2& viewSize);

    public:
        BallScene(Rendering::Viewport viewport);

        void ConnectEvents(Events::EventBoy e);
};


#endif
