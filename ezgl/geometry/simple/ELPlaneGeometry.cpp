//
// Created by wang yang on 2017/10/10.
//

#include "ELPlaneGeometry.h"
#include "../utils/ELVertexBufferBuilder.h"

ELPlaneGeometryPtr ELPlaneGeometry::init(ELVector2 size) {
    baseSetup();
    this->size = size;
    this->uvScale = ELVector2Make(1, 1);
    return selv;
}

ELPlaneGeometryPtr ELPlaneGeometry::init(ELVector2 size, ELVector2 uvScale) {
    baseSetup();
    this->size = size;
    this->uvScale = uvScale;
    return selv;
}

void ELPlaneGeometry::buildVertexBuffer() {
    _vertexBuffers.clear();
    ELVertexBufferPtr vertexBuffer = ELVertexBufferBuilder::buildBaseVertexBuffer(NULL, 0);
    for (int row = 0; row < size.x; ++ row) {
        for (int col = 0; col < size.y; ++col) {
            ELFloat quadData[] = {
                    (ELFloat)(row + 1.0f) - 0.5f * size.x, 0.0f,     (ELFloat)col     - 0.5f * size.y,       0, 1, 0, (ELFloat)(row + 1.0f) / size.x * uvScale.x, 1.0f -  (ELFloat)(col        ) / size.y * uvScale.y,
                    (ELFloat)(row       ) - 0.5f * size.x, 0.0f,     (ELFloat)col     - 0.5f * size.y,       0, 1, 0, (ELFloat)(row       ) / size.x * uvScale.x, 1.0f -  (ELFloat)(col        ) / size.y * uvScale.y,
                    (ELFloat)(row       ) - 0.5f * size.x, 0.0f,     (ELFloat)col + 1 - 0.5f * size.y,       0, 1, 0, (ELFloat)(row       ) / size.x * uvScale.x, 1.0f -  (ELFloat)(col + 1.0f ) / size.y * uvScale.y,
                    (ELFloat)(row       ) - 0.5f * size.x, 0.0f,     (ELFloat)col + 1 - 0.5f * size.y,       0, 1, 0, (ELFloat)(row       ) / size.x * uvScale.x, 1.0f -  (ELFloat)(col + 1.0f ) / size.y * uvScale.y,
                    (ELFloat)(row + 1.0f) - 0.5f * size.x, 0.0f,     (ELFloat)col + 1 - 0.5f * size.y,       0, 1, 0, (ELFloat)(row + 1.0f) / size.x * uvScale.x, 1.0f -  (ELFloat)(col + 1.0f ) / size.y * uvScale.y,
                    (ELFloat)(row + 1.0f) - 0.5f * size.x, 0.0f,     (ELFloat)col     - 0.5f * size.y,       0, 1, 0, (ELFloat)(row + 1.0f) / size.x * uvScale.x, 1.0f -  (ELFloat)(col        ) / size.y * uvScale.y,
            };
            vertexBuffer->append(quadData, sizeof(quadData));
        }
    }
    vertexBuffer->flushBuffer();
    _vertexBuffers.push_back(vertexBuffer);
}