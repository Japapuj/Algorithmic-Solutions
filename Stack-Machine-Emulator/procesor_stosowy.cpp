#include <iostream>

using namespace std;

struct Char {
    char dane;
    Char* nastepny;
};

struct Lista {
    Char* dane;
    Lista* nastepny;
};

void dodajNaStos(Lista*& wierzcholek, Char* dane) { //'
    Lista* nowyWezel = new Lista;
    nowyWezel->dane = dane;
    nowyWezel->nastepny = wierzcholek;
    wierzcholek = nowyWezel;
}

Char* szczytStosu(Lista* wierzcholek) { //szczyt stosu
    return wierzcholek ? wierzcholek->dane : nullptr;
}

void usunListeChar(Char*& lista) {
    if (lista) {
        usunListeChar(lista->nastepny);
        delete lista;
    }
}

void usunZeStosu(Lista*& wierzcholek) { //,
    if (wierzcholek) {
        usunListeChar(wierzcholek->dane);
        Lista* temp = wierzcholek;
        wierzcholek = wierzcholek->nastepny;
        delete temp;
    }
}

void zamienDwaGorne(Lista*& wierzcholek) { //;
    if (wierzcholek && wierzcholek->nastepny) {
        Lista* pierwszy = wierzcholek;
        Lista* drugi = wierzcholek->nastepny;
        pierwszy->nastepny = drugi->nastepny;
        drugi->nastepny = pierwszy;
        wierzcholek = drugi;
    }
}

Lista* wezWezelNaPozycji(Lista* wierzcholek, int indeks, int i = 0) { //@
    if (!wierzcholek) {
        return nullptr;
    }
    if (indeks != i) {
        return wezWezelNaPozycji(wierzcholek->nastepny, indeks, i + 1);
    }
    else {
        return wierzcholek;
    }
}

int charNaInt(Char* lista, int mnoznik = 1) { //@
    if (!lista) return 0;
    int aktualnaCyfra = lista->dane - '0';
    return aktualnaCyfra * mnoznik + charNaInt(lista->nastepny, mnoznik * 10);
}

void wypiszListeChar(Char* lista) { //&
    if (lista) {
        cout << lista->dane;
        wypiszListeChar(lista->nastepny);
    }
}

void wypiszStosSformatowany(Lista* stos, int indeks = 0) { //&
    if (stos) {
        wypiszStosSformatowany(stos->nastepny, indeks + 1);
        cout << indeks << ": ";
        wypiszListeChar(stos->dane);
        cout << endl;
    }
}

Char* skopiujListeChar(Char* lista) { //:
    if (!lista) return nullptr;
    return new Char{ lista->dane, skopiujListeChar(lista->nastepny) };
}

void wypiszSzczytStosu(Char* lista) { //>
    cout << lista->dane;
}

Char* ostatniElement(Char* lista) { //^-
    if (!lista) return nullptr;
    if (lista->nastepny) {
        return ostatniElement(lista->nastepny);
    }
    return lista;
}

void usunOstatniElement(Char*& lista) { //^-
    if (!lista) return;
    if (!lista->nastepny) {
        delete lista;
        lista = nullptr;
    }
    else if (!lista->nastepny->nastepny) {
        delete lista->nastepny;
        lista->nastepny = nullptr;
    }
    else {
        usunOstatniElement(lista->nastepny);
    }
}

void dodajOstatniElement(Char*& lista, char znak) { //-
    if (!lista) {
        lista = new Char{ znak, nullptr };
    }
    else {
        dodajOstatniElement(lista->nastepny, znak);
    }
}

void negacja(Lista*& stos) { //-
    if (!stos) return;
    Char*& lista = stos->dane;
    if (!lista) {
        stos->dane = new Char{ '-', nullptr };
    }
    else if (ostatniElement(lista)->dane == '-') {
        usunOstatniElement(lista);
    }
    else {
        dodajOstatniElement(lista, '-');
    }
}

void wartBezwzgledna(Char*& lista) { //^
    if (!lista) return;
    if (ostatniElement(lista)->dane == '-') {
        usunOstatniElement(lista);
    }
}

void rozlacz(Lista*& stos) { //$
    if (!stos) return;
    Char*& lista = stos->dane;
    Char* pierwszy = lista;
    lista = lista->nastepny;
    pierwszy->nastepny = nullptr;
    dodajNaStos(stos, pierwszy);
}

void zdejmijLiczbe(Lista*& stos) { //]
    if (!stos) return;
    Char*& lista = stos->dane;
    int a = charNaInt(lista);
    char b = char(a);
    usunZeStosu(stos);
    dodajNaStos(stos, new Char{ b, nullptr });
    return;
}

