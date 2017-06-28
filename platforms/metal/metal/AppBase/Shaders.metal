//
//  Shaders.metal
//  SwiftMetalLearn
//
//  Created by wangyang on 2017/5/2.
//  Copyright © 2017年 wangyang. All rights reserved.
//

#include <metal_stdlib>

using namespace metal;

struct VertexIn
{
    packed_float3  position;
    packed_float3  color;
    packed_float2  uv;
};

struct VertexOut
{
    float4  position [[position]];
    float4  color;
    float2 uv;
    float pointSize [[ point_size ]];
};
struct Uniforms
{
    float4x4 transform;
};


vertex VertexOut passThroughVertex(uint vid [[ vertex_id ]],
                                   const device VertexIn* vertexIn [[ buffer(0) ]],
                                   const device Uniforms& uniform [[ buffer(1) ]])
{
    VertexOut outVertex;
    VertexIn inVertex = vertexIn[vid];
    float4x4 mvp = uniform.transform;
    outVertex.position = mvp * float4(inVertex.position, 1.0);
    outVertex.color = float4(1.0, 0.0, 1.0, 1.0);
    outVertex.uv = inVertex.uv;
    
    outVertex.pointSize = 1;
    return outVertex;
};

constexpr sampler s(coord::normalized, address::repeat, filter::linear);

fragment float4 passThroughFragment(VertexOut inFrag [[stage_in]],
                                    texture2d<float> diffuse [[ texture(0) ]])
{
    float4 color = diffuse.sample(s, inFrag.uv);
    return color;
};

