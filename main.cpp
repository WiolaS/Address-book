#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <windows.h> // Sleep()
#include <conio.h> // getch()

using namespace std;

struct Uzytkownik {
    int idUzytkownika;
    string login, haslo;
};

int logowanie (vector <Uzytkownik> uzytkownicy, int liczbaUzytkownikow) {
    Uzytkownik daneUzytkownikaDoZalogowania;

    cout << endl << "Podaj login: ";
    cin >> daneUzytkownikaDoZalogowania.login;

    int i = 0;
    while (i < liczbaUzytkownikow) {
        if (uzytkownicy[i].login == daneUzytkownikaDoZalogowania.login) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob: " << 3 - proby << ": ";
                cin >> daneUzytkownikaDoZalogowania.haslo;
                if (uzytkownicy[i].haslo == daneUzytkownikaDoZalogowania.haslo) {
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

string pobierzDoPionowejKreski (string danePobraneWJednejLinii, int pozycja) {
    string informacja = "";
    do {
        informacja += danePobraneWJednejLinii[pozycja];
        pozycja++;
    } while (danePobraneWJednejLinii[pozycja] != '|');

    return informacja;
}

Uzytkownik rozbijNaPojedynczeDaneUzytkownika (string pobraneWJednejLiniiDaneJednegoUzytkownika) {
    Uzytkownik daneUzytkownika;
    string idTekst = "";
    for (int pozycja = 0; pozycja < pobraneWJednejLiniiDaneJednegoUzytkownika.length(); pozycja++) {

        idTekst = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoUzytkownika, pozycja);
        pozycja += (idTekst.length() +1);  // plus 1 - pominiecie pionowej linii
        daneUzytkownika.idUzytkownika = atoi(idTekst.c_str());

        daneUzytkownika.login = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoUzytkownika, pozycja);
        pozycja += (daneUzytkownika.login.length() +1);

        daneUzytkownika.haslo = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoUzytkownika, pozycja);
        pozycja += (daneUzytkownika.haslo.length() +1);
    }
    return daneUzytkownika;
}
vector <Uzytkownik> dodajObiektdaneUzytkownikaDoWektoraUzytkownicy (vector <Uzytkownik> uzytkownicy, Uzytkownik daneUzytkownika, int nrUzytkownika) {
    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[nrUzytkownika].idUzytkownika = daneUzytkownika.idUzytkownika;
    uzytkownicy[nrUzytkownika].login = daneUzytkownika.login;
    uzytkownicy[nrUzytkownika].haslo = daneUzytkownika.haslo;

    return uzytkownicy;
}

vector <Uzytkownik> odczytajZPlikuUzytkownik (vector <Uzytkownik> uzytkownicy) {
    Uzytkownik daneUzytkownika;
    string pobraneWJednejLiniiDaneJednegoUzytkownika = "";
    int nrUzytkownika = 0;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good() == true) {
        while(getline(plik,pobraneWJednejLiniiDaneJednegoUzytkownika)) {
            daneUzytkownika = rozbijNaPojedynczeDaneUzytkownika (pobraneWJednejLiniiDaneJednegoUzytkownika);
            uzytkownicy = dodajObiektdaneUzytkownikaDoWektoraUzytkownicy (uzytkownicy, daneUzytkownika, nrUzytkownika);
            nrUzytkownika++;
        }
    }
    plik.close();
    return uzytkownicy;
}

void zapiszNowegoUzytkownika(Uzytkownik daneUzytkownikaZarejestrowanego) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

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

vector <Uzytkownik> rejestracja (vector <Uzytkownik> uzytkownicy, int liczbaUzytkownikow) {
    Uzytkownik daneUzytkownikaDoRejestracji;

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
    uzytkownicy = dodajObiektdaneUzytkownikaDoWektoraUzytkownicy ( uzytkownicy, daneUzytkownikaDoRejestracji, liczbaUzytkownikow);
    zapiszNowegoUzytkownika(daneUzytkownikaDoRejestracji);

    return uzytkownicy;
}

