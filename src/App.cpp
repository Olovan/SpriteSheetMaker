#include <App.h>
#include <InputHandler.h>
#include <Utils.h>
#include <MSGL/msglCore.h>
#include <MSGL/msglGraphics.h>
#include <iostream>

using msgl::graphics::Window;
using msgl::graphics::Texture;
using msgl::graphics::Sprite;
using msgl::core::Vec2;
using msgl::core::Input;


/*PRIVATE */
bool App::validateInput(int argc, char* argv[])
{
	if(argc <= 1 || argv[1] == NULL)
	{
		std::cout << "No Image Argument Found" << std::endl;
		exit(0);
		return false;
	}
	return true;
}

/*PUBLIC */
App::App()
{
	Window::initGLFW();
	window.create(600, 600, "SpriteSheetMaker");
	utils::app = this;
	input.setApp(this);
}

App::~App()
{
}

App::App(int argc, char* argv[]) : App()
{
	validateInput(argc, argv);
	texturePath = argv[1];
}

void App::run()
{
	init();
	update();
	close();
}

void App::init()
{
	//Load Texture
	texture = Texture(texturePath);

	window.resize(texture.width, texture.height);

	//Set up Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, texture.width, texture.height, 0, -1, 1);

	//OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Build Background Sprite
	background = Sprite(Vec2(0, 0), Vec2(texture.width, texture.height), &texture);
	background.z = -0.5;
	background.flipTexture = true;

	//Set up Highlight
	currentHighlight = Highlight();
	currentHighlight.setCornerSize( Vec2((float)texture.width/(float)100, (float)texture.height/(float)100) );
	std::cout << currentHighlight.getCornerSize().toString() << std::endl;
}

void App::update()
{
	while( !window.shouldClose() )
	{
		window.pollEvents();
		window.clear();

		input.update();

		background.draw();
		currentHighlight.draw();

		window.swapBuffer();
	}
}

void App::close()
{
}
