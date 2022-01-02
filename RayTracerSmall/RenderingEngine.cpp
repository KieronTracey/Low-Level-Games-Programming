#include "RenderingEngine.h"
RenderingEngine* selfRenderer;

void WWTestRender() 
{
	selfRenderer->TestRender(); 
};

RenderingEngine::RenderingEngine(SceneManager* sceneManager, UI* ap_UI) : sceneManager(sceneManager), mp_UI(ap_UI), SceneElementsRef(nullptr), SceneInfoReference(NULL)
{
	selfRenderer = this;
}

RenderingEngine::~RenderingEngine()
{
	for (int c = 0; c < FrameInfoOutput.size(); ++c)
	{
		for (int l = 0; l < FrameInfoOutput[c].size(); ++l)
		{
			delete FrameInfoOutput[c][l];
			FrameInfoOutput[c][l] = nullptr;
		}
	}

	SceneInfoReference = nullptr;
	SceneElementsRef = nullptr;
	delete sceneManager;
	sceneManager = nullptr;
	delete mp_UI;
	mp_UI = nullptr;
}

void RenderingEngine::Menu()
{
	vector<MenuOption> mainMenu;
	mainMenu.push_back(MenuOption("Render scene", WWTestRender));
	mp_UI->DisplayMenu(mainMenu, "Render engine");
}

void RenderingEngine::TestRender()
{
	if (sceneManager->loadFile)
	{
		sceneManager->SceneRefresh();
		Timing timer;
		timer.TimerStart();

		CalculateNumFramesToRender();

		vector<thread> threadCount;
		vector<Vec3f*> frameCOunt;

		for (int m = 0; m < FrameInfoOutput.size(); m++)
		{
			frameCOunt.push_back(new Vec3f[640 * 480]);
			renderer(FrameInfoOutput[m], m, 640, 480, threadCount, frameCOunt[m]);
		}

		for (int a = 0; a < threadCount.size(); a++)
		{
			if (threadCount[a].joinable())
			{
				threadCount[a].join();
			}
		}

		cout << "Renderered " << frameCOunt.size() << " Frames\n";

		for (int s = 0; s < frameCOunt.size(); s++)
		{
			delete frameCOunt[s];
			frameCOunt[s] = nullptr;
		}

		for (int z = 0; z < FrameInfoOutput.size(); z++)
		{
			for (int x = 0; x < FrameInfoOutput[z].size(); x++)
			{
				delete FrameInfoOutput[z][x];
				FrameInfoOutput[z][x] = nullptr;
			}
			FrameInfoOutput[z].clear();
		}

		threadCount.clear();
		frameCOunt.clear();
		FrameInfoOutput.clear();

		timer.TimerEnd();
		timer.TimeTaken();
	}
	else
	{
		mp_UI->OutputData<string>("No Scene Loaded. Please load a scene and try again");
	}
}



void RenderingEngine::CalculateNumFramesToRender()
{
	float TotalFrames = sceneManager->Length * sceneManager->FPS;
	int iFPS = sceneManager->FPS;
	vector<Sphere*> tempFrameMem;

	for (int k(0); k < TotalFrames; ++k)
	{
		for (int k(0); k < tempFrameMem.size(); ++k)
		{
			tempFrameMem[k] = nullptr;
		}
		tempFrameMem.clear();

		float LPercentage = (k / TotalFrames);
		for (int j(0); j < sceneManager->objectPresent.size(); ++j)
		{
			if (sceneManager->objectPresent[j]->OBJ_startpos != sceneManager->objectPresent[j]->OBJ_endpos)
			{
				Sphere* t3 = new Sphere();
				*t3 = *sceneManager->objectPresent[j];

				t3->OBJ_center.x -= (sceneManager->objectPresent[j]->OBJ_startpos.x - sceneManager->objectPresent[j]->OBJ_endpos.x) * LPercentage;
				t3->OBJ_center.y -= (sceneManager->objectPresent[j]->OBJ_startpos.y - sceneManager->objectPresent[j]->OBJ_endpos.y) * LPercentage;
				t3->OBJ_center.z -= (sceneManager->objectPresent[j]->OBJ_startpos.z - sceneManager->objectPresent[j]->OBJ_endpos.z) * LPercentage;

				tempFrameMem.push_back(t3);
			}
			else
			{
				tempFrameMem.push_back(sceneManager->objectPresent[j]);
			}
		}
		FrameInfoOutput.push_back(tempFrameMem);
	}
	tempFrameMem.clear();
}

