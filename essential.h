#ifndef ESSENTIAL_H_INCLUDED
#define ESSENTIAL_H_INCLUDED

#include <stdbool.h>

#define SDLMODE

#define all_tiles 14
#define zestaw 30
#define t_size 12

struct Element {
   char  title;
   char  top, right, bottom, left;
   int   rotation;
   bool  available;
   bool  isright, isleft, istop, isbottom;
   bool  temple;
   bool  crossing;
   bool  hasCity;
   bool  isCity;
   bool  isTemple;
   bool  isEmblem;
   int   user_id;
   int   id;
   bool ischecked;
};

struct Element element[zestaw];

int i, k, l;
//bool changed = false;
char choice;
char buffer;

int score;
int score_total;
int num_cities;

int x_1;
int y_1;
bool city_closed;

bool found_city;
bool found_neighbour;
int city_positions[2][t_size*t_size];
int score_array[2][t_size*t_size];

int chosen_x;
int chosen_y;
bool finished;
int chosen_user_id;
int m, n, s;

void init(); //funkcja inicjujaca tablice

void rotateClockwise(struct Element *elem);
void placeElement(struct Element *elem, int y, int x);      //Calls positionValid, places, refreshes
bool positionValid(struct Element *elem, int y, int x);     //Checks position validity, surrounding tiles and other crap
bool isNear();
void solve(); //upoœledzona funkcja
bool is_neighbour(int y_1, int y2, int x_1, int x2);

void printTable();
void printAvailable();

void findCities();
void countPoints();
void score2();
void countTemples();


//----------------------------------------------------------
bool isClosed();
void searchForAglomeration();
int mainFullCitiesCalc();
int howManyFullCities();
int cityCountFillCalc();
void pktWaldek();
//-----------------------------------------------------------

void printTxt(); //print current board to a text file

#endif // ESSENTIAL_H_INCLUDED
