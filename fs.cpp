#include <iostream>
using namespace std;
// Tek yönlü bağlı liste için düğüm yapısı
struct Dugum {
    int veri;
    int oncelik;
    Dugum* sonraki;
};

// Öncelik değerine göre bağlı listeye düğüm ekler
void ekle(Dugum** bas, int veri, int oncelik) {
    Dugum* yeniDugum = new Dugum;
    yeniDugum->veri = veri;
    yeniDugum->oncelik = oncelik;

    if (*bas == NULL || (*bas)->oncelik >= oncelik) {
        yeniDugum->sonraki = *bas;
        *bas = yeniDugum;
    }
    else {
        Dugum* simdiki = *bas;
        while (simdiki->sonraki != NULL && simdiki->sonraki->oncelik < oncelik) {
            simdiki = simdiki->sonraki;
        }
        yeniDugum->sonraki = simdiki->sonraki;
        simdiki->sonraki = yeniDugum;
    }
}

// Öncelik değerine göre düğümlerin yerini değiştirir
void dugumDegistir(Dugum** bas, int p1, int p2) {
    if (p1 == p2) return;

    Dugum* oncekiX = NULL, * simdikiX = *bas;
    while (simdikiX && simdikiX->oncelik != p1) {
        oncekiX = simdikiX;
        simdikiX = simdikiX->sonraki;
    }

    Dugum* oncekiY = NULL, * simdikiY = *bas;
    while (simdikiY && simdikiY->oncelik != p2) {
        oncekiY = simdikiY;
        simdikiY = simdikiY->sonraki;
    }

    if (simdikiX == NULL || simdikiY == NULL)
        return;

    if (oncekiX != NULL)
        oncekiX->sonraki = simdikiY;
    else
        *bas = simdikiY;

    if (oncekiY != NULL)
        oncekiY->sonraki = simdikiX;
    else
        *bas = simdikiX;

    Dugum* gecici = simdikiY->sonraki;
    simdikiY->sonraki = simdikiX->sonraki;
    simdikiX->sonraki = gecici;

    // Düğümlerin önceliklerini doğru şekilde güncelle
    int tempOncelik = simdikiX->oncelik;
    simdikiX->oncelik = simdikiY->oncelik;
    simdikiY->oncelik = tempOncelik;
}

// Bağlı listeyi yazdırır
void listeYazdir(Dugum* bas) {
    while (bas != NULL) {
        cout << bas->veri << " ";
        bas = bas->sonraki;
    }
    cout << endl;
}


int main() {
    Dugum* bas = NULL;

    int sayiDizisi[] = {21, 40, 30, 25, 50, 24, 14, 6, 27};
    int oncelikDizisi[] = {1, 2, 3, 1, 1, 2, 3, 1, 3};

    for (int i = 0; i < 9; i++) {
        ekle(&bas, sayiDizisi[i], oncelikDizisi[i]);
    }

    listeYazdir(bas);

    int p1, p2;
    cout << "Yerlerini değiştirmek istediğiniz düğümlerin öncelik değerlerini girin (-1 -1 girerek çıkış yapın):" << endl;
    cin >> p1 >> p2;

    while (p1 != -1 && p2 != -1) {
        dugumDegistir(&bas, p1, p2);
        listeYazdir(bas);
        cin >> p1 >> p2;
    }

    return 0;
}
