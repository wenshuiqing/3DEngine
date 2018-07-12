#pragma once
#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "GraphicsManager.hpp"
#include <GLES/gl.h>
#include "geommath.hpp"
#include "SceneObject.hpp"

namespace My {
    class OpenGLESGraphicsManager : public GraphicsManager
    {
    public:
        virtual int Init();
        virtual void Destroy();

        virtual void Clear();

        virtual void Draw();
    };
}

