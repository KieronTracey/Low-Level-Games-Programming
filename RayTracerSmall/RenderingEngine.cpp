#include "RenderingEngine.h"
RenderingEngine* gp_selfRenderer;

void TestRenderWrapper() { gp_selfRenderer->TestRender(); };
void HDRenderWrapper() { gp_selfRenderer->HDRender(); };

RenderingEngine::RenderingEngine(SceneManager* ap_sceneManager, UI* ap_UI) : mp_sceneManager(ap_sceneManager), mp_UI(ap_UI), mp_refToSceneElements(nullptr), mp_refToSceneInfo(NULL)
{
	gp_selfRenderer = this;
}

RenderingEngine::~RenderingEngine()
{
	for (int i = 0; i < mp_calulatedFrameInformation.size(); ++i)
	{
		for (int j = 0; j < mp_calulatedFrameInformation[i].size(); ++j)
		{
			delete mp_calulatedFrameInformation[i][j];
			mp_calulatedFrameInformation[i][j] = nullptr;
		}
	}

	mp_refToSceneInfo = nullptr;
	mp_refToSceneElements = nullptr;

	delete mp_sceneManager;
	mp_sceneManager = nullptr;

	delete mp_UI;
	mp_UI = nullptr;
}

void RenderingEngine::Menu()
{
	vector<MenuOption> l_mainMenu;
	l_mainMenu.push_back(MenuOption("Test Render", TestRenderWrapper));
	l_mainMenu.push_back(MenuOption("HD Render", HDRenderWrapper));


	mp_UI->DisplayMenu(l_mainMenu, "Rendering Engine");
}

void RenderingEngine::TestRender()
{
	if (mp_sceneManager->loadFile)
	{
		mp_sceneManager->SceneRefresh();
		Timing l_timer;
		l_timer.TimerStart();

		CalculateFramesToRender();

		std::vector<thread> threads;
		std::vector<Vec3f*> frames;

		for (int i = 0; i < mp_calulatedFrameInformation.size(); i++)
		{
			frames.push_back(new Vec3f[640 * 480]);
			render(mp_calulatedFrameInformation[i], i, 640, 480, threads, frames[i]);
		}

		for (int i = 0; i < threads.size(); i++)
		{
			if (threads[i].joinable())
			{
				threads[i].join();
			}
		}

		cout << "Renderered " << frames.size() << " Frames\n";

		for (int i = 0; i < frames.size(); i++)
		{
			delete frames[i];
			frames[i] = nullptr;
		}

		for (int i = 0; i < mp_calulatedFrameInformation.size(); i++)
		{
			for (int j = 0; j < mp_calulatedFrameInformation[i].size(); j++)
			{
				delete mp_calulatedFrameInformation[i][j];
				mp_calulatedFrameInformation[i][j] = nullptr;
			}
			mp_calulatedFrameInformation[i].clear();
		}

		threads.clear();
		frames.clear();
		mp_calulatedFrameInformation.clear();

		l_timer.TimerEnd();
		l_timer.TimeTaken();
	}
	else
	{
		mp_UI->OutputData<string>("Scene Not Loaded please correct this before trying again");
	}
}

void RenderingEngine::HDRender()
{
	if (mp_sceneManager->loadFile)
	{
		mp_sceneManager->SceneRefresh();
		Timing l_timer;
		l_timer.TimerStart();

		CalculateFramesToRender();

		std::vector<thread> threads;
		std::vector<Vec3f*> frames;

		for (int i = 0; i < mp_calulatedFrameInformation.size(); i++)
		{
			frames.push_back(new Vec3f[1920 * 1080]);
			render(mp_calulatedFrameInformation[i], i, 1920, 1080, threads, frames[i]);
		}

		for (int i = 0; i < threads.size(); i++)
		{
			if (threads[i].joinable())
			{
				threads[i].join();
			}
		}

		cout << "Renderered " << frames.size() << " Frames\n";

		for (int i = 0; i < frames.size(); i++)
		{
			delete frames[i];
			frames[i] = nullptr;
		}

		for (int i = 0; i < mp_calulatedFrameInformation.size(); i++)
		{
			for (int j = 0; j < mp_calulatedFrameInformation[i].size(); j++)
			{
				delete mp_calulatedFrameInformation[i][j];
				mp_calulatedFrameInformation[i][j] = nullptr;
			}
			mp_calulatedFrameInformation[i].clear();
		}

		threads.clear();
		frames.clear();
		mp_calulatedFrameInformation.clear();

		l_timer.TimerEnd();
		l_timer.TimeTaken();
	}
	else
	{
		mp_UI->OutputData<string>("Scene Not Loaded please correct this before trying again");
	}
}

