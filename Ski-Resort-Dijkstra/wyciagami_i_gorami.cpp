#include <iostream>
using namespace std;

const int INF = INT_MAX;

struct Pole {
        int czas;
        int x, y;
};

struct Wyciag {
        int cel_x;
        int cel_y;
        int czas_jazdy;
        int co_ile_minut;
        Wyciag* next;
};



void swap(int i, int j, Pole*& heap) {
        Pole temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
}


void heapify_up(int i, Pole*& heap) {
        while (i > 0) {
                int parent = (i - 1) / 2;
                if (heap[i].czas < heap[parent].czas) {
                        swap(i, parent, heap);
                        i = parent;
                }
                else {
                        break;
                }
        }
}


void heapify_down(int i, Pole*& heap, int& heap_size) {
        while (true) {
                int lewy = 2 * i + 1;
                int prawy = 2 * i + 2;
                int najmniejszy = i;

                if (lewy < heap_size && heap[lewy].czas < heap[najmniejszy].czas) {
                        najmniejszy = lewy;
                }
                if (prawy < heap_size && heap[prawy].czas < heap[najmniejszy].czas) {
                        najmniejszy = prawy;
                }

                if (najmniejszy != i) {
                        swap(i, najmniejszy, heap);
                        i = najmniejszy;
                }
                else {
                        break;
                }
        }
}


void push(Pole p, Pole*& heap, int& heap_size) {
        heap[heap_size] = p;
        heapify_up(heap_size, heap);
        heap_size++;
}


Pole top(Pole* heap) {
        return heap[0];
}


void pop(Pole*& heap, int& heap_size) {
        heap_size--;
        heap[0] = heap[heap_size];
        heapify_down(0, heap, heap_size);
}


bool empty(int& heap_size) {
        return heap_size == 0;
}


void dodaj_wyciag(Wyciag*** wyciag_head, int x1, int y1, int x2, int y2, int czas_jazdy, int co_ile_minut) {
        Wyciag* nowy = new Wyciag;
        nowy->cel_x = x2;
        nowy->cel_y = y2;
        nowy->czas_jazdy = czas_jazdy;
        nowy->co_ile_minut = co_ile_minut;
        nowy->next = wyciag_head[y1][x1];
        wyciag_head[y1][x1] = nowy;
}

int main()
{ // mapa[kolumny][wiersze]

        int heap_size = 0;
        //wejscie danych
        int mapaX, mapaY;
        cin >> mapaX >> mapaY;

        int startX, startY;
        cin >> startX >> startY;

        int celX, celY;
        cin >> celX >> celY;

        int wyciagiL;
        cin >> wyciagiL;


        //wyciagi
        Wyciag*** wyciag_head = nullptr;

        if (wyciagiL != 0) {
                //alokacja
                wyciag_head = new Wyciag * *[mapaY];
                for (int i = 0; i < mapaY; i++) {
                        wyciag_head[i] = new Wyciag * [mapaX];
                        for (int j = 0; j < mapaX; j++) {
                                wyciag_head[i][j] = nullptr;
                        }
                }
                //wejscie danych
                for (int i = 0; i < wyciagiL; i++) {
                        int x1, y1, x2, y2, czas_jazdy, co_ile_minut;
                        cin >> x1 >> y1 >> x2 >> y2 >> czas_jazdy >> co_ile_minut;
                        dodaj_wyciag(wyciag_head, x1, y1, x2, y2, czas_jazdy, co_ile_minut);
                }
        }
        //alokacja
        int** mapa;
        int** czas;
        bool** visited;

        visited = new bool* [mapaY];
        mapa = new int* [mapaY];
        czas = new int* [mapaY];


        for (int i = 0; i < mapaY; i++) {
                mapa[i] = new int[mapaX];
                czas[i] = new int[mapaX];
                visited[i] = new bool[mapaX];
        }

        for (int i = 0; i < mapaY; i++) {
                for (int j = 0; j < mapaX; j++) {
                        cin >> mapa[i][j];
                        czas[i][j] = INF;
                        visited[i][j] = false;
                }
        }
        czas[startY][startX] = 0;

        Pole* heap;
        heap = new Pole[(mapaX * mapaY + wyciagiL * 10) + 1]; // +1 zapasowo, bo 0-indeks


        push({ 0, startX, startY }, heap, heap_size);

        int dx[] = { -1,1,0,0 };
        int dy[] = { 0,0,-1,1 };


        //algorytm dijkstry
        while (!empty(heap_size)) {
                Pole p = top(heap);
                pop(heap, heap_size);

                int x = p.x;
                int y = p.y;
                int czasP = p.czas;

                if (visited[y][x]) {
                        continue;
                }
                visited[y][x] = true;
                if (czasP > czas[y][x])
                        continue;
                for (int kierunek = 0; kierunek < 4; kierunek++) {
                        int nx = x + dx[kierunek];
                        int ny = y + dy[kierunek];

                        if (nx >= 0 && nx < mapaX && ny >= 0 && ny < mapaY) {
                                int koszt;
                                if (mapa[ny][nx] > mapa[y][x]) {
                                        koszt = mapa[ny][nx] - mapa[y][x] + 1;
                                }
                                else {
                                        koszt = 1;
                                }
                                if (czas[ny][nx] > czasP + koszt) {
                                        czas[ny][nx] = czasP + koszt;
                                        push({ czas[ny][nx], nx, ny }, heap, heap_size);
                                }
                        }
                }
                //osluga wyciagow z (x,y)
                if (wyciagiL != 0) {
                        Wyciag* w = wyciag_head[y][x];
                        while (w != nullptr)
                        {
                                int odjazd_co = w->co_ile_minut;
                                int oczekiwanie = (odjazd_co - (czasP % odjazd_co)) % odjazd_co;
                                int nowy_czas = czasP + oczekiwanie + w->czas_jazdy;

                                int tx = w->cel_x;
                                int ty = w->cel_y;

                                if (nowy_czas < czas[ty][tx]) {
                                        czas[ty][tx] = nowy_czas;
                                        push({ czas[ty][tx], tx, ty }, heap, heap_size);
                                }
                                w = w->next;
                        }
                }
        }

        cout << czas[celY][celX] << endl;
        if (wyciag_head != nullptr) {
                for (int i = 0; i < mapaY; i++) {
                        for (int j = 0; j < mapaX; j++) {
                                Wyciag* w = wyciag_head[i][j];
                                while (w != nullptr) {
                                        Wyciag* temp = w;
                                        w = w->next;
                                        delete temp;
                                }
                        }
                        delete[] wyciag_head[i];
                }
        }
        for (int i = 0; i < mapaY; i++) {
                delete[] mapa[i];
                delete[] czas[i];
                delete[] visited[i];
        }
        delete[] wyciag_head;
        delete[] mapa;
        delete[] czas;
        delete[] heap;
        delete[] visited;

        return 0;
}