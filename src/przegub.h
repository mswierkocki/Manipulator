#pragma once
#include "wektor.h"

class Przegub
{
private:
	float dlugosc;
	float kat;
	Wektor koniec;
	Wektor poczatek;
public:
    Przegub():dlugosc(0),kat(0){}
	void setDlugosc(float d){dlugosc = d;}
	float getDlugosc(){return dlugosc;}
	void setKat(float k){kat=k;}
	void appKat(float k){kat+=k;}
	float getKat(){return kat;}
	void setkoniec(Wektor W){koniec = W;}
	void setkoniec(float x,float y){koniec.x = x;koniec.y = y;}
	void setpoczatek(Wektor W){poczatek=W;}
	void setpoczatek(float x,float y){poczatek.x = x;poczatek.y = y;}
	Wektor getpoczatek(){return poczatek;}
	Wektor getkoniec(){return koniec;}
	Wektor ObliczPolozenie(Wektor P);

};

