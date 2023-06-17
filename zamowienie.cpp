#include "zamowienie.h"
zamowienie::zamowienie(int nrZ, int nrKZ, string nazwa, float ilosc,float wartosc, float vat,string data, string platnosc)
{
    this->nrZ=nrZ;
    this->nazwa=nazwa;
    this->ilosc=ilosc;
    this->wartosc=wartosc;
    this->vat=vat;
    this->nrKZ=nrKZ;
    this->data=data;
    this->platnosc = platnosc;
}

int zamowienie::returnNrZ()
{
    return nrZ;
}

int zamowienie::returnNrKZ()
{
    return nrKZ;
}

string zamowienie::returnNazwa()
{
    return nazwa;
}

float zamowienie::returnIlosc()
{
    return ilosc;
}

float zamowienie::returnWartosc()
{
    return wartosc;
}

float zamowienie::returnVat()
{
    return vat;
}

string zamowienie::returnData()
{
    return data;
}

string zamowienie::returnPlatnosc()
{
    return platnosc;
}


