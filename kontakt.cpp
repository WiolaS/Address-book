#include <iostream>
#include "kontakt.h"
#include <cstdlib>
#include <fstream>
#include <vector>
#include <windows.h> // Sleep()
#include <conio.h> // getch()

using namespace std;

Kontakt::Kontakt(int identyfikatorKontaktu, int identyfikatorUzytkownika, string imieKontaktu, string nazwiskoKontaktu, string nrTelefonuKontaktu, string emailKontaktu, string adresKontaktu) {
    idAdresata = identyfikatorKontaktu;
    idUzytkownika = idUzytkownika;
    imie = imieKontaktu;
    nazwisko = nazwiskoKontaktu;
    nrTelefonu = nrTelefonuKontaktu;
    email = emailKontaktu;
    adres = adresKontaktu;
}

Kontakt::~Kontakt() {
    imie.clear();
    nazwisko.clear();
    nrTelefonu.clear();
    email.clear();
    adres.clear();
}

string Kontakt::pobierzKontaktDoPionowejKreski (string danePobraneWJednejLinii, int pozycja) {
    string informacja = "";
    do {
        informacja += danePobraneWJednejLinii[pozycja];
        pozycja++;
    } while (danePobraneWJednejLinii[pozycja] != '|');

    return informacja;
}

void Kontakt::rozbijNaPojedynczeDane (string pobraneWJednejLiniiDaneJednegoKontaktu, Kontakt &daneKontaktu) {
    string idTekst = "";
    for (int pozycja = 0; pozycja < pobraneWJednejLiniiDaneJednegoKontaktu.length(); pozycja++) {

        idTekst = pobierzKontaktDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (idTekst.length() +1);  // plus 1 - pominiecie pionowej linii
        daneKontaktu.idAdresata = atoi(idTekst.c_str());

        idTekst = pobierzKontaktDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (idTekst.length() +1);
        daneKontaktu.idUzytkownika = atoi(idTekst.c_str());

        daneKontaktu.imie = pobierzKontaktDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.imie.length() +1);

        daneKontaktu.nazwisko = pobierzKontaktDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.nazwisko.length() +1);

        daneKontaktu.nrTelefonu = pobierzKontaktDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.nrTelefonu.length() +1);

        daneKontaktu.email = pobierzKontaktDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.email.length() +1);

        daneKontaktu.adres = pobierzKontaktDoPionowejKreski (pobraneWJednejLiniiDaneJednegoKontaktu, pozycja);
        pozycja += (daneKontaktu.adres.length() +1);
    }
}

bool Kontakt::sprawdzCzyKontaktZostalUtworzonyPrzezZalogowanegoUzytkownika ( Kontakt &daneKontaktu, int idZalogowanegoKontaktu) {
    if (daneKontaktu.idUzytkownika == idZalogowanegoKontaktu)
        return true;
    else
        return false;
}

int Kontakt::odczytajZPliku (vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika) {
    Kontakt daneKontaktu;
    string pobraneWJednejLiniiDaneJednegoKontaktu = "";
    int nrKontaktu = 0;
    int idOstatniegoAdresata = 0;
    fstream plik;
    plik.open(nazwaPlikuZAdresatami.c_str(), ios::in);

    if(plik.good() == true) {
        while(getline(plik,pobraneWJednejLiniiDaneJednegoKontaktu)) {
            rozbijNaPojedynczeDane (pobraneWJednejLiniiDaneJednegoKontaktu, daneKontaktu);
            if (sprawdzCzyKontaktZostalUtworzonyPrzezZalogowanegoUzytkownika (daneKontaktu, idZalogowanegoUzytkownika)) {
                kontakty.push_back(daneKontaktu);
            }
        }
        idOstatniegoAdresata = daneKontaktu.idAdresata;
        cout << idOstatniegoAdresata <<endl;
    }
    plik.close();

    return idOstatniegoAdresata;
}

