#ifndef APP_H_XGNSWRPH
#define APP_H_XGNSWRPH

#include <MSGL/msglCore.h>
#include <MSGL/msglGraphics.h>
#include <Highlight.h>
#include <InputHandler.h>


#define Window   msgl::graphics::Window
#define Vec2     msgl::core::Vec2
#define vector   std::vector
#define string   std::string
#define Texture  msgl::graphics::Texture
#define Sprite   msgl::graphics::Sprite


class App
{
public:
	App ();
	App (int argc, char* argv[]);
	~App ();

	string                  texturePath;
	string                  fileName;
	string                  textureExtension;
	Window                  window;
	Highlight               currentHighlight;
	vector<Highlight>       highlights;
	Texture                 texture;
	Sprite                  background;

	void run();
	void init();
	void update();
	void close();
private:
	bool validateInput(int argc, char* argv[]);
	InputHandler input;
};

#undef Window
#undef Vec2
#undef vector
#undef string
#undef Texture
#undef Sprite


#endif /* end of include guard: APP_H_XGNSWRPH */