void RenderingEngine::CalculateFramesToRender()
{
	//- Required Var -//
	//- Creating Duplicate Infomraion to use (so wont alter any saved states) -//
	float li_totalFrames = mp_sceneManager->Length * mp_sceneManager->FPS;
	int li_framesPerSecond = mp_sceneManager->FPS;

	//- temp storage -//
	vector<Sphere*> l_tempSceneFrameStorage;

	//- loops through all frames -//
	for (int i(0); i < li_totalFrames; ++i)
	{
		//- deleting the last frame -//
		for (int k(0); k < l_tempSceneFrameStorage.size(); ++k)
		{
			l_tempSceneFrameStorage[k] = nullptr;
		}
		l_tempSceneFrameStorage.clear();

		float lf_lerpPercentage = (i / li_totalFrames);

		//- loop through all elements in the scene -//
		for (int j(0); j < mp_sceneManager->objectPresent.size(); ++j)
		{
			//- Making sure that the element is meant to be animated -//
			if (mp_sceneManager->objectPresent[j]->OBJ_startpos != mp_sceneManager->objectPresent[j]->OBJ_endpos)
			{
				Sphere* temp = new Sphere();
				*temp = *mp_sceneManager->objectPresent[j];

				//- lerp calculation (li_frameCount is a percentage of travel between the two points) -//           //- Percentage of way through frames for even animation speed -//
				temp->OBJ_center.x -= (mp_sceneManager->objectPresent[j]->OBJ_startpos.x - mp_sceneManager->objectPresent[j]->OBJ_endpos.x) * lf_lerpPercentage;
				temp->OBJ_center.y -= (mp_sceneManager->objectPresent[j]->OBJ_startpos.y - mp_sceneManager->objectPresent[j]->OBJ_endpos.y) * lf_lerpPercentage;
				temp->OBJ_center.z -= (mp_sceneManager->objectPresent[j]->OBJ_startpos.z - mp_sceneManager->objectPresent[j]->OBJ_endpos.z) * lf_lerpPercentage;

				l_tempSceneFrameStorage.push_back(temp);
			}
			//- if not animated just push element to the caculatedframeInformation element-//
			else
			{
				l_tempSceneFrameStorage.push_back(mp_sceneManager->objectPresent[j]);
			}
		}
		mp_calulatedFrameInformation.push_back(l_tempSceneFrameStorage);
	}
	l_tempSceneFrameStorage.clear();
}

void RenderingEngine::calculateData(int ai_iteration, int ai_width, int ai_height, float af_invWidth, float af_invHeight, float af_angle, float af_fov, float af_aspectratio, Vec3f* ap_pixel, Vec3f* ap_image, const std::vector<Sphere*>& ar_spheres)
{
	for (unsigned y(0); y < ai_height; ++y)
	{
		for (unsigned x(0); x < ai_width; ++x, ++ap_pixel)
		{
			float xx = (2 * ((x + 0.5) * af_invWidth) - 1) * af_angle * af_aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * af_invHeight)) * af_angle;
			Vec3f raydir(xx, yy, -1);
			raydir.normalizeTemplate();
			*ap_pixel = trace(Vec3f(0), raydir, ar_spheres, 0);
		}
	}

	//Save result to a PPM image (keep these flags if you compile under Windows)
	std::stringstream ss;
	ss << "./spheres" << ai_iteration << ".ppm";
	std::string tempString = ss.str();

	std::ofstream ofs(tempString.c_str(), std::ios::out | std::ios::binary);
	ofs << "P6\n" << ai_width << " " << ai_height << "\n255\n";
	for (unsigned i(0); i < ai_width * ai_height; ++i) {
		ofs << (unsigned char)(std::min(float(1), ap_image[i].x) * 255) <<
			(unsigned char)(std::min(float(1), ap_image[i].y) * 255) <<
			(unsigned char)(std::min(float(1), ap_image[i].z) * 255);
	}
	ofs.close();

	std::cout << "FRAME RENDERED \n";
}