void Kontakt::zapiszDoPliku (Kontakt oryginalnyKontakt) {
    fstream plik;
    plik.open(nazwaTymczasowegoPlikuZAdresatami.c_str(), ios::out | ios::app);
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

void Kontakt::OdczytajAdresatowZPlikuAdresaciIZapiszZeZmianamiDoPlikuTymczasowiAdresaci (vector <Kontakt> &kontakty, int idUsuwanegoAdresata, int idEdytowanegoAdresata) {
    /// Funkcja wywo³ana przy:
    /// tworzeniu nowego Adresata: idUsuwanegoAdresata = 0, idEdytowanegoAdresata = 0;
    /// usuwaniu Adresata: idUsuwanegoAdresata != 0, idEdytowanegoAdresata = 0;
    /// edytowaniu Adresata: idUsuwanegoAdresata = 0, idEdytowanegoAdresata !=0;

    Kontakt pobieranyKontakt;
    string pobraneWJednejLiniiDaneJednegoKontaktu = "";
    int liczbaKontaktow = 0;
    int indeksEdytowanegoAdresata = idEdytowanegoAdresata - 1;
    fstream plik;
    plik.open(nazwaPlikuZAdresatami.c_str(), ios::in);

    if(plik.good() == true) {
        while(getline(plik,pobraneWJednejLiniiDaneJednegoKontaktu)) {

            rozbijNaPojedynczeDane (pobraneWJednejLiniiDaneJednegoKontaktu, pobieranyKontakt);

            if (idUsuwanegoAdresata == 0 && idEdytowanegoAdresata == 0) {
                zapiszDoPliku (pobieranyKontakt);
                liczbaKontaktow++;
            } else if (idUsuwanegoAdresata != 0 && idEdytowanegoAdresata == 0) {
                if (pobieranyKontakt.idAdresata != idUsuwanegoAdresata) {
                    zapiszDoPliku (pobieranyKontakt);
                    liczbaKontaktow++;
                }
            } else if (idUsuwanegoAdresata == 0 && idEdytowanegoAdresata != 0) {
                idEdytowanegoAdresata = kontakty[indeksEdytowanegoAdresata].idAdresata;

                if (pobieranyKontakt.idAdresata != idEdytowanegoAdresata) {
                    zapiszDoPliku (pobieranyKontakt);
                    liczbaKontaktow++;
                } else {
                    zapiszDoPliku (kontakty[indeksEdytowanegoAdresata]);
                    liczbaKontaktow++;
                }
            }
        }
    }
}


int Kontakt::stworzNowyKontakt (vector <Kontakt> &kontakty, int idOstatniegoAdresata, int idZalogowanegoUzytkownika) {
    Kontakt kontakyTworzony;
    system("cls");

    cout << endl << "----------- Tworzenie kontaktu -----------" << endl << endl;
    cout << "Podaj imie:               ";
    cin >> kontakyTworzony.imie;
    cout << "Podaj nazwisko:           ";
    cin.sync();
    cin >> kontakyTworzony.nazwisko;
    cout << "Podaj numer telefonu:     ";
    cin.sync();
    getline(cin, kontakyTworzony.nrTelefonu);
    cout << "Podaj adres email:        ";
    cin.sync();
    cin >> kontakyTworzony.email;
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, kontakyTworzony.adres);
    cin.sync();

    idOstatniegoAdresata++;
    kontakyTworzony.idUzytkownika = idZalogowanegoUzytkownika;
    kontakyTworzony.idAdresata = idOstatniegoAdresata;
    OdczytajAdresatowZPlikuAdresaciIZapiszZeZmianamiDoPlikuTymczasowiAdresaci (kontakty, 0, 0);
    zapiszDoPliku (kontakyTworzony);

    remove (nazwaPlikuZAdresatami.c_str());
    rename( nazwaTymczasowegoPlikuZAdresatami.c_str(), nazwaPlikuZAdresatami.c_str() );
    kontakty.push_back(kontakyTworzony);

    return idOstatniegoAdresata;
}

