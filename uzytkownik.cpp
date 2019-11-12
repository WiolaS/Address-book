#include <iostream>
#include "uzytkownik.h"
#include <cstdlib>
#include <fstream>
#include <vector>
#include <windows.h> // Sleep()
#include <conio.h> // getch()

using namespace std;

Uzytkownik::Uzytkownik(int identyfikatorr, string loginUzytkownikaa, string hasloUzytkownikaa ) {
    idUzytkownika = identyfikatorr;
    login = loginUzytkownikaa;
    haslo = hasloUzytkownikaa;
}

Uzytkownik::~Uzytkownik() {
    login.clear();
    haslo.clear();

}

string Uzytkownik::pobierzDoPionowejKreski (string danePobraneWJednejLinii, int pozycja) {
    string informacja = "";
    do {
        informacja += danePobraneWJednejLinii[pozycja];
        pozycja++;
    } while (danePobraneWJednejLinii[pozycja] != '|');

    return informacja;
}

int Uzytkownik::zamienStringNaInt (string tekst) {
    int liczba = atoi(tekst.c_str());
    return liczba;
}

void Uzytkownik::rozbijNaPojedynczeDaneUzytkownika (string pobraneWJednejLiniiDaneJednegoUzytkownika, Uzytkownik &daneUzytkownika) {
    string idTekst = "";
    for (int pozycja = 0; pozycja < pobraneWJednejLiniiDaneJednegoUzytkownika.length(); pozycja++) {

        idTekst = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoUzytkownika, pozycja);
        pozycja += (idTekst.length() + 1);  // plus 1 - pominiecie pionowej linii
        daneUzytkownika.idUzytkownika = zamienStringNaInt (idTekst);

        daneUzytkownika.login = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoUzytkownika, pozycja);
        pozycja += (daneUzytkownika.login.length() + 1);

        daneUzytkownika.haslo = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoUzytkownika, pozycja);
        pozycja += (daneUzytkownika.haslo.length() + 1);
    }
}

void Uzytkownik::odczytajZPlikuUzytkownik (vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik daneUzytkownika;
    string pobraneWJednejLiniiDaneJednegoUzytkownika = "";
    int nrUzytkownika = 0;

    fstream plik;
    plik.open(nazwaPlikuZUzytkownikami.c_str(), ios::in);

    if(plik.good() == true) {
        while(getline(plik,pobraneWJednejLiniiDaneJednegoUzytkownika)) {
            rozbijNaPojedynczeDaneUzytkownika (pobraneWJednejLiniiDaneJednegoUzytkownika, daneUzytkownika);
            uzytkownicy.push_back(daneUzytkownika);
        }
    }
    plik.close();
}

int Uzytkownik::logowanie (vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik daneUzytkownika;
    int liczbaUzytkownikow = uzytkownicy.size();

    cout << endl << "Podaj login: ";
    cin >> daneUzytkownika.login;

    int i = 0;
    while (i < liczbaUzytkownikow) {
        if (uzytkownicy[i].login == daneUzytkownika.login) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob: " << 3 - proby << ": ";

                cin >> daneUzytkownika.haslo;
                if (uzytkownicy[i].haslo == daneUzytkownika.haslo) {
                    cout << endl << "Zalogowales sie." << endl;
                    Sleep(1800);

                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem." << endl;
    Sleep(1500);

    return 0;
}


void Uzytkownik::zapiszNowegoUzytkownika(Uzytkownik daneUzytkownikaZarejestrowanego) {
    fstream plik;
    plik.open(nazwaPlikuZUzytkownikami.c_str(), ios::out | ios::app);

    if(plik.good()== true) {
        plik << daneUzytkownikaZarejestrowanego.idUzytkownika << "|";
        plik << daneUzytkownikaZarejestrowanego.login << "|";
        plik << daneUzytkownikaZarejestrowanego.haslo << "|" << endl;
        plik.close();
        cout << endl << "Nowe konto uzytkownika zostalo zalozone." << endl;
        Sleep(1900);
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych nowego uzytkownika." << endl;
        Sleep(1900);
    }
}

void Uzytkownik::rejestracja (vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik daneUzytkownikaDoRejestracji;
    int liczbaUzytkownikow = uzytkownicy.size();

    cout << endl << "Podaj swoj login: ";
    cin >> daneUzytkownikaDoRejestracji.login;

    int i = 0;
    while (i < liczbaUzytkownikow) {
        if (uzytkownicy[i].login == daneUzytkownikaDoRejestracji.login) {
            cout << "Taki login juz istnieje. Prosze podac inny: ";
            cin >> daneUzytkownikaDoRejestracji.login;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> daneUzytkownikaDoRejestracji.haslo;

    daneUzytkownikaDoRejestracji.idUzytkownika = liczbaUzytkownikow + 1;
    uzytkownicy.push_back(daneUzytkownikaDoRejestracji);
    zapiszNowegoUzytkownika(daneUzytkownikaDoRejestracji);
}
void Uzytkownik::zapiszPonownieUzytkownikaDoPliku(vector <Uzytkownik> &uzytkownicy) {
    int liczbaUzytkownikow = uzytkownicy.size();
    fstream plik;
    plik.open(nazwaPlikuZUzytkownikami.c_str(), ios::in | ios::out | ios::trunc );

    if(plik.good()) {
        for (int i = 0; i < liczbaUzytkownikow; i++) {
            plik << uzytkownicy[i].idUzytkownika << "|";
            plik << uzytkownicy[i].login << "|";
            plik << uzytkownicy[i].haslo << "|" << endl;
        }
        plik.close();
    }
}

void Uzytkownik::zmianaHasla (vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    Uzytkownik daneUzytkownikaZalogowanego;
    int liczbaUzytkownikow = uzytkownicy.size();
    int dlugoscCiaguTekstowego = 0;

    cout << "Podaj nowe haslo: ";
    cin >> daneUzytkownikaZalogowanego.haslo;

    for (int i = 0; i < liczbaUzytkownikow; i++) {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika) {

            dlugoscCiaguTekstowego = uzytkownicy[idZalogowanegoUzytkownika -1].haslo.length();
            uzytkownicy[idZalogowanegoUzytkownika -1].haslo.replace(0,dlugoscCiaguTekstowego,daneUzytkownikaZalogowanego.haslo);

            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
    zapiszPonownieUzytkownikaDoPliku(uzytkownicy);
}


