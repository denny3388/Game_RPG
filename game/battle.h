#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED
#include"warrior.h"
#include"magician.h"
#include"assassin.h"
#include"hunter.h"
#include"fortune.h"
#include"box.h"
#define RESTORE 4
#define BOX 30
#define BIGMON 4

void battle(int &lv, player &p, string &next)
{
    for( lv=0 ; next=="y" ;)
    {
        lv++;
        if((rand()%100+1)<=BOX && lv!=1)//寶箱
        {
            box(p);
            p.update();
        }
        if((lv-1)%RESTORE==0 && lv!=1)//restore
        {
            p.lv++;
            p.lvup();
            p.update();
            p.recover2max();
            p.getability();
            p.getstatus();
        }
        if(lv%BIGMON==0 && lv!=1)
        {
            bigmonster mo(lv);
            mo.getstatus();
            for(int r=1; p.hp>0 && mo.hp>0; r++)
            {
                cout << endl << "-------------ROUND" << r << "-------------";
                if(p.exestat(mo)){while(!p.action(mo)){}}
                p.update();
                cout << endl;
                p.getstatus();
                mo.getstatus();
                p.update();
            }
        }
        else
        {
            monster mo(lv);
            mo.getstatus();
            for(int r=1; p.hp>0 && mo.hp>0; r++)
            {
                cout << endl << "-------------ROUND" << r << "-------------";
                if(p.exestat(mo)){while(!p.action(mo)){}}
                cout << endl;
                p.getstatus();
                mo.getstatus();
                p.update();
            }
        }
        if(p.hp>0)
        {
            cout << endl << "STAGE " << lv <<" CLEAR!" << endl;
            next = yorn("進入下一關? (y/n) => ");
            cout << endl;
        }
        else
            break;
    }
}

#endif // BATTLE_H_INCLUDED
