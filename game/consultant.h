#ifndef CONSULTANT_H_INCLUDED
#define CONSULTANT_H_INCLUDED
#include"player.h"
#include"skill.h"

class consultant : public player
{
public:
    consultant(int h=250,int m=300,int a=10)
    {
        bhp=h; bmp=m; batk=a;
        maxhp = hp = bhp*(1+sta/50.0);
        maxmp = mp = bmp*(1+inte/40.0);
        miss = dex+sta/2;
        atk = a*(1+inte/50.0);
        cout << "請輸入你的姓名 => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "你成為了一名諮商師!" << endl;
        getability();
        getstatus();
    }
    void update()
    {
        maxhp = hp = bhp*(1+sta/50.0);
        maxmp = mp = bmp*(1+inte/40.0);
        miss = dex+sta/2;
        atk = batk*(1+inte/50.0);
    }
    void attack(monster &m)
    {
        cout << ">>你輔導了敵人!" << endl;
        m.hp -= (rand()%atk-atk/5+1)+atk/5;
        hp -= damage(m);
    }
    bool skill(monster &m)
    {
        int choose=0;

        cout << endl;
        skills sleep(1,"催眠術","使敵方陷入混亂1回合，攻擊傷害將自己承受",30);
        skills talk(2,"三寸不爛之舌","舌燦蓮花地說服對方放棄攻擊，2回合敵方攻擊力大幅減少",25);
        cout << endl << "請選擇要使用的技能 => ";
        while(choose!=1&&choose!=2)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= sleep.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << sleep.name << "]!!!" << endl;
                m.mess += 1;
                hp -= damage(m);
                mp -= sleep.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << sleep.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= talk.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << talk.name << "]!!!" << endl;
                m.weak+=2;
                hp -= damage(m);
                mp -= talk.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << talk.mpcon << " MP)" << endl;
        }
        return false;
    }

    void defense(monster &m)
    {
        cout << ">>" << name << " 防禦了!" << endl;
        hp -= (m.atk()/2);
    }
};

#endif // CONSULTANT_H_INCLUDED