struct Kontakt {
    int idAdresata;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string nrTelefonu;
    string email;
    string adres;
};

Kontakt rozbijNaPojedynczeDane (string pobraneWJednejLiniiDaneJednegoKontaktu) {
    Kontakt daneKontaktu;
    string idTekst = "";
    for (int pozycja = 0; pozycja < pobraneWJednejLiniiDaneJednegoKontaktu.length(); pozycja++) {

        idTekst = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (idTekst.length() +1);  // plus 1 - pominiecie pionowej linii
        daneKontaktu.idAdresata = atoi(idTekst.c_str());

        idTekst = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (idTekst.length() +1);
        daneKontaktu.idUzytkownika = atoi(idTekst.c_str());

        daneKontaktu.imie = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.imie.length() +1);

        daneKontaktu.nazwisko = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.nazwisko.length() +1);

        daneKontaktu.nrTelefonu = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.nrTelefonu.length() +1);

        daneKontaktu.email = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.email.length() +1);

        daneKontaktu.adres = pobierzDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.adres.length() +1);
    }
    return daneKontaktu;
}

vector <Kontakt> dodajObiektdaneKontaktuDoWektoraKontakty (vector <Kontakt> kontakty, Kontakt daneKontaktu, int nrKontaktu) {
    kontakty.push_back(Kontakt());
    kontakty[nrKontaktu].idAdresata = daneKontaktu.idAdresata;
    kontakty[nrKontaktu].idUzytkownika = daneKontaktu.idUzytkownika;
    kontakty[nrKontaktu].imie = daneKontaktu.imie;
    kontakty[nrKontaktu].nazwisko = daneKontaktu.nazwisko;
    kontakty[nrKontaktu].nrTelefonu = daneKontaktu.nrTelefonu;
    kontakty[nrKontaktu].email = daneKontaktu.email;
    kontakty[nrKontaktu].adres = daneKontaktu.adres;

    return kontakty;
}

bool sprawdzCzyKontaktZostalUtworzonyPrzezZalogowanegoUzytkownika ( Kontakt daneKontaktu, int idZalogowanegoKontaktu) {
    if (daneKontaktu.idUzytkownika == idZalogowanegoKontaktu)
        return true;
    else
        return false;
}

vector <Kontakt> odczytajZPliku (vector <Kontakt> kontakty, int idZalogowanegoUzytkownika) {
    Kontakt daneKontaktu;
    string pobraneWJednejLiniiDaneJednegoKontaktu = "";
    int nrKontaktu = 0;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if(plik.good() == true) {
        while(getline(plik,pobraneWJednejLiniiDaneJednegoKontaktu)) {
            daneKontaktu = rozbijNaPojedynczeDane (pobraneWJednejLiniiDaneJednegoKontaktu);
            if (sprawdzCzyKontaktZostalUtworzonyPrzezZalogowanegoUzytkownika (daneKontaktu, idZalogowanegoUzytkownika)) {
                kontakty = dodajObiektdaneKontaktuDoWektoraKontakty (kontakty, daneKontaktu, nrKontaktu);
                nrKontaktu++;
            }
        }
    }
    plik.close();

    return kontakty;
}

void zapiszDoPliku (Kontakt oryginalnyKontakt) {
    fstream plik;
    plik.open("tymczasowiAdresaci.txt", ios::out | ios::app);
    if(plik.good()) {
        plik << oryginalnyKontakt.idAdresata << "|";
        plik << oryginalnyKontakt.idUzytkownika << "|";
        plik << oryginalnyKontakt.imie << "|";
        plik << oryginalnyKontakt.nazwisko << "|";
        plik << oryginalnyKontakt.nrTelefonu << "|";
        plik << oryginalnyKontakt.email << "|";
        plik << oryginalnyKontakt.adres << "|" << endl;

        plik.close();
    }
}

