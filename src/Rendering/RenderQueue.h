#ifndef H_RENDERING_RENDER_QUEUE
#define H_RENDERING_RENDER_QUEUE

#include <set>
#include <functional>
#include <allegro5/allegro.h>

namespace Events
{
    class EventBoy;
}

namespace Rendering
{
    typedef void* RenderHandle;
    typedef std::function<void(void)> RenderCallBack;

    class RenderEntry
    {
        public:
            RenderEntry(RenderHandle handle, RenderCallBack callBack, int depth);
            RenderHandle Handle;
            RenderCallBack CallBack;
            int Depth;
    };

    class RenderEntryOrderer
    {
        public:
            bool operator() (const RenderEntry& left, const RenderEntry& right) const;
    };

    class RenderQueue
    {
        private:
            std::multiset<RenderEntry, RenderEntryOrderer> _renderers;
            bool _active;
            bool _dirty;

        protected:
            void OnAddRenderer(const ALLEGRO_EVENT& event);
            void OnRemoveRenderer(const ALLEGRO_EVENT& event);
            void OnDirty();
            void OnActiveChange(bool val);

        public:
            RenderQueue();

            bool NeedsRender();
            void Render();

            void ConnectEvents(Events::EventBoy& e);
            void DisconnectEvents(Events::EventBoy& e);
    };
}



#endif
