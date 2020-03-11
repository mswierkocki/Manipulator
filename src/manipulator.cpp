#include "manipulator.h"
#include <string>

Manipulator::Manipulator(void){
	TabPrzegubow.reserve(32);
}

void Manipulator::dodajPrzegub(float dl, float kat){
	Przegub p;
	p.setDlugosc(dl);
	p.setKat(kat);
	TabPrzegubow.push_back(p);
}
void Manipulator::dodajPrzegub(){
	dodajPrzegub(DOMYSLNADLUGOSCPRZEGUBU,DOMYSLNYKAT);
}
void Manipulator::usunPrzegub(){
	TabPrzegubow.pop_back();
}
void Manipulator::obliczWspolrzedne(){
	int Ilosc = getIloscPrzegubow();
	Wektor _old,_new;
	float a = 0,l;
	
	if (Ilosc==0){
		efektor = _new;
		
		return;
	}
	
	TabPrzegubow[0].setpoczatek(poczatek);
	for(int i = 0;i<TabPrzegubow.size();i++){
		
		_old = TabPrzegubow[i].getpoczatek();
		a += TabPrzegubow[i].getKat();
		l = TabPrzegubow[i].getDlugosc();
		_new= Wektor(_old.x+l * cosf(a * 3.141592f/180),_old.y+l * sinf(a * 3.141592f/180));
		TabPrzegubow[i].setkoniec(_new);
		if(i==Ilosc-1)
			efektor = _new;
		else
		TabPrzegubow[i+1].setpoczatek(_new);
	}
	
}