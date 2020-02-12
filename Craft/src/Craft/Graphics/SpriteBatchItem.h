#pragma once
#include <Craft/Math/Vectors.h>

namespace Craft { namespace Graphics { 

    struct VertexPositionColorTexture {
        v3 Position;
        v4 Color;
        v2 TextureCoord;
    };

    class SpriteBatchItem {
    private:
        VertexPositionColorTexture m_VertexTL;
        VertexPositionColorTexture m_VertexTR;
        VertexPositionColorTexture m_VertexBL;
        VertexPositionColorTexture m_VertexBR;

        void Set(f32 x, f32 y, f32 w, f32 h, v2 textureBL, v2 textureTR, f32 depth)
        {

        }
    };

}}