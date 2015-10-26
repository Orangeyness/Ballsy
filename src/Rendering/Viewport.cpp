#include "Rendering/Viewport.h"
#include "Util/Loggers/AndroidLogger.h"

#include <cmath>

using Util::Vector2;
using Util::Rect;

namespace Rendering 
{
    Viewport::Viewport(const DisplayMan& display, Vector2 internalSize, Anchor x, Anchor y)
        :   _display(display),
            _size(internalSize),
            _cacheTime(0),
            _xOrigin(x),
            _yOrigin(y)
    {
    }

    void Viewport::GenerateTransform()
    {
        al_identity_transform(&_transform);

        Vector2 viewCenter = _size / 2;
        al_translate_transform(&_transform, -viewCenter.X, -viewCenter.Y);

        float rotation = _display.OrientationRotation();
        al_rotate_transform(&_transform, rotation);
        
        auto displaySize = _display.PortraitSize();
        float scaleFactor = (displaySize / _size).Min();
        al_scale_transform(&_transform, scaleFactor, scaleFactor);

        Vector2 translationForScreenPos;
        switch(_xOrigin)
        {
            case LEFT:
                translationForScreenPos.X = viewCenter.X * scaleFactor;
                break;

            case CENTER:
                translationForScreenPos.X = displaySize.X / 2;
                break;

            case RIGHT:
                translationForScreenPos.X = displaySize.X - viewCenter.X * scaleFactor;
                break;
        }

        switch(_yOrigin)
        {
            case TOP:
                translationForScreenPos.Y = viewCenter.Y * scaleFactor;
                break;

            case CENTER:
                translationForScreenPos.Y = displaySize.Y / 2;
                break;

            case BOTTOM:
                translationForScreenPos.Y = displaySize.Y - viewCenter.Y * scaleFactor;
                break;
        }

        if (abs(rotation) > 0.1)
            translationForScreenPos =~ translationForScreenPos;

        al_translate_transform(&_transform, translationForScreenPos.X, translationForScreenPos.Y);

        al_copy_transform(&_invertedTransform, &_transform);
        al_invert_transform(&_invertedTransform);

        float x1 = 0;
        float y1 = 0;
        float x2 = _size.X;
        float y2 = _size.Y;
        al_transform_coordinates(&_transform, &x1, &y1);
        al_transform_coordinates(&_transform, &x2, &y2);

        _clipRect = Rect(x1, y1, x2, y2);

        _cacheTime = al_get_time();
    }

    void Viewport::SetTransform() 
    {
        al_copy_transform(&_previous, al_get_current_transform());

        if (_cacheTime < _display.LastChangeTime())
            GenerateTransform();

        al_set_clipping_rectangle(
                _clipRect.Left(), 
                _clipRect.Top(), 
                _clipRect.Width(), 
                _clipRect.Height()
            );

        al_use_transform(&_transform);
    }

    void Viewport::UnsetTransform()
    {
        al_use_transform(&_previous);
        al_reset_clipping_rectangle();
    }

    const Vector2& Viewport::Size() const
    {
        return _size;
    }

    bool Viewport::Contains(Vector2 position) const
    {
        return _clipRect.Contains(position);
    }

    Vector2 Viewport::ToViewCoordinates(Vector2 position) const
    {
        al_transform_coordinates(&_invertedTransform, &position.X, &position.Y);

        return position;
    }
}
