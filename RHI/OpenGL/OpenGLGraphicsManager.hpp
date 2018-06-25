#pragma once
#include "GraphicsManager.hpp"

namespace My {
    class OpenGLGraphicsManager : public GraphicsManager
    {
    public:
        virtual int Init();
        virtual void Destroy();

        virtual void Update();
    private:
    };
}

