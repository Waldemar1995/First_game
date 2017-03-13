#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void printTable();
 struct Element *table[3][3] = {{NULL}};
 int i, s, k,l;

 struct Element {
    //char  title[6];
    char  title;
    //int pola[4];
    char  top, right, bottom, left;
    bool istop;
    bool isright;
    bool isbottom;
    bool isleft; //true if avaliable, false if not
    bool iscrossing;
    bool istemple;
    bool iscity;
    int   rotation;
    bool  available;
    int   id;

 };

void printTable()
 {
     printf("Table: \n");

     for(k=0;k<3;k++)
     {
         for (l=0;l<3;l++)
         {
             (table[k][l] == NULL) ? (printf("%d\t",(k*(3))+l)) : (printf("%c\t", table[k][l]->title));
         }
        printf("\n");
     }
 printf("\n");
 }


int main()
{


 struct Element element[9];

 char allElements [14][5] = {{ 'A', 'R', 'P', 'R', 'P' }, //Definicja MOZLIWYCH elementow na sztywno; nie ma np. combinacji C-C-R-R itd.
                             { 'B', 'P', 'P', 'R', 'R' },
                             { 'C', 'P', 'R', 'R', 'R' },
                             { 'D', 'P', 'C', 'C', 'P' },
                             { 'E', 'C', 'P', 'P', 'P' },
                             { 'F', 'C', 'R', 'R', 'P' },
                             { 'G', 'R', 'C', 'P', 'R' },
                             { 'H', 'R', 'C', 'R', 'R' },
                             { 'I', 'R', 'R', 'R', 'R' },
                             { 'J', 'P', 'C', 'P', 'C' },
                             { 'K', 'R', 'C', 'R', 'P' },
                             { 'L', 'C', 'C', 'C', 'C' },  //emblem
                             { 'M', 'P', 'P', 'P', 'R' },  //temple
                             { 'N', 'P', 'P', 'P', 'P' }}; //temple

    srand ( time(NULL) );

    // for(i=0;i<5;i++)
    // {
      //   s = rand()%14;
      //   element[i].top = allElements[i][1];
    //     element[i].right = allElements[i][2];
   //      element[i].bottom = allElements[i][3];
   //      element[i].left = allElements[i][4];
  //      element[i].istop = true;
  //      element[i].isright = true;
  //      element[i].isbottom = true;
  //      element[i].isleft = true; //true if avaliable, false if not
  //      element[i].iscrossing = false;
 //       element[i].istemple = false;
 //       element[i].iscity = false;
  //       element[i].rotation = 0;
  //       element[i].title = allElements[i][0];
  //       element[i].id = i;
 //        element[i].available = true;

     //    if (s == 8 || s == 7 || s == 2) element[i].iscrossing = true;
    //     if (s == 12 || s == 13) element[i].istemple = true;
    //     if (s == 11) element[i].iscity = true;
    // }

  // table[3][3] = { {NULL, &element[3], &element[1]},
   //             {NULL, &element[4], &element[0]},
   //                    {NULL, NULL, NULL}};

        element[0].top = allElements[1][1];
        element[0].right = allElements[1][2];
        element[0].bottom = allElements[1][3];
        element[0].left = allElements[1][4];
        element[0].istop = true;
        element[0].isright = true;
        element[0].isbottom = true;
        element[0].isleft = true; //true if avaliable, false if not
        element[0].iscrossing = false;
        element[0].istemple = false;
        element[0].iscity = false;
        element[0].rotation = 0;
        element[0].title = allElements[1][0];
        element[0].id = 1;
        element[0].available = true;

        element[1].top = allElements[3][1];
        element[1].right = allElements[3][2];
        element[1].bottom = allElements[3][3];
        element[1].left = allElements[3][4];
        element[1].istop = true;
        element[1].isright = true;
        element[1].isbottom = true;
        element[1].isleft = true; //true if avaliable, false if not
        element[1].iscrossing = false;
        element[1].istemple = false;
        element[1].iscity = false;
        element[1].rotation = 0;
        element[1].title = allElements[3][0];
        element[1].id = 3;
        element[1].available = true;

        element[2].top = allElements[9][1];
        element[2].right = allElements[9][2];
        element[2].bottom = allElements[9][3];
        element[2].left = allElements[9][4];
        element[2].istop = true;
        element[2].isright = true;
        element[2].isbottom = true;
        element[2].isleft = true; //true if avaliable, false if not
        element[2].iscrossing = false;
        element[2].istemple = false;
        element[2].iscity = false;
        element[2].rotation = 0;
        element[2].title = allElements[9][0];
        element[2].id = 9;
        element[2].available = true;

        element[3].top = allElements[10][1];
        element[3].right = allElements[10][2];
        element[3].bottom = allElements[10][3];
        element[3].left = allElements[10][4];
        element[3].istop = true;
        element[3].isright = true;
        element[3].isbottom = true;
        element[3].isleft = true; //true if avaliable, false if not
        element[3].iscrossing = false;
        element[3].istemple = false;
        element[3].iscity = false;
        element[3].rotation = 0;
        element[3].title = allElements[10][0];
        element[3].id = 10;
        element[3].available = true;

        element[4].top = allElements[11][1];
        element[4].right = allElements[11][2];
        element[4].bottom = allElements[11][3];
        element[4].left = allElements[11][4];
        element[4].istop = true;
        element[4].isright = true;
        element[4].isbottom = true;
        element[4].isleft = true; //true if avaliable, false if not
        element[4].iscrossing = false;
        element[4].istemple = false;
        element[4].iscity = false;
        element[4].rotation = 0;
        element[4].title = allElements[11][0];
        element[4].id = 11;
        element[4].available = true;

        element[5].top = allElements[9][1];
        element[5].right = allElements[9][2];
        element[5].bottom = allElements[9][3];
        element[5].left = allElements[9][4];
        element[5].istop = true;
        element[5].isright = true;
        element[5].isbottom = true;
        element[5].isleft = true; //true if avaliable, false if not
        element[5].iscrossing = false;
        element[5].istemple = false;
        element[5].iscity = false;
        element[5].rotation = 0;
        element[5].title = allElements[9][0];
        element[5].id = 9;
        element[5].available = true;

        element[6].top = allElements[0][1];
        element[6].right = allElements[0][2];
        element[6].bottom = allElements[0][3];
        element[6].left = allElements[0][4];
        element[6].istop = true;
        element[6].isright = true;
        element[6].isbottom = true;
        element[6].isleft = true; //true if avaliable, false if not
        element[6].iscrossing = false;
        element[6].istemple = false;
        element[6].iscity = false;
        element[6].rotation = 0;
        element[6].title = allElements[0][0];
        element[6].id = 0;
        element[6].available = true;

        element[7].top = allElements[5][1];
        element[7].right = allElements[5][2];
        element[7].bottom = allElements[5][3];
        element[7].left = allElements[5][4];
        element[7].istop = true;
        element[7].isright = true;
        element[7].isbottom = true;
        element[7].isleft = true; //true if avaliable, false if not
        element[7].iscrossing = false;
        element[7].istemple = false;
        element[7].iscity = false;
        element[7].rotation = 0;
        element[7].title = allElements[5][0];
        element[7].id = 5;
        element[7].available = true;

        element[8].top = allElements[1][1];
        element[8].right = allElements[1][2];
        element[8].bottom = allElements[1][3];
        element[8].left = allElements[1][4];
        element[8].istop = true;
        element[8].isright = true;
        element[8].isbottom = true;
        element[8].isleft = true; //true if avaliable, false if not
        element[8].iscrossing = false;
        element[8].istemple = false;
        element[8].iscity = false;
        element[8].rotation = 0;
        element[8].title = allElements[1][0];
        element[8].id = 1;
        element[8].available = true;



        table[0][0] =  &element[0];
        table[0][1] =  &element[1];
        table[0][2] =  &element[2];
        table[1][0] =  &element[3];
        table[1][1] =  &element[4];
        table[1][2] =  &element[5];
        table[2][0] =  &element[6];
        table[2][1] =  &element[7];
        table[2][2] =  &element[8];
        //printf("%c", element[1].right);





        int n, m;
        int points = 0;
        int w = 3; //wymiar pola, tu 3 x 3

         for(n=0; n<w; n++){ //niepe³ny algorytm do liczenia pe³nych miast, brakuje jeszcze opcji kilku iscity obok siebie, nie testowany
            for(m=0; m<w; m++){
                if(table[n][m]->iscity == true){
                 if(m == 0 || n == 0 || m == (w - 1) || m == (w - 1) || table[n + 1][m] == NULL || table[n - 1][m] == NULL || table[n][m + 1] == NULL || table[n][m - 1] == NULL){
                    table[n][m]->istop == false;
                    table[n][m]->isright == false;
                    table[n][m]->isbottom == false;
                    table[n][m]->isleft == false;
                    points = points + 2;
                 }
                if(table[n+1][m]->iscity == false && table[n-1][m]->iscity == false && table[n][m+1]->iscity == false && table[n][m-1]->iscity == false){
                    table[n][m]->istop == false;
                    table[n][m]->isright == false;
                    table[n][m]->isbottom == false;
                    table[n][m]->isleft == false;
                    table[n][m+1]->istop == false;
                    table[n-1][m]->isright == false;
                    table[n][m-1]->isbottom == false;
                    table[n+1][m]->isleft == false;
                    points = points + 11;

                 }
                }
            }
         }




        for(n=0; n<w; n++){ //pe³ny algorytm dope³niaj¹cy puste miejsca, nie testowany
            for(m=0; m<w; m++){
                if (table[n][m] != NULL && table[n][m]->iscity == false){

                 if (table[n][m]->top == C && table[n][m]->istop == true && m==0 ){
                    table[n][m]->istop == false;
                    points = points +1;
                 }

                 if (table[n][m]->left == C && table[n][m]->isleft == true && n==0 ){
                    table[n][m]->isleft == false;
                    points = points +1;
                 }

                 if (table[n][m]->right == C && table[n][m]->isright == true){
                    if(n == (w - 1)){
                        table[n][m]->isright == false;
                        points = points + 1;
                    }
                    if(n != (w - 1) && table[n+1][m] == NULL){
                        table[n][m]->isright == false;
                        points = points + 1;
                    }
                    if(n != (w - 1) && table[n+1][m] != NULL && table[n+1][m]->iscity == false){
                        table[n][m]->isright == false;
                        table[n+1][m]->isleft == false;
                        points = points + 4;
                    }
                 }

                 if(table[n][m]->bottom == C && table[n][m]->isbottom == true){
                    if(m == (w - 1)){
                        table[n][m]->isbottom == false;
                        points = points + 1;
                    }
                    if(m != (w - 1) && table[n][m+1] == NULL){
                        table[n][m]->isbottom == false;
                        points = points + 1;
                    }
                    if(m != (w - 1) && table[n][m+1] != NULL && table[n][m+1]->iscity == false){
                        table[n][m]->isbottom == false;
                        table[n][m+1]->istop == false;
                        points = points + 4;
                    }
                 }
                }
            }
        }


        printTable();
     //   printf("%c", table[0][0]->left);
    // printf("\n %c", element[table[0][0]->id].title);
}

