#include <MSGL/msglCore.h>
#include <MSGL/msglGraphics.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace msgl::graphics;
using namespace msgl::core;

//GLOBALS
std::string EXPORT_FILE_NAME = "SpriteSheet.ss";
std::string filePath;

Window window(640, 480, "Sprite Sheet Creator");
Texture texture;
Sprite currentSprite(Vec2(0, 0), Vec2(0, 0), nullptr);
std::vector<Sprite> sprites;


//UTILITIES
float clampf(float num, float bottom, float top)
{
	return num > top ? top : num < bottom ? bottom : num;
}
int clampi(int num, int bottom, int top)
{
	return num > top ? top : num < bottom ? bottom : num;
}
bool contains(Vec2 point, Sprite sprite)
{
	if( ((point.y > sprite.position.y) != (point.y > (sprite.position.y + sprite.size.y))) && ((point.x > sprite.position.x) != (point.x > (sprite.position.x + sprite.size.x))) )
		return true;
	return false;
}
//Translate Window Pixel Coords to Ortho Coords
Vec2 translateCoords(Vec2 input)
{
	Vec2 retVal = input * Vec2((float)texture.width / (float)window.width, (float)texture.height / (float)window.height);
	retVal.x = clampf(retVal.x, 0, texture.width);
	retVal.y = clampf(retVal.y, 0, texture.height);
	return retVal;
}
//Round to nearest whole value in Vec2
Vec2 roundToNearestCoord(Vec2 input)
{
	Vec2 retVal = Vec2((int)input.x, (int)input.y);
	float xDecimal = input.x - (int)input.x;
	float yDecimal = input.y - (int)input.y;

	if(xDecimal > 0.5f)
		retVal.x += 1;
	if(xDecimal < -0.5f)
		retVal.x -= 1;
	if(yDecimal > 0.5f)
		retVal.y += 1;
	if(yDecimal < -0.5f)
		retVal.y -= 1;

	return retVal;
}
Vec2 floorVec2(Vec2 input)
{
	return Vec2((int)input.x, (int)input.y);
}
//Make Sure that you included a filename
bool checkPath(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Need filename" << std::endl;
		exit(0);
	}
	return true;
}
void openInPreviewWindow(std::string spriteSheet)
{
	std::cout << "Creating Window" << std::endl; //DEBUG
	Window preview(500, 500, "Preview");
	glfwMakeContextCurrent(preview.id);
	std::cout << "Loading Sprites From File: " << filePath << std::endl; //DEBUG
	std::vector<Sprite*> sprites = msgl::core::loadFromFile(spriteSheet);
	std::cout << "Number Sprites Loaded: " << sprites.size() << std::endl; //DEBUG
	SpriteAnimation anim;
	anim.frameRate = 8;
	std::cout << "Putting Sprites in Animation" << std::endl; //DEBUG
	for(Sprite* s : sprites)
	{
		//s->setTexture(&tex, Vec2i(s->position.x, s->position.y), Vec2i(s->size.x, s->size.y));
		s->size = Vec2(1, 1);
		s->position = Vec2(-0.5, -0.5);
		s->setOrigin(s->origin);
		s->setColor(255, 255, 255, 255);
		anim.addFrame(s);
	}

	std::cout << "Preview Setup Done" << std::endl; //DEBUG
	std::cout << "Animation FrameRate: " << anim.frameRate << std::endl;
	std::cout << "Animation Size: " << anim.frames.size() << std::endl;

	while(!preview.shouldClose())
	{
		anim.update(0.016);
		preview.clear();

		anim.currentFrame->draw();

		preview.swapBuffer();
		preview.pollEvents();
	}
	glfwDestroyWindow(preview.id);
	glfwMakeContextCurrent(window.id);
	texture = Texture(filePath);
}
//Export all Sprites to File in Order
void sendToFile(std::string fileName)
{
	std::ofstream file(fileName);
	file << "Filename " << texture.fileName << "\n";
	for(int i = 0; i < sprites.size(); i++)
	{
		file << "Sprite" << " " << sprites[i].position.x << "," << sprites[i].position.y << " " << sprites[i].size.x << "," << sprites[i].size.y << "\n";
	}
	file.close();

	openInPreviewWindow(fileName);
}

std::string getFileName(std::string filePath)
{
	std::string retVal;
	int slashIndex = filePath.find_last_of("/") + 1;
	int dotIndex = filePath.find_last_of(".");
	retVal = filePath.substr(slashIndex, dotIndex - slashIndex);
	return retVal;
}
std::string getFileExtension(std::string filePath)
{
	int extensionIndex = filePath.find_last_of(".") + 1;
	return filePath.substr(extensionIndex, filePath.size() - extensionIndex);
}
Sprite* getSpriteUnderCursor()
{
	Vec2 transMousePos = translateCoords(Input::mousePos);
	for(Sprite &sprite : sprites)
	{
		if(contains(transMousePos, sprite))
			return &sprite;
	}
	return nullptr;
}

