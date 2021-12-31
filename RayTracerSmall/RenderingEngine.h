#ifndef _RENDERING_ENGINE_H_
#define _RENDERING_ENGINE_H_

#include "definitions.h"
#include "UI.h"
#include "VecTemplate.h"
#include "Timing.h"
#include "sphere.h"
#include "SceneManager.h"
#include <thread>

using namespace std;

typedef Vector3<float> Vec3f;

class RenderingEngine
{
public:
    vector<vector<Sphere*>> FrameInfoOutput;
    vector<Sphere*>* SceneInfoReference;
    vector<Sphere*>::pointer SceneElementsReference;

    void MainMenu();
    void TestRendering();

    void CalculateAmmountOfFramesToRender();

    RenderingEngine(SceneManager* SceneManagerReference, UI* ui);
    ~RenderingEngine();

    SceneManager* sceneManagerP;
    UI* mp_UI;

private:

    void rendererFunc(const vector<Sphere*>& OBJ_spheres, int OBJ_iteration, unsigned OBJ_width, unsigned OBJ_height, vector<thread>& numThread, Vec3f* OBJ_image);

    float mixFunc(const float& temp1, const float& temp2, const float& mixVar);

    Vec3f traceFunc(const Vec3f& rayOrigin, const Vec3f& rayDirection, const vector<Sphere*>& sphereAmmount, const int& depthOfObj);

    void dataCalculationFunc(int iteration, int width, int height, float WidthInv, float HeightInv, float angle, float fov, float aspectratio, Vec3f* pixel, Vec3f* image, const vector<Sphere*>& spheres);
};

#endif