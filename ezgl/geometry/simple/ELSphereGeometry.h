//
// Created by wang yang on 2017/8/28.
//

#ifndef EZGL_SPHEREGEOMETRY_H
#define EZGL_SPHEREGEOMETRY_H

#include "../../platform/ELPlatform.h"
#include "../../platform/types/EZGLTypes.h"
#include "../ELGeometry.h"

classDefExt(ELSphereGeometry, public ELGeometry)
public:
    ELSphereGeometryPtr init(ELFloat radius, ELFloat ring, ELFloat segments);
    virtual void buildVertexBuffer();
    void genHalfSphere(ELInt step, ELVertexBufferPtr vertexBuffer);
public:
    ELFloat radius;
    ELFloat ring;
    ELFloat segments;

defEnd


#endif //EZGL_SPHEREGEOMETRY_H
