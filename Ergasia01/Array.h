#pragma once
#include <vector>
using namespace std;
namespace math {
	template <typename T>
	class Array {
	protected:
		unsigned int width;
		unsigned int height;
		vector <T> buffer;
	public:
		const unsigned int getWidth() const { return width; }//epistrefo to mikos tis eikonas
		const unsigned int getHeight() const { return height; }//epistrefo to ipsos tis eikonas
		vector <T>& getRawDataPtr() {
			return buffer;//epistrefo to vector
		}
		void setData(vector<T> &data_ptr) {
			buffer.resize(width*height);//arxikopio to megethos tou vector na einai iso me to ipsos epi to mikos
			for (int i = 0; i < width*height; i++) {//ena for gia na diatrekso to vector
				buffer[i] = data_ptr[i];//se kathe thesi tou vector vazo to stixio stin idia thesi me to data_ptr
			}
		}
		T* operator()(unsigned int x, unsigned int y){//o operator p epistrefi to pixel stin thesi x,y
			if (x < width && y < height) {//elegxo an to x kai to y ine mikrotera apo to mikos kai to ipsos
				return &buffer[y *this->width + x];//epistrefo to stixio stin thesi x,y
			}
			else {
				return &buffer[0];//diaforetika epistrefo to stoixio stin thesi 0
			}
		}
		Array() {//default constructor
			width = height = 0;//arxikopio to ipsos kai to mikos me 0
		}
		Array(unsigned int width, unsigned int height) :buffer(width*height)//constructor p dini arxiki timi sto ipsos kai mikos 
		{
			this->width = width;
			this->height = height;
		}
		Array(unsigned int width, unsigned int height, vector<T> data_ptr) {
			this->width = width;
			this->height = height;
			buffer = data_ptr;
		}
		Array(const Array<T> &src) :buffer(src.width*src.height)//o copy constructor stin lista arxikopioisis dinoume megethos sto vector
		{
			this->width = src.width;
			this->height = src.height;
			for (unsigned int i = 0; i < width*height; i++)//ena for gia na diatreksoume ton buffer k ton src
			{
				buffer[i] = src.buffer[i];//antigrafo ta stoixeia tou src ston buffer
			}

		}
		Array<T>& operator = (const Array<T>& right) {//assigment operator
			if (this != &right) {//elegxo an ta dio stoixeia den einai ta idia
				this->width = right.width;//kano to mikos tou neou antikeimenou iso me tou right
				this->height = right.height;//kano to ipsos tou neou antikeimenou iso me tou right
				buffer.resize(width*height);//kano to megethos tou buffer iso me width *height
				this->buffer = right.buffer;//kano ton buffer iso me ton buffer tou right
			}return *this;//epistrefo to neo antikimeno
		}
		
	};
}