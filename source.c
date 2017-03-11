#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <SDL.h>
#include <SDL2/SDL_image.h>

#undef main
#define all_tiles 14
#define zestaw 30

//można zmieniać dowolnie, mniej więcej ułoży się samo:
#define t_size 12
#define user_cols 10 //kolumny pod tablicą (5,6,10,15)

#define WIDTH t_size*50-15
#define HEIGHT t_size*50+zestaw/user_cols*50+20

struct Element {
   char  title;
   char  top, right, bottom, left;
   int   rotation;
   bool  available;

   bool  temple;
   bool  crossing;
   bool hasCity;

   int user_id;
   int   id;
};

struct Element element[zestaw];

int i, s, k, l, m, n;
//bool changed = false;
char choice;
char buffer;

int chosen_user_id = 0;
int chosen_x = 5;
int chosen_y = 5;

void printTable();
void printAvailable();
void init();
void rotateClockwise(struct Element *elem);
void refreshblocks();           //refreshed tile textures on the table
void placeElement(struct Element *elem, int y, int x);      //Calls positionValid, places, refreshes
bool positionValid(struct Element *elem, int y, int x);     //Checks position validity, surrounding tiles and other crap
void renderblock(int y, int x, struct Element *elem);
void refreshmarker();           //Updates marker position for the table
void refreshAvmarker();         //Updates marker position for the user tiles
bool isNear();
void solve(); //upośledzona funkcja

SDL_Texture *tekstury[all_tiles][4] = {{NULL}};
SDL_Texture *selectedTexture = NULL;
SDL_Texture *marker = NULL;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect rects[t_size][t_size];     // rectangles for TABLE, access through position
SDL_Rect availableRects[zestaw];    // rectangles for USER TILES, access through ID_USER
SDL_Rect markerRect;                // marks table tiles
SDL_Rect markerAvRect;              // marks available user tiles

//SDL_Rect selectedRect;              //enlarged selected tile
//SDL_Rect captionRect;               //"selected tile" rectangle


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

SDL_Rect newSDL_Rect(int xs, int ys, int widths, int heights)
{
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = widths;
    rectangular.h = heights;
    return rectangular;
}

