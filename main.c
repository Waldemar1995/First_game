#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define kl 20   //zak³adana liczba klocków
#define pl 40     //zak³adany rozmiaw planszy

void init(int *id, int *p1, int *p2, int *p3, int *p4, int **pla){ //inicjalizacja klockow i planszy

    int i, m, n;

    for (i = 0; i<kl; i++){     //nadanie pocz¹tkowych wartoœci dla klocków
        id[i] = i;
        p1[i] = 0;
        p2[i] = 0;
        p3[i] = 0;
        p4[i] = 0;
    }
    for (m = 0; m < pl; m++){     //nadanie pocz¹tkowych wartoœci dla planszy
        for(n = 0; n < pl; n++) pla[m][n] = 0;
    }

}

int main()
{
    int i, j, k, l, m, n, p;

    int plansza[pl][pl]; //tablica z identyfikatorami planszy do gry
    int ID[kl]; //identyfikator ka¿dego z 20 kloców
    int pole1[kl]; //pierwsze pole ka¿dego klocka, trzy opcje, 1-city, 2-road, 3-plain
    int pole2[kl];
    int pole3[kl];
    int pole4[kl];

// init (ID, pole1, pole2, pole3, pole4, plansza);
    for (i = 0; i<kl; i++){     //nadanie pocz¹tkowych wartoœci dla klocków
        ID[i] = i;
        pole1[i] = 0;
        pole2[i] = 0;
        pole3[i] = 0;
        pole4[i] = 0;
    }

       srand ( time(NULL) );        //inicjalizaja generatora
    for(p = 0; p<kl; p++){      // losowe przypisanie wartoœci 1, 2 lub 3
        pole1[p] = rand()%3+1;
        pole2[p] = rand()%3+1;
        pole3[p] = rand()%3+1;
        pole4[p] = rand()%3+1;
    }

    for (m = 0; m<pl; m++){     //nadanie pocz¹tkowych wartoœci dla planszy
        for(n = 0; n < pl; n++) plansza[m][n] = 0;
    }

    for (j = 0; j<kl; j++){     //testowe wyswietlanie
        printf("%d \t %d \t %d \t %d \t %d\n", ID[j], pole1[j], pole2[j], pole3[j], pole4[j]);
    }


    for(k = 0; k<pl; k++){          //testowe wyswietlanie
        for(l = 0; l<pl; l++) printf("%d\t", plansza[k][l]);
        printf("\n");
    }
    printf("zaczynamy!\n");
    return 0;
}
