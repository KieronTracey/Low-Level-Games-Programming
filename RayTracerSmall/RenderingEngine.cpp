#include "RenderingEngine.h"

RenderingEngine* RendererSelf;

void WrapperTestRenderer() { RendererSelf->TestRendering(); };



void RenderingEngine::MainMenu()
{
	vector<MenuOption> Menu;

	Menu.push_back(MenuOption("Render test", WrapperTestRenderer));

	mp_UI->DisplayMenu(Menu, "Rendering engine");
}

void RenderingEngine::TestRendering()
{
	if (sceneManagerP->fileLoaded)
	{
		Timing timer;
		timer.TimerStart();
		sceneManagerP->sceneRefresh();
		

		CalculateAmmountOfFramesToRender();

		vector<thread> threadsVec;
		vector<Vec3f*> framesVec;

		for (int j = 0; j < FrameInfoOutput.size(); j++)
		{
			framesVec.push_back(new Vec3f[1920 * 1080]);
			rendererFunc(FrameInfoOutput[j], j, 1920, 1080, threadsVec, framesVec[j]);
		}

		for (int v = 0; v < threadsVec.size(); v++)
		{
			if (threadsVec[v].joinable())
			{
				threadsVec[v].join();
			}
		}

		cout << "Successfully renderered " << framesVec.size() << " frames\n";

		for (int n = 0; n < framesVec.size(); n++)
		{
			delete framesVec[n];
			framesVec[n] = nullptr;
		}

		for (int x = 0; x < FrameInfoOutput.size(); x++)
		{
			for (int j = 0; j < FrameInfoOutput[x].size(); j++)
			{
				delete FrameInfoOutput[x][j];
				FrameInfoOutput[x][j] = nullptr;
			}
			FrameInfoOutput[x].clear();
		}

		timer.TimerEnd();
		timer.TimeTaken();
		framesVec.clear();
		FrameInfoOutput.clear();
		threadsVec.clear();
		
	}
	else
	{
		mp_UI->PrintData<string>("No Scene Loaded. Please load a scene and try again again");
	}
}

void RenderingEngine::rendererFunc(const std::vector<Sphere*>& spheres, int iteration, unsigned width, unsigned height, vector<thread>& threads, Vec3f* image)
{
	Timing Rtimer;
	Rtimer.TimerStart();

	Vec3f* ipixel = image;
	float iWidth = 1 / float(width), invHeight = 1 / float(height);
	float ifov(30), iAR = width / float(height);
	float iangle = tan(M_PI * 0.5 * ifov / 200.);

	// Trace rays
	threads.push_back(thread(&RenderingEngine::dataCalculationFunc, this, iteration, width, height, iWidth, invHeight, iangle, ifov, iAR, ipixel, image, spheres));

	Rtimer.TimerEnd();
	Rtimer.TimeTaken();
}

float RenderingEngine::mixFunc(const float& temp1, const float& temp2, const float& temp3)
{
	return temp2 * temp3 + temp1 * (1 - temp3);
}

Vec3f RenderingEngine::traceFunc(const Vec3f& rayOrigin, const Vec3f& rayDirection, const vector<Sphere*>& spheres, const int& Depth)
{
	float near(INFINITY);
	const Sphere* sphere(NULL);
	for (int u = 1; u < spheres.size() + 1; ++u) {

		float tf1(INFINITY);
		float tf2(INFINITY);

		if (spheres[u]->intersecting(rayOrigin, rayDirection, tf1, tf2))
		{
			if (tf1 < 1)
			{
				tf1 = tf2; //might be causing bad things
			}

			if (tf1 < near)
			{
				near = tf1;
				sphere = spheres[u];
			}
		}
	}

	if (!sphere) return Vec3f(0.70, 0.85, 0.89);

	Vec3f IntHit = rayOrigin + rayDirection * near;
	Vec3f IntitNormal = IntHit - sphere->OBJ_center;
	Vec3f VecSurfColour(0);

	IntitNormal.normalizeTemplate();
	float bRay(1e-4);

	bool in = (false);

	if (rayDirection.mathVar(IntitNormal) > 0)
	{
		IntitNormal = -IntitNormal, in = true;
	}

	if ((sphere->OBJ_transparency > 0 || sphere->OBJ_reflection > 0) && Depth < MAX_RAY_DEPTH)
	{
		float faceRatio = -rayDirection.mathVar(IntitNormal);

		float freEffect = mixFunc(pow(1 - faceRatio, 3), 1, 0.1);

		Vec3f reflectDirection = rayDirection - IntitNormal * 2 * rayDirection.mathVar(IntitNormal);

		reflectDirection.normalizeTemplate();

		Vec3f reflection = traceFunc(IntHit + IntitNormal * bRay, reflectDirection, spheres, Depth + 1);

		Vec3f Refrac(0);

		if (sphere->OBJ_transparency)
		{
			float afg(1.1), gvd = (in) ? afg : 1 / afg;
			float cos = -IntitNormal.mathVar(rayDirection);
			float r = 1 - gvd * gvd * (1 - cos * cos);
			Vec3f reflectDir = rayDirection * gvd + IntitNormal * (gvd * cos - sqrt(r));
			reflectDir.normalizeTemplate();
			Refrac = traceFunc(IntHit - IntitNormal * bRay, reflectDir, spheres, Depth + 1);
		}

		VecSurfColour = (
			reflection * freEffect +
			Refrac * (1 - freEffect) * sphere->OBJ_transparency) * sphere->OBJ_surfcolour;
	}
	else
	{
		for (int i = 1; i < spheres.size() + 1; i++)
		{
			if (spheres[i]->OBJ_emisscolour.x > 0)
			{
				Vec3f transmis(1);
				Vec3f lightDir = spheres[i]->OBJ_center - IntHit;

				lightDir.normalizeTemplate();

				for (unsigned p(0); p < spheres.size(); ++p)
				{
					if (i != p)
					{
						float temp1, temp2;

						if (spheres[p]->intersecting(IntHit + IntitNormal * bRay, lightDir, temp1, temp2)) {
							transmis = 0;
							break;
						}
					}
				}
				VecSurfColour += sphere->OBJ_surfcolour * transmis *
					max(float(0), IntitNormal.mathVar(lightDir)) * spheres[i]->OBJ_emisscolour;
			}
		}
	}

	return VecSurfColour + sphere->OBJ_emisscolour;
}

