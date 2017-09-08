//
// Created by wang yang on 2017/9/8.
//

#ifndef EZGL_ELCYLINDERGEOMETRY_H
#define EZGL_ELCYLINDERGEOMETRY_H

#include "../../platform/ELPlatform.h"
#include "../../platform/types/EZGLTypes.h"
#include "../ELGeometry.h"

classDefExt(ELCylinderGeometry, public ELGeometry)
public:
    ELCylinderGeometryPtr init(ELFloat radius, ELFloat height, ELFloat sides, ELFloat heightSegments);
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

#endif //EZGL_ELCYLINDER_H
