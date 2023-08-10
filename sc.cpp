#include <iostream>
// Tek yönlü bağlı liste için düğüm yapısı
struct Dugum {
    int veri;
    int oncelik;
    struct Dugum* sonraki;
};

// Öncelik değerine göre bağlı listeye düğüm ekler
void ekle(struct Dugum** bas, int veri, int oncelik) {
    struct Dugum* yeniDugum = (struct Dugum*)malloc(sizeof(struct Dugum));
    yeniDugum->veri = veri;
    yeniDugum->oncelik = oncelik;
    yeniDugum->sonraki = NULL;

    if (*bas == NULL) {
        *bas = yeniDugum;
    }
    else if ((*bas)->oncelik >= oncelik) {
        yeniDugum->sonraki = *bas;
        *bas = yeniDugum;
    }
    else {
        struct Dugum* simdiki = *bas;
        while (simdiki->sonraki != NULL && simdiki->sonraki->oncelik < oncelik) {
            simdiki = simdiki->sonraki;
        }
        yeniDugum->sonraki = simdiki->sonraki;
        simdiki->sonraki = yeniDugum;
    }
}

// Öncelik değerine göre düğümlerin yerini değiştirir
void dugumDegistir(struct Dugum** bas, int p1, int p2) {
    if (p1 == p2) return;

    struct Dugum* oncekiX = NULL, *simdikiX = *bas;
    while (simdikiX && simdikiX->oncelik != p1) {
        oncekiX = simdikiX;
        simdikiX = simdikiX->sonraki;
    }

    struct Dugum* oncekiY = NULL, *simdikiY = *bas;
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

    struct Dugum* gecici = simdikiY->sonraki;
    simdikiY->sonraki = simdikiX->sonraki;
    simdikiX->sonraki = gecici;

    // Düğümlerin önceliklerini doğru şekilde güncelle
    int tempOncelik = simdikiX->oncelik;
    simdikiX->oncelik = simdikiY->oncelik;
    simdikiY->oncelik = tempOncelik;
}

// Bağlı listeyi yazdırır
void listeYazdir(struct Dugum* bas) {
    while (bas != NULL) {
        printf("%d ", bas->veri);
        bas = bas->sonraki;
    }
    printf("\n");
}

int main() {
    printf("soru2.c calisti:\n");
    struct Dugum* bas = NULL;

    int sayiDizisi[] = {21, 40, 30, 25, 50, 24, 14, 6, 27};
    int oncelikDizisi[] = {1, 2, 3, 1, 1, 2, 3, 1, 3};
    for (int i = 0; i < 9; i++) {
        ekle(&bas, sayiDizisi[i], oncelikDizisi[i]);
    }
    listeYazdir(bas);
    int p1, p2;

    while (1) {
        printf("Yerlerini değiştirmek istediğiniz düğümlerin öncelik değerlerini girin (-1 -1 girerek çıkış yapın):\n");
        scanf("%d %d", &p1, &p2);
        if (p1 == -1 && p2 == -1) {
            printf("Program sonlandırıldı.\n");
            break;
        }
        listeYazdir(bas);

        dugumDegistir(&bas, p1, p2);
        listeYazdir(bas);
        struct Dugum* simdiki = bas;
        while (simdiki != NULL) {
            if (simdiki->oncelik == p1) {
                simdiki->oncelik = p2;
            }
            else if (simdiki->oncelik == p2) {
                simdiki->oncelik = p1;
            }
            simdiki = simdiki->sonraki;
        }

        printf("%d öncelik değeri %d iken %d; %d öncelik değeri %d iken %d yapılmıştır.\n", p1, p1, p2, p2, p2, p1);

        printf("\n");
    }

    return 0;
}
