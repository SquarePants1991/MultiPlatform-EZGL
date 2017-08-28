//
// Created by wang yang on 2017/8/23.
//

#include "ELCubeGeometry.h"
#include "../utils/ELVertexBufferBuilder.h"

ELCubeGeometryPtr ELCubeGeometry::init(ELVector3 size) {
    baseSetup();
    this->size = size;
    return selv;
}

void ELCubeGeometry::buildVertexBuffer() {
    ELFloat cubeData[] = {
            // X轴0.5处的平面
            0.5f * size.x,   -0.5f * size.y,   0.5f * size.z, 1,  0,  0, 0, 0,
            0.5f * size.x,   -0.5f * size.y,  -0.5f * size.z, 1,  0,  0, 0, 1,
            0.5f * size.x,   0.5f * size.y,   -0.5f * size.z, 1,  0,  0, 1, 1,
            0.5f * size.x,   0.5f * size.y,   -0.5f * size.z, 1,  0,  0, 1, 1,
            0.5f * size.x,   0.5f * size.y,    0.5f * size.z, 1,  0,  0, 1, 0,
            0.5f * size.x,   -0.5f * size.y,   0.5f * size.z, 1,  0,  0, 0, 0,
            // X轴-0.5处的平面
            -0.5f * size.x,  0.5f * size.y,   -0.5f * size.z, -1,  0,  0, 1, 1,
            -0.5f * size.x,  -0.5f * size.y,  -0.5f * size.z, -1,  0,  0, 0, 1,
            -0.5f * size.x,  -0.5f * size.y,   0.5f * size.z, -1,  0,  0, 0, 0,
            -0.5f * size.x,  -0.5f * size.y,   0.5f * size.z, -1,  0,  0, 0, 0,
            -0.5f * size.x,  0.5f * size.y,    0.5f * size.z, -1,  0,  0, 1, 0,
            -0.5f * size.x,  0.5f * size.y,   -0.5f * size.z, -1,  0,  0, 1, 1,


            0.5f * size.x,   0.5f * size.y,   -0.5f * size.z, 0,  1,  0, 1, 1,
            -0.5f * size.x,  0.5f * size.y,   -0.5f * size.z, 0,  1,  0, 0, 1,
            -0.5f * size.x,  0.5f * size.y,   0.5f * size.z, 0,  1,  0, 0, 0,
            -0.5f * size.x,  0.5f * size.y,   0.5f * size.z, 0,  1,  0, 0, 0,
            0.5f * size.x,   0.5f * size.y,   0.5f * size.z, 0,  1,  0, 1, 0,
            0.5f * size.x,   0.5f * size.y,   -0.5f * size.z, 0,  1,  0, 1, 1,

            -0.5f * size.x,  -0.5f * size.y,  0.5f * size.z, 0,  -1,  0, 0, 0,
            -0.5f * size.x,  -0.5f * size.y,  -0.5f * size.z, 0,  -1,  0, 0, 1,
            0.5f * size.x,   -0.5f * size.y,  -0.5f * size.z, 0,  -1,  0, 1, 1,
            0.5f * size.x,   -0.5f * size.y,  -0.5f * size.z, 0,  -1,  0, 1, 1,
            0.5f * size.x,   -0.5f * size.y,  0.5f * size.z, 0,  -1,  0, 1, 0,
            -0.5f * size.x,  -0.5f * size.y,  0.5f * size.z, 0,  -1,  0, 0, 0,

            -0.5f * size.x,   0.5f * size.y,  0.5f * size.z,   0,  0,  1, 0, 0,
            -0.5f * size.x,  -0.5f * size.y,  0.5f * size.z,  0,  0,  1, 0, 1,
            0.5f * size.x,   -0.5f * size.y,  0.5f * size.z,  0,  0,  1, 1, 1,
            0.5f * size.x,   -0.5f * size.y,  0.5f * size.z,   0,  0,  1, 1, 1,
            0.5f * size.x,   0.5f * size.y,   0.5f * size.z,    0,  0,  1, 1, 0,
            -0.5f * size.x,  0.5f * size.y,   0.5f * size.z,  0,  0,  1, 0, 0,

            0.5f * size.x,   -0.5f * size.y,  -0.5f * size.z,  0,  0,  -1, 1, 1,
            -0.5f * size.x,  -0.5f * size.y,  -0.5f * size.z,  0,  0,  -1, 0, 1,
            -0.5f * size.x,  0.5f * size.y,   -0.5f * size.z,   0,  0,  -1, 0, 0,
            -0.5f * size.x,  0.5f * size.y,   -0.5f * size.z,  0,  0,  -1, 0, 0,
            0.5f * size.x,   0.5f * size.y,   -0.5f * size.z,    0,  0,  -1, 1, 0,
            0.5f * size.x,   -0.5f * size.y,  -0.5f * size.z,   0,  0,  -1, 1, 1,
    };
    _vertexBuffers.clear();

    ELVertexBufferPtr vertexBuffer = ELVertexBufferBuilder::buildBaseVertexBuffer(cubeData, sizeof(cubeData) / sizeof(ELFloat));
    _vertexBuffers.push_back(vertexBuffer);
}