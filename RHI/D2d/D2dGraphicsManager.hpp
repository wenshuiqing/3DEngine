#pragma once
#include <d2d1.h>
#include "GraphicsManager.hpp"

namespace My {
    class D2dGraphicsManager : public GraphicsManager
    {
    public:
        virtual int Init();
        virtual void Destroy();

        virtual void Update();

    protected:
        HRESULT CreateGraphicsResources();
    protected:
        ID2D1Factory            *m_pFactory = nullptr;
        ID2D1HwndRenderTarget   *m_pRenderTarget = nullptr;
    };
}

