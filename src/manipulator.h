#pragma once
#include "Przegub.h"
#include <vector>
class Manipulator
{
private:
	std::vector<Przegub> TabPrzegubow;
	int IloscPrzegubow;
	Wektor poczatek;
	Wektor efektor;

public:
	float  DOMYSLNADLUGOSCPRZEGUBU;
	float  DOMYSLNYKAT;
	Manipulator(void);

	void setIloscPrzegubow(int n){IloscPrzegubow = n;}
	int getIloscPrzegubow(){ return IloscPrzegubow;}
	Wektor getPoczatek(){ return poczatek;}
	void setPoczatek(Wektor W){poczatek = W;}
	
	Wektor getEfektor(){ return efektor;}
	void setEfektor(Wektor W){efektor = W;}
	
	Przegub& getPrzegub(int n){return TabPrzegubow[n];}
	std::vector<Przegub>& getTabPrzegobow(){ return TabPrzegubow;}
	void dodajPrzegub();
	void dodajPrzegub(float dl, float kat);
	void usunPrzegub();
	void obliczWspolrzedne();
};

