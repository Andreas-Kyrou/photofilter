/* Andreas Kyrou 3160211
*/



#include "filter.h"
#include "Image.h"
#include "Array.h"
#include <iostream>
#include <string>

using namespace std;
using namespace imaging;
using namespace math;

int main(int argc, char* argv[]) {
	Color a, c;//dio antikeimena tipou color p tha paroun tis times gia to filtro linear
	float g;//mia metavliti tipou float gia to filter gamma
	int z;//mia metavliti p tha tin xriastoume gia na elegxoume an einai sosti i arithmi gia ta filra
	string name (argv[argc-1]);//i metavliti p tha apothikefsoume arxika to onoma tis eikonas
	string filename = name.substr(0, name.length() - 4);//apokoptoume to onoma apo tin kataliksi
	string kataliksi=name.substr(name.length() - 4, 4);;//apokoptoue tin kataliksi apo to onoma
	Image eikona;//ena antikeimeno tipou image gia na epeksergastoume tin eikona
	string p;//mia metavlliti tipou string pou tha xrisimopioithi gia diaforous elegxous 

	if (argc > 2) {//diaforetiko to perno apo ton pinaka argv
		if (!eikona.load(filename, kataliksi)) {//kalo tin load tis image k an epistrepsi false tipono minima lathous
					cerr << "Program cannot open or find the image" << endl;
					return 0;//kai termatizi to programma
				}
		for (int i = 1; i < argc - 2; i++) {//ena for gia na diatrekso ton pinaka argv p periexi tis plirofories gia ta filtra kai tin eikona
			p = argv[i];//vazoume kathe fora to stixeio stin thesi i stin p 
			if (p.compare("-f")==0) {//elegxo an to stixeio einai to -f p ipodiloni tin arxi enos filtrou
				i++; //auksano to i kata ena
				
				p = argv[i]; 
				if (p.compare("linear")==0) {//elegxo ean to stixio einai i leksi linear
				 z = i;//vazo to z iso me to i gia na elekso efoson to filtro einai to linear ean eina ta epomena 6 stoixeia arithmi
				 for (int j = 0; j < 6; j++) {//ena for gia ton elegxo
					
					 if (isdigit(*argv[++z]) < 0) {//kathe fora elegxo ean to stoixeio einai arithmos xoris na pirakso to i
						 cerr << "Wrong parameters for linear filter" << endl;//ean den einai tipono minima lathous
						 return 0;//kai termatizo
					 }
				 }
					Color a(atof(argv[++i]),atof(argv[++i]), atof(argv[++i]));//dimiourgo to antikeimeno to a tipou color p tha xrisimopioithi sto filtro
					Color c(atof(argv[++i]), atof(argv[++i]), atof(argv[++i]));////dimiourgo to antikeimeno to a tipou color p tha xrisimopioithi sto filtro
					FilterLinear linear(a, c);//dimiourgo ena antikeimeno tipou filter linear to opio perni parametrousto a kai c
						eikona = linear << eikona;//kalo ton operator tis filter linear gia na epeksergasti tin eikona
					p = argv[i]; 
				}
				
				else if ( p.compare("gamma")==0) {//ean to stoixeio einai to gamma
					if (isdigit(*argv[++i])>0) //elegxo an to epomeno stoixeio eina arithmos
						g = (float)atof(argv[i]);//an einai to apothikevo stin metavliti g 
					if ( g<0.5 && g>2.0) {//elegxo an einai metaksi 0.5 kai 2
						cerr << "Wrong parameters for filter gamma" << endl;//an oxi tipono minima lathous
						return 0;//kai termatizo
					}
					else {
					FilterGamma gamma(g);//dimiourgo ena antikeimeno tipou filter gamma me parametro g
					eikona =gamma<< (eikona);//kalo ton operator tis filter gamma gia na efarmosi to filtro stin eikona
					}
				}
				else { cout << "The name of filter does not exist" << endl; return 0; }//ean ta onomata einai lathos tipono minima lathous kai termatizi
			}
			else { cerr << "You must be give filters for the picture" << endl;  return 0; }//ean ta orismata einai ligotera apo 2 tipono minima lathous kai termatizi
		}
		
		filename = filename.substr(0,filename.length()-7)+"filtered_" + filename.substr(filename.length()-7,7);//apokopto sigkekrimena to onoma tou arxiou kai vazo metaksi tou path kai tou onomatos tin prothesi filtered_
		
		if (!eikona.save(filename, kataliksi)) {//kalo tin save gia na apothikefsi tin eikona
			cerr << "Program cannot write the image" << endl;//an apotixi tipono minima lathous 
			return 0;//kai termatizo
		}
	}
	else {
		cerr << "Agruments is less " << endl;//an edose lathos parametrous kata tin ektelesi tou programmatos apo to cmd ou tipono minima lathous
	}
	system("pause");
	return 0;

}