//[comment]
// Main rendering function. We compute a camera ray for each pixel of the image
// trace it and return a color. If the ray hits a sphere, we return the color of the
// sphere at the intersection point, else we return the background color.
//[/comment]
void RenderingEngine::render(const std::vector<Sphere*>& spheres, int iteration, unsigned width, unsigned height, vector<thread>& ap_threads, Vec3f* ap_image)
{
	Timing l_timer;
	l_timer.TimerStart();

	Vec3f* pixel = ap_image;
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float fov(30), aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5 * fov / 180.);

	// Trace rays
	ap_threads.push_back(std::thread(&RenderingEngine::calculateData, this, iteration, width, height, invWidth, invHeight, angle, fov, aspectratio, pixel, ap_image, spheres));

	l_timer.TimerEnd();
	l_timer.TimeTaken();
}

float RenderingEngine::mix(const float& a, const float& b, const float& mix)
{
	return b * mix + a * (1 - mix);
}

//[comment]
// This is the main trace function. It takes a ray as argument (defined by its origin
// and direction). We test if this ray intersects any of the geometry in the scene.
// If the ray intersects an object, we compute the intersection point, the normal
// at the intersection point, and shade this point using this information.
// Shading depends on the surface property (is it transparent, reflective, diffuse).
// The function returns a color for the ray. If the ray intersects an object that
// is the color of the object at the intersection point, otherwise it returns
// the background color.
//[/comment]
Vec3f RenderingEngine::trace(const Vec3f& rayorig, const Vec3f& raydir, const std::vector<Sphere*>& spheres, const int& depth)
{
	float tnear(INFINITY);
	const Sphere* sphere(NULL);
	// find intersection of this ray with the sphere in the scene
	for (int i = 0; i < spheres.size(); ++i) {
		float t0(INFINITY), t1(INFINITY);
		if (spheres[i]->intersecting(rayorig, raydir, t0, t1)) {
			if (t0 < 0) t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				sphere = spheres[i];
			}
		}
	}
	// if there's no intersection return black or background color
	if (!sphere) return Vec3f(0.79, 0.94, 0.98);
	Vec3f surfaceColor(0); // color of the ray/surfaceof the object intersected by the ray
	Vec3f phit = rayorig + raydir * tnear; // point of intersection
	Vec3f nhit = phit - sphere->OBJ_center; // normal at the intersection point
	nhit.normalizeTemplate(); // normalize normal direction
					  // If the normal and the view direction are not opposite to each other
					  // reverse the normal direction. That also means we are inside the sphere so set
					  // the inside bool to true. Finally reverse the sign of IdotN which we want
					  // positive.
	float bias(1e-4); // add some bias to the point from which we will be tracing
	bool inside(false);
	if (raydir.mathVar(nhit) > 0) nhit = -nhit, inside = true;
	if ((sphere->OBJ_transparency > 0 || sphere->OBJ_reflection > 0) && depth < MAX_RAY_DEPTH) {
		float facingratio = -raydir.mathVar(nhit);
		// change the mix value to tweak the effect
		float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
		// compute reflection direction (not need to normalize because all vectors
		// are already normalized)
		Vec3f refldir = raydir - nhit * 2 * raydir.mathVar(nhit);
		refldir.normalizeTemplate();
		Vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1);
		Vec3f refraction(0);
		// if the sphere is also transparent compute refraction ray (transmission)
		if (sphere->OBJ_transparency) {
			float ior(1.1), eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
			float cosi = -nhit.mathVar(raydir);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vec3f refrdir = raydir * eta + nhit * (eta * cosi - sqrt(k));
			refrdir.normalizeTemplate();
			refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
		}
		// the result is a mix of reflection and refraction (if the sphere is transparent)
		surfaceColor = (
			reflection * fresneleffect +
			refraction * (1 - fresneleffect) * sphere->OBJ_transparency) * sphere->OBJ_surfcolour;
	}
	else {
		// it's a diffuse object, no need to raytrace any further
		for (int i = 0; i < spheres.size(); i++) {
			if (spheres[i]->OBJ_emisscolour.x > 0) {
				// this is a light
				Vec3f transmission(1);
				Vec3f lightDirection = spheres[i]->OBJ_center - phit;
				lightDirection.normalizeTemplate();
				for (unsigned j(0); j < spheres.size(); ++j) {
					if (i != j) {
						float t0, t1;
						if (spheres[j]->intersecting(phit + nhit * bias, lightDirection, t0, t1)) {
							transmission = 0;
							break;
						}
					}
				}
				surfaceColor += sphere->OBJ_surfcolour * transmission *
					std::max(float(0), nhit.mathVar(lightDirection)) * spheres[i]->OBJ_emisscolour;
			}
		}
	}

	return surfaceColor + sphere->OBJ_emisscolour;
}