int main(int argc, char **argv)
{

    window = SDL_CreateWindow("Carcassonne", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

{ //-------------------rotated textures-----//działa to działa, nie chce mi się zmieniać

    tekstury[0][0] = IMG_LoadTexture(renderer, "obr/tileA.bmp");
    tekstury[1][0] = IMG_LoadTexture(renderer, "obr/tileB.bmp");
    tekstury[2][0] = IMG_LoadTexture(renderer, "obr/tileC.bmp");
    tekstury[3][0] = IMG_LoadTexture(renderer, "obr/tileD.bmp");
    tekstury[4][0] = IMG_LoadTexture(renderer, "obr/tileE.bmp");
    tekstury[5][0] = IMG_LoadTexture(renderer, "obr/tileF.bmp");
    tekstury[6][0] = IMG_LoadTexture(renderer, "obr/tileG.bmp");
    tekstury[7][0] = IMG_LoadTexture(renderer, "obr/tileH.bmp");
    tekstury[8][0] = IMG_LoadTexture(renderer, "obr/tileI.bmp");
    tekstury[9][0] = IMG_LoadTexture(renderer, "obr/tileJ.bmp");
    tekstury[10][0] = IMG_LoadTexture(renderer, "obr/tileK.bmp");
    tekstury[11][0] = IMG_LoadTexture(renderer, "obr/tileL.bmp");
    tekstury[12][0] = IMG_LoadTexture(renderer, "obr/tileM.bmp");
    tekstury[13][0] = IMG_LoadTexture(renderer, "obr/tileN.bmp");

    tekstury[0][1] = IMG_LoadTexture(renderer, "obr1/tileA.bmp");
    tekstury[1][1] = IMG_LoadTexture(renderer, "obr1/tileB.bmp");
    tekstury[2][1] = IMG_LoadTexture(renderer, "obr1/tileC.bmp");
    tekstury[3][1] = IMG_LoadTexture(renderer, "obr1/tileD.bmp");
    tekstury[4][1] = IMG_LoadTexture(renderer, "obr1/tileE.bmp");
    tekstury[5][1] = IMG_LoadTexture(renderer, "obr1/tileF.bmp");
    tekstury[6][1] = IMG_LoadTexture(renderer, "obr1/tileG.bmp");
    tekstury[7][1] = IMG_LoadTexture(renderer, "obr1/tileH.bmp");
    tekstury[8][1] = IMG_LoadTexture(renderer, "obr1/tileI.bmp");
    tekstury[9][1] = IMG_LoadTexture(renderer, "obr1/tileJ.bmp");
    tekstury[10][1] = IMG_LoadTexture(renderer, "obr1/tileK.bmp");
    tekstury[11][1] = IMG_LoadTexture(renderer, "obr1/tileL.bmp");
    tekstury[12][1] = IMG_LoadTexture(renderer, "obr1/tileM.bmp");
    tekstury[13][1] = IMG_LoadTexture(renderer, "obr1/tileN.bmp");

    tekstury[0][2] = IMG_LoadTexture(renderer, "obr2/tileA.bmp");
    tekstury[1][2] = IMG_LoadTexture(renderer, "obr2/tileB.bmp");
    tekstury[2][2] = IMG_LoadTexture(renderer, "obr2/tileC.bmp");
    tekstury[3][2] = IMG_LoadTexture(renderer, "obr2/tileD.bmp");
    tekstury[4][2] = IMG_LoadTexture(renderer, "obr2/tileE.bmp");
    tekstury[5][2] = IMG_LoadTexture(renderer, "obr2/tileF.bmp");
    tekstury[6][2] = IMG_LoadTexture(renderer, "obr2/tileG.bmp");
    tekstury[7][2] = IMG_LoadTexture(renderer, "obr2/tileH.bmp");
    tekstury[8][2] = IMG_LoadTexture(renderer, "obr2/tileI.bmp");
    tekstury[9][2] = IMG_LoadTexture(renderer, "obr2/tileJ.bmp");
    tekstury[10][2] = IMG_LoadTexture(renderer, "obr2/tileK.bmp");
    tekstury[11][2] = IMG_LoadTexture(renderer, "obr2/tileL.bmp");
    tekstury[12][2] = IMG_LoadTexture(renderer, "obr2/tileM.bmp");
    tekstury[13][2] = IMG_LoadTexture(renderer, "obr2/tileN.bmp");

    tekstury[0][3] = IMG_LoadTexture(renderer, "obr3/tileA.bmp");
    tekstury[1][3] = IMG_LoadTexture(renderer, "obr3/tileB.bmp");
    tekstury[2][3] = IMG_LoadTexture(renderer, "obr3/tileC.bmp");
    tekstury[3][3] = IMG_LoadTexture(renderer, "obr3/tileD.bmp");
    tekstury[4][3] = IMG_LoadTexture(renderer, "obr3/tileE.bmp");
    tekstury[5][3] = IMG_LoadTexture(renderer, "obr3/tileF.bmp");
    tekstury[6][3] = IMG_LoadTexture(renderer, "obr3/tileG.bmp");
    tekstury[7][3] = IMG_LoadTexture(renderer, "obr3/tileH.bmp");
    tekstury[8][3] = IMG_LoadTexture(renderer, "obr3/tileI.bmp");
    tekstury[9][3] = IMG_LoadTexture(renderer, "obr3/tileJ.bmp");
    tekstury[10][3] = IMG_LoadTexture(renderer, "obr3/tileK.bmp");
    tekstury[11][3] = IMG_LoadTexture(renderer, "obr3/tileL.bmp");
    tekstury[12][3] = IMG_LoadTexture(renderer, "obr3/tileM.bmp");
    tekstury[13][3] = IMG_LoadTexture(renderer, "obr3/tileN.bmp");
}
    //selectedTexture = IMG_LoadTexture(renderer, "selected.bmp");-------opcjonalne
    //marker = IMG_LoadTexture(renderer, "marker2.bmp");

    SDL_Event event;
    SDL_RenderClear(renderer); //Clear screen


//----------automatycznie rozkłada pola w oknie dla zadanych wielkości - nie grzebać! ----------//
    for(m=0;m<t_size;m++) //table tiles
        {
            for(n=0;n<t_size;n++)
            {
                rects[n][m] = newSDL_Rect(22 + m*45, 22 + n*45, 44, 44);
                SDL_SetRenderDrawColor(renderer, 113, 140, 147, 255);
                SDL_RenderFillRect(renderer, &rects[n][m]);
            }
        }
    init();
    for(m=0;m<zestaw;m++) //tiles displaying available elements
    {
        s=m/user_cols;

        availableRects[m] = newSDL_Rect((t_size-user_cols)*22 + 22 + (m-user_cols*s)*45, t_size*50+45*s+10, 44, 44);
        SDL_SetRenderDrawColor(renderer, 113, 180, 147, 255);
        SDL_RenderFillRect(renderer, &availableRects[m]);
        s = element[m].id;
        SDL_RenderCopy(renderer, tekstury[s][element[m].rotation], NULL, &availableRects[m]);

    }
//---------------------------------------------------------------------------------------------//

    //selectedRect = newSDL_Rect(t_size*50+100, 200, 88, 88); -----------ewentualne dodatki
    //SDL_SetRenderDrawColor(renderer, 113, 180, 147, 255);
    //SDL_RenderFillRect(renderer, &selectedRect);

    //captionRect = newSDL_Rect(t_size*50+85, 110, 120, 88);
    //SDL_RenderCopy(renderer, selectedTexture, NULL, &captionRect);


    markerRect = newSDL_Rect(rects[chosen_y][chosen_x].x-1,rects[chosen_y][chosen_x].y-1,46,46);
    markerAvRect = newSDL_Rect(availableRects[0].x-1,availableRects[0].y-1,46,46);
    //default positions and colors for markers
    SDL_SetRenderDrawColor(renderer, 220, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &markerRect);
    SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
    SDL_RenderDrawRect(renderer, &markerAvRect);

    printAvailable();
    printTable();

    SDL_RenderPresent(renderer);

    bool finished = 0;

    printf("[R] to rotate, [SPACE] to place, [ESC] to end\n[WASD], arrows to choose tile\n[O] to solve automatically in a retarded way\n");

    while(!finished)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                }
            }
            break;
            case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            {
                                finished = true;
                                break;
                            }
                        case SDLK_p:
                        case SDLK_SPACE:
                            {
                                    placeElement(&element[chosen_user_id], chosen_y,chosen_x);
                                    //printAvailable();
                                    //printTable();
                                break;
                            }

                        case SDLK_r:
                            {
                                rotateClockwise(&element[chosen_user_id]);
                                refreshblocks();
                                break;
                            }
                        case SDLK_UP:
                            {
                                (chosen_y==0) ? (chosen_y=0) : (chosen_y--);
                                refreshmarker();
                                break;
                            }
                        case SDLK_DOWN:
                            {
                                (chosen_y==t_size-1) ? (chosen_y=t_size-1) : (chosen_y++);
                                refreshmarker();
                                break;
                            }
                        case SDLK_RIGHT:
                            {
                                (chosen_x==t_size-1) ? (chosen_x=t_size-1) : (chosen_x++);
                                refreshmarker();
                                break;
                            }
                        case SDLK_LEFT:
                            {
                                (chosen_x==0) ? (chosen_x=0) : (chosen_x--);
                                refreshmarker();
                                break;
                            }
                        case SDLK_a:
                            {
                               (chosen_user_id==0) ? (chosen_user_id=0) : (chosen_user_id--);
                                refreshAvmarker();
                                break;
                            }
                        case SDLK_d:
                            {
                                (chosen_user_id==zestaw-1) ? (chosen_user_id=zestaw-1) : (chosen_user_id++);
                                refreshAvmarker();
                                break;
                            }
                        case SDLK_s:
                            {
                                (chosen_user_id/user_cols==(zestaw-1)/user_cols) ? (chosen_user_id=chosen_user_id) : (chosen_user_id+=user_cols);
                                refreshAvmarker();
                                break;
                            }
                        case SDLK_w:
                            {
                                (chosen_user_id<user_cols) ? (chosen_user_id=chosen_user_id) : (chosen_user_id-=user_cols);
                                refreshAvmarker();
                                break;
                            }
                        case SDLK_o:
                            {
                                solve();
                                break;
                            }
                    }
                }
        }
    SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
