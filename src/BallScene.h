#ifndef H_BALL_SCENE
#define H_BALL_SCENE

#include "Events/EventLoop.h"

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
        ALLEGRO_EVENT _needRenderEvent;
        Ball _balls[5];
        int _width;
        int _height;

        void OnRender();
        void OnUpdate(EventQueueAccessor eQ);
        void OnPause();
        void OnResume();

    public:
        BallScene(int width, int height);
        ~BallScene();

        void SetupTalk(EventQueueAccessor eQ);
        void SetupListen(EventQueueAccessor eQ);
};


#endif
