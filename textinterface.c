#include "textinterface.h"
#include "essential.h"

#ifndef SDLMODE

void interface_init()
{
    chosen_x = 5;
    chosen_y = 5;
    int chosen_user_id = 0;
    init();
}
void user_loop()
{
    bool finished = false;
    char choice;
    printf("Press 'L' to load from file <set.txt>; Press 'N' to choose another file.\n");
    printf("'P' to display randomly chosen tiles, 'O' to solve, 'E' to exit.\n");
    while(!finished){
    scanf("%c", &choice);
    switch(choice)
    {
    case 'l':
    case 'L':
        {
            loadExperimental();
            printf("Press 'O' to solve automatically. Press 'S' to save the result.\n");
            break;
        }
    case 'N':
    case 'n':
        {
            printf("Function not ready.\n");
            break;
        }
    case 'E':
    case 'e':
        {
            finished = true;
            break;
        }
    case 'O':
    case 'o':
        {
            solve();
            printf("Press 'S' to save the result.\n");
            break;

        }
    case 'S':
    case 's':
        {
            printTxt();
            break;
        }
    case 'a':
    case 'A':
        {
            init();
            break;
        }
    case 'p':
    case 'P':
        {
            printAvailable();
            printf("\nPress 'O' to solve automatically.\n");
            break;
        }

    }
    }
}
void end_application()
{

}

#endif // SDLMODE
