#include <iostream>
#include <conio.h> // getch ()
#include <cstdlib>  //system (CLS)
#include <time.h>  //srand
#include <windows.h> //spanko i idzdoxy


using namespace std;

void idzdoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X=x;
    dwPos.Y=y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}


int szerokosc; int wysokosc;

int cokolwiek (int &x)
{
    cout << "Zmien dane!"<< endl;
    cout << "Drugiej szansy nie bêdzie :)" << endl;
    cin >> x;
    if (x<10 || x>40) x = 30;
}

int szybkosc;

int gora; int dol; int prawo; int lewo;
char pole[40][40];

int wspolzednaXweza;
int wspolzednaYweza;
int wspolzednaXjedzenia;
int wspolzednaYjedzenia;
int dlugosc=3;
int historiaWspolzednejX[10000];
int historiaWspolzednejY[10000];
int ile=0;
int klawisz;
char kierunek='p';
char waz=178;
char jablko=260;
char pd=188;
char pg=187;
char lg=201;
char ld=200;
char poz=205;
char pion=186;


int main()
{
    cout << "Podaj szerokosc planszy od 10 do 40:" << endl;
    cin >> szerokosc;
    if (szerokosc<10 || szerokosc>40) cokolwiek(szerokosc);

    cout << "Podaj wysokosc planszy od 10 do 40:" << endl;
    cin >> wysokosc;
    if (wysokosc<10 || wysokosc>40) cokolwiek(wysokosc);

    cout << "Podaj szybkosc  od 1 do 10:" << endl;
    cin >> szybkosc;
    if (szybkosc<1) szybkosc=1;
    if (szybkosc>10) szybkosc=10;

    cout << "Wybierz klawisze, do sterowania wezem:" << endl;
    cout << "Gora to:" << endl;
    gora=getch();
    if (gora==224)gora+=getch();
    if (gora==0)gora-=getch();

    cout << "Dol to:" << endl;
    dol=getch();
    if (dol==224)dol+=getch();
    if (dol==0)dol-=getch();

    cout << "Lewo to:" << endl;
    lewo=getch();
    if (lewo==224)lewo+=getch();
    if (lewo==0)lewo-=getch();

    cout << "Prawo to:" << endl;
    prawo=getch();
    if (prawo==224)prawo+=getch();
    if (prawo==0)prawo-=getch();

    //wartosci "p" tablicy

    for (int i=0 ; i<wysokosc ; i++)
    {
        for (int j=0 ; j<szerokosc ; j++)
        {
            pole[j][i]='p';
        }

    }

    srand(time(NULL)); //generator losowania

    wspolzednaXweza=rand()% szerokosc;
    wspolzednaYweza=rand()% wysokosc;

    pole[wspolzednaXweza][wspolzednaYweza]='w';

    do{
        wspolzednaXjedzenia=rand()% szerokosc;
        wspolzednaYjedzenia=rand()% wysokosc;
    }while (pole[wspolzednaXjedzenia][wspolzednaYjedzenia]!='p');

    pole[wspolzednaXjedzenia][wspolzednaYjedzenia]='j';

    system("CLS");
// rozpoczecie gry

        idzdoxy(0,0);
     //plansza
    // gorna

        cout << lg;
        for (int i=0; i<szerokosc ; i++)
        {
            cout << poz << poz;
        }
        cout << pg;

        for (int i=0; i<wysokosc ; i++)
        {
            cout << endl << pion;  // lewa ramka
            for (int j=0; j<szerokosc ; j++)
            {
                if(pole[j][i]=='p') cout << "  ";
                if(pole[j][i]=='w') cout << waz << waz;
                if(pole[j][i]=='j') cout << jablko << jablko;
            }
            cout << pion;  // prawa ramka
        }

        cout << endl;

    // dolna

        cout << ld;
        for (int i=0; i<szerokosc ; i++)
        {
            cout << poz << poz;
        }
        cout << pd;
//petla
    for (;;)
    {
        ile++;
        historiaWspolzednejX[ile]=wspolzednaXweza;
        historiaWspolzednejY[ile]=wspolzednaYweza;



        Sleep(1000/szybkosc); //czekaj- spanko

        if (kbhit())  //guziczki
        {
            klawisz=getch();
            if(klawisz==224)klawisz+=getch();
            if(klawisz==0)klawisz-=getch();

            if(klawisz==gora && (kierunek=='l' || kierunek=='p')) kierunek='g';
            if(klawisz==dol && (kierunek=='l' || kierunek=='p')) kierunek='d';
            if(klawisz==lewo && (kierunek=='g' || kierunek=='d')) kierunek='l';
            if(klawisz==prawo && (kierunek=='g' || kierunek=='d')) kierunek='p';

        }



        if (kierunek=='d') wspolzednaYweza++;
        if (kierunek=='g') wspolzednaYweza--;
        if (kierunek=='l') wspolzednaXweza--;
        if (kierunek=='p') wspolzednaXweza++;



        //waz przechodzi przez sciany
        if (wspolzednaXweza==szerokosc) wspolzednaXweza=0;
        if (wspolzednaXweza==-1) wspolzednaXweza=szerokosc-1;
        if (wspolzednaYweza==wysokosc) wspolzednaYweza=0;
        if (wspolzednaYweza==-1) wspolzednaYweza=wysokosc-1;

        //jak sie ugryzie
        if (pole[wspolzednaXweza][wspolzednaYweza]=='w')
        {
            idzdoxy(0, wysokosc+4);
            cout << endl << "\aKoniec gry, Twoja dlugosc weza to : " << dlugosc+1;
            break;
        }

        //jak zje
        if (pole[wspolzednaXweza][wspolzednaYweza]=='j')
        {
            dlugosc++;
            do{
                wspolzednaXjedzenia=rand()% szerokosc;
                wspolzednaYjedzenia=rand()% wysokosc;
                }while (pole[wspolzednaXjedzenia][wspolzednaYjedzenia]!='p');

            pole[wspolzednaXjedzenia][wspolzednaYjedzenia]='j';
            idzdoxy(wspolzednaXjedzenia*2+1,wspolzednaYjedzenia+1);
            cout << jablko << jablko;

        }
        else   //ogonek
        {
           pole[historiaWspolzednejX[ile-dlugosc]][historiaWspolzednejY[ile-dlugosc]]='p';
            idzdoxy(historiaWspolzednejX[ile-dlugosc]*2+1,historiaWspolzednejY[ile-dlugosc]+1);
            cout << "  ";
        }


        pole[wspolzednaXweza][wspolzednaYweza]='w';
        idzdoxy(wspolzednaXweza*2+1,wspolzednaYweza+1);
        cout << waz << waz;

    }  //koniec petli

    getch();
    getch();
    getch();
    return 0;
}
