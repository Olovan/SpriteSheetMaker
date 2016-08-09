#ifndef HIGHLIGHT_H_ZGS18JUL
#define HIGHLIGHT_H_ZGS18JUL


#include <MSGL/msglCore.h>
#include <MSGL/msglGraphics.h>

#define Vec2 		msgl::core::Vec2  
#define Sprite 		msgl::graphics::Sprite
#define ButtonListener  msgl::core::ButtonListener


class Highlight : public ButtonListener
{
public:
	Highlight ();
	Highlight (Vec2 position, Vec2 size);

	void		draw();
	Highlight 	clone();
	Vec2 		getPosition();
	void 		setPosition(Vec2 position);
	Vec2 		getSize();
	void 		setSize(Vec2 size);
	void 		setVisible(bool visible);
	bool 		getVisible();
	Vec2		getCornerSize();
	void		setCornerSize(Vec2 size);
	//ButtonListener
	void		buttonPressed(int button, int mods);
	void		buttonReleased(int button, int mods);
private:
	bool 		containsMouse();
	void 		updateSprites();
	void 		repositionCorners();
	bool 		visible;
	Vec2 		position;
	Vec2 		size;
	Sprite 		highlight;
	Sprite 		corners[4];
};

#undef Vec2
#undef Sprite
#undef ButtonListener


#endif /* end of include guard: HIGHLIGHT_H_ZGS18JUL */
