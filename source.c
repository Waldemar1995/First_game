#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "essential.h"

#ifdef SDLMODE
#undef main
#include "graphics.h" //plik naglowkowy z graficznymi wersjami
#else
#include "textinterface.h" //plik naglowkowy z tekstowymi wersjami
#endif // SDLMODE


char allElements [14][5] = {{ 'A', 'R', 'P', 'R', 'P' }, //All possible elements
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
                            { 'M', 'P', 'P', 'R', 'P' },  //temple
                            { 'N', 'P', 'P', 'P', 'P' }}; //temple

struct Element *table[t_size][t_size] = {{NULL}};


int main(int argc, char **argv)
{
    init(); //funkcja inicjujaca tablice
    interface_init();
    user_loop();
    end_application();

    return 0;
}

void printTable()
{
    printf("Table: \n");

    for(k=0;k<t_size;k++)
    {
        for (l=0;l<t_size;l++)
        {
            (table[k][l] == NULL) ? (printf("%d\t",(k*(t_size))+l)) : (printf("%c\t", table[k][l]->title));
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
            printf("%d: %c %c %c %c R%d [type %c] hasCity: %d\n", element[i].user_id, element[i].top, element[i].right, element[i].bottom, element[i].left, element[i].rotation, element[i].title, element[i].hasCity );
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
        element[i].id = s;
        element[i].user_id = i;
        element[i].available = true;
        element[i].hasCity = false;
        element[i].isCity = false;
        if(s>2&&s<12&&s!=8&&s!=3) element[i].hasCity = true; //wywalam s=3 bo wsadza byle gdzie i są problemy
        if(s==11) element[i].isCity = true;
        if(s==12||s==13) element[i].isTemple = true;
        else element[i].isTemple = false;
    }
}

void rotateClockwise(struct Element *elem)
{
    if(elem->available){
        (elem->rotation>2) ? (elem->rotation = 0) : (elem->rotation = elem->rotation + 1);
        buffer = elem->top;
        elem->top = elem->left;
        elem->left = elem->bottom;
        elem->bottom = elem->right;
        elem->right = buffer;
    }
    //else printf("invalid tile\n");
}

void placeElement(struct Element *elem, int y, int x)
{
    if(positionValid(elem, y, x))
    {
                    elem->available = false;
                    table[y][x] = elem;
                    #ifdef SDLMODE
                    renderblock(y,x,elem);
                    SDL_RenderPresent(renderer);
                    #endif // SDLMODE
    }
    else printf("invalid position\n");

}

bool positionValid(struct Element *elem, int y, int x)
{
//-------paskudnie wygląda, ale jest milion warunków do spełnienia
    if(elem->available&&x<t_size&&y<t_size&&table[y][x]==NULL){
    if(y==0||table[y-1][x]==NULL||elem->top==table[y-1][x]->bottom){
        if(x==(t_size-1)||(table[y][x+1]==NULL)||elem->right==table[y][x+1]->left){
           if((y==(t_size-1))||(table[y+1][x]==NULL)||elem->bottom==table[y+1][x]->top) {
                if(x==0||table[y][x-1]==NULL||elem->left==table[y][x-1]->right)
                {
                    return true;
                }else return false;
           }else return false;
        }else return false;
    }   else return false;
    } else return false;
}

void solve()
{
    //struct Element *el = NULL;
    bool found = false;
    bool all = false;
    bool placed = false;
    int i_city = 0;
    chosen_x--;
    for(i=0;i<zestaw;i++)
    {
        if(element[i].available&&element[i].title == 'L'){
            placeElement(&element[i],chosen_y,chosen_x);
            found=true;
            city_positions[0][i_city] = chosen_x;
            city_positions[1][i_city] = chosen_y;
            i_city++;
            chosen_x++;
        }
        //SDL_Delay(10);
    }
    if(!found)
    {
        placeElement(&element[0],chosen_y,chosen_x);
    }
        //chosen_y--;
//        for(i=0;i<zestaw;i++)
//        {
//                if(element[i].available&&element[i].hasCity){
//                    for(m=0;m<3;m++)
//                    {
//                        if(positionValid(&element[i],chosen_y,chosen_x))
//                        {
//                            placeElement(&element[i],chosen_y,chosen_x);
//                            chosen_x--;
//                        }
//                        else rotateClockwise(&element[i]);
//                    }
//                }
//            //SDL_Delay(10);
//        }
    //bool nocities = false;

    while(!all)
    {
        all=true;
        if(found)
        { //skip the whole thing if there are no isCity elements
        for(m=0;m<zestaw;m++)
        {
            i_city = 0; //0 to iterate through city_positions
            if(element[m].available&&element[m].hasCity)
            {
                //SDL_Delay(30);
                //if there was an isCity element, try first to put something next to it
                placed = false;
                while(city_positions[0][i_city]!=0&&!placed)
                {  // printf("found!");
                    chosen_x = city_positions[0][i_city];
                    chosen_y = city_positions[1][i_city];
                    //SDL_Delay(30);
                    for(s=0;s<4;s++)
                    {
                        if(positionValid(&element[m],chosen_y-1,chosen_x))
                        {
                            placeElement(&element[m],chosen_y-1,chosen_x);
                            placed=true;
                        }
                        else rotateClockwise(&element[m]);
                    }
                    if(!placed)
                    {
                            for(s=0;s<4;s++)
                            {
                                if(positionValid(&element[m],chosen_y,chosen_x-1))
                                {
                                    placeElement(&element[m],chosen_y,chosen_x-1);
                                    placed=true;
                                }
                                else rotateClockwise(&element[m]);
                            }
                    }
                    if(!placed)
                    {
                            for(s=0;s<4;s++)
                            {
                                if(positionValid(&element[m],chosen_y+1,chosen_x))
                                {
                                    placeElement(&element[m],chosen_y+1,chosen_x);
                                    placed=true;
                                }
                                else rotateClockwise(&element[m]);
                            }
                    }
                    if(!placed)
                    {
                            for(s=0;s<4;s++)
                            {
                                if(positionValid(&element[m],chosen_y,chosen_x+1))
                                {
                                    placeElement(&element[m],chosen_y,chosen_x+1);
                                    placed=true;
                                }
                                else rotateClockwise(&element[m]);
                            }
                    }
                    i_city++;
                }
            }
        }
        }

        for(m=0;m<zestaw;m++)
        {
                placed = false;
                int x = 0;
                int y = 0;
                int dx = 0;
                int dy = -1;
                int t = t_size;
            if(element[m].available)
            {
                all = false;
                for(i=0;i<t_size*t_size-1;i++)
                {
                    if((-t_size/2<x&&x<=t_size/2)&&(-t_size/2<y&&y<=t_size/2))
                    {
                        chosen_x = t_size/2+x-1;
                        chosen_y = t_size/2+y-1;
                        //refreshmarker();
                        if(!placed&&table[chosen_y][chosen_x]==NULL&&isNear(chosen_y,chosen_x)) //if place is empty and near another tile
                        {
                            for(s=0;s<4;s++)
                            {
                                if(positionValid(&element[m],chosen_y,chosen_x))
                                {
                                    placeElement(&element[m],chosen_y,chosen_x);
                                    placed=true;
                                }
                                else rotateClockwise(&element[m]);
                            }
                        }
                        //SDL_Delay(50);
                    }
                    if((x==y)||(x<0&&x==-y)||(x>0&&x==1-y))
                    {
                        t = dx;
                        dx = -dy;
                        dy = t;
                    }
                        x = x+dx;
                        y = y+dy;
                }
            }
        }
    }
}
bool isNear(int y, int x)
{
    if((y>0&&table[y-1][x]!=NULL)||(y<t_size-1&&table[y+1][x]!=NULL)||(x<t_size-1&&table[y][x+1]!=NULL)||(x>0&&table[y][x-1]!=NULL)) return true;
    else return false;
}

void findCities() {
    num_cities=0;
    for(k=0; k<t_size*t_size; k++)
    {
     city_positions[0][k] = city_positions[1][k] = -1;
     score_array[0][k] = score_array[1][k] = -1;
    }
    for(k=0; k<t_size; k++){
        for(l=0; l<t_size; l++){
            if(table[k][l] != NULL&&table[k][l]->isCity){
                city_positions[0][num_cities] = k;
                city_positions[1][num_cities] = l;
                num_cities++;
                //city_found++;
            }
            }
        }
}

void score2(){

    findCities();
    if(city_positions[0][0] != -1) found_city = true;
    score = 0;
    score_total = 0;
    num_cities = 0;

    while(found_city){

        found_city = false;
        for(i=0; i<t_size; i++){
            if(city_positions[1][i]!=-1){
                found_city = true;
                y_1 = score_array[0][num_cities] = city_positions[0][i];
                x_1 = score_array[1][num_cities] = city_positions[1][i];
                num_cities++;
                city_positions[1][i] = -1;
                found_neighbour = true;

                while(found_neighbour){
                    found_neighbour = false;
                    for(m=0; m<t_size; m++){
                        if(city_positions[1][m] != -1 && is_neighbour(x_1, city_positions[0][m], y_1, city_positions[1][m]) ){
                            found_neighbour = true;
                            score_array[1][num_cities] = x_1 = city_positions[1][m];
                            score_array[0][num_cities] = y_1 = city_positions[0][m];
                            num_cities++;
                            city_positions[1][m] = -1;
                        }
                    }
                }
                    countPoints();
                        //clean score_array
                    num_cities = 0;
                    for(m=0;m<t_size;m++)
                    {
                       score_array[1][m] = -1;
                    }
                    score = 0;
                    num_cities = 0;
            }

        }
    }
    printf("\nScore: %d\n", score_total);
    countTemples();
    }

bool is_neighbour(int y_1, int y2, int x_1, int x2){
return abs(y_1-y2)+abs(x_1-x2)<2;
}

void countPoints()
{
        city_closed = true;
        for(n=0;n<t_size;n++)
        {
            if(score_array[1][n]!=-1){
                y_1 = score_array[0][n];
                x_1 = score_array[1][n];
                score++;
                if(y_1>0&&table[y_1-1][x_1]!=NULL&&(table[y_1-1][x_1]->isCity||table[y_1-1][x_1]->bottom=='C')) //top
                {
                    if(!table[y_1-1][x_1]->isCity&&table[y_1-1][x_1]->bottom=='C') score++;
                }
                else city_closed = false;
                if(x_1<t_size&&table[y_1][x_1+1]!=NULL&&(table[y_1][x_1+1]->isCity||table[y_1][x_1+1]->left=='C')) //right
                {
                    if(!table[y_1][x_1+1]->isCity&&table[y_1][x_1+1]->left=='C') score++;
                }
                else city_closed = false;
                if(y_1<t_size&&table[y_1+1][x_1]!=NULL&&(table[y_1+1][x_1]->isCity||table[y_1+1][x_1]->top=='C')) //bottom
                {
                    if(!table[y_1+1][x_1]->isCity&&table[y_1+1][x_1]->top=='C') score++;
                }
                else city_closed = false;
                if(x_1>0&&table[y_1][x_1-1]!=NULL&&(table[y_1][x_1-1]->isCity||table[y_1][x_1-1]->right=='C')) //left
                {
                    if(!table[y_1][x_1-1]->isCity&&table[y_1][x_1-1]->right=='C') score++;
                }
                else city_closed = false;
            }
            }
        if(city_closed) {
                score = score*2;
        }
    score+=num_cities;
    score_total +=score;
}

void countTemples()
{
    for(k=0; k<t_size; k++){
        for(l=0; l<t_size; l++){
            if(table[k][l] != NULL&&table[k][l]->isTemple)
            {
                score_total++;
                if(k>0&&table[k-1][l]!=NULL) score_total++;
                if(k>0&&l>0&&table[k-1][l-1]!=NULL) score_total++;
                if(k>0&&l<t_size-1&&table[k-1][l+1]!=NULL) score_total++;

                if(k<t_size-1&&table[k+1][l]!=NULL) score_total++;
                if(k<t_size-1&&l<t_size-1&&table[k+1][l+1]!=NULL) score_total++;
                if(k<t_size-1&&l>0&&table[k+1][l-1]!=NULL) score_total++;

                if(l<t_size-1&&table[k][l+1]!=NULL) score_total++;
                if(l>0&&table[k][l-1]!=NULL) score_total++;
            }
        }
    }
    printf("Score with temples: %d\n", score_total);
}
