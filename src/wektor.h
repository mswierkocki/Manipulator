#pragma once
#include <iostream>
class Wektor
{
public:
	float x,y;
	Wektor(void){ x= 0; y=0;}
	Wektor(float _x, float _y){x = _x;y=_y;}
	friend std::ostream& operator << (std::ostream &Swyj, Wektor W);
	friend std::istream& operator >> (std::istream &Swej, Wektor& W);
	Wektor operator +(Wektor W);
};

