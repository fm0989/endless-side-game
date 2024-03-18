#include "obj.hpp"

Obj::Obj(int sym,int value,int type,int namei){
    Obj::sym = sym;
    Obj::value = value;
    Obj::type = type;
    Obj::namei = namei;
}
Obj::Obj(){}

void Obj::Effetto(int& vita,int& score){
    if(type==0)
        vita += value;
    else if(type==1)
        score += value;
    else
        {score += value;vita += value;}
}

void AddObj(Obj instance,int coord,pobjl& objlist){  //Funzione aggiungi oggetto
    pobjl tmp = new objl;
    tmp->o = instance;
    tmp->coord = coord;
    tmp->next = NULL;
    if(objlist == NULL)
    {
        objlist=tmp;
    }
    else
    {
        pobjl p=objlist;
        while(p->next != NULL)
        {
            p=p->next;
        }
        p->next = tmp;
    }
}
void RemoveObj(int namei,pobjl &objlist){  // indice oggetto, lista da cui rimuovere
    pobjl p=objlist;
    if(objlist->o.namei == namei)       // eliminazione in testa
    {
        objlist = p->next;
        delete p;
        return;
    }
    while(p != NULL)                     // riordina lista quando elimina
    {
        pobjl q=p->next;
        if(q->o.namei == namei)
        {
            p->next = q->next;
            delete q;
            return;
        }
        p=p->next;
    }
}
int ObjCoord(Obj instance,pobjl objlist){  //coordinate oggetto
    pobjl p=objlist;
    while(p!=NULL)
    {
        if(instance.namei==p->o.namei)
            return p->coord;
        p=p->next;
    }
    return 0;
}
Obj FindObj(int coord,pobjl objlist){     //resitutisce oggetto
    pobjl p=objlist;
    while(p->next!=NULL)
    {
        if(coord==p->coord)
            return p->o;
        p=p->next;
    }
    return p->o;
}



Giocatore::Giocatore():Obj(59,0,0,1){   //simbolo, valore, tipo, id 
}
