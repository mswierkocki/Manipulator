#include <stdio.h>
#define _NO_CRT_STDIO_INLINE
// VS 19 correction
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
#endif

#include "scena.h"

using namespace std;
Scena* scena;
#ifdef main
#undef main
#endif
int main(){
	scena = new Scena();
	bool koniec = false;
	char znak = '?';
	scena->wczytajStatus("manipulator.cfg");
	scena->Menu();
	while(!koniec){
		cout<<"Twoj wybor (? - menu)> ";
		cin>>znak;
		switch(znak){
			case 'z': scena->ZmianaParametru();
			break;
			case 'a': scena->DodajPrzegub();
			break;
			case 'd': scena->UsunPrzegub();
			break;
			case 's':scena->Symulacja();
			break;
			case 'k':koniec = true;
			break;
			case '?':break;
			default: cout<<"Niepoprawna opcja!"<<endl;
			break;
		}
		scena->WypiszHUD();
		if(znak=='?')
			scena->Menu();
	}	
	delete scena;
  return 0;
}