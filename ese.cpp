#include "livello.hpp"


using namespace std;


int main(){
    initscr();
    refresh();
    srand(time(0));

    int input=0;
    do{
        Livello lvl = Livello();
        lvl.Print();//contiene func di ncurses
        //lvl.printobjl();
    do{
        input = getch();
        if(input==67)//destra
        {
            lvl.Move(1);
        }
        if(input==68)//sinistra
        {
            lvl.Move(-1);
        }
        if(input==65)//sopra
        {
            lvl.Move(2);
        }
        if(input==66)//sotto
        {
            lvl.Move(-2);
        }
        clear();
        lvl.Print();
        //lvl.printobjl();
        //printw("%d",input);
    }while(lvl.vita>0 && lvl.score>=0);//CONDIZIONI DI GAME OVER
    while(input!=(int)'i' && input!=(int)'e')
    {
        clear();
        printw("\n\t\t\tGAME OVER");
        printw("\n\tScore: %d\tHighest Level: %d",lvl.score,lvl.diff);
        printw("\nPress 'e' to exit or 'i' to start over.");
        input = getch();
    }
    clear();
    printw("\n");
    }while(input!=(int)'e');
    
    endwin();
    
    return 0;
}
