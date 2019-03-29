#include <iostream>
#include <irrlicht.h>

#include "ToonShaderCallBack.h"

using namespace irr;

int main(void) {

//---------------------------------------------------------------------------------------------------------------------
// Initialisation de Irrlicht
//---------------------------------------------------------------------------------------------------------------------

    IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800,600), 32, false, true, false, 0);

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager *sceneManager = device->getSceneManager();

//---------------------------------------------------------------------------------------------------------------------
//  Initialisation des shaders
//---------------------------------------------------------------------------------------------------------------------


    bool pixel_shader_support = (driver->queryFeature(video::EVDF_PIXEL_SHADER_1_1) || driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1));
    bool vertex_shader_support = (driver->queryFeature(video::EVDF_VERTEX_SHADER_1_1) || driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1));

    if(!vertex_shader_support || !pixel_shader_support){
        std::cerr << "Les shaders 1.1 ne sont pas supportes par votre carte graphique." << std::endl << "Veuillez utilisez la version sans shaders du jeu" << std::endl;
        return 0;
    }

    video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();

    s32 toonMaterialType = 0;

    if(gpu){
        ToonShaderCallBack* shader_callback = new ToonShaderCallBack(device);

        toonMaterialType = gpu->addHighLevelShaderMaterialFromFiles("toon_vert_shader.vert", "main", video::EVST_VS_1_1,  "toon_pixel_shader.frag", "main", video::EPST_PS_1_1, shader_callback, video::EMT_SOLID);
        shader_callback->drop();
    }

//---------------------------------------------------------------------------------------------------------------------
//  Initialisation du contenu
//---------------------------------------------------------------------------------------------------------------------

    //model->setMaterialType((video::E_MATERIAL_TYPE)toonMaterialType);

    std::cout << "Test réussi" << std::endl;


//---------------------------------------------------------------------------------------------------------------------
//  Boucle principale
//---------------------------------------------------------------------------------------------------------------------


    sceneManager->addCameraSceneNode(0, core::vector3df(0.0f, 0.0f, 0.0f));

    while(device->run()){
        driver->beginScene(true, true, video::SColor(255,255,255,255));
        sceneManager->drawAll();
        driver->endScene();
    }


    device->drop();

    return 0;
}

