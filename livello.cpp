#include "livello.hpp"

frame* basegen(frame *lvl,int d, Giocatore &pl){
    frame *tmp;//Livello nuovo
    tmp = new frame;
    tmp->next = NULL;
    tmp->prev=lvl;
    tmp->objlist = new objl();
    if(lvl!=NULL)
        lvl->next = tmp;
    
    srand(time(0)*14532);/////GENERAZIONE SPAZIO
    for(int i=0;i<H;i++)//H
    {   
        int flat = 0; //piattaforme
        for(int t=0;t<L;t++)//L
        {
            int rnd = rand()%1000;
            if(t>0)
                rnd = (rand()/tmp->f[i*L+t-1]-32)%1000;
            srand(rand()*rnd);
            if(rnd < (d*100)%1000 )
            {
                flat = 4;
            }

            if(i==0 || i==H-1)//Tetto e base
            {
                tmp->f[i*L+t] = LS;
            }
            else if(i%2 == 0 && i>1 && i<H-2 && t>2 && t<L-2 && flat>0)//genera piani compresi tra L-1 e 2  e tra H-2 e 1 ogni 2 righe pari
            {
                flat--;

                tmp->f[i*L+t] = LS;
            }
            else
            {
                tmp->f[i*L+t] = 32;
            }
        }
    }
    ////////////////GENERAZIONE OGGETTI
    pl=Giocatore();
    int objindex=2;
    Obj b1 = Obj(42,10,1,0);    //*
    Obj b2 = Obj(64,25,1,0);    //@
    Obj n1 = Obj(109,-10,0,0);  //m
    Obj n2 = Obj(108,-30,0,0);  //l
    Obj n3 = Obj(110,-20,0,0);  //n
    Obj b3 = Obj(43,5,0,0);     //+
    Obj n4 = Obj(119,-5,2,0);  //w
    Obj objg[]{b1,n1,b2,n2,b3,n3,n4};

    for(int i=1;i<H-1;i++)
    {   
        for(int t=1;t<L-1;t++)
        {
            if(i==1 && t==1)//GIOCATORE
            {
                tmp->f[i*L+t] = pl.sym;
                AddObj(pl,i*L+t,tmp->objlist);
            }
            if(i%2 == 1 && i<H-1 && t>2 && t<L-2)//compreso tra L-1 e 2  e tra H-2 e 1 ogni 2 righe dispari
            {
                int rnd = rand()%1000;
                if(rnd/2 < (d*5)%1000 && tmp->f[(i-1)*L+t] == LS)//OGGETTI
                {
                    Obj tmpj = objg[rnd%(sizeof(objg)/sizeof(*objg))];
                    tmpj.namei = objindex;
                    tmp->f[i*L+t] = tmpj.sym;
                    AddObj(tmpj,i*L+t,tmp->objlist);
                    objindex++;
                }
            }
        }
    }
    
    return tmp;
}

Livello::Livello(){
    diff=0;
    vita=100;
    score=0;
    
    level=NULL;
    level=basegen(level,diff,pl);//Levels list setup
    
    for(int i=0;i<H;i++)//Muro iniziale
    {   
        for(int t=0;t<L;t++)
        {
            if(t==0 && i%(H-1) != 0)
                level->f[i*L+t] = HS;
        }
    }
}
void Livello::Nextlvl(){
    diff++;
    if(level->next==NULL){
        level=basegen(level,diff,pl);
    }
    else
    {
        level=level->next;
    }
}
void Livello::Prevlvl(){
    if(level->prev != NULL){
        level=level->prev;
        diff--;
    }
}
void Livello::Print()//STAMPA A SCHERMO
{
    for(int i=H-1;i>=0;i--)
    {
        for(int t=0;t<L;t++)
        {
            char str = (char)level->f[i*L+t];
            printw("%c", str);
        }
        printw("\n");
    }
    printw("LEVEL: %d", diff);
    printw("\t");
    printw("HEALTH: %d", vita);
    printw("\t");
    printw("SCORE: %d", score);
    printw("\n");
}
void Livello::Remove(Obj instance){
    level->f[ObjCoord(pl,level->objlist)] = 32; 
    instance.Effetto(vita,score);
    RemoveObj(instance.namei,level->objlist);

}
void Livello::Move(int add){
    int tmp = ObjCoord(pl,level->objlist);
    if((add==1 || add==-1))// Mov orizz
    {
        if(level->f[tmp+add-L]==LS){
            if((tmp+add)%40 == 0)//Confine sinistro
            {
                Prevlvl();
            }
            else if(((tmp+add)+1)%40 == 0)//Confine destro
            {
                Nextlvl();
            }
            else
            {
                if (level->f[tmp+add] != 32)
                {
                    Remove(FindObj(tmp+add,level->objlist));
                }
                Remove(pl);
                AddObj(pl,tmp+add, level->objlist);
                level->f[tmp+add] = pl.sym;
            }
        }
    }
    else if(tmp+L*add<(H-1)*L && tmp+L*add>L)  //Mov verticale
    {
        if(add==2 && level->f[tmp+L*add/2]!=32)// mov su
        {
            if (level->f[tmp+L*add] != 32)
            {
                Remove(FindObj(tmp+L*add,level->objlist));
            }
            Remove(pl);
            AddObj(pl,tmp+L*add, level->objlist);
            level->f[tmp+L*add] = pl.sym;
        }
        else if(add==-2 && level->f[tmp+L*add/2*3]!=32)// mov giu
        {
            if (level->f[tmp+L*add] != 32)
            {
                Remove(FindObj(tmp+L*add,level->objlist));
            }
            Remove(pl);
            AddObj(pl,tmp+L*add, level->objlist);
            level->f[tmp+L*add] = pl.sym;
        }
    }
}
void Livello::printobjl(){//DEBUG
    objl *p = level->objlist;
    while(p!=NULL)
    {
        printw("%c %d %d \n",(char)p->o.sym,p->o.namei,p->coord);
        p=p->next;
    }
}
