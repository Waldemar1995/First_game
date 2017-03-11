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


 struct Element element[5];

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

     for(i=0;i<5;i++)
     {
      //   s = rand()%14;
         element[i].top = allElements[i][1];
         element[i].right = allElements[i][2];
         element[i].bottom = allElements[i][3];
         element[i].left = allElements[i][4];
        element[i].istop = true;
        element[i].isright = true;
        element[i].isbottom = true;
        element[i].isleft = true; //true if avaliable, false if not
        element[i].iscrossing = false;
        element[i].istemple = false;
        element[i].iscity = false;
         element[i].rotation = 0;
         element[i].title = allElements[i][0];
         element[i].id = i;
         element[i].available = true;

         if (s == 8 || s == 7 || s == 2) element[i].iscrossing = true;
         if (s == 12 || s == 13) element[i].istemple = true;
         if (s == 11) element[i].iscity = true;
     }

  // table[3][3] = { {NULL, &element[3], &element[1]},
   //             {NULL, &element[4], &element[0]},
   //                    {NULL, NULL, NULL}};
        table[0][1] =  &element[1];
        printf("%c", element[2].right);


        printTable();
        printf("%c", table[0][1]->left);
}

