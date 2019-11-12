#include <iostream>
#include <vector>

using namespace std;

class Kontakt {

    int idAdresata;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string nrTelefonu;
    string email;
    string adres;

public:
    Kontakt(int = 0, int = 0, string = "", string = "", string = "", string = "", string = "");
    ~Kontakt();
    string nazwaPlikuZAdresatami = "Adresaci.txt";
    string nazwaTymczasowegoPlikuZAdresatami = "TymczasowiAdresaci.txt";

    string pobierzKontaktDoPionowejKreski (string danePobraneWJednejLinii, int pozycja);
    void rozbijNaPojedynczeDane (string pobraneWJednejLiniiDaneJednegoKontaktu, Kontakt &daneKontaktu);
    bool sprawdzCzyKontaktZostalUtworzonyPrzezZalogowanegoUzytkownika ( Kontakt &daneKontaktu, int idZalogowanegoKontaktu);
    int odczytajZPliku (vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika);
    void zapiszDoPliku (Kontakt oryginalnyKontakt);
    void OdczytajAdresatowZPlikuAdresaciIZapiszZeZmianamiDoPlikuTymczasowiAdresaci (vector <Kontakt> &kontakty, int idUsuwanegoAdresata, int idEdytowanegoAdresata);
    int stworzNowyKontakt (vector <Kontakt> &kontakty, int idOstatniegoAdresata, int idZalogowanegoUzytkownika);
    void wyswietlSzczegolyKontaktu(vector <Kontakt> &kontakty, int nrIdKontaktu);
    int wyswietlListeWybranychKontaktow (vector <Kontakt> &kontakty, string wyszukiwaneImie, string wyszukiwaneNazwisko);
    void znajdzKontaktPoImieniu (vector <Kontakt> &kontakty);
    void znajdzKontaktPoNazwisku (vector <Kontakt> &kontakty);
    void wyswietlListeWszystkichKontaktow (vector <Kontakt> &kontakty);
    void wyswietlMenuListyKontaktow (vector <Kontakt> &kontakty);
    void wyswietlWszystkieKontakty (vector <Kontakt> &kontakty);
    void usunWybranyKontakt (vector <Kontakt> &kontakty);
    void edytujWybranyKontakt (vector <Kontakt> &kontakty, int wyborId);
    void wybierzKontaktDoEdycji (vector <Kontakt> &kontakty);
    void usunElementyWektoraKontakty (vector <Kontakt> &kontakty);
};
