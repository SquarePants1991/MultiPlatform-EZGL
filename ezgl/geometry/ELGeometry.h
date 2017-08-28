//
// Created by wang yang on 2017/8/23.
//

#ifndef EZGL_ELGEOMETRY_H
#define EZGL_ELGEOMETRY_H

#include "../platform/ELPlatform.h"

classDef(ELGeometry)
public:
    void baseSetup() {
        needRefreshVertexBuffer = true;
    }

    void setNeedRefreshVertexBuffer() {
        needRefreshVertexBuffer = true;
    }

    std::vector<ELVertexBufferPtr> vertextBuffers() {
        if (needRefreshVertexBuffer) {
            buildVertexBuffer();
        }
        return _vertexBuffers;
    }

    ELPrimitivesType primitivesTypeForVertexBuffer(ELInt index) {
        return ELPrimitivesTypeTriangle;
    }

    // virtual methods
    virtual void buildVertexBuffer() {

    }

protected:
    std::vector<ELVertexBufferPtr> _vertexBuffers;

private:
    bool needRefreshVertexBuffer;

defEnd


#endif //EZGL_ELGEOMETRY_H
