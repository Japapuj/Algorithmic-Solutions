# 🛰️ Emulator Procesora Stosowego (Model A15D)

> "Państwo Gedanum postanowiło podbić kosmos... Sondy muszą być inteligentne i energooszczędne, do sterowania nimi potrzebny jest więc nowy procesor."

Projekt ten jest implementacją emulatora fikcyjnego procesora **STOS** (Stosowy Translator Obiektów Symbolicznych), stworzonego na potrzeby symulacji sterowania sondami kosmicznymi. Rozwiązanie łączy w sobie implementację maszyny stosowej z obsługą **Wielkich Liczb (BigInt)**.

## 📜 Fabuła Zadania (Kontekst)
Zaprojektowanie procesora zlecono komisji Ekspertów Technologii Interstelarnych. Twoim zadaniem było napisanie emulatora, aby przyspieszyć prace nad kolonizacją nowych planet.
*Zadanie pochodzi z lokalnego konkursu programistycznego (Gedanum = Gdańsk).*

## ⚙️ Architektura Maszyny

Procesor składa się z trzech głównych elementów:
1.  **Pamięć programu:** Ciąg instrukcji (jeden znak = jedna instrukcja).
2.  **Wskaźnik instrukcji (IP):** Wskazuje na aktualnie wykonywaną operację.
3.  **Stos danych:** Przechowuje **listy znaków**.

### Reprezentacja Danych (BigInt)
Unikalną cechą tego procesora jest sposób przechowywania liczb. Są one trzymane jako listy cyfr w odwrotnej kolejności:
* Liczba `123` -> Lista `321`
* Liczba `-1234` -> Lista `4321-` (minus zawsze na końcu)

Dzięki temu procesor obsługuje arytmetykę liczb o **dowolnej długości** (ograniczonej tylko pamięcią), co wymagało zaimplementowania własnych algorytmów dodawania i odejmowania na listach (Big Integer Arithmetic).

## 🛠️ Lista Instrukcji (Instruction Set)

| Znak | Opis Instrukcji |
| :---: | :--- |
| `'` | Włóż na stos pustą listę. |
| `,` | Zdejmij (usuń) listę z wierzchołka stosu. |
| `:` | Duplikuj: włóż na stos kopię listy z wierzchołka. |
| `;` | Swap: zamień miejscami dwie górne listy. |
| `@` | Pick: zdejmij liczbę `A`, skopiuj na wierzchołk listę z `A`-tej pozycji głębiej. |
| `.` | Input: wczytaj znak i dołącz na początek listy na szczycie. |
| `>` | Output: wypisz i usuń pierwszy znak z listy na szczycie. |
| `!` | Negacja logiczna (zamienia puste/0 na 1, inne na 0). |
| `<` | Mniejsze niż (`B < A`). Wynik 1 lub 0. |
| `=` | Równe (`B == A`). Wynik 1 lub 0. |
| `~` | Push IP: włóż na stos aktualny numer instrukcji. |
| `?` | Skok warunkowy: jeśli `W` != 0, skocz do adresu `T`. |
| `-` | Negacja arytmetyczna (dodaj/usuń minus na końcu). |
| `^` | Wartość bezwzględna (usuń minus). |
| `$` | Split: odłącz pierwszy znak listy i włóż go jako nową listę na stos. |
| `#` | Join: zdejmij listę `A` i dołącz ją na koniec listy pod spodem. |
| `+` | Dodawanie dużych liczb (`A + B`). |
| `&` | Debug: Wypisz całą zawartość stosu. |
| `]` | Int to Char (ASCII). |
| `[` | Char to Int (ASCII). |
| `Inne` | Każdy inny znak jest dołączany na początek listy na szczycie stosu. |

## 🧪 Przykłady Działania

### Test 1: Operacje na listach i arytmetyka
**Program:** `'123'-456&+&`
**Wyjście:**
```text
1: 321
0: 654-
0: 333-
```
🚀 Jak uruchomić
```
g++ procesor_stosowy.cpp -o emulator
# Uruchomienie z ręcznym wpisywaniem (najpierw program, potem dane):
./emulator
```
Autor: Dominik Szwed Student Informatyki, Politechnika Gdańska
