#ifndef H_SCENE_TIMER
#define H_SCENE_TIMER

#include "Events/Events.h"

#include <allegro5/allegro.h>

class SceneTimer
{
    private:
        ALLEGRO_TIMER* _timer;
        Events::EventCallBack _updateCallBack;

        void OnPause();
        void OnResume();

    public:
        SceneTimer(int fps, Events::EventCallBack updateCallBack);
        ~SceneTimer();

        void ConnectEvents(Events::EventBoy e);
        void DisconnectEvents(Events::EventBoy e);
};


#endif
