#include "BallInputListener.h"

#include "Events/UserEvents/BallCreation.h"

using namespace Events;
using namespace Events::UserEvents;
using namespace std::placeholders;

BallInputListener::BallInputListener(const Rendering::Viewport& viewport)
    :   _viewport(viewport),
        _inputActive(false)
{
}

void BallInputListener::ConnectEvents(EventBoy& e)
{
    EventCallBack onDown = std::bind(&BallInputListener::OnInput, this, _1, _2, BallCreationState::STARTED);
    EventCallBack onMove = std::bind(&BallInputListener::OnInput, this, _1, _2, BallCreationState::MOVED);
    EventCallBack onUp   = std::bind(&BallInputListener::OnInput, this, _1, _2, BallCreationState::COMPLETED);

    e   .Listen(ALLEGRO_EVENT_TOUCH_BEGIN).Do(onDown);
    e   .Listen(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN).Do(onDown);

    e   .Listen(ALLEGRO_EVENT_TOUCH_MOVE).Do(onMove);
    e   .Listen(ALLEGRO_EVENT_MOUSE_AXES).Do(onMove);

    e   .Listen(ALLEGRO_EVENT_TOUCH_END).Do(onUp); 
    e   .Listen(ALLEGRO_EVENT_TOUCH_CANCEL).Do(onUp);
    e   .Listen(ALLEGRO_EVENT_MOUSE_BUTTON_UP).Do(onUp);
}

void BallInputListener::DisconnectEvents(EventBoy& e)
{
    e   .Listen(ALLEGRO_EVENT_TOUCH_BEGIN).Stop();
    e   .Listen(ALLEGRO_EVENT_TOUCH_MOVE).Stop();
    e   .Listen(ALLEGRO_EVENT_TOUCH_END).Stop();
    e   .Listen(ALLEGRO_EVENT_TOUCH_CANCEL).Stop();
    e   .Listen(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN).Stop();
    e   .Listen(ALLEGRO_EVENT_MOUSE_AXES).Stop();
    e   .Listen(ALLEGRO_EVENT_MOUSE_BUTTON_UP).Stop();
}

void BallInputListener::OnInput(const ALLEGRO_EVENT& event, EventBoy e, BallCreationState state)
{
    Vector2 position;

    if (state == STARTED)
        _inputActive = true;

    if (!_inputActive)
        return;

    if (state == COMPLETED)
        _inputActive = false;

    if (IsTouchEvent(event))
    {
        if (!event.touch.primary)
            return;

        position.X = event.touch.x;
        position.Y = event.touch.y;
    }
    else
    {
        position.X = event.mouse.x;
        position.Y = event.mouse.y;
    }

    if (!_viewport.Contains(position))
    {
        _inputActive = false;

        if (BallCreationState::STARTED)
            return;

        state = BallCreationState::COMPLETED;
    }

    position = _viewport.ToViewCoordinates(position);

    e.Talk(BallCreation(state, position));
}

bool BallInputListener::IsTouchEvent(const ALLEGRO_EVENT& event)
{
    return  event.type == ALLEGRO_EVENT_TOUCH_BEGIN ||
            event.type == ALLEGRO_EVENT_TOUCH_MOVE  ||
            event.type == ALLEGRO_EVENT_TOUCH_END   ||
            event.type == ALLEGRO_EVENT_TOUCH_CANCEL;
}
