#pragma once
#include "ActorUID.h"

class DrawableObject;
class Renderer;


namespace ic {

    class RenderComponent {

        void removeChild();
        void addBackChild();
        void addFrontChild();
        void addDrawableObject();
        void move();
        void update(Renderer& renderer);

        std::vector<std::unique_ptr<DrawableObject>> drawables
        std::vector<std::unique_ptr<RenderComponent>> frontchildren;
        std::vector<std::unique_ptr<RenderComponent>> backchildren;
        ActorUID id;
    };
}