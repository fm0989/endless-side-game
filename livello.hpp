#define L 40//40
#define H 9//8
#define HS 91
#define LS 61
#include "obj.hpp"
#include <ctime>
#include <ncurses.h>

    struct frame{    //lista livello a schermo
    int f[L*H];      //vettore griglia di gioco
    pobjl objlist;  
    frame *prev;
    frame *next;
    };

    frame* basegen(frame*,int,Giocatore&);

class Livello{
public:

    frame *level;
    Giocatore pl;
    int diff;  
    int vita;
    int score;

    Livello();
    void Nextlvl();
    void Prevlvl();
    void Print();
    void Remove(Obj);
    void Move(int);
    void printobjl(); //DEBUG
};
