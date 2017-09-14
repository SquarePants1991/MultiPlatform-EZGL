//
// Created by wang yang on 2017/9/14.
//

#ifndef EZGL_SKYBOXTESTS_H
#define EZGL_SKYBOXTESTS_H

#include "TestScene.h"
#include "renderer/ELSkyBoxRenderer.h"
#include "geometry/ELGeometry.h"

class SkyBoxTests: public TestScene {
public:
    SkyBoxTests(std::map<std::string, ELRenderPiplinePtr> piplines);
    virtual void update(ELFloat deltaTime);

protected:
    ELSkyBoxRendererPtr renderer;
    ELTexturePtr skyBoxMap;
    std::vector<ELGeometryPtr> geometries;
};

#endif //EZGL_SKYBOXTESTS_H
