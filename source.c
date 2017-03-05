#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define zestaw 5
#define size_t 7

struct Element {
   //char  title[6];
   char  title;
   //int pola[4];
   char  top, right, bottom, left;
   int   rotation;
   bool  available;
   int   id;
};

struct Element element[zestaw];

int i, s, k, l;
char choice, name;
void printTable();
void printAvailable();
void init();
void rotateClockwise(struct Element *elem);
void placeElement(struct Element *elem, int position);

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

struct Element *table[size_t][size_t] = {{NULL}};


int main () {

    printf("CARCASSONNE\n\n");
    init();
    placeElement(&element[0], 24);
    printAvailable();
    printTable();

    int chosen_ID, position = 100;

    while(1)
    {
        printf("[p] to place, [r] to rotate, [e] to end:\n");
        scanf("%c[^\n]\n", &choice);
        switch(choice) {

        case 'p':
            printf("Place an element: [ID, Position]:\n");
            scanf("%d %d", &chosen_ID, &position);
            (chosen_ID<zestaw&&chosen_ID>=0) ? (placeElement(&element[chosen_ID], position)) : (printf("invalid ID"));
            printTable();
            break;
        case 'r':
            printf("Choose ID:\n");
            scanf("%d", &chosen_ID);
            rotateClockwise(&element[chosen_ID]);
            printAvailable();
            break;
        case 'e':
            return 0;
        default:
            printf("value invalid\n\n");
        }
    }

return 0;
}

void printTable()
{
    printf("Table: \n");

    for(k=0;k<size_t;k++)
    {
        for (l=0;l<size_t;l++)
        {
            (table[k][l] == NULL) ? (printf("%d\t",(k*(size_t))+l)) : (printf("%c\t", table[k][l]->title));
        }
        printf("\n");
    }
printf("\n");
}

void printAvailable() {
    printf("Available elements:\n");
    for(i=0;i<zestaw;i++)
    {
        if(element[i].available){
            printf("%d: %c %c %c %c R%d [type %c]\n", element[i].id, element[i].top, element[i].right, element[i].bottom, element[i].left, element[i].rotation, element[i].title );
        }
    }
printf("\n");
}

void init() {

    srand ( time(NULL) );

    for(i=0;i<zestaw;i++)
    {
        s = rand()%14;
        element[i].top = allElements[s][1];
        element[i].right = allElements[s][2];
        element[i].bottom = allElements[s][3];
        element[i].left = allElements[s][4];

        element[i].rotation = 0;
        element[i].title = allElements[s][0];
        element[i].id = i;
        element[i].available = true;
    }
}

rotateClockwise(struct Element *elem)
{
   (elem->rotation>2) ? (elem->rotation = 0) : (elem->rotation = elem->rotation + 1);
}

void placeElement(struct Element *elem, int position)
{
    if(elem->available&&position<size_t*size_t&&table[position/(size_t-1)][position%(size_t-1)]==NULL) {
        elem->available = false;
        table[position/size_t][position%size_t] = &elem->title;

        printf("\n");
        //printTable();
    }
    else {
        printf("invalid ID or position");
    }

}
