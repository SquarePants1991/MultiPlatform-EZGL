//
// Created by wang yang on 2017/8/23.
//

#ifndef EZGL_SIMPLEGEOMETRYTESTS_H
#define EZGL_SIMPLEGEOMETRYTESTS_H

#include "TestScene.h"
#include "renderer/ELLambertPhongRenderer.h"
#include "geometry/ELGeometry.h"

class GeometryTestsBase: public TestScene {
public:
    GeometryTestsBase(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);
    virtual void preprocessMVP(ELMatrix4 *projection, ELMatrix4 *view, ELMatrix4 *model, ELFloat deltaTime) {}
protected:
    ELLambertPhongRendererPtr lambertPhongRenderer;
    ELTexturePtr diffuseTexture;
    std::vector<ELGeometryPtr> geometries;
};


#endif //EZGL_SIMPLEGEOMETRYTESTS_H
