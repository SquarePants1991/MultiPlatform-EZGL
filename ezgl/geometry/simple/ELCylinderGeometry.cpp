//
// Created by wang yang on 2017/9/8.
//

#include "ELCylinderGeometry.h"
#include "../utils/ELVertexBufferBuilder.h"

ELCylinderGeometryPtr ELCylinderGeometry::init(ELFloat radius, ELFloat height, ELFloat sides, ELFloat heightSegments) {
    baseSetup();
    selv->radius = radius;
    selv->height = height;
    selv->sides = sides;
    selv->heightSegments = heightSegments;
    return selv;
}

void ELCylinderGeometry::buildVertexBuffer() {
    _vertexBuffers.clear();
    ELVertexBufferPtr vertexBuffer = ELVertexBufferBuilder::buildBaseVertexBuffer(NULL,0);
    genCircle(ELVector3Make(0, height / 2, 0), true, vertexBuffer);
    genCircle(ELVector3Make(0, -height / 2, 0), false, vertexBuffer);
    genSide(vertexBuffer);
    vertexBuffer->flushBuffer();
    _vertexBuffers.push_back(vertexBuffer);
}

void ELCylinderGeometry::genCircle(ELVector3 centerPosition, ELBool isTop, ELVertexBufferPtr vertexBuffer) {
    ELFloat startAngle = 0.0;
    ELFloat endAngle = 3.1415926 * 2.0;
    ELFloat step = (endAngle - startAngle) / sides;
    ELVector3 normal = ELVector3Make(0, 1, 0);
    if (!isTop) {
        step = -step;
        normal = ELVector3MultiplyScalar(normal, -1);
    }

    for (int side = 0; side < sides; ++side) {
        ELFloat angle = side * step;
        ELFloat nextAngle = (side + 1) * step;
        ELFloat x0 = centerPosition.x + cos(angle) * radius;
        ELFloat y0 = centerPosition.y;
        ELFloat z0 = centerPosition.z + sin(angle) * radius;
        ELFloat x1 = centerPosition.x + cos(nextAngle) * radius;
        ELFloat y1 = centerPosition.y;
        ELFloat z1 = centerPosition.z + sin(nextAngle) * radius;

        ELFloat triangles[] = {
            centerPosition.x, centerPosition.y, centerPosition.z, normal.x, normal.y, normal.z, 0.5f, 0.5f,
            x1, y1, z1, normal.x, normal.y, normal.z, (ELFloat)(x1 / radius + 1.0f) * 0.5f, (ELFloat)(z1 / radius + 1.0f) * 0.5f,
            x0, y0, z0, normal.x, normal.y, normal.z, (ELFloat)(x0 / radius + 1.0f) * 0.5f, (ELFloat)(z0 / radius + 1.0f) * 0.5f,
        };
        vertexBuffer->append(triangles, sizeof(triangles));
    }
}

void ELCylinderGeometry::genSide(ELVertexBufferPtr vertexBuffer) {
    ELFloat startAngle = 0.0;
    ELFloat endAngle = -3.1415926 * 2.0;
    ELFloat step = (endAngle - startAngle) / sides;
    ELFloat segmentHeight = height / heightSegments;
    for (int segment = 0; segment < heightSegments; ++segment) {
        for (int side = 0; side < sides; ++side) {
            ELFloat beginHeight = (segment + 1)* segmentHeight - height / 2;
            ELFloat endHeight = segment * segmentHeight - height / 2;
            ELFloat angle = side * step;
            ELFloat nextAngle = (side + 1) * step;
            ELVector3 leftTop = ELVector3Make(cos(angle) * radius, beginHeight, sin(angle) * radius);
            ELVector3 leftBottom = ELVector3Make(cos(angle) * radius, endHeight, sin(angle) * radius);
            ELVector3 normalLeft = ELVector3Normalize(ELVector3Make(cos(angle) * radius, 0, sin(angle) * radius));
            ELVector3 rightTop = ELVector3Make(cos(nextAngle) * radius, beginHeight, sin(nextAngle) * radius);
            ELVector3 rightBottom = ELVector3Make(cos(nextAngle) * radius, endHeight, sin(nextAngle) * radius);
            ELVector3 normalRight = ELVector3Normalize(ELVector3Make(cos(nextAngle) * radius, 0, sin(nextAngle) * radius));

            ELFloat triangles[] = {
                    leftTop.x, leftTop.y, leftTop.z, normalLeft.x, normalLeft.y, normalLeft.z, side / sides, (segment + 1) / (ELFloat)heightSegments,
                    leftBottom.x, leftBottom.y, leftBottom.z, normalLeft.x, normalLeft.y, normalLeft.z, side / sides, segment / (ELFloat)heightSegments,
                    rightTop.x, rightTop.y, rightTop.z, normalRight.x, normalRight.y, normalRight.z, (side + 1)/ sides, (segment + 1) / (ELFloat)heightSegments,

                    rightTop.x, rightTop.y, rightTop.z, normalRight.x, normalRight.y, normalRight.z, (side + 1)/ sides, (segment + 1) / (ELFloat)heightSegments,
                    leftBottom.x, leftBottom.y, leftBottom.z, normalLeft.x, normalLeft.y, normalLeft.z, side / sides,  segment / (ELFloat)heightSegments,
                    rightBottom.x, rightBottom.y, rightBottom.z, normalRight.x, normalRight.y, normalRight.z, (side + 1)/ sides, segment / (ELFloat)heightSegments,
            };
            vertexBuffer->append(triangles, sizeof(triangles));
        }
    }
}