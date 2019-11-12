#include <iostream>
#include <vector>

using namespace std;

class Uzytkownik {

    int idUzytkownika;
    string login, haslo;

public:
    Uzytkownik(int = 0, string = "", string = "");
    ~Uzytkownik();
    string nazwaPlikuZUzytkownikami = "Uzytkownicy.txt";

    string pobierzDoPionowejKreski (string danePobraneWJednejLinii, int pozycja);
    int wyznaczPozycjeWPobieranejLinii (int pozycja, string tekst);
    int zamienStringNaInt (string tekst);
    void rozbijNaPojedynczeDaneUzytkownika (string pobraneWJednejLiniiDaneJednegoUzytkownika, Uzytkownik &daneUzytkownika);
    void odczytajZPlikuUzytkownik (vector <Uzytkownik> &uzytkownicy);
    int logowanie (vector <Uzytkownik> &uzytkownicy);
    void zapiszNowegoUzytkownika(Uzytkownik daneUzytkownikaZarejestrowanego);
    void rejestracja (vector <Uzytkownik> &uzytkownicy);
    void zapiszPonownieUzytkownikaDoPliku(vector <Uzytkownik> &uzytkownicy);
    void zmianaHasla (vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika);

};
