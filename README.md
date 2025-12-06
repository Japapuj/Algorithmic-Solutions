# 🧮 Algorithmic Solutions & Data Structures (C++)

Zbiór zaawansowanych implementacji algorytmicznych zrealizowanych w języku C++. Repozytorium koncentruje się na niskopoziomowej optymalizacji, własnych implementacjach struktur danych (bez użycia STL tam, gdzie to możliwe) oraz rozwiązywaniu złożonych problemów logicznych.

## 📂 Przegląd Projektów

### 1. Symulator Maszyny Stosowej (`/Stack-Machine-Emulator`)
* **Plik:** `procesor_stosowy.cpp`
* **Opis:** Kompletny emulator wirtualnego procesora opartego na architekturze stosowej. Program interpretuje ciąg instrukcji (kod ezoteryczny) operujący na danych.
* **Kluczowe mechaniki:**
    * **Big Integer Arithmetic:** Implementacja arytmetyki na bardzo dużych liczbach przechowywanych jako **listy jednokierunkowe** (dodawanie, odejmowanie, porównywanie liczb o dowolnej długości).
    * **Zarządzanie pamięcią:** Ręczna obsługa wskaźników i struktur listowych (`struct Lista`, `struct Char`).
    * **Logika sterowania:** Obsługa skoków warunkowych, pętli i operacji logicznych.

### 2. Najkrótsza Ścieżka w Terenie z Wyciągami (`/Ski-Resort-Dijkstra`)
* **Plik:** `wyciagami_i_gorami.cpp`
* **Opis:** Rozwiązanie problemu optymalizacyjnego polegającego na znalezieniu najszybszej trasy w terenie górzystym (siatka 2D) z uwzględnieniem "teleportów" (wyciągów narciarskich) działających w określonych interwałach czasowych.
* **Algorytm:** **Dijkstra** zmodyfikowany o logikę oczekiwania na cykliczne zdarzenia (wyciągi).
* **Custom Data Structures:**
    * Własna implementacja **Kopca Binarnego** (Priority Queue) z operacjami `heapify_up` i `heapify_down`.
    * Reprezentacja grafu na siatce z dynamiczną alokacją tablic 2D/3D.

### 3. Dynamiczna Tablica Rzadka (`/Dynamic-Sparse-Table`)
* **Plik:** `dynamic_sparse_table.cpp`
* **Opis:** Implementacja dynamicznej struktury drzewiastej (zmienny współczynnik rozgałęzienia $n$ i $k$) służącej do efektywnego przechowywania i wyszukiwania wartości w rzadkiej przestrzeni kluczy.
* **Funkcjonalności:** Wstawianie (`Insert`), Usuwanie (`Remove`), Wyszukiwanie (`Find`) oraz przechodzenie drzewa (`Inorder Traversal`).
* **Zastosowanie:** Optymalizacja zużycia pamięci przy przechowywaniu danych o dużej rozpiętości indeksów.

## 🛠️ Technologie
* **Język:** C++
* **Paradygmaty:** Programowanie strukturalne, ręczne zarządzanie pamięcią (`new`/`delete`), wskaźniki.
* **Algorytmy:** Teoria grafów (Shortest Path), Struktury Danych (Heap, Linked List, Trees), Arytmetyka precyzyjna (BigInt).

---
Autor: Dominik Szwed
Student Informatyki, Politechnika Gdańska