//    if(changed)
//    {
//        for(m=0;m<t_size;m++)
//        {
//            for(n=0;n<t_size;n++)
//            {
//                if(table[m][n]!=NULL)
//                {
//                    renderblock(n, m, table[m][n]);
//                }
//            }
//        } ------------------//PRZESZUKIWANIE TABLICY, JESLI POTRZEBNE DO INNEJ WERSJI
       // SDL_RenderPresent(renderer);
//    //changed = false;

    SDL_Delay(50);
    }}

    //SDL_DestroyTexture(tekstury);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
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
            printf("%d: %c %c %c %c R%d [type %c]\n", element[i].user_id, element[i].top, element[i].right, element[i].bottom, element[i].left, element[i].rotation, element[i].title );
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
        element[i].hasCity;
        if(i>2&&i<12&&i!=8) element[i].hasCity = true;
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
    else printf("invalid tile\n");
}

void placeElement(struct Element *elem, int y, int x)
{
    if(positionValid(elem, y, x))
    {
                    elem->available = false;
                    table[y][x] = elem;
                    renderblock(y,x,elem);
                    SDL_RenderPresent(renderer);
    }
    else printf("invalid position\n");

}

void renderblock(int y, int x, struct Element *elem)
{
    SDL_RenderCopy(renderer, tekstury[elem->id][elem->rotation], NULL, &rects[y][x]);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 113, 113, 113, 255);
    SDL_RenderFillRect(renderer, &availableRects[elem->user_id]);
}

