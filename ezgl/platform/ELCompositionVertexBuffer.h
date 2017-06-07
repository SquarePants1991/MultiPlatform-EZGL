//
// Created by wangyang on 2017/6/7.
//

#ifndef EZGL_ELCOMPOSEDVERTEXBUFFER_H
#define EZGL_ELCOMPOSEDVERTEXBUFFER_H

#include "ELCppBase.h"
#include "ELCrossPlatformObject.h"
#include "ELVertexBuffer.h"
#include <cassert>

classDefExt(ELCompositionVertexBuffer, public ELCrossPlatformObject)

public:
    std::vector<ELVertexBufferPtr> buffers;
    ELCompositionVertexBufferPtr init() {
        return self;
    }

    void appendVertexBuffer(ELVertexBufferPtr vertexBuffer) {
        buffers.push_back(vertexBuffer);
    }

    ELInt vertexCount() {
        ELInt vertexCount = 0;
        // TODO: 考虑只有Debug时检测一致性
        for (auto iter = buffers.begin(); iter != buffers.end(); ++iter) {
            ELVertexBufferPtr subBuffer = *iter;
            // 所有子buffer的顶点数必须一致
            assert (vertexCount == 0 || vertexCount == subBuffer->vertexCount());
            vertexCount = subBuffer->vertexCount();
        }
        return vertexCount;
    }

defEnd


#endif //EZGL_ELCOMPOSEDVERTEXBUFFER_H
