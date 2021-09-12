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
    int protect=0;//�k���Ȧ�
    int good=0;
    int bad=0;//�R�B�e�R
    int shade=0;//�v�l�Ϫ�
    int faces=0;//���e�N
    int excited=0;//�D�ͥ���
    int chances=0;//�����Ӱ�
    int invisible=0;//�D�����Τ��O

    player()
    {
        string yn="n";
        while(yn=="n")
        {
            cout << "�Ш̧ǿ�J��O�B�O�q�B���O�B�ӱ�(�`�M��50) => ";
            cin >> sta >> str >> inte >> dex;
            if(sta+str+inte+dex>50) {cout << "��O���`�M����W�L50!" << endl;}
            else if(sta<0||str<0||inte<0||dex<0) {cout << "��O�Ȥ��ର�t��!" << endl;}
            else {yn=yorn("�T�w��J��O��? (y/n) => ");}
        }
    }
    void getstatus()
    {
        cout << "�A�� HP/MP �� [" << (hp<0?0:hp) << "/" << (mp<0?0:mp) << "]" << endl;
    }
    void getability()
    {
        cout << "�A�{�b���Ŭ� "<< lv << " ��" << endl;
        cout << "�����O�� [" << lowatk << "~" << atk << "]" << endl;
        cout << "�j�ײv�� " << miss << " % (�W����" << maxmiss << "%)" << endl;
    }
    void lvup()
    {
        int a=0,b=0,c=0,d=0;
        string yn="n";
        cout << "���Ŵ���!" << endl;
        while(yn=="n")
        {
            cout << "�Ш̧ǿ�J��O�B�O�q�B���O�B�ӱ�(�`�M��10) => ";
            cin >> a >> b >> c >> d;
            if(a+b+c+d>10) {cout << "��O���`�M����W�L10!" << endl;}
            else if(a<0||b<0||c<0||d<0) {cout << "��O�Ȥ��ର�t��!" << endl;}
            else {yn=yorn("�T�w��J��O��? (y/n) => ");}
        }
        sta+=a; str+=b; inte+=c; dex+=d;
        cout << endl;
    }
    void recover2max()
    {
        hp=maxhp;
        mp=maxmp;
    }
    virtual void update() = 0;//�ɯū��s��O��
    bool action(monster &m)
    {
        string ac="";
        cout << endl << name << "�A�A�Q�Ĩ�������? (1����/2�ޯ�/3���m) => ";
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
        cout << ">>" << name << " ���m�F!" << endl;
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
                cout << ">>�A�j�פF�ĤH������!" << endl;
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
        cout << ">>���^�X����[��z]�ĪG�v�T�A�����O�p�T�U��!(�ٳ� " << --weak << " �^�X)" << endl;
    }
    if(slow)
    {
        miss*=0.7;
        cout << ">>���^�X����[��w]�ĪG�v�T�A�j�ײv�j�T�U��!(�ѤU " << --slow << " �^�X)" << endl;
    }
    if(poison)
    {
        hp-=10;
        cout << ">>���^�X����[���r]�ĪG�v�T�AHP�p�T���!(�ѤU " << --poison << " �^�X)" << endl;
    }
    if((--noskill)>=0)
    {
        cout << ">>���^�X����[����]�ĪG�v�T�A�L�k�ϥΧޯ�!(�ѤU " << noskill << " �^�X)" << endl;
    }
    //buff
    if(protect)
    {
        cout << ">>�A�B��k�����Ȧ��U�A�L�k�Ĩ�����ʧ@!(�ѤU " << --protect << " �^�X)" << endl << endl;
        hp += (10+inte*1.1);
        if(hp>maxhp) hp=maxhp;
        hp -= damage(m);
        return false;
    }
    if(shade)
    {
        cout << ">>���^�X�]��[�v�ê�]���ĪG�A�j�ײv�j�T�W��!(�ѤU " << --shade << " �^�X)" << endl;
        miss*=2;
    }
    if(faces)
    {
        cout << ">>���^�X�]��[���e�N]���ĪG�A�t�������v�j�T�W��!(�ѤU " << --faces << " �^�X)" << endl;
    }
    if(excited)
    {
        cout << ">>���^�X�]��[�D�ͥ���]���ĪG�A�����O�p�T�W��!(�ѤU " << --excited << " �^�X)" << endl;
        atk*=1.2;
    }
    if(chances==2)
    {
        cout << ">>�]��[�����Ӱ�]���ĪG�A���^�X�L�k���!" << endl << endl;
        chances--;
        hp -= damage(m);
        return false;
    }
    if(chances==1)
    {
        cout << ">>���^�X�]��[�����Ӱ�]���ĪG�A�����O�j�T����!" << endl;
        atk*=2.5;
        chances--;
    }
    return true;
}

#endif // PLAYER_H_INCLUDED