//INPUT LOGIC
class InputManager: public KeyListener, public ButtonListener
{
public:
	void update()
	{
		if(Input::buttons[GLFW_MOUSE_BUTTON_1] && Input::keys[GLFW_KEY_LEFT_SHIFT])
		{
			currentSprite.position = roundToNearestCoord(translateCoords(Input::mousePos));
		}
		else if(Input::buttons[GLFW_MOUSE_BUTTON_1])
		{
			currentSprite.size = roundToNearestCoord(translateCoords(Input::mousePos)) - currentSprite.position;
			currentSprite.setOrigin(currentSprite.origin);
		}
	}
	void keyPressed(int key, int mods)
	{
		if(key == GLFW_KEY_ENTER)
		{
			std::cout << "EXPORTING" << std::endl; //DEBUG
			sendToFile(EXPORT_FILE_NAME + ".ss");
		}
	}
	void keyReleased(int key, int mods)
	{
	}
	void keyHeld(int key, int mods)
	{
	}
	void buttonPressed(int button, int mods)
	{
		if(button == GLFW_MOUSE_BUTTON_1 && mods == GLFW_MOD_SHIFT)
		{
			Sprite* sprite = getSpriteUnderCursor();
			if(sprite == nullptr)
				return;
			currentSprite.size = sprite->size;
			currentSprite.setColor(50, 200, 70, 80);
			currentSprite.z = 0.2f;
			currentSprite.setOrigin(currentSprite.origin);
		}
		else if(button == GLFW_MOUSE_BUTTON_1)
		{
			Vec2 transMousePos = translateCoords(Input::mousePos);
			transMousePos = roundToNearestCoord(transMousePos);
			currentSprite = Sprite(transMousePos, Vec2(0, 0), nullptr);
			currentSprite.setColor(50, 200, 70, 80);
			currentSprite.z = 0.2f;
		}


		//If you right click on a Sprite it is deleted
		if(button == GLFW_MOUSE_BUTTON_2)
		{
			Vec2 transMousePos = translateCoords(Input::mousePos);
			for(Sprite& sprite : sprites)
			{
				if(contains(transMousePos, sprite))
				{ //Switch it with the last item and pop off the last item
					sprite = sprites[sprites.size() - 1];
					sprites.pop_back();
				}
			}
		}
	}
	void buttonReleased(int button, int mods)
	{
		if(button == GLFW_MOUSE_BUTTON_1 && mods == GLFW_MOD_SHIFT)
		{
			currentSprite.setOrigin(currentSprite.origin);
			sprites.push_back(currentSprite);
			currentSprite.setColor(0, 0, 0, 0);
		}
		if(button == GLFW_MOUSE_BUTTON_1)
		{
			currentSprite.size = roundToNearestCoord(translateCoords(Input::mousePos)) - currentSprite.position;
			currentSprite.setOrigin(currentSprite.origin);
			if(currentSprite.size.x != 0 && currentSprite.size.y != 0)
			{
				sprites.push_back(currentSprite);
			}
			currentSprite.setColor(0, 0, 0, 0);
		}
	}
	void buttonHeld(int button, int mods) //Useless TODO Remove This method from Interface
	{
	}
};


/*
//MAIN LOOP
int main(int argc, char *argv[])
{
	checkPath(argc, argv);

	InputManager input;
	Input::addButtonListener(&input);
	Input::addKeyListener(&input);
	//Must supply a file name when running this program
	filePath = argv[1];
	std::cout << filePath << std::endl; //DEBUG
	EXPORT_FILE_NAME = getFileName(filePath);
	std::cout << EXPORT_FILE_NAME << std::endl;
	std::cout << getFileExtension(filePath) << std::endl;

	texture = Texture(filePath);

	if(texture.id == 0)
	{
		exit(0);
	}

	window.resize(texture.width, texture.height);
	window.setOrtho(0, window.width, window.height, 0, -1, 1);

	Sprite background(Vec2(0, 0), Vec2(window.width, window.height), &texture);
	background.flipTexture = true; //Our coordinate system is upside down (0,0 is TOP LEFT) so flip the texture


	while(!window.shouldClose())
	{
		window.pollEvents();
		input.update();
		window.clear();

		background.draw();
		currentSprite.draw();
		for(Sprite sprite : sprites)
		{
			sprite.draw();
		}

		window.swapBuffer();
	}

	return 0;
}
*/
