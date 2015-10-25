#include "Rendering/Viewport.h"
#include "Util/Loggers/AndroidLogger.h"

using Util::Vector2;

namespace Rendering 
{
    Viewport::Viewport(const DisplayMan& display, Vector2 internalSize, Anchor x, Anchor y)
        :   _display(display),
            _size(internalSize),
            _anchorOrigin((float)x / 2, (float)y /2)
    {
    }

    void Viewport::SetTransform() 
    {
        al_copy_transform(&_previous, al_get_current_transform());

        ALLEGRO_TRANSFORM t;
        al_identity_transform(&t);

        const Vector2& displaySize = _display.PortraitSize();

        float rotation = _display.OrientationRotation();
        al_rotate_transform(&t, rotation);

        const Vector2& translation = _display.OrientationTranslation() * ~_size;
        al_translate_transform(&t, translation.X, translation.Y);

        float scaleFactor = (displaySize / _size).Min();
        al_scale_transform(&t, scaleFactor, scaleFactor);

        /*
        Vector2 viewOrigin = _anchorOrigin * _size;
        Vector2 screenOrigin = _anchorOrigin * displaySize;

        Util::Loggers::AndroidLogger::Log("Ballsy anchor", _anchorOrigin.ToString());   
        Util::Loggers::AndroidLogger::Log("Ballsy view origin", viewOrigin.ToString());   
        Util::Loggers::AndroidLogger::Log("Ballsy screen origin", screenOrigin.ToString());   

        al_transform_coordinates(&t, &viewOrigin.X, &viewOrigin.Y);

        Vector2 offset = screenOrigin - viewOrigin;

        al_translate_transform(&t, offset.X, offset.Y);*/

        al_use_transform(&t);
    }

    void Viewport::UnsetTransform()
    {
        al_use_transform(&_previous);
    }

    const Vector2& Viewport::Size() const
    {
        return _size;
    }
}
