
/* Andreas Kyrou 3160211
		*/






#include "Image.h"
#include <string>
#include "ppm.h"
#include <vector>
#include "Array.h"
#include "Vec3.h"
#include <iostream>

using namespace std;
using namespace math;

namespace imaging {
	Color Image::getPixel(unsigned int x, unsigned int y) {
		Color* c=0;//kano ena neo antikimeno tipou color
		if (x < width && y < height)//elegxo an to x,y einai mikrotero apo to ipsos kai mikos tis ikonas
			 c =operator()(x, y);////kalo ton neo operator p dimiourgisame gia na epistrefi to pixel stin thesi(X,Y)
	return *c;//epistrefo to pixel
	}
	void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
		
		if (x < width && y < height) {//elegxo an to x kai y pou perasame os parametrous einai mikrotera apo to ipsos k platos tis eikonas
			Color *c = operator()(x, y);//kalo ton neo operator p dimiourgisame gia na epistrefi to pixel stin thesi(X,Y)
			*c = value;	//kano to pixel sto simio (x,y) iso me to pixel p perasame os orisma
			
		}
	}

	Image::Image(unsigned int width, unsigned int height): Array(width,height)//stin lista arxiothetisis tou constractor 
	{	}//divazoume se pion constructor tis array tha pai to idio kai sta ipolipa
	Image::Image()
	{	}
	Image::Image(unsigned int width, unsigned int height, const vector<Color> data_ptr): Array(width,height,data_ptr)
	{	}
	Image::Image(const Image &src) : Array(src)
	{	}
	Image::~Image() {
	}

	Image & Image::operator = (const Image & right) {//o assigment operator gia tin image
		Array :: operator  =(right);//kalo ton operator tis array
		return *this;//epistrefo to antikimeno p m epestrepse o operator tis array
	}
	bool Image::load(const std::string & filename, const std::string & format) {
		if (format != ".ppm") {//elegxo an i kataliksi tou arxiou eina ppm 
			cerr << "Format of image must be .ppm" << endl;//an den einai tipono minima lathous
			return false;//epistrefo false
		}
		else {
			string name;//to olokliromeno onoma tis eikonas
			name = filename;//vazo sto name to filename p pirame apo tin main
			name.append(format);		//prostheto tin kataliksi tou arxiou g na mporo na anikso to reuma eisodou k na diavaso to ipsos mikos tis eikonas
			int w, h;//2 int g na apothikefsoume mesa to ipsos k to platos tis eikonas p tha diavasoume stin readppm

			const char* onoma = name.c_str();//kano to onoma tis eikonas se const char g na mporo na to peraso os orisma stin methodo 
			float * buf = ReadPPM(onoma, &w, &h);//enas pinakas tipou component_t(float) me onoma buf opou tha apothikefsoume ton pinaka tis readppm
			if (buf == nullptr)//an epistrepsi null i read
				return false;//epistrefo false
			this->buffer.resize(w*h);//arxikopio to megethos tou buffer

			for (int i = 0; i < w*h ; i++) {//diatrexo ton pinaka buf
				this->buffer[i] = Color(buf[3*i], buf[3*i + 1], buf[3*i + 2]);//gemizo ton buffer me antikimena tipou color p antiprosopevoun ta pixel tis eikonas
				
			}
			this->width = w;//dino sto antikeimeno p dimiourgisa stin main tis times tis eikonas
			this->height = h;

			delete[] buf;//diegrafo ton pinaka me ta arxika stoixeia tis eikonas
			return true;
		}

	}
	bool Image::save(const std::string & filename, const std::string & format) {
		if (format != ".ppm") {//elegxo an to format einai .ppm
			cerr << "The format for the new picture must be .ppm" << endl;//an den einai tipono minima lathous
			return false;//epistrefo false
		}
		else {

			string name1;//kano mia metavliti i opoia tha einai to onoma tou neou arxeiou
			name1 = filename; name1.append(format);//prostheto sto onoma tin kataliksi .ppm
			float *p = new float[width*height * 3];//dimiourgo ena pinaka g ta nea stoixeia tis eikonas
			
			for (unsigned int i = 0; i < width*height; i++) {//diatrexo ton buffer
				p[3*i] = buffer[i].r;//vazo ta nea stoixia ston pinaka
				p[3*i+1] = buffer[i].g;
				p[3*i+2] = buffer[i].b;
				
			}
			if (!WritePPM(p, width, height, name1.c_str())) {//kalo tin write ppm g na grapso to neo arxeio tis eikonas
				cerr << "WritePPM cannot write the picture" << endl;
				delete[] p;//diagrafo ton pinaka p desmefsa
				return false;//epistrefo false an i write den kataferi na to grapsi 
			}

			delete[] p;//diagrafo ton pinaka p desmefsa
		}return true;//epistrefo true an ola pane kala

	}
}