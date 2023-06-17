#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H
#include <iostream>
#include <string>
#include <vector>
//#include "klient.h"
using namespace std;

class zamowienie
{
public:

    int nrZ;
    int nrKZ;
    string nazwa,data,platnosc;
    float cena,vat,wartosc,ilosc;
    zamowienie(int nrZ, int nrKZ, string nazwa, float ilosc,float wartosc, float vat,string data,string platnosc);
    int returnNrZ();
    int returnNrKZ();
    string returnNazwa();
    float returnIlosc();
    float returnWartosc();
    float returnVat();
    string returnData();
    string returnPlatnosc();

};

#endif // ZAMOWIENIE_H