int zapiszNowyKontaktDoPliku (vector <Kontakt> kontakty, Kontakt daneKontaktowe) {
    fstream plik;
    Kontakt oryginalnyKontakt;
    string pobraneWJednejLiniiDaneJednegoKontaktu = "";
    int nrKontaktu = 0;
    fstream plikAdresaci;
    plikAdresaci.open("Adresaci.txt", ios::in);

    if(plikAdresaci.good() == true) {
        while(getline(plikAdresaci,pobraneWJednejLiniiDaneJednegoKontaktu)) {

            oryginalnyKontakt = rozbijNaPojedynczeDane (pobraneWJednejLiniiDaneJednegoKontaktu);
            zapiszDoPliku (oryginalnyKontakt);
            nrKontaktu++;
        }
    }

    if (nrKontaktu != 0) {
        daneKontaktowe.idAdresata = oryginalnyKontakt.idAdresata + 1;
    } else if (nrKontaktu == 0) {
        daneKontaktowe.idAdresata = nrKontaktu + 1;
    }
    zapiszDoPliku (daneKontaktowe);
    nrKontaktu++;

    return daneKontaktowe.idAdresata;
}

vector <Kontakt> stworzNowyKontakt (vector <Kontakt> kontakty, int liczbaKontaktow, int idZalogowanegoUzytkownika) {
    Kontakt daneKontaktu;
    system("cls");

    cout << endl << "----------- Tworzenie kontaktu -----------" << endl << endl;
    cout << "Podaj imie:               ";
    cin >> daneKontaktu.imie;
    cout << "Podaj nazwisko:           ";
    cin.sync();
    cin >> daneKontaktu.nazwisko;
    cout << "Podaj numer telefonu:     ";
    cin.sync();
    getline(cin, daneKontaktu.nrTelefonu);
    cout << "Podaj adres email:        ";
    cin.sync();
    cin >> daneKontaktu.email;
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, daneKontaktu.adres);
    cin.sync();

    daneKontaktu.idUzytkownika = idZalogowanegoUzytkownika;
    daneKontaktu.idAdresata = zapiszNowyKontaktDoPliku (kontakty, daneKontaktu);
    remove ("Adresaci.txt");
    rename( "tymczasowiAdresaci.txt", "Adresaci.txt" );
    kontakty = dodajObiektdaneKontaktuDoWektoraKontakty (kontakty, daneKontaktu, liczbaKontaktow);

    return kontakty;
}

void wyswietlSzczegolyKontaktu(vector <Kontakt> kontakty, int nrIdKontaktu) {
    int liczbaJedenDoLiczbyPorzadkowej = 1;

    cout << "------------------------------------------";
    cout << endl << "Id:                 " << nrIdKontaktu + liczbaJedenDoLiczbyPorzadkowej  << endl;
    cout << "imie i nazwisko:    " << kontakty[nrIdKontaktu].imie << " " << kontakty[nrIdKontaktu].nazwisko << endl;
    cout << "nr telefonu:        " << kontakty[nrIdKontaktu].nrTelefonu << endl;
    cout << "adres email:        " << kontakty[nrIdKontaktu].email<< endl;
    cout << "adres zamieszkania: " << kontakty[nrIdKontaktu].adres << endl;
    cout << "------------------------------------------" << endl;
}

int wyswietlListeWybranychKontaktow (vector <Kontakt> kontakty, int liczbaKontaktow, string wyszukiwaneImie, string wyszukiwaneNazwisko) {
    int liczbaWynikow = 0;
    int liczbaJedenDoLiczbyPorzadkowej = 1;

    for (int i = 0; i < liczbaKontaktow; i++) {
        if (wyszukiwaneImie == kontakty[i].imie || wyszukiwaneNazwisko == kontakty[i].nazwisko) {
            cout << i + liczbaJedenDoLiczbyPorzadkowej  << ". " << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
            liczbaWynikow++;
        }
    }
    return liczbaWynikow;
}

