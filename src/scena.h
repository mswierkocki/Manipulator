#pragma once
#include "manipulator.h"
#include "iniparser.h"
#include "GL\glfw.h"
#include <gl\GLU.h>
#include <cstdlib>
#include <iostream>
#include <stdarg.h>


class Scena
{
private:
	IniParser cfg;
	Manipulator manipulator;
	float omega; // Speed of Joint
	int idObecnegoPrzegubu;
public:
	Scena(void);
	~Scena(void){zapiszStatus("manipulator.cfg");}
	bool wczytajStatus(const std::string nazwaPliku);
	bool zapiszStatus(const std::string nazwaPliku);

	void WypiszHUD();
	void Menu();
	void DodajPrzegub();
	void UsunPrzegub();
	void ZmianaParametru();

	void Symulacja();
	GLboolean inicjujGl();
	GLint rysujScene();
	void keyListener(int key, bool s);

	float x,y;
	float camX,camY,camZ;
};
extern Scena *scena;

