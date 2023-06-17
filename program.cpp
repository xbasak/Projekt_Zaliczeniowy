#include "program.h"
#include "klient.h"
#include "zamowienie.h"
#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include <ctime>
using namespace std;

void program::menu()
{
    char buffer[30];
    string data;
    ofstream plik;
    plik.open("C:/Users/Arek/Desktop/Projekt/klienci.txt");
    if (plik.is_open())
    {
        plik<<"NR\tPLEC\tIMIE\tNAZWISKO\tADRES\t"<<endl;
    }
    plik.close();
    int nrK=0;
    int nrZ=100;
    int nrKZ = 0;
    cout<<"NR\tFUNKCJA"<<endl
       <<"1)\tDodaj klienta"<<endl
      <<"2)\tModyfikuj istniejacego klienta"<<endl
     <<"3)\tWyswietl dostepne produkty"<<endl
    <<"4)\tZloz zamowienie"<<endl
    <<"5)\tEdytuj zamowienie"<<endl
    <<"6)\tWyswietl liste zamowien"<<endl
    <<"7)\tZapisz klientow do plikow"<<endl
    <<"8)\tZapisz zamowienia do plikow"<<endl
    <<"9)\tWyjdz z programu"<<endl<<endl;
    int x=0;
    string imie,nazwisko,plec,adres;
    string nazwa,platnosc;
    float ilosc;
    while(x!=9)
    {
        cout<<"***Wybierz numer zadania ktore chcesz wykonac: ";cin>>x;cout<<endl;
        switch(x)
        {
        case 1:
        {
            nrK+=1;
            cout<<"Podaj plec(kobieta/mezczyzna): "; cin>>plec;
            cout<<"Podaj imie: "; cin>>imie;
            cout<<"Podaj nazwisko: "; cin>>nazwisko;cin.ignore();
            cout<<"Podaj adres: "; getline(cin,adres);cin.ignore();
            cout<<endl;
            dodajKlienta(nrK,plec,imie,nazwisko,adres);
        } break;
        case 2: break;
        case 3: wyswietlProdukty(); break;
        case 4:
        {
            time_t CurrentTime = time(nullptr);
            tm* Czas1 = localtime(&CurrentTime);
            strftime(buffer, sizeof(buffer),"%d-%m-%Y %H:%M",Czas1);
            data = buffer;
            nrZ+=1;
            cout<<"Podaj nr Klienta dla ktorego skladasz zamowienie: ";cin>>nrKZ;
            cout<<"Podaj nazwe produktu: "; cin>>nazwa;
            cout<<"Podaj ilosc: ";cin>>ilosc;
            cout<<"Podaj sposob platnosci:(karta/gotowka): ";cin>>platnosc;
            dodajZamowienie(nrZ,nrKZ,nazwa,ilosc,data,platnosc);
        } break;
        case 5: break;
        case 6: wyswietlZamowienia(zakupy);break;
        case 7: klientDoPliku(klienci); break;
        case 8: break;
        case 9: exit(0); break;
        default:
            cout<<"*ZLY NUMER*"<<endl<<endl;
        }
    }
}

void program::dodajKlienta(int nrK,string plec, string imie, string nazwisko, string adres)
{
    klient nowy(nrK,plec, imie, nazwisko, adres);
    klienci.push_back(nowy);
}

void program::dodajZamowienie(int nrZ, int nrKZ, string nazwa, float ilosc, string data,string platnosc)
{
    int nrP;
    ifstream plik1;
    plik1.open("C:/Users/Arek/Desktop/Projekt/Lista.txt");
    string nazwaProduktu,zmienna;
    float iloscProduktow, cenaProduktu,cena,vat,wartosc;
    getline(plik1,zmienna);
    cout<<nazwaProduktu<<endl;
    for(int i=0; i<15;i++)
    {
        plik1>>nrP>>nazwaProduktu>>iloscProduktow>>cenaProduktu;
        if(nazwa == nazwaProduktu)
        {
            cena = cenaProduktu;
            vat = 0.23*cena;
            wartosc += ilosc*cena;
        }
    }
    zamowienie nowe(nrZ,nrKZ,nazwa,ilosc,wartosc,vat,data,platnosc);
    zakupy.push_back(nowe);
}

