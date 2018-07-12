#pragma once
#include "WindowsApplication.hpp"

namespace My {
    class OpenGLApplication : public WindowsApplication {
    public:
        OpenGLApplication(GfxConfiguration& config)
            : WindowsApplication(config) {};

        virtual int Init();
        virtual void Destroy();
        virtual void Update();

    private:
        HDC   m_hDC;
        HGLRC m_RenderContext;
    };
}
