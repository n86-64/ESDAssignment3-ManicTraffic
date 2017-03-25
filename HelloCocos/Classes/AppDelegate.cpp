#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

bool AppDelegate::applicationDidFinishLaunching() 
{
	std::string appName = "Manic Traffic Alpha";

#ifdef _DEBUG 
	appName = "Manic traffic DEBUG v1.0a OpenGL 4.5 (Dont you leak this now OR ELSE)";
#endif

	const int width = 1280, height = 720;
	auto director = Director::getInstance();

	auto glview = director->getOpenGLView();
	if (!glview)
	{
		glview = GLViewImpl::create(appName);
		glview->setFrameSize(width, height);
		glview->setDesignResolutionSize(
			width, height,
			ResolutionPolicy::EXACT_FIT);

		director->setOpenGLView(glview);
	}

	auto scene = RHMainMenu::create();
	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground() 
{

}

void AppDelegate::applicationWillEnterForeground() 
{

}