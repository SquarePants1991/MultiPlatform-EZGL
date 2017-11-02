//
// Created by wang yang on 2017/11/2.
//

#include "ELTerrain.h"
#include "../utils/ELVertexBufferBuilder.h"

ELTerrainPtr ELTerrain::init(std::string heightMapPath, ELVector2 terrainSize, ELFloat terrainHeight) {
    baseSetup();
    selv->heightMapPath = heightMapPath;
    selv->terrainSize = terrainSize;
    selv->terrainHeight = terrainHeight;
    return selv;
}

void ELTerrain::buildVertexBuffer() {
    _vertexBuffers.clear();
    ELTexturePtr heightMap = ELTexture::alloc()->init(selv->heightMapPath, ELTextureStoreTypeCPU);
    unsigned char * buffer = heightMap->imageData;
    selv->heightMapSize = ELVector2Make(heightMap->width, heightMap->height);
    size_t bytesPerPixel = 4;
    size_t bytesPerRow = bytesPerPixel * heightMap->width;

    for (int row = 0;row < terrainSize.y - 1; ++row) {
        ELVertexBufferPtr vertexBuffer = ELVertexBufferBuilder::buildBaseVertexBuffer(NULL,0);
        for (int col = 0;col <= terrainSize.x; ++col) {
            ELVector3 position1 = vertexPosition(col, row, buffer, bytesPerRow, bytesPerPixel);
            ELVector3 normal1 = vertexNormal(position1, col, row, buffer, bytesPerRow, bytesPerPixel);
            ELFloat vertex1[] = {
                    position1.x, position1.y, position1.z, normal1.x, normal1.y, normal1.z,col / (ELFloat)terrainSize.x * 2, row / (ELFloat)terrainSize.y * 2
            };
            vertexBuffer->append(vertex1, sizeof(vertex1));

            ELVector3 position2 = vertexPosition(col, row + 1, buffer, bytesPerRow, bytesPerPixel);
            ELVector3 normal2 = vertexNormal(position2, col, row + 1, buffer, bytesPerRow, bytesPerPixel);
            ELFloat vertex2[] = {
                    position2.x, position2.y, position2.z, normal2.x, normal2.y, normal2.z, col / (ELFloat)terrainSize.x * 2, (row + 1) / (ELFloat)terrainSize.y * 2
            };
            vertexBuffer->append(vertex2, sizeof(vertex2));
        }
        vertexBuffer->flushBuffer();
        _vertexBuffers.push_back(vertexBuffer);
    }
}

ELPrimitivesType ELTerrain::primitivesTypeForVertexBuffer(ELInt index) {
    return ELPrimitivesTypeTriangleStrip;
}


ELVector3 ELTerrain::vertexPosition(int col, int row, unsigned char * buffer, size_t bytesPerRow, size_t bytesPerPixel) {
    long long offset = (int)(row / terrainSize.y * heightMapSize.y) * bytesPerRow + (int)(col / terrainSize.x * heightMapSize.x) * bytesPerPixel;
    unsigned char r = buffer[offset];
    ELFloat x = col;
    ELFloat y = r / 255.0 * terrainHeight;
    ELFloat z = row;
    return ELVector3Make(x, y, z);
}

ELVector3 ELTerrain::vertexNormal(ELVector3 position, int col, int row, unsigned char * buffer, size_t bytesPerRow, size_t bytesPerPixel) {
    ELVector3 sides[4]; // 最多四条共享边
    int sideCount = 0;
// 统计顶点有几条共享边，从而计算法线
    if (col >= 1) {
//左边有共享边
        ELVector3 leftPosition = vertexPosition(col - 1, row, buffer, bytesPerRow, bytesPerPixel);
        ELVector3 vectorLeft = ELVector3Subtract(leftPosition, position);
        sides[sideCount] = vectorLeft;
        sideCount++;
    }
    if (row >= 1) {
//前面有共享边
        ELVector3 frontPosition = vertexPosition(col, row - 1, buffer, bytesPerRow, bytesPerPixel);
        ELVector3 vectorFront = ELVector3Subtract(frontPosition, position);
        sides[sideCount] = vectorFront;
        sideCount++;
    }
    if (col < terrainSize.x - 1) {
//右边有共享边
        ELVector3 rightPosition = vertexPosition(col + 1, row, buffer, bytesPerRow, bytesPerPixel);
        ELVector3 vectorRight = ELVector3Subtract(rightPosition, position);
        sides[sideCount] = vectorRight;
        sideCount++;
    }
    if (row < terrainSize.y - 1) {
//后面有共享边
        ELVector3 backPosition = vertexPosition(col, row + 1, buffer, bytesPerRow, bytesPerPixel);
        ELVector3 vectorBack = ELVector3Subtract(backPosition, position);
        sides[sideCount] = vectorBack;
        sideCount++;
    }

    ELVector3 normal = ELVector3Make(0, 0, 0);
    for (int i = 0; i < sideCount; ++i) {
        ELVector3 vec = sides[i];
        if (i == sideCount - 1 && i != 3) {
            continue;
        }
        ELVector3 vec2 = i == sideCount - 1 ? sides[0] : sides[i + 1];
        normal = ELVector3Add(normal, ELVector3CrossProduct(vec2, vec));
    }
    return ELVector3Normalize(normal);
}
