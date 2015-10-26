#ifndef H_RENDERING_VIEWPORT
#define H_RENDERING_VIEWPORT

#include "DisplayMan.h"
#include "Util/Vector2.h"
#include "Util/Rect.h"

#include <allegro5/allegro.h>

using Util::Vector2;
using Util::Rect;

namespace Rendering
{
    enum Anchor
    {
        MIN = 0,
        LEFT = 0,
        TOP = 0,

        CENTER = 1,

        MAX = 2,
        RIGHT = 2,
        BOTTOM = 2
    };

    class Viewport
    {
        private:
            const DisplayMan& _display;
            Vector2 _size;
            ALLEGRO_TRANSFORM _previous;
            ALLEGRO_TRANSFORM _transform;
            ALLEGRO_TRANSFORM _invertedTransform;
            Rect _clipRect;
            double _cacheTime;
            Anchor _xOrigin;
            Anchor _yOrigin;

        protected:
            void GenerateTransform();

        public:
            Viewport(const DisplayMan& display, Vector2 internalSize, Anchor x, Anchor y);

            void SetTransform();
            void UnsetTransform();

            const Vector2& Size() const;
            bool Contains(Vector2 position) const;
            Vector2 ToViewCoordinates(Vector2 position) const;
    };
}

#endif
