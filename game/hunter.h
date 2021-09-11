#ifndef HUNTER_H_INCLUDED
#define HUNTER_H_INCLUDED
#include"player.h"
#include"skill.h"

class hunter : public player
{
public:
    skills poison;
    skills live;
    skills chance;
    hunter(int h=400,int m=200,int a=25)
    {
        bhp=h; bmp=m; batk=a;
        update();
        recover2max();
        cout << "請輸入你的姓名 => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "，你成為了一名獵人!" << endl;
        getability();
        getstatus();
    }
    void update()
    {
        maxhp = bhp*(1+sta/50.0);
        maxmp = bmp*(1+inte/50.0);
        miss=dex*0.25+sta*0.1+3;
        if(miss>maxmiss)miss=maxmiss;
        atk = batk*(1+str/100.0+dex/100.0);
        lowatk = atk*0.2;
    }
    void attack(monster &m)
    {
        cout << ">>你對敵人射出了弓箭!" << endl;;
        int d = (rand()%(atk-lowatk+1))+lowatk;
        m.hp -= d;
        hp -= damage(m);
    }
    bool skill(monster &m)
    {
        if(noskill>=0){
            cout << ">>你陷入[束縛]狀態，此回合無法使用技能!" << endl;
            return false;
        }
        int choose=0;
        poison.set(1,"劇毒陷阱","3回合內使敵方中毒，每回合受到少量傷害",40);
        live.set(2,"求生本能","2回合內自身攻擊力小幅提升",35);
        chance.set(3,"伺機而動","下回合無法行動，下下回合的攻擊力大幅提升",50);
        if(halfmp)//技能秘笈道具效果
        {
            poison.mpcon/=2; live.mpcon/=2; chance.mpcon/=2; halfmp=0;
            cout << "(此次發動技能消耗MP減半)" << endl;
        }
        cout << endl << "請選擇要使用的技能 => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= poison.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << poison.name << "]!!!" << endl;
                m.poison=3;
                hp -= damage(m);
                mp -= poison.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << poison.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= live.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << live.name << "]!!!" << endl;
                excited=2;
                hp -= damage(m);
                mp -= live.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << live.mpcon << " MP)" << endl;
        }
        else if(choose==3)
        {
            if(mp >= chance.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << chance.name << "]!!!" << endl;
                chances=2;
                hp -= damage(m);
                mp -= chance.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << chance.mpcon << " MP)" << endl;
        }
        return false;
    }
};



#endif // HUNTER_H_INCLUDED
