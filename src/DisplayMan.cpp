#include "DisplayMan.h"

#include "Util/TracedException.h"

#include <string>
#include <math.h>

using namespace Events;
using namespace std::placeholders;

DisplayMan::DisplayMan(const Vector2& size)
    :   _size(size),
        _portraitSize(size),
        _lastChangeTime(0)
{
    if (!al_is_system_installed())
        throw TracedException("Creating Display Before al_init");

    _display = al_create_display(_size.X, _size.Y);

    if (_display == nullptr)
        throw TracedException("Bad Display");

    SetTransformForOrientation(al_get_display_orientation(_display));
}

DisplayMan::~DisplayMan()
{
    al_destroy_display(_display);
}

void DisplayMan::OnHaltDrawing(Events::EventBoy e)
{
    al_acknowledge_drawing_halt(_display);

    OnSwitchOut(e);
}

void DisplayMan::OnResumeDrawing(Events::EventBoy e)
{
    al_acknowledge_drawing_resume(_display);

    OnSwitchIn(e);
}

void DisplayMan::OnSwitchOut(Events::EventBoy e)
{
    e   .Talk(EVENT_SCENE_PAUSE);
    e   .Talk(EVENT_RENDER_NOT_ALLOWED);
}

void DisplayMan::OnSwitchIn(Events::EventBoy e)
{
    e   .Talk(EVENT_SCENE_RESUME);
    e   .Talk(EVENT_RENDER_ALLOWED);
}

void DisplayMan::OnDisplayOrientation(const ALLEGRO_EVENT& event, Events::EventBoy boy)
{
    SetTransformForOrientation(event.display.orientation);
}

void DisplayMan::OnDisplayResize(const ALLEGRO_EVENT& event, Events::EventBoy boy)
{
    al_acknowledge_resize(_display);

    _size.X = event.display.width;
    _size.Y = event.display.height;

    int orientation = al_get_display_orientation(_display);

    if (orientation == ALLEGRO_DISPLAY_ORIENTATION_0_DEGREES || 
        orientation == ALLEGRO_DISPLAY_ORIENTATION_180_DEGREES)
    {
        _portraitSize = _size;
    }
    else
    {
        _portraitSize.X = _size.Y;
        _portraitSize.Y = _size.X;
    }

    SetTransformForOrientation(orientation);
}

void DisplayMan::SetTransformForOrientation(int orientation)
{
    _orientationRotation = 0;

    switch(orientation)
    {
        case ALLEGRO_DISPLAY_ORIENTATION_0_DEGREES:
            break;
        case ALLEGRO_DISPLAY_ORIENTATION_90_DEGREES:
            _orientationRotation = M_PI/2;
            break;
        case ALLEGRO_DISPLAY_ORIENTATION_180_DEGREES:
            break;
        case ALLEGRO_DISPLAY_ORIENTATION_270_DEGREES:
            _orientationRotation = -M_PI/2;
            break;
    }

    _lastChangeTime = al_get_time();
}

const Vector2& DisplayMan::PortraitSize() const
{
    return _portraitSize;
}

const Vector2& DisplayMan::Size() const
{
    return _size;
}

float DisplayMan::OrientationRotation() const
{
    return _orientationRotation;
}

double DisplayMan::LastChangeTime() const
{
    return _lastChangeTime;
}

void DisplayMan::ConnectEvents(Events::EventBoy e)
{
    e   .TalkFrom(al_get_display_event_source(_display));

    e   .Listen(ALLEGRO_EVENT_DISPLAY_HALT_DRAWING)
        .Do(std::bind(&DisplayMan::OnHaltDrawing, this, _2));

    e   .Listen(ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING)
        .Do(std::bind(&DisplayMan::OnResumeDrawing, this, _2));

    e   .Listen(ALLEGRO_EVENT_DISPLAY_SWITCH_IN)
        .Do(std::bind(&DisplayMan::OnSwitchIn, this, _2));

    e   .Listen(ALLEGRO_EVENT_DISPLAY_SWITCH_OUT)
        .Do(std::bind(&DisplayMan::OnSwitchOut, this, _2));

    e   .Listen(ALLEGRO_EVENT_DISPLAY_RESIZE)
        .Do(std::bind(&DisplayMan::OnDisplayResize, this, _1, _2));

    e   .Listen(ALLEGRO_EVENT_DISPLAY_ORIENTATION)
        .Do(std::bind(&DisplayMan::OnDisplayOrientation, this, _1, _2));
}
