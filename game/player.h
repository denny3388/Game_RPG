#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include<iomanip>
#include<string>
#include"monster.h"

using namespace std;
class player
{
public:
    //basic ability
    string name;
    float sta,str,inte,dex;
    float miss,maxmiss=40;
    int maxhp,hp,bhp;
    int maxmp,mp,bmp;
    int lv=1;
    int atk,batk,lowatk;
    //debuff
    int halfmp=0,noskill=-1;
    int weak=0,slow=0,poison=0;
    //buff
    int protect=0;//女神庇佑
    int good=0;
    int bad=0;//命運占卜
    int shade=0;//影子使者
    int faces=0;//易容術
    int excited=0;//求生本能
    int chances=0;//伺機而動
    int invisible=0;//道具隱形斗篷

    player()
    {
        string yn="n";
        while(yn=="n")
        {
            cout << "請依序輸入體力、力量、智力、敏捷(總和為50) => ";
            cin >> sta >> str >> inte >> dex;
            if(sta+str+inte+dex>50) {cout << "能力值總和不能超過50!" << endl;}
            else if(sta<0||str<0||inte<0||dex<0) {cout << "能力值不能為負值!" << endl;}
            else {yn=yorn("確定輸入能力值? (y/n) => ");}
        }
    }
    void getstatus()
    {
        cout << "你的 HP/MP 為 [" << (hp<0?0:hp) << "/" << (mp<0?0:mp) << "]" << endl;
    }
    void getability()
    {
        cout << "你現在等級為 "<< lv << " 級" << endl;
        cout << "攻擊力為 [" << lowatk << "~" << atk << "]" << endl;
        cout << "迴避率為 " << miss << " % (上限為" << maxmiss << "%)" << endl;
    }
    void lvup()
    {
        int a=0,b=0,c=0,d=0;
        string yn="n";
        cout << "等級提升!" << endl;
        while(yn=="n")
        {
            cout << "請依序輸入體力、力量、智力、敏捷(總和為10) => ";
            cin >> a >> b >> c >> d;
            if(a+b+c+d>10) {cout << "能力值總和不能超過10!" << endl;}
            else if(a<0||b<0||c<0||d<0) {cout << "能力值不能為負值!" << endl;}
            else {yn=yorn("確定輸入能力值? (y/n) => ");}
        }
        sta+=a; str+=b; inte+=c; dex+=d;
        cout << endl;
    }
    void recover2max()
    {
        hp=maxhp;
        mp=maxmp;
    }
    virtual void update() = 0;//升級後更新能力值
    bool action(monster &m)
    {
        string ac="";
        cout << endl << name << "，你想採取什麼行動? (1攻擊/2技能/3防禦) => ";
        while(ac!="1" && ac!="2" && ac!="3")
            cin >> ac;
        cout << endl;

        if(ac == "1")
        {
            attack(m);
            return true;
        }
        else if(ac == "2")
        {
            if(skill(m))
                return true;
            return false;
        }
        else if(ac == "3")
        {
            defense(m);
            return true;
        }
    }
    virtual void attack(monster &) = 0;
    virtual bool skill(monster &) = 0;
    void defense(monster &m)
    {
        cout << ">>" << name << " 防禦了!" << endl;
        hp -= (damage(m)/2);
    }
    bool exestat(monster &);
    int damage(monster &m)
    {
        if(rand()%100+1 < m.skillprob && m.hp>0)
        {
            int choose=m.skill();
            switch(choose)
            {
            case 1:{poison=3;break;}
            case 2:{noskill=2;break;}
            case 3:{weak=3;break;}
            case 4:{slow=3;break;}
            }
            return 0;
        }
        else
        {
            int d = m.atk();
            if(d>0 && (rand()%100+1 < miss || invisible-->0))
            {
                cout << ">>你迴避了敵人的攻擊!" << endl;
                return 0;
            }
            return d;
        }
    }
};

bool player::exestat(monster& m)
{
    cout << endl;
    //debuff
    if(weak)
    {
        atk*=0.8;
        cout << ">>此回合受到[虛弱]效果影響，攻擊力小幅下降!(還剩 " << --weak << " 回合)" << endl;
    }
    if(slow)
    {
        miss*=0.7;
        cout << ">>此回合受到[遲鈍]效果影響，迴避率大幅下降!(剩下 " << --slow << " 回合)" << endl;
    }
    if(poison)
    {
        hp-=10;
        cout << ">>此回合受到[中毒]效果影響，HP小幅減少!(剩下 " << --poison << " 回合)" << endl;
    }
    if((--noskill)>=0)
    {
        cout << ">>此回合受到[束縛]效果影響，無法使用技能!(剩下 " << noskill << " 回合)" << endl;
    }
    //buff
    if(protect)
    {
        cout << ">>你處於女神的庇佑下，無法採取任何動作!(剩下 " << --protect << " 回合)" << endl << endl;
        hp += (10+inte*1.1);
        if(hp>maxhp) hp=maxhp;
        hp -= damage(m);
        return false;
    }
    if(shade)
    {
        cout << ">>此回合因為[影藏者]的效果，迴避率大幅上升!(剩下 " << --shade << " 回合)" << endl;
        miss*=2;
    }
    if(faces)
    {
        cout << ">>此回合因為[易容術]的效果，暗殺完成率大幅上升!(剩下 " << --faces << " 回合)" << endl;
    }
    if(excited)
    {
        cout << ">>此回合因為[求生本能]的效果，攻擊力小幅上升!(剩下 " << --excited << " 回合)" << endl;
        atk*=1.2;
    }
    if(chances==2)
    {
        cout << ">>因為[伺機而動]的效果，此回合無法行動!" << endl << endl;
        chances--;
        hp -= damage(m);
        return false;
    }
    if(chances==1)
    {
        cout << ">>此回合因為[伺機而動]的效果，攻擊力大幅提升!" << endl;
        atk*=2.5;
        chances--;
    }
    return true;
}

#endif // PLAYER_H_INCLUDED
