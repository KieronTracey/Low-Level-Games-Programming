#ifndef _RENDERING_ENGINE_H_
#define _RENDERING_ENGINE_H_

#include <thread>

#include "SceneManager.h"
#include "UI.h"
#include "definitions.h"
#include "VecTemplate.h"
#include "Timing.h"
#include "sphere.h"

typedef Vector3<float> Vec3f;

class RenderingEngine
{
public:

    void TestRender();
    void Menu();

    void CalculateNumFramesToRender();

    vector<vector<Sphere*>> FrameInfoOutput;
    vector<Sphere*>* SceneInfoReference;
    vector<Sphere*>::pointer SceneElementsRef;
    SceneManager* sceneManager;
    UI* mp_UI;

    RenderingEngine(SceneManager* sceneManagerReference, UI* UI);
    ~RenderingEngine();

private:
    void renderer(const vector<Sphere*>& sphere, int iterations, unsigned Swidth, unsigned Sheight, vector<thread>& threads, Vec3f* image);
    float Ren_mix(const float& t1, const float& t2, const float& ren_mix);
    Vec3f trace(const Vec3f& rayorigin, const Vec3f& raydirection, const vector<Sphere*>& sphere, const int& depth);

    void calculateData(int aiteration, int awidth, int aheight, float aInvWidth, float aInvHeight, float aAngle, float afov, float aAspectratio, Vec3f* aPixel, Vec3f* aimage, const vector<Sphere*>& aSpheres);

};

#endif