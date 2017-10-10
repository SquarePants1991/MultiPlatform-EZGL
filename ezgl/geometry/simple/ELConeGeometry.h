//
// Created by wang yang on 2017/10/10.
//

#ifndef EZGL_ELCONEGEOMETRY_H
#define EZGL_ELCONEGEOMETRY_H

#include "../../platform/ELPlatform.h"
#include "../../platform/types/EZGLTypes.h"
#include "../ELGeometry.h"

classDefExt(ELConeGeometry, public ELGeometry)
public:
    ELConeGeometryPtr init(ELFloat radius, ELFloat height, ELFloat sides, ELFloat heightSegments);
    virtual void buildVertexBuffer();
public:
    ELFloat radius;
    ELFloat height;
    ELFloat sides;
    ELFloat heightSegments;

private:
    void genCircle(ELVector3 centerPosition, ELBool isTop, ELVertexBufferPtr vertexBuffer);
    void genSide(ELVertexBufferPtr vertexBuffer);
defEnd

#endif //EZGL_ELCONEGEOMETRY_H
