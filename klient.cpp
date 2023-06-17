#include "klient.h"
#include <vector>
#include <iostream>
using namespace std;

klient::klient(int nrK,string plec, string imie, string nazwisko, string adres)
{
    this->nrK=nrK;
    this->plec=plec;
    this->imie=imie;
    this->nazwisko=nazwisko;
    this->adres=adres;
}

string klient::returnPlec()
{
    return plec;
}

string klient::returnImie()
{
    return imie;
}

string klient::returnNazwisko()
{
    return nazwisko;
}

string klient::returnAdres()
{
    return adres;
}

int klient::returnNrK()
{
    return nrK;
}