void refreshblocks()
{
    for(m=0;m<zestaw;m++) //user
    {
        if(element[m].available){
            SDL_RenderCopy(renderer, tekstury[element[m].id][element[m].rotation], NULL, &availableRects[m]);
        }
    }
    SDL_RenderPresent(renderer);
}

void refreshmarker()
{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &markerRect);
        markerRect.x = 21 + chosen_x*45;
        markerRect.y = 21 + chosen_y*45;
        SDL_SetRenderDrawColor(renderer, 220, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &markerRect);
        SDL_RenderPresent(renderer);
}

void refreshAvmarker()
{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &markerAvRect);
        markerAvRect.x = (t_size-user_cols)*22 + 21 + chosen_user_id%user_cols*45;
        markerAvRect.y = 9 + t_size*50 + (chosen_user_id/user_cols)*45;
        SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
        SDL_RenderDrawRect(renderer, &markerAvRect);
        SDL_RenderPresent(renderer);

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
    for(i=0;i<zestaw;i++)
    {
        if(element[i].available&&element[i].title == 'L'){
            placeElement(&element[i],chosen_y,chosen_x);
            found=true;
            chosen_x++;
        }
        //SDL_Delay(10);
    }
    if(!found)
    {
        placeElement(&element[0],chosen_y,chosen_x);
    }
    else{
            chosen_y--;
        for(i=0;i<zestaw;i++)
        {
                if(element[i].available&&element[i].hasCity){
                    for(m=0;m<3;m++)
                    {
                        if(positionValid(&element[i],chosen_y,chosen_x))
                        {
                            placeElement(&element[i],chosen_y,chosen_x);
                            chosen_x--;
                        }
                        else rotateClockwise(&element[i]);
                    }
                }
            //SDL_Delay(10);
        }
    }
    bool nocities = false;
    while(!all)
    {
        all=true;
        for(m=0;m<zestaw;m++)
        {
            if(element[m].available&&(nocities||element[m].hasCity))
            {
                all = false;
                placed = false;

                int x = 0;
                int y = 0;
                int dx = 0;
                int dy = -1;
                int t = t_size;
                for(i=0;i<t_size*t_size-1;i++)
                {
                    if((-t_size/2<x&&x<=t_size/2)&&(-t_size/2<y&&y<=t_size/2))
                    {
                        chosen_x = t_size/2+x-1;
                        chosen_y = t_size/2+y-1;
                        //refreshmarker();
                        if(!placed&&table[chosen_y][chosen_x]==NULL&&isNear(chosen_y,chosen_x)) //if place is empty and near another tile
                        {
                            for(s=0;s<3;s++)
                            {
                                if(positionValid(&element[m],chosen_y,chosen_x))
                                {
                                    placeElement(&element[m],chosen_y,chosen_x);
                                    placed=true;
                                }
                                else rotateClockwise(&element[i]);
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
        } nocities = true;
    }
}
bool isNear(int y, int x)
{
    if((y>0&&table[y-1][x]!=NULL)||(y<t_size-1&&table[y+1][x]!=NULL)||(x<t_size-1&&table[y][x+1]!=NULL)||(x>0&&table[y][x-1]!=NULL)) return true;
    else return false;
}