void Kontakt::wyswietlSzczegolyKontaktu(vector <Kontakt> &kontakty, int nrIdKontaktu) {
    int liczbaJeden = 1;

    cout << "------------------------------------------";
    cout << endl << "Id:                 " << nrIdKontaktu + liczbaJeden << endl;
    cout << "imie i nazwisko:    " << kontakty[nrIdKontaktu].imie << " " << kontakty[nrIdKontaktu].nazwisko << endl;
    cout << "nr telefonu:        " << kontakty[nrIdKontaktu].nrTelefonu << endl;
    cout << "adres email:        " << kontakty[nrIdKontaktu].email<< endl;
    cout << "adres zamieszkania: " << kontakty[nrIdKontaktu].adres << endl;
    cout << "------------------------------------------" << endl;
}

int Kontakt::wyswietlListeWybranychKontaktow (vector <Kontakt> &kontakty, string wyszukiwaneImie, string wyszukiwaneNazwisko) {
    int liczbaKontaktow = kontakty.size();
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

void Kontakt::znajdzKontaktPoImieniu (vector <Kontakt> &kontakty) {
    int liczbaKontaktow = kontakty.size();
    string imie;
    int liczbaWynikow = 0;
    int wyborId;
    int liczbaJedenDoLiczbyPorzadkowej = 1;

    system("cls");
    cout << endl << "---------- Wyszukiwanie kontaktu ----------" << endl << endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << endl;

    liczbaWynikow = wyswietlListeWybranychKontaktow (kontakty, imie, " ");

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

void Kontakt::znajdzKontaktPoNazwisku (vector <Kontakt> &kontakty) {
    int liczbaKontaktow = kontakty.size();
    string nazwisko;
    int liczbaWynikow = 0;
    int wyborId;
    int liczbaJedenDoLiczbyPorzadkowej = 1;

    system("cls");
    cout << endl << "---------- Wyszukiwanie kontaktu ----------" << endl << endl;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << endl;

    liczbaWynikow = wyswietlListeWybranychKontaktow (kontakty, " ", nazwisko);

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

void Kontakt::wyswietlListeWszystkichKontaktow (vector <Kontakt> &kontakty) {
    int liczbaKontaktow = kontakty.size();
    int liczbaJedenDoLiczbyPorzadkowej = 1;
    system("cls");

    cout << endl << "-------------- Lista kontaktow ---------------" << endl << endl;

    for (int i = 0; i < liczbaKontaktow; i++) {
        cout << i + liczbaJedenDoLiczbyPorzadkowej  << ". " << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
    }
}


void Kontakt::wyswietlMenuListyKontaktow (vector <Kontakt> &kontakty) {
    int liczbaKontaktow = kontakty.size();
    char wyborMenu;

    cout << endl << "1. Wroc do listy kontaktow" << endl;
    cout << "2. Wroc do menu glownego" << endl;

    wyborMenu = getch();

    switch(wyborMenu) {
    case '1':
        wyswietlWszystkieKontakty (kontakty);
        break;

    case '2':
        break;

    default:
        cout << "Wybrano niepoprawny numer. Powrot do menu glownego." << endl;
        Sleep(1900);
        break;
    }
}

void Kontakt::wyswietlWszystkieKontakty (vector <Kontakt> &kontakty) {
    int liczbaKontaktow = kontakty.size();
    int wyborId;
    int liczbaWynikow = 0;
    int liczbaJedenDoLiczbyPorzadkowej = 1;

    if (liczbaKontaktow == 0) {
        cout << "Brak kontaktow w pamieci programu." << endl;
        Sleep(2000);
    } else {
        wyswietlListeWszystkichKontaktow (kontakty);
        cout << endl << "Wyswietl szczegoly kontaktu: (wybierz numer) " << endl;

        cin >> wyborId;
        liczbaWynikow = 0;

        for (int i = 0; i < liczbaKontaktow; i++) {
            if (wyborId == (i + liczbaJedenDoLiczbyPorzadkowej)) {
                system("cls");
                wyswietlSzczegolyKontaktu(kontakty, i);
                wyswietlMenuListyKontaktow (kontakty);
                liczbaWynikow++;
            }
        }
        if (liczbaWynikow == 0) {
            cout <<"Brak wynikow dla wybranego numeru." << endl;
            Sleep(1500);
            wyswietlWszystkieKontakty (kontakty);
        }
    }
}

void Kontakt::usunWybranyKontakt (vector <Kontakt> &kontakty) {
    int liczbaKontaktow = kontakty.size();
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
        wyswietlListeWszystkichKontaktow (kontakty);
        cout << endl << "Wybierz id kontaktu, ktory chcesz usunac:  " << endl;
        cin >> wyborId;

        for (int i = 0; i < liczbaKontaktow; i++) {
            if (wyborId == (i + liczbaJedenDoLiczbyPorzadkowej)) {
                cout << "Czy na pewno chcesz usunac ten kontakt? \nt (tak) / n (nie): ";

                cin >> potwierdzenieUsuniecia;
                if (potwierdzenieUsuniecia == 't') {

                    idUsuwanegoAdresata = kontakty[wyborId - 1].idAdresata;
                    OdczytajAdresatowZPlikuAdresaciIZapiszZeZmianamiDoPlikuTymczasowiAdresaci (kontakty, idUsuwanegoAdresata, 0);
                    remove (nazwaPlikuZAdresatami.c_str());
                    rename( nazwaTymczasowegoPlikuZAdresatami.c_str(), nazwaPlikuZAdresatami.c_str() );
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
}

void Kontakt::edytujWybranyKontakt (vector <Kontakt> &kontakty, int wyborId) {
    Kontakt edytowanyKontakt;
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
        cin >> edytowanyKontakt.imie;
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].imie.length();
        kontakty[wyborId -1].imie.replace(0,dlugoscCiaguTekstowego,edytowanyKontakt.imie);
        edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '2': {
        cout << "Podaj nowe nazwisko: ";
        cin >> edytowanyKontakt.nazwisko;
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].nazwisko.length();
        kontakty[wyborId -1].nazwisko.replace(0,dlugoscCiaguTekstowego,edytowanyKontakt.nazwisko);
        edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '3': {

        cout << "Podaj nowy numer telefonu: ";
        getline(cin, edytowanyKontakt.nrTelefonu);
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].nrTelefonu.length();
        kontakty[wyborId -1].nrTelefonu.replace(0,dlugoscCiaguTekstowego,edytowanyKontakt.nrTelefonu);
        edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '4': {
        cout << "Podaj nowy email: ";
        cin >> edytowanyKontakt.email;
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].email.length();
        kontakty[wyborId -1].email.replace(0,dlugoscCiaguTekstowego,edytowanyKontakt.email);
        edytujWybranyKontakt (kontakty, wyborId);
        break;
    }

    case '5': {
        cout << "Podaj nowy adres: ";
        getline(cin, edytowanyKontakt.adres);
        cin.sync();

        dlugoscCiaguTekstowego = kontakty[wyborId -1].adres.length();
        kontakty[wyborId -1].adres.replace(0,dlugoscCiaguTekstowego,edytowanyKontakt.adres);
        edytujWybranyKontakt (kontakty, wyborId);
        break;
    }
    case '6':
        break;

    default:
        break;
    }
}

void Kontakt::wybierzKontaktDoEdycji (vector <Kontakt> &kontakty) {
    int numerIdKontaktu = kontakty.size();
    int wyborId = 0;

    system("cls");
    if (numerIdKontaktu == 0) {
        cout << "Brak kontaktow w pamieci programu." << endl;
        Sleep(2000);
    } else {
        wyswietlListeWszystkichKontaktow (kontakty);
        cout << endl << "Wybierz id kontaktu, ktory chcesz edytowac:  " << endl;
        cin >> wyborId;

        edytujWybranyKontakt (kontakty, wyborId);
        OdczytajAdresatowZPlikuAdresaciIZapiszZeZmianamiDoPlikuTymczasowiAdresaci (kontakty, 0, wyborId);
        remove (nazwaPlikuZAdresatami.c_str());
        rename( nazwaTymczasowegoPlikuZAdresatami.c_str(), nazwaPlikuZAdresatami.c_str() );
    }
}

void Kontakt::usunElementyWektoraKontakty (vector <Kontakt> &kontakty) {
    int liczbaKontaktow = kontakty.size();
    kontakty.erase(kontakty.begin(), kontakty.begin() + liczbaKontaktow );
}
