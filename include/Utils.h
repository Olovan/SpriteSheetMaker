#ifndef UTILS_H_7JJDHIMX
#define UTILS_H_7JJDHIMX

#include <MSGL/msglCore.h>
#include <MSGL/msglGraphics.h>
#include <App.h>


#define Vec2 msgl::core::Vec2
#define Sprite msgl::graphics::Sprite


namespace utils
{

extern App* app;

template<typename T>
T clamp(T input, T min, T max)
{
	return input > max ? max : input < min ? min : input;
}

template <typename T>
T roundToNearestCoord(T input)
{
	T base = (int)input;
	T remainder = input - (int)input;

	if(remainder <= -0.5)
	{
		return base - 1;
	}
	if(remainder >= 0.5)
	{
		return base + 1;
	}
	return base;
}

inline Vec2 roundToNearestCoord(Vec2 input)
{
	return Vec2(roundToNearestCoord(input.x), roundToNearestCoord(input.y));
}

inline Vec2 convertCoords(Vec2 input)
{
	return Vec2(input.x * (float)app->texture.width / (float)app->window.width, input.y * (float)app->texture.height / (float)app->window.height);
}

inline bool contains(Sprite sprite, Vec2 point)
{
    return false;
}

} //Namespace utils

#undef Vec2
#undef Sprite

#endif /* end of include guard: UTILS_H_7JJDHIMX */
