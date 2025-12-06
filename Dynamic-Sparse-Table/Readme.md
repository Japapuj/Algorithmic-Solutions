# 🌳 Dynamic Sparse Table (Trie-based)

Niestandardowa implementacja struktury danych łączącej cechy **tablicy rzadkiej** oraz **drzewa Trie**. Projekt powstał jako alternatywa dla tablic haszujących, oferując deterministyczny czas dostępu w przypadku pesymistycznym.

## 🧠 Teoria i Zasada Działania

Struktura służy do przechowywania wartości indeksowanych kluczami z szerokiego uniwersum. Drzewo jest parametryzowane dwiema wartościami:
* **$N$**: Liczba węzłów potomnych korzenia.
* **$K$**: Liczba węzłów potomnych dla każdego innego węzła (poza korzeniem).

### Mechanika Adresowania (Mapping)
W przeciwieństwie do klasycznych drzew BST, pozycja elementu w tym drzewie jest ściśle wyliczana matematycznie na podstawie operacji **modulo** i **dzielenia całkowitego**:

1.  **Korzeń:** Jeśli jest wolny, klucz jest zapisywany w korzeniu.
2.  **Poziom 1:** Wybieramy dziecko o indeksie `index = key % N`. Klucz jest modyfikowany: `key = key / N`.
3.  **Kolejne poziomy:** Wybieramy dziecko o indeksie `index = key % K`. Klucz jest modyfikowany: `key = key / K`.

Dzięki temu struktura działa podobnie do systemu liczbowego o zmiennej podstawie ($N$, a potem $K$).

### Operacje

* **Insert (`I`):** Wstawia klucz. Rozwiązuje kolizje schodząc w głąb drzewa aż do napotkania wolnego węzła.
* **Lookup (`L`):** Sprawdza obecność klucza w czasie proporcjonalnym do wysokości drzewa (zależnej od wielkości klucza oraz parametrów $N, K$).
* **Delete (`D`):** Najbardziej złożona operacja. Usuwanie węzła wewnętrznego wymaga zachowania spójności drzewa.
    * *Strategia:* Znalezienie **kandydata do zamiany** (węzeł zewnętrzny/liść) znajdującego się "najbardziej na lewo" w poddrzewie usuwanego węzła.
    * Wartość kandydata jest kopiowana na miejsce usuwanego elementu, a sam liść jest fizycznie usuwany z pamięci.
* **Print (`P`):** Przechodzenie drzewa metodą **Preorder Traversal** w celu wizualizacji jego struktury.

## 🛠️ Technologie
* **Język:** C++
* **Optymalizacja:** Użycie `scanf`/`printf` dla szybszego I/O.
* **Pamięć:** Dynamiczna alokacja węzłów (`struct Node`, `new`, `delete[]`) – struktura zajmuje pamięć tylko dla istniejących ścieżek (stąd "Sparse Table").

## 🚀 Jak uruchomić i przetestować

Program działa w trybie wsadowym, przyjmując komendy ze standardowego wejścia.

### Kompilacja
```bash
g++ dynamic_sparse_table.cpp -o sparse_table
```
Format Wejścia
  1. Liczba zestawów testowych.
  2. Zakres kluczy (Min, Max).
  3. Parametry.Lista komend (I, L, D, P).

Przykładowy test:
```bash
echo "1
0 100
2 2
I 10
I 2
I 12
L 10
L 5
D 10
P" | ./sparse_table
```
Autor: Dominik Szwed Student Informatyki, Politechnika Gdańska
