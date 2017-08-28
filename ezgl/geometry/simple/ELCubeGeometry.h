//
// Created by wang yang on 2017/8/23.
//

#ifndef EZGL_CUBEGEOMETRY_H
#define EZGL_CUBEGEOMETRY_H

#include "../../platform/ELPlatform.h"
#include "../../platform/types/EZGLTypes.h"
#include "../ELGeometry.h"


classDefExt(ELCubeGeometry, public ELGeometry)
public:
    ELCubeGeometryPtr init(ELVector3 size);
    virtual void buildVertexBuffer();

public:
    ELVector3 size;

defEnd


#endif //EZGL_CUBEGEOMETRY_H