void znajdzKontaktPoImieniu (vector <Kontakt> kontakty, int liczbaKontaktow) {
    string imie;
    int liczbaWynikow = 0;
    int wyborId;
    int liczbaJedenDoLiczbyPorzadkowej = 1;

    system("cls");
    cout << endl << "---------- Wyszukiwanie kontaktu ----------" << endl << endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << endl;

    liczbaWynikow = wyswietlListeWybranychKontaktow (kontakty, liczbaKontaktow, imie, " ");

    if (liczbaWynikow == 0) {
        cout << "Brak wynikow dla wyszukiwanego imienia." << endl;
        Sleep(1900);
    } else {
        cout << endl<< "Wyswietl szczegoly kontaktu: (wybierz numer) " << endl;
        cin >> wyborId;
        liczbaWynikow = 0;

        for (int i = 0; i < liczbaKontaktow; i++) {
            if (wyborId == (i + liczbaJedenDoLiczbyPorzadkowej) && imie == kontakty[i].imie) {
                wyswietlSzczegolyKontaktu(kontakty, i);
                liczbaWynikow++;
            }
        }
        if (liczbaWynikow == 0) {
            cout <<"Brak wynikow dla wybranego numeru." << endl;
        }
    }
    getch();
}

void znajdzKontaktPoNazwisku (vector <Kontakt> kontakty, int liczbaKontaktow) {
    string nazwisko;
    int liczbaWynikow = 0;
    int wyborId;
    int liczbaJedenDoLiczbyPorzadkowej = 1;

    system("cls");
    cout << endl << "---------- Wyszukiwanie kontaktu ----------" << endl << endl;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << endl;

    liczbaWynikow = wyswietlListeWybranychKontaktow (kontakty, liczbaKontaktow, " ", nazwisko);

    if (liczbaWynikow == 0) {
        cout << "Brak wynikow dla wyszukiwanego nazwiska." << endl;
        Sleep(1900);
    } else {
        cout << endl<< "Wyswietl szczegoly kontaktu: (wybierz numer) " << endl;
        cin >> wyborId;
        liczbaWynikow = 0;

        for (int i = 0; i < liczbaKontaktow; i++) {
            if (wyborId == (i + liczbaJedenDoLiczbyPorzadkowej) && nazwisko == kontakty[i].nazwisko) {
                wyswietlSzczegolyKontaktu(kontakty, i);
                liczbaWynikow++;
            }
        }
        if (liczbaWynikow == 0) {
            cout <<"Brak wynikow dla wybranego numeru." << endl;
        }
    }
    getch();
}

void wyswietlListeWszystkichKontaktow (vector <Kontakt> kontakty, int liczbaKontaktow) {
    int liczbaJedenDoLiczbyPorzadkowej = 1;
    system("cls");

    cout << endl << "-------------- Lista kontaktow ---------------" << endl << endl;

    for (int i = 0; i < liczbaKontaktow; i++) {
        cout << i + liczbaJedenDoLiczbyPorzadkowej  << ". " << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
    }
}

void wyswietlWszystkieKontakty (vector <Kontakt> kontakty, int liczbaKontaktow);

void wyswietlMenuListyKontaktow (vector <Kontakt> kontakty, int liczbaKontaktow) {
    char wyborMenu;

    cout << endl << "1. Wroc do listy kontaktow" << endl;
    cout << "2. Wroc do menu glownego" << endl;

    wyborMenu = getch();

    switch(wyborMenu) {
    case '1':
        wyswietlWszystkieKontakty (kontakty, liczbaKontaktow);
        break;

    case '2':
        break;

    default:
        cout << "Wybrano niepoprawny numer. Powrot do menu glownego." << endl;
        Sleep(1900);
        break;
    }
}

