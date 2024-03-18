#include <iostream>

class Obj{
public:
    int namei; // Identificativo
    int sym;   // Simbolo utilizzato in codice ASCII
    int value; // Valore di effetto
    int type;  //0 = vita. 1 = score. !1 e !0 = vita e score
    Obj(int sym,int value,int type,int namei); //Def oggetto
    Obj();  // utile per definire lista di oggetti
    void Effetto(int&,int&);
};
class Giocatore: public Obj{
public:
    Giocatore();
};


struct objl{  //lista oggetti
    int coord;
    Obj o;
    objl *next;
};
typedef objl *pobjl;

void AddObj(Obj ,int ,pobjl&);//Aggiunge oggetto a lista
void RemoveObj(int ,pobjl&);//Rimuove oggetto dalla lista
int ObjCoord(Obj ,pobjl);//Ritorna coordinate oggetto
Obj FindObj(int ,pobjl);//Ritorna oggetto
