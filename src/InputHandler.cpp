#include <InputHandler.h>
#include <App.h>
#include <Utils.h>

using msgl::core::Input;
using msgl::core::Vec2;

InputHandler::InputHandler() : KeyListener(), ButtonListener()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::update()
{
	Vec2 transPos = utils::convertCoords(Input::mousePos);
	transPos = utils::roundToNearestCoord(transPos);
	transPos = Vec2( utils::clamp((int)transPos.x, 0, app->texture.width), utils::clamp((int)transPos.y, 0, app->texture.height));
	Vec2 newSize = transPos - app->currentHighlight.getPosition();
	switch(state)
	{
		case CREATE:
			app->currentHighlight.setSize(newSize);
			break;
		case MOVE:
			break;
		case COPY:
			break;
		default: //DO NOTHING
			break;
	}//switch
}
//KeyListener
void InputHandler::keyPressed(int key, int mods)
{
}
void InputHandler::keyReleased(int key, int mods)
{
}
void InputHandler::keyHeld(int key, int mods)
{
}
//ButtonListener
void InputHandler::buttonPressed(int button, int mods)
{
	switch( button )
	{
	case GLFW_MOUSE_BUTTON_1:
		//Copy
		if( mods == GLFW_MOD_SHIFT )
		{
			std::cout << "Shift Click at: " << Input::mousePos.toString() << std::endl;
		} 
		//Move
		else if ( mods == GLFW_MOD_CONTROL )
		{
			std::cout << "Control Click at: " << Input::mousePos.toString() << std::endl;
		} 
		//Create
		else
		{
			std::cout << "Click at: " << Input::mousePos.toString() << std::endl; //DEBUG
			std::cout << (app == nullptr ? "Null App" : "Non-Null App") << std::endl; //DEBUG
			app->currentHighlight.setVisible(true);
			std::cout << utils::convertCoords( Input::mousePos ).toString() << std::endl; //DEBUG
			app->currentHighlight.setPosition( utils::roundToNearestCoord(utils::convertCoords(Input::mousePos)) );
			app->currentHighlight.setSize( Vec2 (0, 0) );
			state = CREATE;
		}
		break;
	case GLFW_MOUSE_BUTTON_2:
		//Destroy
		std::cout << "Right Click at: " << Input::mousePos.x << ", " << Input::mousePos.y << std::endl;
		break;
	}
}
void InputHandler::buttonReleased(int button, int mods)
{
	switch (button)
	{
		case GLFW_MOUSE_BUTTON_1:
			if( mods == GLFW_MOD_SHIFT )
			{
				state = DEFAULT;
			}
			else if( mods == GLFW_MOD_CONTROL )
			{
				state = DEFAULT;
			}
			else
			{
				Vec2 convertedCoords = utils::convertCoords(Input::mousePos);
				convertedCoords = utils::roundToNearestCoord(convertedCoords);
				convertedCoords = Vec2( utils::clamp((int)convertedCoords.x, 0, app->texture.width), utils::clamp((int)convertedCoords.y, 0, app->texture.height));
				Vec2 pos = app->currentHighlight.getPosition();
				app->currentHighlight.setSize( convertedCoords  - pos ); 
				state = DEFAULT;
			}
			break;
		case GLFW_MOUSE_BUTTON_2:
			state = DEFAULT;
			break;
	}
}
void InputHandler::buttonHeld(int button, int mods) //TODO Remove this from API
{
}

//Getters and Setters
void InputHandler::setApp(App* app)
{
	this->app = app;
}

App* InputHandler::getApp()
{
	return app;
}