void wyswietlWszystkieKontakty (vector <Kontakt> kontakty, int liczbaKontaktow) {
    int wyborId;
    int liczbaWynikow = 0;
    int liczbaJedenDoLiczbyPorzadkowej = 1;

    if (liczbaKontaktow == 0) {
        cout << "Brak kontaktow w pamieci programu." << endl;
        Sleep(2000);
    } else {
        wyswietlListeWszystkichKontaktow (kontakty, liczbaKontaktow);
        cout << endl << "Wyswietl szczegoly kontaktu: (wybierz numer) " << endl;

        cin >> wyborId;
        liczbaWynikow = 0;

        for (int i = 0; i < liczbaKontaktow; i++) {
            if (wyborId == (i + liczbaJedenDoLiczbyPorzadkowej)) {
                system("cls");
                wyswietlSzczegolyKontaktu(kontakty, i);
                wyswietlMenuListyKontaktow (kontakty, liczbaKontaktow);
                liczbaWynikow++;
            }
        }
        if (liczbaWynikow == 0) {
            cout <<"Brak wynikow dla wybranego numeru." << endl;
            Sleep(1500);
            wyswietlWszystkieKontakty (kontakty, liczbaKontaktow);
        }
    }
}
void zapiszPonownieKontaktyDoPlikuUsun (vector <Kontakt> kontakty, int idUsuwanegoAdresata) {
    fstream plik;
    Kontakt oryginalnyKontakt;
    string pobraneWJednejLiniiDaneJednegoKontaktu = "";
    int nrKontaktu = 0;
    fstream plikAdresaci;
    plikAdresaci.open("Adresaci.txt", ios::in);

    if(plikAdresaci.good() == true) {
        while(getline(plikAdresaci,pobraneWJednejLiniiDaneJednegoKontaktu)) {

            oryginalnyKontakt = rozbijNaPojedynczeDane (pobraneWJednejLiniiDaneJednegoKontaktu);

            if (oryginalnyKontakt.idAdresata != idUsuwanegoAdresata) {
                zapiszDoPliku (oryginalnyKontakt);
            }
        }
        nrKontaktu++;
    }
}

vector <Kontakt> usunWybranyKontakt (vector <Kontakt> kontakty, int liczbaKontaktow) {

    int wyborId = 0;
    int liczbaWynikow = 0;
    char potwierdzenieUsuniecia;
    int liczbaJedenDoLiczbyPorzadkowej = 1;
    int idUsuwanegoAdresata = 0;

    system("cls");

    if (liczbaKontaktow == 0) {
        cout << "Brak kontaktow w pamieci programu." << endl;
        Sleep(2000);
    } else {
        wyswietlListeWszystkichKontaktow (kontakty, liczbaKontaktow);
        cout << endl << "Wybierz id kontaktu, ktory chcesz usunac:  " << endl;
        cin >> wyborId;

        for (int i = 0; i < liczbaKontaktow; i++) {
            if (wyborId == (i + liczbaJedenDoLiczbyPorzadkowej)) {
                cout << "Czy na pewno chcesz usunac ten kontakt? \nt (tak) / n (nie): ";

                cin >> potwierdzenieUsuniecia;
                if (potwierdzenieUsuniecia == 't') {

                    idUsuwanegoAdresata = kontakty[wyborId - 1].idAdresata;
                    zapiszPonownieKontaktyDoPlikuUsun(kontakty, idUsuwanegoAdresata);
                    remove ("Adresaci.txt");
                    rename( "tymczasowiAdresaci.txt", "Adresaci.txt" );
                    kontakty.erase(kontakty.begin() + i);
                    liczbaWynikow++;
                    cout << "Kontakt zostal usuniety.";
                    Sleep(1900);

                } else {
                    liczbaWynikow++;
                    cout <<"Nie usunieto kontaktu." << endl;
                    Sleep(1900);
                }
            }
        }
        if (liczbaWynikow == 0) {
            cout <<"Brak wynikow dla wybranego numeru. Nie usunieto kontaktu." << endl;
            Sleep(1900);
        }
    }
    return kontakty;

}

