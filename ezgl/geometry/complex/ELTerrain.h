//
// Created by wang yang on 2017/11/2.
//

#ifndef EZGL_TERRAIN_H
#define EZGL_TERRAIN_H

#include "../../platform/ELPlatform.h"
#include "../../platform/types/EZGLTypes.h"
#include "../ELGeometry.h"

classDefExt(ELTerrain, public ELGeometry)
public:
    ELTerrainPtr init(std::string heightMapPath, ELVector2 terrainSize, ELFloat terrainHeight);
    virtual void buildVertexBuffer();
    virtual ELPrimitivesType primitivesTypeForVertexBuffer(ELInt index);
public:
    std::string heightMapPath;
    ELVector2 terrainSize;
    ELFloat  terrainHeight;
private:
    ELVector2 heightMapSize;
    ELVector3 vertexPosition(int col, int row, unsigned char * buffer, size_t bytesPerRow, size_t bytesPerPixel);
    ELVector3 vertexNormal(ELVector3 position, int col, int row, unsigned char * buffer, size_t bytesPerRow, size_t bytesPerPixel);
defEnd


#endif //EZGL_TERRAIN_H