void RenderingEngine::calculateData(int iteration, int width, int height, float invWidth, float invHeight, float angle, float fov, float aspectratio, Vec3f* pixel, Vec3f* image, const vector<Sphere*>& spheres)
{
	for (unsigned y(0); y < height; ++y)
	{
		for (unsigned x(0); x < width; ++x, ++pixel)
		{
			float x2 = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float y2 = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			Vec3f raydirection(x2, y2, -1);
			raydirection.normalizeTemplate();
			*pixel = trace(Vec3f(0), raydirection, spheres, 0);
		}
	}

	stringstream stStream;
	stStream << "./spheres" << iteration << ".ppm";
	std::string tempString = stStream.str();

	std::ofstream ofs(tempString.c_str(), ios::out | ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned i(0); i < width * height; ++i) {
		ofs << (unsigned char)(min(float(1), image[i].x) * 255) <<
			(unsigned char)(min(float(1), image[i].y) * 255) <<
			(unsigned char)(min(float(1), image[i].z) * 255);
	}
	ofs.close();

	cout << "Frame rendered \n";
}

void RenderingEngine::renderer(const vector<Sphere*>& spheres, int iteration, unsigned width, unsigned height, vector<thread>& aThreads, Vec3f* Aimage)
{
	Timing timer;
	timer.TimerStart();
	Vec3f* pixel = Aimage;
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float fov(30), aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5 * fov / 180.);

	aThreads.push_back(thread(&RenderingEngine::calculateData, this, iteration, width, height, invWidth, invHeight, angle, fov, aspectratio, pixel, Aimage, spheres));
	timer.TimerEnd();
	timer.TimeTaken();
}

float RenderingEngine::Ren_mix(const float& t1, const float& t2, const float& mix)
{
	return t2 * mix + t1 * (1 - mix);
}

Vec3f RenderingEngine::trace(const Vec3f& rayOrigin, const Vec3f& rayDirection, const vector<Sphere*>& spheres, const int& depth)
{
	float tnear(INFINITY);
	const Sphere* sphere(NULL);
	for (int l = 0; l < spheres.size(); ++l) {
		float t4(INFINITY), t1(INFINITY);
		if (spheres[l]->intersecting(rayOrigin, rayDirection, t4, t1)) {
			if (t4 < 0) t4 = t1;
			if (t4 < tnear) {
				tnear = t4;
				sphere = spheres[l];
			}
		}
	}
	if (!sphere) return Vec3f(0.80, 0.95, 0.99);
	Vec3f surfaceColor(0);
	Vec3f phit = rayOrigin + rayDirection * tnear; 
	Vec3f nhit = phit - sphere->OBJ_center;
	nhit.normalizeTemplate(); 
	float oBias(1e-4);
	bool in(false);
	if (rayDirection.mathVar(nhit) > 0) nhit = -nhit, in = true;

	if ((sphere->OBJ_transparency > 0 || sphere->OBJ_reflection > 0) && depth < MAX_RAY_DEPTH) 
	{
		float faceratio = -rayDirection.mathVar(nhit);
		float FE = Ren_mix(pow(1 - faceratio, 3), 1, 0.1);

		Vec3f refldir = rayDirection - nhit * 2 * rayDirection.mathVar(nhit);

		refldir.normalizeTemplate();

		Vec3f reflection = trace(phit + nhit * oBias, refldir, spheres, depth + 1);
		Vec3f refraction(0);

		if (sphere->OBJ_transparency) {
			float IO(1.1), Eta = (in) ? IO : 1 / IO;
			float cosi = -nhit.mathVar(rayDirection);
			float j = 1 - Eta * Eta * (1 - cosi * cosi);
			Vec3f refractionDirection = rayDirection * Eta + nhit * (Eta * cosi - sqrt(j));
			refractionDirection.normalizeTemplate();
			refraction = trace(phit - nhit * oBias, refractionDirection, spheres, depth + 1);
		}

		surfaceColor = (reflection * FE + refraction * (1 - FE) * sphere->OBJ_transparency) * sphere->OBJ_surfcolour;
	}
	else 
	{
		for (int o = 0; o < spheres.size(); o++) {
			if (spheres[o]->OBJ_emisscolour.x > 0) {
				Vec3f transmis(1);
				Vec3f lightDir = spheres[o]->OBJ_center - phit;
				lightDir.normalizeTemplate();
				for (unsigned v(0); v < spheres.size(); ++v) {
					if (o != v) {
						float t5;
						float t6;
						if (spheres[v]->intersecting(phit + nhit * oBias, lightDir, t5, t6)) {
							transmis = 0;
							break;
						}
					}
				}
				surfaceColor += sphere->OBJ_surfcolour * transmis *
					std::max(float(0), nhit.mathVar(lightDir)) * spheres[o]->OBJ_emisscolour;
			}
		}
	}

	return surfaceColor + sphere->OBJ_emisscolour;
}