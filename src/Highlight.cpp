#include <Highlight.h>
#include <Utils.h>
#include <MSGL/msglCore.h>

using msgl::core::Vec2;
using msgl::core::Input;
using msgl::graphics::Sprite;


/*PRIVATE API*/
void Highlight::repositionCorners()
{
	corners[0].position = Vec2(  position.x,             			 position.y          );
	corners[1].position = Vec2(  position.x + size.x - corners[1].size.x,    position.y          );
	corners[2].position = Vec2(  position.x,                                 position.y + size.y - corners[2].size.y );
	corners[3].position = Vec2(  position.x + size.x - corners[3].size.x,    position.y + size.y - corners[3].size.y );
}
void Highlight::updateSprites()
{
	highlight    .setOrigin( highlight.origin  );
	corners[0]   .setOrigin( corners[0].origin );
	corners[1]   .setOrigin( corners[1].origin );
	corners[2]   .setOrigin( corners[2].origin );
	corners[3]   .setOrigin( corners[3].origin );
}
bool Highlight::containsMouse()
{
	//if( Input::mousePos.x > position.x && Input::mousePos.y > position.y && Input::mousePos.x <
	
	return false;
}


/* PUBLIC API */
//Constructors
Highlight::Highlight() : ButtonListener()
{
	highlight.setColor(0, 120, 0, 80);
	highlight.z = 0.2;
	for(int i = 0; i < 4; i++)
	{
		corners[i].z = 0.3;
		corners[i].setColor(120, 0, 0, 255);
		corners[i].texture = nullptr;
	}
}

Highlight::Highlight(Vec2 position, Vec2 size) : Highlight::Highlight()
{
	position = position;
	size = size;
	updateSprites();
}

//Methods
void Highlight::draw()
{
	if(!visible)
	{
		return;
	}
	highlight.draw();
	for(int i = 0; i < 4; i++)
	{
		corners[i].draw();
	}
}

Highlight Highlight::clone()
{
	return Highlight(this->position, this->size);
}

//ButtonListener
void Highlight::buttonPressed(int button, int mods)
{
	std::cout << "Highlight Coords: " << utils::convertCoords(Input::mousePos).toString() << std::endl; //DEBUG
}
void Highlight::buttonReleased(int button, int mods)
{
	std::cout << "Highlight Released" << std::endl; //DEBUG
}
//Getters and Setters
Vec2 Highlight::getCornerSize() { return corners[0].size; }
void Highlight::setCornerSize(Vec2 size)
{
	std::cout << "Resizing Corners: " << size.toString() << std::endl; //DEBUG
	for(int i = 0; i < 4; i++)
	{
		std::cout << "Resizing Corner" << std::endl; //DEBUG
		corners[i].size = size;
		corners[i].setOrigin( corners[i].origin );
	}
}

Vec2 Highlight::getSize() { return size; }
void Highlight::setSize(Vec2 size) 
{ 
	this->size             = size; 
	highlight.size         = size;

	repositionCorners();
	updateSprites();
}

Vec2 Highlight::getPosition() { return position; }
void Highlight::setPosition(Vec2 position) 
{ 
	this->position = position; 

	highlight.position = position;
	repositionCorners();
	updateSprites();
}

bool Highlight::getVisible() { return visible; }
void Highlight::setVisible(bool visible) { this->visible = visible; }
