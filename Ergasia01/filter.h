#pragma once
#include "Image.h"
#include "Vec3.h"
#include <vector>
using namespace imaging;
typedef math::Vec3<float> Color;

class Filter
{
public:
	virtual Image operator <<(const Image & image) = 0;
};
class FilterGamma :public Filter
{
private:
	float g;
public:
	FilterGamma(float g);
	FilterGamma(const FilterGamma &src);

	Image operator << (const Image &image);
};
class FilterLinear : public Filter
{
private:
	Color a, c;
public:
	FilterLinear(Color a, Color c);
	FilterLinear(const FilterLinear &src);
	Image operator<<(const Image& image);
};