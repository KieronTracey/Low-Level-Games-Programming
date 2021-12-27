#ifndef _RENDERING_ENGINE_H_
#define _RENDERING_ENGINE_H_

#include <thread>

#include "sphere.h"
#include "definitions.h"
#include "SceneManager.h"
#include "UI.h"
#include "VecTemplate.h"
#include "Timing.h"

//- Define for Vec3f Required at start of each header -//
typedef Vec3<float> Vec3f;

class RenderingEngine
{
public:

    //- Manager Methods -//
    RenderingEngine(SceneManager* ap_sceneManagerRef, UI* ap_UI);
    ~RenderingEngine();


    //- User Accessed/Defined -//
    void Menu();
    void TestRender();
    void HDRender();


    //- Developer Accessed/Defined -//
    void CalculateFramesToRender();

    vector<vector<Sphere*>> mp_calulatedFrameInformation;
    vector<Sphere*>* mp_refToSceneInfo;
    vector<Sphere*>::pointer mp_refToSceneElements;
    SceneManager* mp_sceneManager;
    UI* mp_UI;

private:
    void render(const std::vector<Sphere*>& spheres, int iteration, unsigned width, unsigned height, vector<thread>& ap_threads, Vec3f* ap_image);
    float mix(const float& a, const float& b, const float& mix);
    Vec3f trace(const Vec3f& rayorig, const Vec3f& raydir, const std::vector<Sphere*>& spheres, const int& depth);

    void calculateData(int ai_iteration, int ai_width, int ai_height, float af_invWidth, float af_invHeight, float af_angle, float af_fov, float af_aspectratio, Vec3f* ap_pixel, Vec3f* ap_image, const std::vector<Sphere*>& ar_spheres);

    //- Templates -//
};

#endif // !_RENDERING_ENGINE_H_