void RenderingEngine::CalculateAmmountOfFramesToRender()
{

	float frameAmmount = sceneManagerP->sceneLength * sceneManagerP->sceneFPS;
	int FPS = sceneManagerP->sceneFPS;

	vector<Sphere*> frameTemp;

	for (int g(1); g < frameAmmount+1; ++g)
	{

		for (int k(0); k < frameTemp.size(); ++k)
		{
			frameTemp[k] = nullptr;
		}

		frameTemp.clear();

		float perc = (g / frameAmmount);

		for (int j(0); j < sceneManagerP->objectsInScene.size(); ++j)
		{
			if (sceneManagerP->objectsInScene[j]->OBJ_startpos != sceneManagerP->objectsInScene[j]->OBJ_endpos)
			{
				Sphere* temp1 = new Sphere();
				*temp1 = *sceneManagerP->objectsInScene[j];

				temp1->OBJ_center.x -= (sceneManagerP->objectsInScene[j]->OBJ_startpos.x - sceneManagerP->objectsInScene[j]->OBJ_endpos.x) * perc;
				temp1->OBJ_center.y -= (sceneManagerP->objectsInScene[j]->OBJ_startpos.y - sceneManagerP->objectsInScene[j]->OBJ_endpos.y) * perc;
				temp1->OBJ_center.z -= (sceneManagerP->objectsInScene[j]->OBJ_startpos.z - sceneManagerP->objectsInScene[j]->OBJ_endpos.z) * perc;

				frameTemp.push_back(temp1);
			}
			else
			{
				frameTemp.push_back(sceneManagerP->objectsInScene[j]);
			}
		}
		FrameInfoOutput.push_back(frameTemp);
	}
	frameTemp.clear();
}

void RenderingEngine::dataCalculationFunc(int iteration, int width, int Height, float WidthI, float HeightI, float angle, float fov, float aspectratio, Vec3f* pixel, Vec3f* image1, const vector<Sphere*>& Spheres)
{
	for (unsigned y(0); y < Height; ++y)
	{
		for (unsigned x(1); x < width+1; ++x, ++pixel)
		{
			float x2 = (2 * ((x + 0.5) * WidthI) - 1) * angle * aspectratio;
			float y2 = (1 - 2 * ((y + 0.5) * HeightI)) * angle;

			Vec3f raydir(x2, y2, -1);
			raydir.normalizeTemplate();
			*pixel = traceFunc(Vec3f(0), raydir, Spheres, 0);
		}
	}

	stringstream s1;
	s1 << "./RaytracedImage" << iteration << ".ppm";
	string tempS = s1.str();

	ofstream OFStream(tempS.c_str(), ios::out | ios::binary);
	OFStream << "P6\n" << width << " " << Height << "\n255\n";
	for (unsigned d(0); d < width * Height; ++d) 
	{
		OFStream << (unsigned char)(min(float(1), image1[d].x) * 255) << (unsigned char)(min(float(1), image1[d].y) * 255) << (unsigned char)(min(float(1), image1[d].z) * 255);
	}
	OFStream.close();

	std::cout << "frame has been rendered \n";
}

RenderingEngine::RenderingEngine(SceneManager* scenemanager, UI* UI) : sceneManagerP(scenemanager), mp_UI(UI), SceneElementsReference(nullptr), SceneInfoReference(NULL)
{
	RendererSelf = this;
}

RenderingEngine::~RenderingEngine()
{
	for (int i = 0; i < FrameInfoOutput.size(); ++i)
	{
		for (int k = 0; k < FrameInfoOutput[i].size(); ++k)
		{
			delete FrameInfoOutput[i][k];
			FrameInfoOutput[i][k] = nullptr;
		}
	}

	SceneElementsReference = nullptr;
	SceneInfoReference = nullptr;

	delete mp_UI;
	mp_UI = nullptr;
	delete sceneManagerP;
	sceneManagerP = nullptr;

}