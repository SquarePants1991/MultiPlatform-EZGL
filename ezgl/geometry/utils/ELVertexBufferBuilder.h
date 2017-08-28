//
// Created by wang yang on 2017/8/24.
//

#ifndef EZGL_ELBASEVERTEXBUFFERBUILDER_H
#define EZGL_ELBASEVERTEXBUFFERBUILDER_H

#import "platform/ELPlatform.h"

class ELVertexBufferBuilder {
public:
    // 支持基本的position+normal+uv模型
    static ELVertexBufferPtr buildBaseVertexBuffer(ELFloat *data, ELInt dataLength);
};


#endif //EZGL_ELBASEVERTEXBUFFERBUILDER_H