void intToChar(int a, Lista*& stos) { //[
    if (!stos) return;
    if (a == 0) return;
    char b = char((a % 10) + '0');
    intToChar(a / 10, stos);
    Char* nowyChar = new Char{ b, stos->dane };
    stos->dane = nowyChar;
    return;
}

void zdejmijListe(Lista*& stos) { //[
    if (!stos) return;
    Char*& lista = stos->dane;
    if (!lista) return;
    char znak = lista->dane;
    int a = int(znak);
    usunZeStosu(stos);
    dodajNaStos(stos, nullptr);
    intToChar(a, stos);
    return;
}

void dolaczDoKonca(Char*& lista, Char* doPolaczenia) { //#
    if (!lista) {
        lista = doPolaczenia;
    }
    else if (!lista->nastepny) {
        lista->nastepny = doPolaczenia;
    }
    else {
        dolaczDoKonca(lista->nastepny, doPolaczenia);
    }
}

void dolaczNaKoniec(Lista*& stos) { //#
    if (!stos || !stos->nastepny) return;
    Char* listaA = stos->dane;
    Lista* temp = stos;
    stos = stos->nastepny;
    delete temp;
    dolaczDoKonca(stos->dane, listaA);
}

void dodajNumerInstrukcji(Lista*& stos, int* numer) { //#
    if (*numer == 0)
    {
        Char* nowyChar = new Char{ '0', nullptr };
        dodajNaStos(stos, nowyChar);
        return;
    }
    dodajNaStos(stos, nullptr);
    intToChar(*numer, stos);
}

void negacjaLogiczna(Lista*& stos) { //!
    if (!stos) return;
    Char*& lista = stos->dane;
    if (lista == nullptr || (lista->dane == '0' && lista->nastepny == nullptr)) {
        usunZeStosu(stos);
        dodajNaStos(stos, new Char{ '1', nullptr });
        return;
    }
    usunZeStosu(stos);
    dodajNaStos(stos, new Char{ '0', nullptr });
}

bool wiodace(Char*& lista) {
        if (!lista) return true;
        if (lista->dane != '0' && lista->dane !='-') return false;
    if (!lista->nastepny) return true;
        return wiodace(lista->nastepny);
}

int dlugosc(Char*& lista) {
    if (!lista) return 0;

    if (lista->dane == '0' || lista->dane=='-') {
                if (!lista->nastepny) return 0;
        if (wiodace(lista->nastepny)) return 0;
    }
    if (!lista->nastepny) return 1;
        if (lista->dane == '-') return 0 + dlugosc(lista->nastepny);
    return 1 + dlugosc(lista->nastepny);
}

bool czyUjemne(Char*& lista) { //0-dodatnie 1-ujemne
    if (!lista) return false;
    if (!lista->nastepny) {
                if (lista->dane == '-') return true;
                else return false;
    }
    return czyUjemne(lista->nastepny);
}

int przyrownanie(Char*& listaA, Char*& listaB, int licznik) { //1-a wieksze, -1-b wieksze, 0-rowne
    int wynik = 0;
    if (licznik == 1) {
            if (listaA->dane > listaB->dane) return 1;
            if (listaA->dane < listaB->dane) return -1;
            return 0;
    }
        wynik = przyrownanie(listaA->nastepny, listaB->nastepny, licznik - 1);
        if (wynik != 0) return wynik;
        if (listaA->dane > listaB->dane) return 1;
        if (listaA->dane < listaB->dane) return -1;
    return 0;
}

int porownanie(Char*& listaA, Char*& listaB) { //1-a wieksze, -1-b wieksze, 0-rowne
        if (!listaA && !listaB) return 0;
    int dlugoscA = dlugosc(listaA);
        int dlugoscB = dlugosc(listaB);
        bool ujemneA = czyUjemne(listaA);
        bool ujemneB = czyUjemne(listaB);
    if (dlugoscA == 0 && dlugoscB == 0) return 0;
    if (ujemneA == 1 && ujemneB == 0) return -1;
    if (ujemneA == 0 && ujemneB == 1) return 1;
        if (dlugoscA > dlugoscB) return (ujemneA == 1) ? -1 : 1;
        if (dlugoscB > dlugoscA) return (ujemneB == 1) ? 1 : -1;
    int wynik=przyrownanie(listaA, listaB, dlugoscA);
    if (ujemneA == 1 && ujemneB == 1) {
                return -1 * wynik;
    }
        return wynik;
}

bool czySkokWarunkowy(Char*& listaW) { //?
        if (!listaW) return false;
        if (listaW->dane == '0' && listaW->nastepny == nullptr) return false;
        return true;
}
void skokWarunkowy(Char*& listaT, Char*& listaW, int* numerInstrukcji) { //?
    if (listaW == nullptr || !czySkokWarunkowy(listaW)) return;
        if (!listaT) return;
        *numerInstrukcji = charNaInt(listaT)-1;
    return;
}

