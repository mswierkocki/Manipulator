#include "scena.h"
using namespace std;

Scena::Scena(void){
	int IloscPrzegubow;
	float X= 0,Y = 0;
	if(cfg.readFile("config.ini")==0){ 
	if(!cfg.getValue("default","axes",&IloscPrzegubow))
		IloscPrzegubow = 3;
	
	if(!cfg.getValue("default","length",&manipulator.DOMYSLNADLUGOSCPRZEGUBU))
		manipulator.DOMYSLNADLUGOSCPRZEGUBU = 5;

	if(!cfg.getValue("default","angle",&manipulator.DOMYSLNYKAT))
		manipulator.DOMYSLNYKAT = 75;
	
	if(!cfg.getValue("default","x",&X))
		X = 0;
	if(!cfg.getValue("default","y",&Y))
		Y = 0;
	if(!cfg.getValue("basic","omega",&omega))
		omega = 1;
	if(!cfg.getValue("basic","start",&idObecnegoPrzegubu))
		idObecnegoPrzegubu = 0;

	}
	else{
		cfg.addEntry("default","axes","3");
		cfg.addEntry("default","length","5");
		cfg.addEntry("default","angle","75");
		cfg.addEntry("default","x","0");
		cfg.addEntry("default","y","0");
		cfg.addEntry("basic","omega","0.1");
		cfg.addEntry("basic","start","0");
		cfg.saveEntry("config.ini");
		cout<<"Ponowne uruchomienie programu skorzysta z pliku konfiguracyjnego"<<endl;
	IloscPrzegubow = 3;
	manipulator.DOMYSLNADLUGOSCPRZEGUBU = 5;
	manipulator.DOMYSLNYKAT = 75;
	omega = 0.1;
	idObecnegoPrzegubu = 0;
	}


	manipulator.setPoczatek(Wektor(X,Y));
	for(int i = 0; i<IloscPrzegubow;i++){
		manipulator.dodajPrzegub();
	}
	manipulator.setIloscPrzegubow(IloscPrzegubow);
}
bool Scena::zapiszStatus(std::string nazwaPliku){
	fstream fs;
	fs.open(nazwaPliku.c_str(),ios::in |ios::out| ios::trunc);
	vector<Przegub> TabPrz = manipulator.getTabPrzegobow();
	fs<<manipulator.getPoczatek()<<endl;
	for(int i = 0;i<TabPrz.size();i++){
		fs<<TabPrz[i].getpoczatek()<<" "<<TabPrz[i].getkoniec()<<endl;
	}

	return true;
}
bool Scena::wczytajStatus(std::string nazwaPliku){
	fstream fs;
	Wektor w;
	fs.open(nazwaPliku.c_str(),ios::out|ios::in);
	if(!fs.is_open())
		return false;
	fs>>w;
	manipulator.setPoczatek(w);
	while(!fs.eof()){
	fs>>w;

	}

	return true;
}

void Scena::WypiszHUD(){
	manipulator.obliczWspolrzedne();
	cout<<"Aktualne wspolrzedne i parametry:"<<endl;
	vector<Przegub> TabPrz = manipulator.getTabPrzegobow();
	int i;
	for(i = 0; i<TabPrz.size();i++){
		cout<<"Ogniwo:"<<i;
		cout<<"\t Dlugosc"<<":"<<TabPrz[i].getDlugosc();
		cout<<"\t q"<<i<<":" <<TabPrz[i].getKat();
		cout<<"\t Pocz"<<TabPrz[i].getpoczatek();
		cout<<"\t Kon"<<TabPrz[i].getkoniec();
		cout<<endl;
	}
	cout<<"\t\t\t\t\t Efektor"<<manipulator.getEfektor()<<endl;
	
}
void Scena::Menu(){
	cout<<"z - Zmien parametr wybranego przegubu"<<endl;
	cout<<"a - Dodaj Przegub"<<endl;
	cout<<"d - Usun Przegub"<<endl;
	cout<<"s - Symulacja" << endl;
	cout<<"? - ponowne wyswietlenie menu"<<endl;
	cout<<"k - koniec programu"<<endl;	
}
void Scena::DodajPrzegub(){
	float dl,kat;
	cout<<"Podaj dlugosc przegubu: ";
	cin>>dl;
	cout<<"Podaj kat przegubu: ";
	cin>>kat;
	manipulator.dodajPrzegub(dl,kat);
	manipulator.setIloscPrzegubow(manipulator.getIloscPrzegubow()+1);
	
}
void Scena::UsunPrzegub(){
	int ilosc = manipulator.getIloscPrzegubow();
	if(ilosc>0){
		char z='x';
		cout<<"Czy na pewno chcesz usunac ostatni przegub? (t)ak/(n)ie > ";
		while((z!='t')&&(z!='n'))cin>>z;
		if(z=='t'){
			manipulator.usunPrzegub();
			manipulator.setIloscPrzegubow(ilosc-1);
		}
	}
}
void Scena::ZmianaParametru(){
	int ktory=-1;
	char znak = 'x';
	int ilosc = manipulator.getIloscPrzegubow();
	float wartosc;

	if(ilosc!=0){
		cout<<"Zmiana ktorego przegubu?(0,"<<ilosc-1<<") > "<<endl;
		while(ktory<0||ktory>=ilosc)
			cin>>ktory;
		cout<<"Chcesz zmienic (d)lugosc czy (k)at? > ";
		while(znak!='k'&&znak!='d')
			cin>>znak;
		if(znak=='d'){
			cout<<"Podaj zadana dlugosc > ";
			cin>>wartosc;
			manipulator.getPrzegub(ktory).setDlugosc(wartosc);
		}
		if(znak=='k'){
			cout<<"Podaj zadana kat > ";
			cin>>wartosc;
			manipulator.getPrzegub(ktory).setKat(wartosc);
		}
	}
	else cout<<"Nie ma przegubow :("<<endl;

}





