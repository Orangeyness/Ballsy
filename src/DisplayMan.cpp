#include "DisplayMan.h"

#include "Util/TracedException.h"
#include "Util/Loggers/AndroidLogger.h"

#include <string>
#include <math.h>

using namespace Events;
using namespace std::placeholders;

DisplayMan::DisplayMan(int width, int height)
{
    if (!al_is_system_installed())
        throw TracedException("Creating Display Before al_init");

    _display = al_create_display(width, height);

    if (_display == nullptr)
        throw TracedException("Bad Display");

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
    Util::Loggers::AndroidLogger::Log("Ballsy", "DisplayMan::OnDisplayOrientation");

    SetTransformForOrientation(event.display.orientation);
}

void DisplayMan::OnDisplayResize(const ALLEGRO_EVENT& event, Events::EventBoy boy)
{
    Util::Loggers::AndroidLogger::Log("Ballsy", "DisplayMan::OnDisplayResize");
    Util::Loggers::AndroidLogger::Log("Ballsy", std::to_string(event.display.width));
    Util::Loggers::AndroidLogger::Log("Ballsy", std::to_string(event.display.height));

    al_acknowledge_resize(_display);

    SetTransformForOrientation(al_get_display_orientation(_display));
}

void DisplayMan::SetTransformForOrientation(int orientation)
{
    ALLEGRO_TRANSFORM t;
    al_identity_transform(&t);

    int width = al_get_display_width(_display);
    int height = al_get_display_height(_display);

    switch(orientation)
    {
        case ALLEGRO_DISPLAY_ORIENTATION_0_DEGREES:
            Util::Loggers::AndroidLogger::Log("Ballsy", "0");
            break;
        case ALLEGRO_DISPLAY_ORIENTATION_90_DEGREES:
            Util::Loggers::AndroidLogger::Log("Ballsy", "90");
            al_rotate_transform(&t, M_PI/2);
            al_translate_transform(&t, width, 0);
            break;
        case ALLEGRO_DISPLAY_ORIENTATION_180_DEGREES:
            Util::Loggers::AndroidLogger::Log("Ballsy", "180");
            break;
        case ALLEGRO_DISPLAY_ORIENTATION_270_DEGREES:
            Util::Loggers::AndroidLogger::Log("Ballsy", "270");
            al_rotate_transform(&t, -M_PI/2);
            al_translate_transform(&t, 0, height);
            break;
    }
    al_use_transform(&t);
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