vector <Kontakt> edytujWybranyKontakt (vector <Kontakt> kontakty, int wyborId) {
    Kontakt edytowaneKontakty;
    int dlugoscCiaguTekstowego = 0;
    system("cls");

    wyswietlSzczegolyKontaktu(kontakty, (wyborId -1));

    cout << endl << "-------- Edytuj: --------" << endl << endl;
    char wyborMenu;

    cout << "1. imie" << endl;
    cout << "2. nazwisko" << endl;
    cout << "3. numer telefonu" << endl;
    cout << "4. email" << endl;
    cout << "5. adres" << endl;
    cout << "6. powrot do menu" << endl << endl;

    wyborMenu = getch();

    switch(wyborMenu) {
    case '1': {
        cout << "Podaj nowe imie: ";
        cin >> edytowaneKontakty.imie;
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].imie.length();
        kontakty[wyborId -1].imie.replace(0,dlugoscCiaguTekstowego,edytowaneKontakty.imie);
        kontakty = edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '2': {
        cout << "Podaj nowe nazwisko: ";
        cin >> edytowaneKontakty.nazwisko;
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].nazwisko.length();
        kontakty[wyborId -1].nazwisko.replace(0,dlugoscCiaguTekstowego,edytowaneKontakty.nazwisko);
        kontakty = edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '3': {

        cout << "Podaj nowy numer telefonu: ";
        getline(cin, edytowaneKontakty.nrTelefonu);
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].nrTelefonu.length();
        kontakty[wyborId -1].nrTelefonu.replace(0,dlugoscCiaguTekstowego,edytowaneKontakty.nrTelefonu);
        kontakty = edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '4': {
        cout << "Podaj nowy email: ";
        cin >> edytowaneKontakty.email;
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].email.length();
        kontakty[wyborId -1].email.replace(0,dlugoscCiaguTekstowego,edytowaneKontakty.email);
        kontakty = edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '5': {
        cout << "Podaj nowy adres: ";
        getline(cin, edytowaneKontakty.adres);
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].adres.length();
        kontakty[wyborId -1].adres.replace(0,dlugoscCiaguTekstowego,edytowaneKontakty.adres);
        kontakty = edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '6':
        break;

    default:
        break;
    }

    return kontakty;
}

void zapiszPonownieKontaktyDoPliku (vector <Kontakt> kontakty, int indeksEdytowanegoKontaktu) {
    fstream plik;
    Kontakt oryginalnyKontakt;
    string pobraneWJednejLiniiDaneJednegoKontaktu = "";
    int nrKontaktu = 0;

    fstream plikAdresaci;
    plikAdresaci.open("Adresaci.txt", ios::in);

    if(plikAdresaci.good() == true) {
        while(getline(plikAdresaci,pobraneWJednejLiniiDaneJednegoKontaktu)) {
            oryginalnyKontakt = rozbijNaPojedynczeDane (pobraneWJednejLiniiDaneJednegoKontaktu);

            if (oryginalnyKontakt.idAdresata != kontakty[indeksEdytowanegoKontaktu].idAdresata) {
                zapiszDoPliku (oryginalnyKontakt);
            } else  {
                zapiszDoPliku (kontakty[indeksEdytowanegoKontaktu]);
            }
        }
        nrKontaktu++;
    }
}

vector <Kontakt> wybierzKontaktDoEdycji (vector <Kontakt> kontakty, int numerIdKontaktu) {
    int wyborId = 0;

    system("cls");
    if (numerIdKontaktu == 0) {
        cout << "Brak kontaktow w pamieci programu." << endl;
        Sleep(2000);
    } else {
        wyswietlListeWszystkichKontaktow (kontakty, numerIdKontaktu);
        cout << endl << "Wybierz id kontaktu, ktory chcesz edytowac:  " << endl;
        cin >> wyborId;

        kontakty = edytujWybranyKontakt (kontakty, wyborId);
        zapiszPonownieKontaktyDoPliku(kontakty, (wyborId - 1));
        remove ("Adresaci.txt");
        rename( "tymczasowiAdresaci.txt", "Adresaci.txt" );
    }

    return kontakty;
}

