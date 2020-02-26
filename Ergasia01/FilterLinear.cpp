#include "filter.h"
#include "Image.h"
#include "Vec3.h"
#include <vector>
#include <cmath>
#include <iostream>
FilterLinear::FilterLinear(Color a, Color c)
{
	this->a = a;
	this->c = c;
}

Image FilterLinear::operator<<(const Image & image)
{
	Image copy(image);//kalo ton copy constructor tis image me parametro image
	for (unsigned int i = 0; i < image.getWidth(); i++) {//dio for gia na diatrekso ta pixel tis eikonas
		for (unsigned int j = 0; j < image.getHeight(); j++) {
			
			Color pixel = (this->a*copy.getPixel(i, j)) + this->c;//ena antikeimeno tipou color to opio tha exi to tropopioimeno pixel
			pixel=pixel.clampToUpperBound(1);//ean to tropopioimeno pixel exi times pano apo 1 sta xromata tis kani iso me 1
			pixel=pixel.clampToLowerBound(0);//ean to tropopioimeno pixel exi times kato apo 0 sta xromata tis kani iso me 0
			copy.setPixel(i, j, pixel);//apothikevo to tropopioimeno pixel stin thesi tou paliou
		}
	}return copy;//epistrefo tin nea eikona
}
FilterLinear::FilterLinear(const FilterLinear &src) {
	this->a = src.a;
	this->c = src.c;
}