void dodawanie(Char*& listaA, Char*& listaB, Char*& wynik, int licznikA, int licznikB, int przeniesienie = 0) {//a.length>=b.length
        if (!listaA && !listaB) return;
    int a, b;
        a = listaA->dane - '0';
    if (licznikB == 0) b = 0;
        else b = listaB->dane - '0';
    
        int suma = a + b + przeniesienie;
        if (suma >= 10) {
                przeniesienie = 1;
                suma -= 10;
        }
        else {
                przeniesienie = 0;
        }
    if (licznikA == 1) {
        dodajOstatniElement(wynik, suma + '0');
        if (przeniesienie == 1) dodajOstatniElement(wynik, '1');
        return;
    }
    dodajOstatniElement(wynik, suma + '0');
        if (licznikA > 1 && licznikB > 1) dodawanie(listaA->nastepny, listaB->nastepny, wynik, licznikA - 1, licznikB - 1, przeniesienie);
        if (licznikA > 1 && (licznikB == 1 || licznikB==0)) dodawanie(listaA->nastepny, listaB, wynik, licznikA - 1, 0, przeniesienie);
    
}

void odejmowanie(Char*& listaA, Char*& listaB, Char*& wynik, int licznikA, int licznikB, int przeniesienie = 0) {//a>=b
        if (!listaA && !listaB) return;
        int a, b;
        a = listaA->dane - '0';
        if (licznikB == 0) b = 0;
        else b = listaB->dane - '0';

        int roznica = a - b - przeniesienie;
        if (roznica < 0) {
                przeniesienie = 1;
                roznica += 10;
        }
        else {
                przeniesienie = 0;
        }
        if (licznikA == 1) {
        dodajOstatniElement(wynik, roznica + '0');
                return;
        }
        dodajOstatniElement(wynik, roznica + '0');
        if (licznikA > 1 && licznikB > 1) odejmowanie(listaA->nastepny, listaB->nastepny, wynik, licznikA - 1, licznikB - 1, przeniesienie);
        if (licznikA > 1 && (licznikB == 1 || licznikB == 0)) odejmowanie(listaA->nastepny, listaB, wynik, licznikA - 1, 0, przeniesienie);

}

Char* znajdzOstatni(Char*& lista) {
        if (!lista) return nullptr;
        if (!lista->nastepny) return lista;
        return znajdzOstatni(lista->nastepny);
}

void usunWiodaceZera(Char*& lista) {
    if (!lista) return;
        Char* ostatni = znajdzOstatni(lista);
    if (ostatni->dane == '0') {
                usunOstatniElement(lista);
                usunWiodaceZera(lista);
    }
}


void dzialania(Char*& listaA, Char*& listaB, Char*& wynik) {//+
        if (!listaA || !listaB) return;
        bool ujemneA = czyUjemne(listaA);
        bool ujemneB = czyUjemne(listaB);
        int dlugoscA = dlugosc(listaA);
        int dlugoscB = dlugosc(listaB);
    if (!ujemneA && !ujemneB) {
                if (dlugoscA >= dlugoscB) dodawanie(listaA, listaB, wynik, dlugoscA, dlugoscB);
                else dodawanie(listaB, listaA, wynik, dlugoscB, dlugoscA);
        return;
        }
    else if (ujemneA && ujemneB) {
        if (dlugoscA >= dlugoscB) dodawanie(listaA, listaB, wynik, dlugoscA, dlugoscB);
        else dodawanie(listaB, listaA, wynik, dlugoscB, dlugoscA);
                dodajOstatniElement(wynik, '-');
        return;
    }
    else if (ujemneA && !ujemneB) {
                wartBezwzgledna(listaA);
        if (porownanie(listaA, listaB) == 1) {
                        odejmowanie(listaA, listaB, wynik, dlugoscA, dlugoscB);
                        usunWiodaceZera(wynik);
                        if (wynik == nullptr) dodajOstatniElement(wynik, '0');
                        if(porownanie(listaA, listaB)!=0) dodajOstatniElement(wynik, '-');
            return;
        }
        else {
                        odejmowanie(listaB, listaA, wynik, dlugoscB, dlugoscA);
            usunWiodaceZera(wynik);
            if (wynik == nullptr) dodajOstatniElement(wynik, '0');
            return;
        }
        }
    else if (!ujemneA && ujemneB) {
                wartBezwzgledna(listaB);
        if (porownanie(listaA, listaB) == 1) {
                        odejmowanie(listaA, listaB, wynik, dlugoscA, dlugoscB);
            usunWiodaceZera(wynik);
            if (wynik == nullptr) dodajOstatniElement(wynik, '0');
                        return;
                }
                else {
                        odejmowanie(listaB, listaA, wynik, dlugoscB, dlugoscA);
            usunWiodaceZera(wynik);
            if (wynik == nullptr) dodajOstatniElement(wynik, '0');
                        if (porownanie(listaA, listaB)!=0) dodajOstatniElement(wynik, '-');
                        return;
        }
    }
}


