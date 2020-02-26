/* Andreas Kyrou 3160211
*/

#include "ppm.h"
#include <iostream>
#include<fstream>
#include <string>
#include <string.h>
using namespace std;
using namespace imaging;

float * imaging::ReadPPM(const char * filename, int * w, int * h) {
	int format;//to mikos,platos kai to 255 tis eikonas
	string title;//o titlos stin arxi to p6
	ifstream input(filename, ios_base::in | ios_base::binary);//anoigo reuma eisodou me to arxio tis eikonas
	if (input) {//elegxo an aniksekanonika to arxio
		input >> title;//apothikevo sto title ton titlo tis eikonas
		if (title != "P6") {//elegxo an o tittlos einai p6 
			cerr << "The type of picture is wrong" << endl;//an den einai tipono minima sfalmatos
			input.close();//klino to reuma eisodou
			return nullptr;//epistrefo keno deikti
		}
		input >> *w;//diavazo to mikos apo to arxeio
		if (*w <= 0) {//elegxo an einai arnitiko
			cerr << "The weight of picture cannot be zero or negative" << endl;//tipono minima lathous an einai 0 i arnitiko to mikos
			input.close();//klino to reuma eisodou afou einai lathos
			return nullptr;//epistrefi keno deikti
		}
		input >> *h;//diavazo k apothikevo to ipsos apo to arxeio
		if (*h <= 0) {//elegxo an to ipsos einai 0 i arnitiko
			cerr << "The height of picture cannot be zero or negative" << endl;//tipono minima lathous 
			input.close();//klino to reuma eisodou
			return nullptr;//epistrefo keno deikti
		}
		input >> format;//diavazo to vathos xromatos
		if (format != 255) {//elegxo an einai 255
			cerr << "The format of picture has to be 255" << endl;//an den einai tipono minima lathous
			input.close();//klino to reuma isodou
			return nullptr;//epistrefo enan keno deikti
		}
		cout << "Image dimensions are: " << *w << " x " << *h << endl;//tipono tis diastasis tis eikonas
		input.get();//perno ton telefteo keno xaraktira
		unsigned char* pixels = new unsigned char[(*w)*(*h) * 3];//dimourgo ena pinaka megethous oso to ipsos*to platos*3 p einai ta xromata ton pixels
		float* buffer = new float[(*w)*(*h) * 3];//dimiourgo enan pinaka float o opios tha apothikefsi tis times apo[0,1]
		input.read((char*)pixels, (*w)*(*h) * 3);//diavazo ola ta stoixia tis eikonas diladi ta xromata ton pixels
		for (int i = 0; i < (*w)*(*h) * 3; i++) {//diatrexo ton pinaka me ta arxika pixels
			buffer[i] = pixels[i] / (float)format;//diero ta arxika pixels me double to 255 g na paro tin diadiki timi otan diereso me 255
		     		}
		delete[] pixels;//diagrafo ton pinaka me ta arxika pixels
		return buffer;//epistrefo ton pinaka float me ta xromata kathe pixel se morfi [0,1]
	}
	else {
		cerr << "file cannot be open" << endl; return nullptr;
	}
}
bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {

	ofstream output(filename, ios_base::out | ios_base::binary);//anigo reuma eksodou me to arxio
	if (output) {//elegxo to reuma eisodou
		output << "P6" << endl << w << endl << h << endl<< 255 << endl;//tipono mesa sto arxeio tin epikefalida tis eikonas
		unsigned char* pixe = new unsigned char[w*h * 3];//dimiourgo enan pinaka g ta nea stoixia
		for ( int i = 0; i < w*h * 3; i++) {//diatrexo ton pinaka data me ta arnitika pixel tis photo
			pixe[i] = (unsigned char)(data[i] * 255);//pollaplasiazo ta xromata *255 gia na paro tin sosti tous morfi kai ta vazo ston neo pinaka
			
		}
		output.write(( char*)pixe, w*h *3);//grafo sto arxeio ta nea pixels
		delete[] pixe;//diagrafo ton pinaka 
		return true;//k epistrefo true
	}
	else {
		cerr << "The file cannot be open" << endl;//an den anoikse sosta tipose minima lathous
		return false;//epestrepse false
	}
}