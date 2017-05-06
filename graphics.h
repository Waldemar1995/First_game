#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "essential.h"

#ifdef SDLMODE

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

//można zmieniać dowolnie, mniej więcej ułoży się samo:
#define user_cols 10 //kolumny pod tablicą (5,6,10,15)

#define WIDTH t_size*50-15
#define HEIGHT t_size*50+zestaw/user_cols*50+20

SDL_Rect rects[t_size][t_size];     // rectangles for TABLE, access through position
SDL_Rect availableRects[zestaw];    // rectangles for USER TILES, access through ID_USER
SDL_Rect markerRect;                // marks table tiles
SDL_Rect markerAvRect;              // marks available user tiles

//SDL_Rect selectedRect;              //enlarged selected tile
//SDL_Rect captionRect;               //"selected tile" rectangle

SDL_Rect newSDL_Rect();
SDL_Renderer *renderer;
SDL_Texture *marker;
SDL_Event event;

void interface_init();
void user_loop();
void end_application();

void refreshblocks();           //refreshed tile textures on the table
void refreshmarker();           //Updates marker position for the table
void refreshAvmarker();         //Updates marker position for the user tiles
void renderblock(int y, int x, struct Element *elem);

FILE *output;

#endif // SDLMODE

#endif // GRAPHICS_H_INCLUDED
