#ifndef TOONSHADERCALLBACK_H_INCLUDED
#define TOONSHADERCALLBACK_H_INCLUDED

#include <iostream>
#include <irrlicht.h>

using namespace irr;

class ToonShaderCallBack : public video::IShaderConstantSetCallBack
{
    private:
        IrrlichtDevice* device;

    public:
        ToonShaderCallBack(IrrlichtDevice* _device)
        {
            device = _device;
        }

        virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
        {
            video::IVideoDriver* driver = services->getVideoDriver();

            core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
            invWorld.makeInverse();
            services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);

            core::matrix4 worldViewProj;
            worldViewProj = driver->getTransform(video::ETS_PROJECTION);
            worldViewProj *= driver->getTransform(video::ETS_VIEW);
            worldViewProj *= driver->getTransform(video::ETS_WORLD);
            services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);

            core::vector3df pos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
            services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32*>(&pos), 4);

            core::vector3df lightDir(0.0f, 1.0f, 0.0f);
            services->setVertexShaderConstant("LightDir", reinterpret_cast<f32*>(&lightDir), 4);

            video::SColorf col(0.0f, 1.0f, 1.0f, 0.0f);
            services->setVertexShaderConstant("mLightColor", reinterpret_cast<f32*>(&col), 4);

            core::matrix4 world = driver->getTransform(video::ETS_WORLD);
            world = world.getTransposed();
            services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);

            int a = 0; services->setPixelShaderConstant("Texture0", (const float*)&a, 1);
            a = 1; services->setPixelShaderConstant("Texture1", (const float*)&a, 1);
            a = 2; services->setPixelShaderConstant("Texture2", (const float*)&a, 1);
            a = 3; services->setPixelShaderConstant("Texture3", (const float*)&a, 1);

        }
};

#endif // TOONSHADERCALLBACK_H_INCLUDED
