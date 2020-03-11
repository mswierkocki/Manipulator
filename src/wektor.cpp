#include "wektor.h"

std::ostream& operator << (std::ostream &Swyj, Wektor W){

	return Swyj<<"("<<W.x<<","<<W.y<<")";
}

std::istream& operator >>(std::istream &Swej, Wektor& W){
	char z;
	Swej>>z;
	if(z!='('){
	Swej.setstate(std::ios::failbit);
	return Swej;
}
	Swej>>W.x;
	Swej>>z;
	if(z !=','){
	Swej.setstate(std::ios::failbit);
	return Swej;
}
	Swej>>W.y;
	Swej>>z;
	if(z !=')'){
	Swej.setstate(std::ios::failbit);
	return Swej;
}

	return Swej;
}
Wektor Wektor::operator+(Wektor W){
	return Wektor(x+W.x,y+W.y);
}