#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

#include "essential.h"

#ifdef SDLMODE

SDL_Window *window = NULL;
SDL_Texture *tekstury[all_tiles][4] = {{NULL}};
SDL_Texture *selectedTexture = NULL;


SDL_Rect newSDL_Rect(int xs, int ys, int widths, int heights)
{
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = widths;
    rectangular.h = heights;
    return rectangular;
}

void interface_init()
{
    chosen_x = 5;
    chosen_y = 5;
    int chosen_user_id = 0;
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


    SDL_RenderClear(renderer); //Clear screen

    for(m=0;m<t_size;m++) //table tiles
        {
            for(n=0;n<t_size;n++)
            {
                rects[n][m] = newSDL_Rect(22 + m*45, 22 + n*45, 44, 44);
                SDL_SetRenderDrawColor(renderer, 113, 140, 147, 255);
                SDL_RenderFillRect(renderer, &rects[n][m]);
            }
        }
    for(m=0;m<zestaw;m++) //tiles displaying available elements
    {
        s=m/user_cols;

        availableRects[m] = newSDL_Rect((t_size-user_cols)*22 + 22 + (m-user_cols*s)*45, t_size*50+45*s+10, 44, 44);
        SDL_SetRenderDrawColor(renderer, 113, 180, 147, 255);
        SDL_RenderFillRect(renderer, &availableRects[m]);
        s = element[m].id;
        SDL_RenderCopy(renderer, tekstury[s][element[m].rotation], NULL, &availableRects[m]);

    }
    markerRect = newSDL_Rect(rects[chosen_y][chosen_x].x-1,rects[chosen_y][chosen_x].y-1,46,46);
    markerAvRect = newSDL_Rect(availableRects[0].x-1,availableRects[0].y-1,46,46);
    //default positions and colors for markers
    SDL_SetRenderDrawColor(renderer, 220, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &markerRect);
    SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
    SDL_RenderDrawRect(renderer, &markerAvRect);

    //printAvailable();
    //printTable();

    SDL_RenderPresent(renderer);

    bool finished = 0;

    printf("[R] to rotate, [SPACE] to place, [ESC] to end\n[WASD], arrows to choose tile\n[O] to solve automatically in a retarded way\n");

}
void user_loop()
{
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
                        //case SDLK_p:
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
                        case SDLK_c:
                            {
                                //countPoints();
                                score2();
                                break;
                            }
                        case SDLK_x:
                            {
                                pktWaldek();
                                break;
                            }
                        case SDLK_p:
                            {
                                printTxt();
                                break;
                            }
                        case SDLK_PERIOD:
                            {
                                loadExperimental();
                                refreshblocks();
                                break;
                            }
                    }
                }
        }
    SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);


    SDL_Delay(50);
    }}
}

void end_application()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
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

#endif
