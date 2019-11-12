#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <windows.h> // Sleep()
#include <conio.h> // getch()
#include "uzytkownik.h"
#include "kontakt.h"

using namespace std;

void wyswietlMenuNiezalogowanegoUzytkownika() {
    system("cls");
    cout << endl << "------- KSIAZKA ADRESOWA -------" << endl << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zamknij program" << endl;
}

void wyswietlMenuZalogowanegoUzytkownika() {
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
}

int main() {

    vector <Uzytkownik> uzytkownicy;
    Uzytkownik uzytkownikPobrany;
    Uzytkownik uzytkownikRejestrujacy;
    Uzytkownik uzytkownikLogujacy;

    int idZalogowanegoUzytkownika = 0;  // 0 tj. zaden uzytkownik nie jest zalogowany
    int idOstatniegoAdresata = 0;
    char wybor;

    vector <Kontakt> kontakty;
    Kontakt pobranyKontakt;
    Kontakt kontaktTworzony;
    Kontakt kontaktPobieranyZPliku;
    Kontakt kontaktEdytowany;
    Kontakt kontaktUsuwany;

    uzytkownikPobrany.odczytajZPlikuUzytkownik(uzytkownicy);

    while(1) {
        if (idZalogowanegoUzytkownika == 0) {
            wyswietlMenuNiezalogowanegoUzytkownika();
            wybor = getch();

            switch(wybor) {
            case '1': {
                idZalogowanegoUzytkownika = uzytkownikLogujacy.logowanie(uzytkownicy);
                break;
            }
            case '2': {
                uzytkownikRejestrujacy.rejestracja(uzytkownicy);
                break;
            }
            case '3':
                exit(0);
            }
        } else {
            if (kontakty.empty() == true) {
                idOstatniegoAdresata = pobranyKontakt.odczytajZPliku (kontakty, idZalogowanegoUzytkownika);
            }
            wyswietlMenuZalogowanegoUzytkownika();
            wybor = getch();
            switch(wybor) {
            case '1':
                idOstatniegoAdresata = kontaktTworzony.stworzNowyKontakt (kontakty, idOstatniegoAdresata, idZalogowanegoUzytkownika);
                break;

            case '2':
                pobranyKontakt.znajdzKontaktPoImieniu (kontakty);
                break;

            case '3':
               pobranyKontakt.znajdzKontaktPoNazwisku (kontakty);
                break;

            case '4':
                pobranyKontakt.wyswietlWszystkieKontakty(kontakty);
                break;

            case '5':kontaktUsuwany.usunWybranyKontakt (kontakty);
                break;

            case '6':
                kontaktEdytowany.wybierzKontaktDoEdycji (kontakty);
                break;

            case '7':
                uzytkownikPobrany.zmianaHasla (uzytkownicy, idZalogowanegoUzytkownika);
                break;

            case '8':
                idZalogowanegoUzytkownika = 0;
                pobranyKontakt.usunElementyWektoraKontakty (kontakty);
                break;
            }
        }
    }
    return 0;
}


