#ifndef H_RENDERING_VIEWPORT
#define H_RENDERING_VIEWPORT

#include "DisplayMan.h"
#include "Util/Vector2.h"

#include <allegro5/allegro.h>

using Util::Vector2;

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
            Vector2 _anchorOrigin;
            ALLEGRO_TRANSFORM _previous;

        public:
            Viewport(const DisplayMan& display, Vector2 internalSize, Anchor x, Anchor y);

            void SetTransform();
            void UnsetTransform();
            const Vector2& Size() const;
    };
}

#endif