int GLFWCALL Close(){
	glfwTerminate();
	return GL_TRUE;
}
void GLFWCALL My_Key_Callback(int key, int action)
{
	  if( !scena )
      return;
	  scena->keyListener(key, (action==GLFW_PRESS) );
   
}
 

GLboolean Scena::inicjujGl()
{
	
	
	glfwInit();
	glfwOpenWindow(800,600,8,8,8,0,0,0,GLFW_WINDOW);
	glfwSetWindowTitle("Symulacja");
	glfwSetWindowCloseCallback(Close);
	glfwSetKeyCallback(My_Key_Callback);
	
	camX=camY=camZ = 1.0f;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,8.0f/6.0f,0.1f,1000);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glLoadIdentity();
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glfwEnable(GLFW_KEY_REPEAT);
	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glClearDepth(1.0f);            //Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);       //Enables Depth Testing
    glDepthFunc(GL_LEQUAL);        //The type of depth test to do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return GL_TRUE;				  // Initialization Went OK
}



void Scena::Symulacja(){
	cout<<"Startuje symulacje"<<endl;
	bool koniec = false;
	x = y= 0.0f;
	if(inicjujGl()==GL_FALSE)
		koniec = true;
	while((glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS)&&koniec==false){
		
		if(glfwGetWindowParam(GLFW_OPENED)==GL_FALSE)
			koniec = true;
		rysujScene();
		glfwSwapBuffers();
		glfwSleep(1.0/80);
	}
	
	Close();
	glfwCloseWindow();
	cout<<"Koniec symulacji"<<endl;
}

GLint Scena::rysujScene(){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//reset view matrix
		glLoadIdentity();
		gluLookAt(camX+100,camY+30,-30,0,0,0,0,1,0);	
		static float a = 2;
	
		//antialiasing
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POINT_SMOOTH);


		glLineWidth(6);

		glPointSize(12);
		vector<Przegub> TabPrz = manipulator.getTabPrzegobow();

		for(int i=0; i<TabPrz.size(); i++)
		{
			
			if(i==idObecnegoPrzegubu) glColor3f(1,0,0);
			else glColor3f(1,1,1);
			
			glBegin(GL_LINES);
				glVertex3f(TabPrz[i].getpoczatek().x,TabPrz[i].getpoczatek().y,0);
				glVertex3f(TabPrz[i].getkoniec().x,TabPrz[i].getkoniec().y,0);
			glEnd();

			glBegin(GL_POINTS);
				glVertex3f(TabPrz[i].getpoczatek().x,TabPrz[i].getpoczatek().y,0);
			glEnd();
			glColor3f(0,1,0);
			
			glBegin(GL_POINTS);
				glVertex3f(TabPrz[i].getkoniec().x,TabPrz[i].getkoniec().y,0);
			glEnd();
		}


		glLineWidth(2);
		glColor3f(0,1,0);
		glBegin(GL_LINES);
		glVertex3f(-100,0,0);
		glVertex3f(100,0,0);
		glVertex3f(0,-100,0);
		glVertex3f(0,100,0);
		glVertex3f(0,0,-100);
		glVertex3f(0,0,100);

		glEnd();

		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		return 0;
}
void Scena::keyListener(int key, bool s){
	int ilosc = manipulator.getIloscPrzegubow();
	static float x = 0,y = 0,z = 0;
 if (key == 'A' && s == GLFW_PRESS){
	 idObecnegoPrzegubu += 1;
}
if (key == 'S' && s == GLFW_PRESS){
	 manipulator.getPrzegub(idObecnegoPrzegubu).appKat(-omega);
 }
if (key == 'D' && s == GLFW_PRESS){
idObecnegoPrzegubu-=1;
 }
 if (key == 'W' && s == GLFW_PRESS){
	 manipulator.getPrzegub(idObecnegoPrzegubu).appKat(omega);
 }
 if (key == GLFW_KEY_UP && s == GLFW_PRESS){
	 camX+=1;
 }
 if (key == GLFW_KEY_DOWN && s == GLFW_PRESS){ camX-=1; }
 if (key == GLFW_KEY_LEFT && s == GLFW_PRESS){ camY +=1;}
 if (key == GLFW_KEY_RIGHT && s == GLFW_PRESS){ camY-=1;}

 manipulator.obliczWspolrzedne();
 if(idObecnegoPrzegubu>=ilosc)idObecnegoPrzegubu-=ilosc;
 if(idObecnegoPrzegubu<0)idObecnegoPrzegubu+=ilosc;
}

