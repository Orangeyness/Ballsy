#ifndef H_DISPLAY_MAN
#define H_DISPLAY_MAN

#include "Events/Events.h"
#include "Util/Vector2.h"
#include <allegro5/allegro.h>

using Util::Vector2;

class DisplayMan
{
    private:
        ALLEGRO_DISPLAY* _display;
        Vector2 _size;
        Vector2 _portraitSize;
        Vector2 _orientationTranslation;
        float _orientationRotation;

        void SetTransformForOrientation(int orientation);

        void OnHaltDrawing(Events::EventBoy boy);
        void OnResumeDrawing(Events::EventBoy boy);
        void OnSwitchOut(Events::EventBoy boy);
        void OnSwitchIn(Events::EventBoy boy);
        void OnDisplayOrientation(const ALLEGRO_EVENT& event, Events::EventBoy boy);
        void OnDisplayResize(const ALLEGRO_EVENT& event, Events::EventBoy boy);

    public:
        DisplayMan(const Vector2& size);
        ~DisplayMan();

        const Vector2& PortraitSize() const;
        const Vector2& Size() const;
        const Vector2& OrientationTranslation() const;
        float OrientationRotation() const;

        void ConnectEvents(Events::EventBoy boy);
};


#endif
