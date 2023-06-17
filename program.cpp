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
    int nrK=0;
    int nrZ=100;
    int nrKZ = 0;
    cout<<"NR\tFUNKCJA"<<endl
       <<"1)\tDodaj klienta"<<endl
      <<"2)\tModyfikuj istniejacego klienta"<<endl
     <<"3)\tWyswietl dostepne produkty"<<endl
    <<"4)\tZloz zamowienie"<<endl
    <<"5)\tEdytuj zamowienia"<<endl
    <<"6)\tWyswietl liste zamowien"<<endl
    <<"7)\tZapisz klientow do plikow"<<endl
    <<"8)\tWyjdz z programu"<<endl<<endl;
    int x=0;
    string imie,nazwisko,plec,adres;
    string nazwa,platnosc;
    float ilosc;
    while(x!=8)
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
            cout<<"Podaj adres: "; getline(cin,adres);
            cout<<endl;
            dodajKlienta(nrK,plec,imie,nazwisko,adres);
        } break;
        case 2:
        {
            string tak;
            int wyjscie1=1;
            int opcjaK=0;
            cout<<"Podaj nr klienta, ktorego chcesz edytowac: ";cin>>nrZ;cout<<endl;
            while(wyjscie1==1)
            {
                cout<<"Wybierz pole do edycji:\n\n1>Plec\n2>Imie\n3>Nazwisko\n4>Adres\n>:";cin>>opcjaK;
                edytujKlienta(klienci,opcjaK,nrK);
                cout<<"Czy chcesz zmienic cos jeszcze?(tak/nie): ";cin>>tak;
                if(tak!="tak")
                {
                    wyjscie1=0;
                }

            }
        }break;
        case 3: wyswietlProdukty(); break;
        case 4:
        {
            time_t CurrentTime = time(nullptr);
            tm* Czas = localtime(&CurrentTime);
            strftime(buffer, sizeof(buffer),"%d-%m-%Y %H:%M",Czas);
            data = buffer;
            nrZ+=1;
            cout<<"Podaj nr Klienta dla ktorego skladasz zamowienie: ";cin>>nrKZ;
            cout<<"Podaj nazwe produktu: "; cin>>nazwa;
            cout<<"Podaj ilosc: ";cin>>ilosc;
            cout<<"Podaj sposob platnosci:(karta/gotowka): ";cin>>platnosc;
            dodajZamowienie(nrZ,nrKZ,nazwa,ilosc,data,platnosc);
        } break;
        case 5:
        {
            string tak;
            int wyjscie1=1;
            int opcjaZ=0;
            cout<<"Podaj nr zamowienia, ktore chcesz edytowac: ";cin>>nrZ;cout<<endl;
            while(wyjscie1==1)
            {
                cout<<"Wybierz pole do edycji:\n\n1>Nazwa[rodzaj produktu]\n2>Ilosc\n3>Sposob Platnosci\n>:";cin>>opcjaZ;
                edytujZamowienie(zakupy,opcjaZ,nrZ);
                cout<<"Czy chcesz zmienic cos jeszcze?(tak/nie): ";cin>>tak;
                if(tak!="tak")
                {
                    wyjscie1=0;
                }
            }
        }; break;
        case 6: wyswietlZamowienia(zakupy);break;
        case 7: klientDoPliku(klienci); break;
        case 8: exit(0); break;
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
            vat = ilosc*(0.23*cena);
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
    cout<<"Nr-Zamowienia\tNr-Klienta\tNazwa\tIlosc\tWartosc-Zamowien\tStawka-VAT\tData-Zamowienia\tSposob-Platnosci"<<endl;
        for(auto &zmienna: zakupy)
        {
            cout<<zmienna.returnNrZ()<<"\t\t"<<zmienna.returnNrKZ()<<"\t\t"<<zmienna.returnNazwa()<<"\t"
               <<zmienna.returnIlosc()<<"\t\t"<<zmienna.returnWartosc()<<"\t\t"<<zmienna.returnVat()<<"\t\t"<<zmienna.returnData()<<"\t"<<zmienna.returnPlatnosc()<<endl;
            plik2<<zmienna.returnNrZ()<<"\t\t"<<zmienna.returnNrKZ()<<"\t\t"<<zmienna.returnNazwa()<<"\t\t"
                <<zmienna.returnWartosc()<<"\t\t"<<zmienna.returnVat()<<"\t\t"<<zmienna.returnData()<<"\t"<<zmienna.returnPlatnosc()<<endl;
        }
        cout<<endl;