void program::klientDoPliku(vector<klient> klienci)
{
    ofstream plik;
    plik.open("C:/Users/Arek/Desktop/Projekt/klienci.txt");
    if (plik.is_open()) {
        cout << "Zapisuje do pliku" << endl;
        for (auto zmienna: klienci)
        {
            plik<<zmienna.returnNrK()<<"\t"<<zmienna.returnPlec()<<"\t"<<zmienna.returnImie()<<"\t"
               <<zmienna.returnNazwisko()<<"\t"<<zmienna.returnAdres()<<"\t"<<endl;
        }
    }
    plik.close();
    ofstream plik3;
    int i=0;
    plik3.open("C:/Users/Arek/Desktop/Projekt/klienciBin.txt", ios_base::out | ios::binary);

    for (auto klient: klienci)
    {
        i++;
        int a = klient.returnNrK(); plik3.write(reinterpret_cast<char *>(&a), sizeof(i));
        string b = klient.returnPlec(); plik3.write(reinterpret_cast<char *>(&b), sizeof(i));
        string c = klient.returnImie(); plik3.write(reinterpret_cast<char *>(&c), sizeof(i));
        string d = klient.returnNazwisko(); plik3.write(reinterpret_cast<char *>(&d), sizeof(i));
        string e = klient.returnAdres(); plik3.write(reinterpret_cast<char *>(&e), sizeof(i));
    }
}

void program::wyswietlZamowienia(vector<zamowienie> zakupy)
{
    ofstream plik2;
    plik2.open("C:/Users/Arek/Desktop/Projekt/zamowienia.txt");
    cout<<endl<<"ZAMOWIENIA:"<<endl;
    cout<<"Nr-Zamowienia\tNr-Klienta\tNazwa\tWartosc-Zamowien\tStawka-VAT\tData-Zamowienia\tSposob-Platnosci"<<endl;
    for(auto zmienna: zakupy)
    {
        cout<<zmienna.returnNrZ()<<"\t\t"<<zmienna.returnNrKZ()<<"\t\t"<<zmienna.returnNazwa()<<"\t\t"
           <<zmienna.returnWartosc()<<"\t\t"<<zmienna.returnVat()<<"\t\t"<<zmienna.returnData()<<"\t"<<zmienna.returnPlatnosc()<<endl;
        plik2<<zmienna.returnNrZ()<<"\t\t"<<zmienna.returnNrKZ()<<"\t\t"<<zmienna.returnNazwa()<<"\t\t"
            <<zmienna.returnWartosc()<<"\t\t"<<zmienna.returnVat()<<"\t\t"<<zmienna.returnData()<<"\t"<<zmienna.returnPlatnosc()<<endl;
    }
    plik2.close();
    ofstream plik4;
    int i=0;
    plik4.open("C:/Users/Arek/Desktop/Projekt/zamowieniaBin.txt", ios_base::out | ios::binary);

    for (auto zamowienie: zakupy)
    {
        i++;
        int a = zamowienie.returnNrZ(); plik4.write(reinterpret_cast<char *>(&a), sizeof(i));
        int b = zamowienie.returnNrKZ(); plik4.write(reinterpret_cast<char *>(&b), sizeof(i));
        string c = zamowienie.returnNazwa(); plik4.write(reinterpret_cast<char *>(&c), sizeof(i));
        float d = zamowienie.returnWartosc(); plik4.write(reinterpret_cast<char *>(&d), sizeof(i));
        float e = zamowienie.returnVat(); plik4.write(reinterpret_cast<char *>(&e), sizeof(i));
        string f = zamowienie.returnData(); plik4.write(reinterpret_cast<char *>(&f), sizeof(i));
        string g = zamowienie.returnPlatnosc(); plik4.write(reinterpret_cast<char *>(&g), sizeof(i));
    }
    plik4.close();
}

void program::wyswietlProdukty()
{
    ifstream plik1;
    plik1.open("C:/Users/Arek/Desktop/Projekt/Lista.txt");
    string zmienna;
    string zmienna1;
    while(getline(plik1,zmienna))
    {
        zmienna1 = zmienna;
        cout<<zmienna1<<endl;
    }
    plik1.close();
    cout<<endl;
}

