#ifndef PROGRAM_H
#define PROGRAM_H
#include <iostream>
#include <string>
#include <vector>
//#include <fstream>
#include "zamowienie.h"
#include "klient.h"

using namespace std;

class program
{
public:
    void menu();
    void dodajKlienta(int nrK, string plec, string imie, string nazwisko, string adres);
    void dodajZamowienie(int nrZ,int nrKZ, string nazwa, float ilosc,string data,string platnosc);
    void klientDoPliku(vector<klient> klienci);
    void klientZPliku();
    void wyswietlZamowienia(vector<zamowienie> zakupy);
    void wyswietlProdukty();
    vector<klient> klienci;
    vector<zamowienie> zakupy;
    int opcjaK,opcjaZ;
    void edytujKlienta(vector<klient> klienci, int opcjaK,int nrK);
    void edytujZamowienie(vector<zamowienie> zakupy, int opcjaZ,int nrZ);
};

#endif // PROGRAM_H
