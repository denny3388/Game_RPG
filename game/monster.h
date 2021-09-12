#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;

class monster
{
public:
    //status
    int freeze=0,mess=0,poison=0,weak=0;
    //constitution
    int lv;
    int hp;
    int atkv;
    int lowatkv;//最低攻擊力
    int skillprob=0;
    monster(){}
    monster(int l)
    {
        lv = l;
        hp = 80+20*lv;
        atkv = 8+2*lv;
        lowatkv=0.25*atkv;
        cout <<"**********************************************************" << endl <<
             "STAGE " << lv << endl;
        cout << "敵人的攻擊力為 [" << lowatkv << "~" << atkv << "]" << endl;
    }
    void getstatus()
    {
        cout << "敵人HP為 [" << (hp<0?0:hp) << "]" << endl;
    }
    int atk()
    {
        if(hp>0)
        {
            if(freeze>0)
            {
                cout << ">>敵人陷入[凍結]狀態，此回合無法攻擊!(剩下 " << --freeze << " 回合)" << endl;
                return 0;
            }
            else if(mess>0)
            {
                cout << ">>敵人陷入[混亂]狀態，對自己發動了攻擊!(剩下 " << --mess << " 回合)" << endl;
                hp -= (rand()%(atkv-lowatkv+1))+lowatkv;
                return 0;
            }
            else if(poison>0)
            {
                int pd = (rand()%(atkv-lowatkv+1))+lowatkv;
                int d = (rand()%(8+2*lv))+1;
                cout << ">>敵人陷入[中毒]狀態，受到了" << pd << "點傷害!(剩下 " << --poison << " 回合)" << endl;
                cout << ">>敵人發動了攻擊!" << endl;
                hp -= pd;
                return d;
            }
            else if(weak>0){
                int d = (rand()%(atkv-lowatkv+1))+lowatkv;
                cout << ">>敵人陷入[頹靡]狀態，攻擊力大幅下降!(剩下 " << --weak << " 回合)" << endl;
                cout << ">>敵人發動了攻擊!" << endl;
                return d/5;
            }
            else
            {
                int d = (rand()%(atkv-lowatkv+1))+lowatkv;
                cout << ">>敵人發動了攻擊!" << endl;
                return d;
            }
        }
        else
        {
            cout << ">>敵人被擊倒了!" << endl;
            return 0;
        }
    }
    virtual int skill(){}
};

class bigmonster: public monster{
public:
    int maxskillprob = 40;
    bigmonster(int l){
        skillprob = 10+lv;
        if(skillprob>maxskillprob) skillprob=maxskillprob;
        lv = l;
        hp = 80+20*lv;
        atkv = 8+2*lv;
        lowatkv = 0.4*atkv;
        cout <<"**********************************************************" << endl <<
             "STAGE " << lv << endl;
        cout << "你碰到了精英敵人!!!" << endl;
        cout << "敵人的攻擊力為 [" << lowatkv << "~" << atkv << "]" << endl;
    }
    int skill(){
        int choose = rand()%4+1;
//        choose = 2;
        switch(choose){
            case 1:{
                cout << ">>敵人使出[劇毒之陣]!你陷入[中毒]狀態3回合，HP持續減少!" << endl;
                return 1; break;
            }
            case 2:{
               cout << ">>敵人使出[荊棘枷鎖]!你陷入[束縛]狀態2回合，無法發動技能!" << endl;
                return 2; break;
            }

            case 3:{
                cout << ">>敵人使出[血魔法咒]!你陷入[虛弱]狀態3回合，攻擊力小幅下降!" << endl;
                return 3; break;
            }

            case 4:{
                cout << ">>敵人使出[遲緩光線]!你陷入[遲鈍]狀態3回合，迴避率小幅下降!" << endl;
                return 4; break;
            }
        }
    }

    int atk()
    {
        if(hp>0)
        {
            if(freeze>0)
            {
                cout << ">>敵人陷入[凍結]狀態，此回合無法攻擊!(剩下 " << --freeze << " 回合)" << endl;
                return 0;
            }
            else if(mess>0)
            {
                cout << ">>敵人陷入[混亂]狀態，對自己發動了攻擊!(剩下 " << --mess << " 回合)" << endl;
                hp -= (rand()%(atkv-lowatkv+1))+lowatkv;
                return 0;
            }
            else if(poison>0)
            {
                int pd = (rand()%(atkv-lowatkv+1))+lowatkv;
                int d = (rand()%(8+2*lv))+1;
                cout << ">>敵人陷入[中毒]狀態，受到了" << pd << "點傷害!(剩下 " << --poison << " 回合)" << endl;
                cout << ">>敵人發動了攻擊!" << endl;
                hp -= pd;
                return d;
            }
            else if(weak>0){
                int d = (rand()%(atkv-lowatkv+1))+lowatkv;
                cout << ">>敵人陷入[頹靡]狀態，攻擊力大幅下降!(剩下 " << --weak << " 回合)" << endl;
                cout << ">>敵人發動了攻擊!" << endl;
                return d/5;
            }
            else
            {
                int d = (rand()%(atkv-lowatkv+1))+lowatkv;
                cout << ">>敵人發動了攻擊!" << endl;
                return d;
            }
        }
        else
        {
            cout << ">>敵人被擊倒了!" << endl;
            return 0;
        }
    }
};

string yorn(string info){
    string yesorno;
    while(yesorno!="y" && yesorno!="n")
    {
        cout << info;
        cin >> yesorno;
    }
    return yesorno;
}
#endif // MONSTER_H_INCLUDED
