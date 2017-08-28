//
// Created by wang yang on 2017/8/28.
//

#include "ELSphereGeometry.h"
#include "../utils/ELVertexBufferBuilder.h"

ELSphereGeometryPtr ELSphereGeometry::init(ELFloat radius, ELFloat ring, ELFloat segments) {
    baseSetup();
    selv->radius = radius;
    selv->ring = ring;
    selv->segments = segments;
    return selv;
}

void ELSphereGeometry::genHalfSphere(ELInt step, ELVertexBufferPtr vertexBuffer) {
    // 半圆
    for (int i = 0;fabs(i) < ring;i+=step) {
        ELFloat ringHeight = radius * i / ring;
        ELFloat ringRadius = sqrt(pow(radius, 2) - pow(ringHeight, 2));
        ELFloat ringHeightNext = radius * (i + step) / ring;
        ELFloat ringRadiusNext = sqrt(pow(radius, 2) - pow(ringHeightNext, 2));

        for (int j=0;j< segments ;j++) {
            int segmentIndex = step > 0 ? j : (segments - j);
            ELFloat radian = segmentIndex / segments * M_PI * 2;
            ELFloat radianNext = (segmentIndex + step) / segments * M_PI * 2;

            ELFloat x_r1_x0 = cos(radian) * ringRadius;
            ELFloat x_r1_y0 = ringHeight;
            ELFloat x_r1_z0 = sin(radian) * ringRadius;
            ELFloat x_r1_x1 = cos(radianNext) * ringRadius;
            ELFloat x_r1_y1 = ringHeight;
            ELFloat x_r1_z1 = sin(radianNext) * ringRadius;

            ELFloat x_r2_x0 = cos(radian) * ringRadiusNext;
            ELFloat x_r2_y0 = ringHeightNext;
            ELFloat x_r2_z0 = sin(radian) * ringRadiusNext;
            ELFloat x_r2_x1 = cos(radianNext) * ringRadiusNext;
            ELFloat x_r2_y1 = ringHeightNext;
            ELFloat x_r2_z1 = sin(radianNext) * ringRadiusNext;

            bool isTriangle = x_r2_x0 == x_r2_x1 && x_r2_z0 == x_r2_z1;
            ELFloat pi = (ELFloat)M_PI;
            if (isTriangle) {
                ELVector3 normal1 = ELVector3Normalize(ELVector3Make(x_r2_x0, x_r2_y0, x_r2_z0));
                ELVector3 normal2 = ELVector3Normalize(ELVector3Make(x_r1_x0, x_r1_y0, x_r1_z0));
                ELVector3 normal3 = ELVector3Normalize(ELVector3Make(x_r1_x1, x_r1_y1, x_r1_z1));
                ELFloat triangles[] = {
                        x_r1_x1, x_r1_y1, x_r1_z1, normal3.x, normal3.y, normal3.z, radianNext / (pi * 2.0f), 1.0f - (x_r1_y1 + radius) / (radius * 2),
                        x_r1_x0, x_r1_y0, x_r1_z0, normal2.x, normal2.y, normal2.z, radian / (pi * 2.0f), 1.0f - (x_r1_y0 + radius) / (radius * 2),
                        x_r2_x0, x_r2_y0, x_r2_z0, normal1.x, normal1.y, normal1.z, 0.5f, 1.0f - (x_r2_y0 + radius) / (radius * 2),
                };
                vertexBuffer->append(triangles, sizeof(triangles));
            } else {
                ELVector3 normal1 = ELVector3Normalize(ELVector3Make(x_r2_x0, x_r2_y0, x_r2_z0));
                ELVector3 normal2 = ELVector3Normalize(ELVector3Make(x_r1_x0, x_r1_y0, x_r1_z0));
                ELVector3 normal3 = ELVector3Normalize(ELVector3Make(x_r1_x1, x_r1_y1, x_r1_z1));
                ELVector3 normal4 = ELVector3Normalize(ELVector3Make(x_r2_x1, x_r2_y1, x_r2_z1));
                ELFloat rect[] = {
                        x_r1_x1, x_r1_y1, x_r1_z1, normal3.x, normal3.y, normal3.z, radianNext / pi / 2, 1.0f - (x_r1_y1 + radius) / (radius * 2),
                        x_r1_x0, x_r1_y0, x_r1_z0, normal2.x, normal2.y, normal2.z, radian / pi / 2, 1.0f - (x_r1_y0 + radius) / (radius * 2),
                        x_r2_x0, x_r2_y0, x_r2_z0, normal1.x, normal1.y, normal1.z, radian / pi / 2, 1.0f - (x_r2_y0 + radius) / (radius * 2),


                        x_r1_x1, x_r1_y1, x_r1_z1, normal3.x, normal3.y, normal3.z, radianNext / pi / 2, 1.0f - (x_r1_y1 + radius) / (radius * 2),
                        x_r2_x0, x_r2_y0, x_r2_z0, normal1.x, normal1.y, normal1.z, radian / pi / 2, 1.0f - (x_r2_y0 + radius) / (radius * 2),
                        x_r2_x1, x_r2_y1, x_r2_z1, normal4.x, normal4.y, normal4.z, radianNext / pi / 2, 1.0f - (x_r2_y1 + radius) / (radius * 2),
                };
                vertexBuffer->append(rect, sizeof(rect));
            }
        }
    }
}

void ELSphereGeometry::buildVertexBuffer() {
    _vertexBuffers.clear();
    ELVertexBufferPtr vertexBuffer = ELVertexBufferBuilder::buildBaseVertexBuffer(NULL,0);
    genHalfSphere(1, vertexBuffer);
    genHalfSphere(-1, vertexBuffer);
    vertexBuffer->flushBuffer();
    _vertexBuffers.push_back(vertexBuffer);
}