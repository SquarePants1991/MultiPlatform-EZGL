//
// Created by wang yang on 2017/10/10.
//

#ifndef EZGL_ELPLANEGEOMETRY_H
#define EZGL_ELPLANEGEOMETRY_H


#include "../../platform/ELPlatform.h"
#include "../../platform/types/EZGLTypes.h"
#include "../ELGeometry.h"


classDefExt(ELPlaneGeometry, public ELGeometry)
public:
    ELPlaneGeometryPtr init(ELVector2 size);
    ELPlaneGeometryPtr init(ELVector2 size, ELVector2 uvScale);
    virtual void buildVertexBuffer();

public:
    ELVector2 size;
    ELVector2 uvScale;
defEnd

#endif //EZGL_ELPLANEGEOMETRY_H
