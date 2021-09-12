#ifndef MAGICIAN_H_INCLUDED
#define MAGICIAN_H_INCLUDED
#include"player.h"
#include"skill.h"

class magician : public player
{
public:
    magician(int h=200,int m=350,int a=20)
    {
        bhp=h; bmp=m; batk=a;
        update();
        recover2max();
        cout << "請輸入你的姓名 => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "，你成為了一名法師!" << endl;
        getability();
        getstatus();
    }
    void update()
    {
        maxhp = bhp*(1+sta/50.0);
        maxmp = bmp*(1+inte/50.0);
        miss = dex*0.2+sta*0.1+1;
        if(miss>maxmiss)miss=maxmiss;
        atk = batk*(1+inte/50.0);
        lowatk = atk*0.2;
    }
    void attack(monster &m)
    {
        cout << ">>你用法術攻擊了敵人!" << endl;
        m.hp -= (rand()%(atk-lowatk+1))+lowatk;
       hp -= damage(m);
    }
    bool skill(monster &m)
    {
        if(noskill>=0){
            cout << ">>你陷入[束縛]狀態，此回合無法使用技能!" << endl;
            return false;
        }
        int choose=0;
        skills snow(1,"冷吱吱風暴","對敵方造成少量傷害，並封鎖敵人行動2回合",40);
        skills god(2,"女神庇佑","3回合內無法採取任何動作，並於每回合回復HP",60);
        skills curse(3,"嗜血詛咒","消耗自己現有 25% 的HP，扣除敵方現有的 50% HP",100);
        if(halfmp)//技能秘笈道具效果
        {
            snow.mpcon/=2; god.mpcon/=2; curse.mpcon/=2; halfmp=0;
            cout << "(此次發動技能消耗MP減半)" << endl;
        }
        cout << endl << "請選擇要使用的技能 => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= snow.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << snow.name << "]!!!" << endl;
                m.freeze+=2;
                m.hp -= (rand()%(lowatk))+1;
                hp -= damage(m);
                mp -= snow.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << snow.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= god.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << god.name << "]!!!" << endl;
                protect+=3;
                hp -= damage(m);
                mp -= god.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << god.mpcon << " MP)" << endl;
        }
        else if(choose==3){
            if(mp >= curse.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << curse.name << "]!!!" << endl;
                m.hp *= 0.5;
                hp *= 0.75;
                hp -= damage(m);
                mp -= curse.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << curse.mpcon << " MP)" << endl;
        }
        return false;
    }
};

#endif // MAGICIAN_H_INCLUDED