//    for(int k=0;k<zakupy.size();k++)
//    {
//        cout<<zakupy[k].nrZ<<"\t\t"<<zakupy[k].nrKZ<<"\t\t"<<zakupy[k].nazwa<<"\t"
//           <<zakupy[k].ilosc<<"\t\t"<<zakupy[k].wartosc<<"\t\t"<<zakupy[k].vat<<"\t\t"<<zakupy[k].data<<"\t"<<zakupy[k].platnosc<<endl;
//        plik2<<zakupy[k].nrZ<<"\t\t"<<zakupy[k].nrKZ<<"\t\t"<<zakupy[k].nazwa<<"\t"
//            <<zakupy[k].ilosc<<"\t\t"<<zakupy[k].wartosc<<"\t\t"<<zakupy[k].vat<<"\t\t"<<zakupy[k].data<<"\t"<<zakupy[k].platnosc<<endl;
//    }
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

void program::edytujKlienta(vector<klient> &klienci, int opcjaK,int nrK)
{
    int k = nrK-1;
    string nowaPlec, noweImie, noweNazwisko, nowyAdres;
    if(opcjaK == 1)
    {
        cout<<"Podaj inna plec: ";cin>>nowaPlec;
        klienci[k].plec = nowaPlec;
    }
    else if(opcjaK == 2)
    {
        cout<<"Podaj inne imie: ";cin>>noweImie;
        klienci[k].imie = noweImie;
    }
    else if(opcjaK == 3)
    {
        cout<<"Podaj inne nazwisko ";cin>>noweNazwisko;
        klienci[k].nazwisko = noweNazwisko;
    }
    else if(opcjaK == 4)
    {
        cin.ignore();
        cout<<"Podaj innay adres: ";
        getline(cin,nowyAdres);
        klienci[k].adres = nowyAdres;
    }

}

void program::edytujZamowienie(vector<zamowienie> &zakupy,int opcjaZ,int nrZ)
{
    ifstream plik5;
    int nr;
    plik5.open("C:/Users/Arek/Desktop/Projekt/Lista.txt");
    string nazwaProduktu,zmienna;
    float iloscProduktow, cenaProduktu;
    string zmianaProduktu;
    string zmianaPlatnosci;
    int zmianaIlosci;
    getline(plik5,zmienna);
    cout<<nazwaProduktu<<endl;
    int k=nrZ-101;
    if(opcjaZ==1)
    {
        cout<<"Podaj nowy produkt: ";cin>>zmianaProduktu;
        for(int i=0; i<15;i++)
        {
            plik5>>nr>>nazwaProduktu>>iloscProduktow>>cenaProduktu;
            if(nazwaProduktu == zmianaProduktu)
            {
                zakupy[k].nazwa = zmianaProduktu;
                cout<<"Podaj ilosc:  "; cin>>zmianaIlosci;
                zakupy[k].ilosc = zmianaIlosci;
                zakupy[k].wartosc = zmianaIlosci * cenaProduktu;
                zakupy[k].vat = 0;
                zakupy[k].vat = zmianaIlosci*(0.23*cenaProduktu);
//                cout<<zakupy[k].nrZ<<"\t\t"<<zakupy[k].nrKZ<<"\t\t"<<zakupy[k].nazwa<<"\t"
//                   <<zakupy[k].ilosc<<"\t\t"<<zakupy[k].wartosc<<"\t\t"<<zakupy[k].vat<<"\t\t"<<zakupy[k].data<<"\t"<<zakupy[k].platnosc<<endl;
                break;
            }
        }
    }
    else if(opcjaZ == 2)
    {
        for(int i=0;i<15;i++)
        {
            plik5>>nr>>nazwaProduktu>>iloscProduktow>>cenaProduktu;
            if(nazwaProduktu == zakupy[k].nazwa)
            {
                cout<<"Podaj nowa ilosc: ";cin>>zmianaIlosci;
                zakupy[k].ilosc = zmianaIlosci;
                zakupy[k].wartosc = zmianaIlosci*cenaProduktu;
            }
        }
    }
    else if(opcjaZ == 3)
    {
        for(int i=0; i<15;i++)
        {
            plik5>>nr>>nazwaProduktu>>iloscProduktow>>cenaProduktu;
            if(nazwaProduktu == zakupy[k].nazwa)
            {

                cout<<"Podaj nowy sposob platnosci:(karta/gotowka): ";cin>>zmianaPlatnosci;
                zakupy[k].platnosc = zmianaPlatnosci;

            }
        }
    }
    plik5.close();
}

