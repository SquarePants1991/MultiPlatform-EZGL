//
// Created by wang yang on 2017/8/24.
//

#include "ELVertexBufferBuilder.h"

ELVertexBufferPtr ELVertexBufferBuilder::buildBaseVertexBuffer(ELFloat *data, ELInt dataLength) {
    ELVertexBufferPtr vertexBuffer = ELVertexBuffer::alloc()->init(data, sizeof(ELFloat) * dataLength, sizeof(ELFloat) * 8, ELVertexBufferTypeStatic);
    ELVertexAttribute positionAttr;
    positionAttr.dataType = ELVertexAttributeDataTypeFloat;
    positionAttr.sizeInBytes = sizeof(ELFloat) * 3;
    positionAttr.offsetInBytes = 0;
    positionAttr.name = "v_position";
    vertexBuffer->addAttribute(positionAttr);
    ELVertexAttribute colorAttr;
    colorAttr.dataType = ELVertexAttributeDataTypeFloat;
    colorAttr.sizeInBytes = sizeof(ELFloat) * 3;
    colorAttr.offsetInBytes = sizeof(ELFloat) * 3;
    colorAttr.name = "v_normal";
    vertexBuffer->addAttribute(colorAttr);
    ELVertexAttribute uvAttr;
    uvAttr.dataType = ELVertexAttributeDataTypeFloat;
    uvAttr.sizeInBytes = sizeof(ELFloat) * 2;
    uvAttr.offsetInBytes = sizeof(ELFloat) * 6;
    uvAttr.name = "v_texcoord";
    vertexBuffer->addAttribute(uvAttr);
    return vertexBuffer;
}