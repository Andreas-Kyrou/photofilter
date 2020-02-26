#include "filter.h"
#include "Image.h"
#include "Vec3.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
FilterGamma::FilterGamma(float g)
{
	this->g = g;
}
Image FilterGamma::operator<<(const Image & image)
{
	Image copy(image);//kalo ton copy constructor tis image me parametro tin eikona p perasame os orisma
	for (unsigned int i = 0; i < image.getWidth(); i++) {//dio for gia na diatreksoume tin eikona
		for (unsigned int j = 0; j < image.getHeight(); j++) {
			Color pixels = copy.getPixel(i, j);//antikeimeno tipou color to opio tha pernoume to pixel stin thesi i,j
			pixels.r = pow(pixels.r, this->g);//ipsonoume ton arithmo tou kokkinou xromatos tou pixel stin dinami g
			pixels.g = pow(pixels.g, this->g);//ipsonoume ton arithmo tou prasinou xromatos tou pixel stin dinami g
			pixels.b = pow(pixels.b, this->g);//ipsonoume ton arithmo tou mple xromatos tou pixel stin dinami g
			
			copy.setPixel(i, j, pixels);//kanoume to pixel stin thesi i,j iso me to neo pixel
		}
	}	

	return copy;//epistrefoume tin tropopioimeni eikona
}
FilterGamma::FilterGamma(const FilterGamma &src) {
	this->g = src.g;
}