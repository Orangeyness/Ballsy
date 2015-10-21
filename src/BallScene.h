#ifndef H_BALL_SCENE
#define H_BALL_SCENE

#include "EventLoop.h"

#include <allegro5/allegro.h>

struct Ball
{
    float x;
    float y;
    float xspeed;
    float yspeed;
    float radius;
};

class BallScene
{
    private:
        ALLEGRO_TIMER* _timer;
        Ball _balls[5];
        int _width;
        int _height;

        EventCallbackResult Render(const ALLEGRO_EVENT& event);
        EventCallbackResult Update(const ALLEGRO_EVENT& event);

    public:
        BallScene(int width, int height);
        ~BallScene();

        void SetEventLoop(EventLoopListenerAdder loop);
        ALLEGRO_EVENT_SOURCE* GetEventSource() const;
};


#endif
