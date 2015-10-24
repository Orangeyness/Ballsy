#ifndef H_DISPLAY_MAN
#define H_DISPLAY_MAN

#include "Events/Events.h"

#include <allegro5/allegro.h>

class DisplayMan
{
    private:
        ALLEGRO_DISPLAY* _display;

        void SetTransformForOrientation(int orientation);

        void OnHaltDrawing(Events::EventBoy boy);
        void OnResumeDrawing(Events::EventBoy boy);
        void OnSwitchOut(Events::EventBoy boy);
        void OnSwitchIn(Events::EventBoy boy);
        void OnDisplayOrientation(const ALLEGRO_EVENT& event, Events::EventBoy boy);
        void OnDisplayResize(const ALLEGRO_EVENT& event, Events::EventBoy boy);

    public:
        DisplayMan(int width, int height);
        ~DisplayMan();

        void ConnectEvents(Events::EventBoy boy);
};


#endif
