#ifndef WARRIOR_H_INCLUDED
#define WARRIOR_H_INCLUDED
#include"player.h"
#include"skill.h"

class warrior : public player
{
public:
    warrior(int h=450,int m=150, int a=30)
    {
        bhp=h; bmp=m; batk=a;
        update();
        recover2max();
        cout << "請輸入你的姓名 => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "，你成為了一名戰士!" << endl;
        getability();
        getstatus();
    }
    void update()
    {
        maxhp = bhp*(1+sta/50.0);
        maxmp = bmp*(1+inte/50.0);
        miss = dex*0.2+sta*0.15+2;
        if(miss>maxmiss) miss=maxmiss;
        atk = batk*(1+str/50.0);
        lowatk = atk*0.2;
    }
    void attack(monster &m)
    {
        int d=(rand()%atk-lowatk+1)+lowatk;
        cout << ">>你用劍攻擊了敵人!" << endl;
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
        skills justice(1,"正義之劍","對敵方造成 80+120% 的傷害",35);
        skills shield(2,"神聖之盾","反擊此回合敵方造成的 50% 傷害",25);
        skills rush(3,"越挫越勇","此回合內，自身的HP剩餘越少，對敵方造成傷害越高",50);

        if(halfmp)//技能秘笈道具效果
        {
            justice.mpcon/=2; shield.mpcon/=2; rush.mpcon/=2; halfmp=0;
            cout << "(此次發動技能消耗MP減半)" << endl;
        }
        cout << endl << "請選擇要使用的技能 => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= justice.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << justice.name << "]!!!" << endl;
                m.hp -= 50+1.2*atk;
                hp -= damage(m);
                mp -= justice.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << justice.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= shield.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << shield.name << "]!!!" << endl;
                int d = damage(m)/2;
                m.hp -= d;
                hp -= d;
                mp -= shield.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << shield.mpcon << " MP)" << endl;
        }
        else if(choose==3){
            if(mp >= rush.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << rush.name << "]!!!" << endl;
                float hpleft = (float)hp/(float)maxhp;
                int d=(rand()%atk-lowatk+1)+lowatk;

                if(0<hpleft&&hpleft<=0.1) d*=5;
                else if(0.1<hpleft&&hpleft<=0.3) d*=4;
                else if(0.3<hpleft&&hpleft<=0.5) d*=3;
                else d*=2;

                m.hp -= d;
                hp -= damage(m);
                mp -= rush.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << rush.mpcon << " MP)" << endl;
        }
        return false;
    }
};


#endif // WARRIOR_H_INCLUDED
