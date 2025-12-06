# ⛷️ Najkrótsza Ścieżka w Terenie z Wyciągami (Dijkstra)

> "Jesteś przewodnikiem górskim, który musi zaplanować najszybszą trasę na szczyt dla grupy turystów. Masz do dyspozycji mapę wysokości terenu oraz rozkład jazdy lokalnych wyciągów narciarskich. Pamiętaj: wspinaczka zajmuje więcej czasu niż schodzenie, a na wyciąg czasem trzeba poczekać!"

Projekt rozwiązuje problem znalezienia najkrótszej ścieżki w grafie ważonym (siatka terenu), gdzie wagi krawędzi są dynamiczne (zależą od czasu dotarcia do danego węzła – harmonogram wyciągów).

## 🧩 Opis Problemu

Teren reprezentowany jest jako siatka pól o określonej wysokości. Poruszanie się między polami rządzi się fizyką górską:
1.  **Podejście (Pod górę):** Kosztowne czasowo. Czas = `Różnica wysokości + 1 min`.
2.  **Zejście/Płasko:** Szybkie. Czas = `1 min`.

### Mechanika Wyciągów (Time-Dependent Edges)
Dodatkowym elementem są wyciągi ("teleporty"), które łączą odległe punkty mapy.
* **Czas podróży:** Stała wartość (np. 10 minut jazdy).
* **Harmonogram (Cykliczność):** Wyciągi kursują co `K` minut. Jeśli dotrzesz na stację w minucie niebędącej wielokrotnością `K`, musisz poczekać.
* **Wzór na oczekiwanie:** `Czekanie = (Interwał - (AktualnyCzas % Interwał)) % Interwał`.

## 🛠️ Implementacja Techniczna

Rozwiązanie opiera się na zmodyfikowanym **Algorytmie Dijkstry**. Zamiast używać gotowych kontenerów STL, w celu demonstracji zrozumienia struktur danych, zaimplementowano własne rozwiązania:

* **Custom Min-Heap:** Ręczna implementacja kopca binarnego (funkcje `heapify_up`, `heapify_down`, `push`, `pop`) służąca jako Kolejka Priorytetowa.
* **Zarządzanie Pamięcią:** Ręczna alokacja i dealokacja wielowymiarowych tablic dynamicznych (`int**`, `bool**`, `Wyciag***`) przy użyciu operatorów `new` i `delete`.
* **Reprezentacja Grafu:** Hybrydowa – siatka 2D dla ruchu pieszego + listy sąsiedztwa dla wyciągów w każdym węźle.

## 🚀 Jak uruchomić i przetestować

Program przyjmuje dane ze standardowego wejścia (`stdin`). Format danych:
`WymiaryMapy -> Start -> Meta -> LiczbaWyciągów -> OpisWyciągów -> MapaWysokości`.

### Kompilacja
```bash
g++ wyciagami_i_gorami.cpp -o narty
```
2. Mapa z wyciągami (Logika oczekiwania)
Tutaj kluczowe jest wybranie wyciągu, na który trzeba dłużej poczekać, ale jedzie szybciej lub startuje bliżej.
```bash
echo "9 9 0 0 8 8 5
0 1 2 0 5 2
0 1 2 0 1 3
2 0 4 0 3 7
4 1 8 8 20 11
4 2 8 8 10 12
0 9 0 9 0 9 0 9 0
0 9 0 9 0 9 0 9 0
0 9 0 9 0 9 0 9 0
0 9 0 9 0 9 0 9 0
0 9 0 9 0 9 0 9 0
0 9 0 9 0 9 0 9 0
0 9 0 9 0 9 0 9 0
0 9 0 9 0 9 0 9 0
0 9 0 9 0 9 0 9 0" | ./narty
```
Oczekiwany wynik: 22

Autor: Dominik Szwed Student Informatyki, Politechnika Gdańska
