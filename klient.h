#ifndef KLIENT_H
#define KLIENT_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class klient
{
public:
    string imie;
    string nazwisko;
    string plec;
    string adres;
    int nrK;
    klient(int nrK,string plec, string imie, string nazwisko, string adres);
    string returnPlec();
    string returnImie();
    string returnNazwisko();
    string returnAdres();
    int returnNrK();
    klient();
};

#endif // KLIENT_H