vector <Uzytkownik> zmianaHasla (vector <Uzytkownik> uzytkownicy, int liczbaUzytkownikow, int idZalogowanegoUzytkownika) {
    Uzytkownik daneUzytkownikaZalogowanego;
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

    return uzytkownicy;
}

void zapiszPonownieUzytkownikaDoPliku(vector <Uzytkownik> uzytkownicy, int liczbaUzytkownikow) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in | ios::out | ios::trunc );

    if(plik.good()) {
        for (int i = 0; i < liczbaUzytkownikow; i++) {
            plik << uzytkownicy[i].idUzytkownika << "|";
            plik << uzytkownicy[i].login << "|";
            plik << uzytkownicy[i].haslo << "|" << endl;
        }
        plik.close();
    }
}

vector <Kontakt> usunElementyWektoraKontakty (vector <Kontakt> kontakty, int liczbaKontaktow) {
    kontakty.erase(kontakty.begin(), kontakty.begin() + liczbaKontaktow );

    return kontakty;
}

int main() {

    vector <Uzytkownik> uzytkownicy;
    int liczbaUzytkownikow = 0;
    int idZalogowanegoUzytkownika = 0;  // 0 tj. zaden uzytkownik nie jest zalogowany
    char wybor;

    vector <Kontakt> kontakty;
    int liczbaKontaktow = 0;

    uzytkownicy = odczytajZPlikuUzytkownik(uzytkownicy);
    liczbaUzytkownikow = uzytkownicy.size();

    while(1) {
        if (idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << endl << "------- KSIAZKA ADRESOWA -------" << endl << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "3. Zamknij program" << endl;
            wybor = getch();

            switch(wybor) {
            case '1': {

                idZalogowanegoUzytkownika = logowanie(uzytkownicy, liczbaUzytkownikow);
                kontakty = odczytajZPliku (kontakty, idZalogowanegoUzytkownika);
                liczbaKontaktow = kontakty.size();
                break;
            }

            case '2':
                uzytkownicy = rejestracja(uzytkownicy, liczbaUzytkownikow);
                liczbaUzytkownikow++;
                break;

            case '3':
                exit(0);
            }
        } else {
            system("cls");
            cout << endl << "------- KSIAZKA ADRESOWA -------" << endl << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl << endl;
            cout << "Twoj wybor: ";

            wybor = getch();
            switch(wybor) {
            case '1':

                kontakty = stworzNowyKontakt (kontakty, liczbaKontaktow, idZalogowanegoUzytkownika);
                liczbaKontaktow = kontakty.size();
                break;

            case '2':
                znajdzKontaktPoImieniu (kontakty, liczbaKontaktow);
                break;

            case '3':
                znajdzKontaktPoNazwisku (kontakty, liczbaKontaktow);
                break;

            case '4':
                wyswietlWszystkieKontakty(kontakty, liczbaKontaktow);
                break;

            case '5':
                kontakty = usunWybranyKontakt (kontakty, liczbaKontaktow);
                liczbaKontaktow = kontakty.size();
                break;

            case '6':
                kontakty = wybierzKontaktDoEdycji (kontakty, liczbaKontaktow);
                break;

            case '7':
                uzytkownicy = zmianaHasla (uzytkownicy, liczbaUzytkownikow, idZalogowanegoUzytkownika);
                zapiszPonownieUzytkownikaDoPliku(uzytkownicy, liczbaUzytkownikow);
                break;

            case '8':
                idZalogowanegoUzytkownika = 0;
                kontakty = usunElementyWektoraKontakty (kontakty, liczbaKontaktow);
                liczbaKontaktow = kontakty.size();
                break;
            }
        }
    }
    return 0;
}