void wykonajInstrukcje(char instrukcja, Lista*& stos, const char*& wejscie, int* numerInstrukcji) {
    switch (instrukcja) {
    case '\'':
        dodajNaStos(stos, nullptr);
        break;
    case ',':
        usunZeStosu(stos);
        break;
    case ':':
        if (stos) {
            dodajNaStos(stos, skopiujListeChar(szczytStosu(stos)));
        }
        break;
    case ';':
        zamienDwaGorne(stos);
        break;
    case '@':
        if (stos) {
            Char* A = szczytStosu(stos);
            if (A) {
                int indeks = charNaInt(A);
                usunZeStosu(stos);
                Lista* docelowyWezel = wezWezelNaPozycji(stos, indeks);
                if (docelowyWezel) {
                    dodajNaStos(stos, skopiujListeChar(docelowyWezel->dane));
                }
            }
        }
        break;
    case '&':
        wypiszStosSformatowany(stos);
        break;
    case '.':
        if (stos && *wejscie) {
            Char* A = new Char{ *wejscie, stos->dane };
            stos->dane = A;
            wejscie++;
        }
        break;
    case '>':
        if (stos) {
            wypiszSzczytStosu(szczytStosu(stos));
            usunZeStosu(stos);
        }
        break;
    case '-':
        negacja(stos);
        break;
    case '^':
        if (stos) {
            Char*& lista = stos->dane;
            wartBezwzgledna(lista);
        }
        break;
    case '$':
        rozlacz(stos);
        break;
    case ']':
        zdejmijLiczbe(stos);
        break;
    case '[':
        zdejmijListe(stos);
        break;
    case '#':
        dolaczNaKoniec(stos);
        break;
    case '~':
        dodajNumerInstrukcji(stos, numerInstrukcji);
        break;
    case '!':
        negacjaLogiczna(stos);
        break;
    case '=':
        if (stos) {
            Char*& listaA = stos->dane;
            Char*& listaB = stos->nastepny->dane;
            int wynik = porownanie(listaA, listaB);
            usunZeStosu(stos);
            usunZeStosu(stos);
            if (wynik == 0) {
                dodajNaStos(stos, new Char{ '1', nullptr });
            }
            else {
                dodajNaStos(stos, new Char{ '0', nullptr });
            }
        }
        break;
    case '<':
        if (stos) {
            Char*& listaA = stos->dane;
            Char*& listaB = stos->nastepny->dane;
            int wynik = porownanie(listaA, listaB);
            usunZeStosu(stos);
            usunZeStosu(stos);
            if (wynik == 1) {
                dodajNaStos(stos, new Char{ '1', nullptr });
            }
            else {
                dodajNaStos(stos, new Char{ '0', nullptr });
            }
        }
        break;
    case '?':
        if (stos) {
                        Char*& listaT = stos->dane;
                        Char*& listaW = stos->nastepny->dane;
            skokWarunkowy(listaT, listaW, numerInstrukcji);
                        usunZeStosu(stos);
                        usunZeStosu(stos);
        }
        break;
    case '+':
        if (stos) {
                        Char*& listaA = stos->dane;
                        Char*& listaB = stos->nastepny->dane;
            Char* wynik = nullptr;
                        dzialania(listaA, listaB, wynik);
            usunZeStosu(stos);
            usunZeStosu(stos);
                        usunWiodaceZera(wynik);
                        if (wynik == nullptr) {
                                dodajNaStos(stos, new Char{ '0', nullptr });
                        }
                        else {
                                dodajNaStos(stos, wynik);
                        }
                }
                break;
    default:
        if (stos) {
            Char* nowyChar = new Char{ instrukcja, stos->dane };
            stos->dane = nowyChar;
        }
        break;
    }
}

void uruchomProgram(const char program[], const char* wejscie, Lista*& stos, int numerInstrukcji = 0) {
    while (program[numerInstrukcji]) {
                wykonajInstrukcje(program[numerInstrukcji], stos, wejscie, &numerInstrukcji);
        numerInstrukcji++;
    }
}

void usunWszystkieZeStosu(Lista*& stos) {
    if (stos) {
        usunZeStosu(stos);
        usunWszystkieZeStosu(stos);
    }
}

int main() {
    char program[20001];
    char wejscie[20001];
    cin >> program >> wejscie;

    Lista* stos = nullptr;
    uruchomProgram(program, wejscie, stos);
    usunWszystkieZeStosu(stos);
    return 0;
}