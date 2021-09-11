#ifndef ASSASSIN_H_INCLUDED
#define ASSASSIN_H_INCLUDED
#include"player.h"
#include"skill.h"

class assassin : public player
{
public:
    int success = 20;//暗殺成功率
    skills kill;
    skills shadow;
    skills face;

    assassin(int h=320,int m=150,int a=20)
    {
        bhp=h; bmp=m; batk=a;
        update();
        recover2max();
        cout << "請輸入你的姓名=> ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "，你成為了一名刺客!" << endl;
        getability();
        getstatus();
    }
    void update()
    {
        maxhp = bhp*(1+sta/50.0);
        maxmp = bmp*(1+inte/50.0);
        miss = dex*0.3+sta*0.1+5;
        if(miss>maxmiss)miss=maxmiss;
        atk = batk*(1+dex/50.0);
        lowatk = atk*0.2;
    }
    void attack(monster &m)
    {
        cout << ">>你用暗器攻擊了敵人!" << endl;
        m.hp -= (rand()%(atk-lowatk+1))+lowatk;
        hp -= damage(m);
    }
    bool skill(monster &m)
    {
        if(noskill>=0){
            cout << ">>你陷入[束縛]狀態，此回合無法使用技能!" << endl;
            return false;
        }
        srand(time(NULL));
        int choose=0;
        kill.set(1,"暗殺","有一定機率可直接擊倒敵人",50);
        shadow.set(2,"影藏者","藏身於黑暗中，3回合內迴避率大幅提升",35);
        face.set(3,"易容術","變裝降低敵人戒心，3回合內暗殺完成率大幅提升",40);
        if(halfmp)//技能秘笈道具效果
        {
            kill.mpcon/=2; shadow.mpcon/=2; face.mpcon/=2; halfmp=0;
            cout << "(此次發動技能消耗MP減半)" << endl;
        }
        cout << endl << "請選擇要使用的技能 => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= kill.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << kill.name << "]!!!" << endl;
                int s = faces>0?success*2:success;
                if((rand()%100)+1 <= s)
                {
                    cout << ">>暗殺完成!" << endl;
                    m.hp = 0;
                    m.atk();
                }
                else
                {
                    cout << ">>暗殺失敗!" << endl;
                    hp -= damage(m);
                }
                mp -= kill.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << kill.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= shadow.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << shadow.name << "]!!!" << endl;
                shade = 3;
                hp -= damage(m);
                mp -= shadow.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << shadow.mpcon << " MP)" << endl;
        }
        else if(choose==3)
        {
            if(mp >= face.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << face.name << "]!!!" << endl;
                faces = 3;
                hp -= damage(m);
                mp -= face.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << face.mpcon << " MP)" << endl;
        }
        return false;
    }
};


#endif // ASSASSIN_H_INCLUDED
