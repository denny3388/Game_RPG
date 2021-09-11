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
        cout << "�п�J�A���m�W => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "�A�A�����F�@�W�y�H!" << endl;
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
        cout << ">>�A��ĤH�g�X�F�}�b!" << endl;;
        int d = (rand()%(atk-lowatk+1))+lowatk;
        m.hp -= d;
        hp -= damage(m);
    }
    bool skill(monster &m)
    {
        if(noskill>=0){
            cout << ">>�A���J[����]���A�A���^�X�L�k�ϥΧޯ�!" << endl;
            return false;
        }
        int choose=0;
        poison.set(1,"�@�r����","3�^�X���ϼĤ褤�r�A�C�^�X����ֶq�ˮ`",40);
        live.set(2,"�D�ͥ���","2�^�X���ۨ������O�p�T����",35);
        chance.set(3,"�����Ӱ�","�U�^�X�L�k��ʡA�U�U�^�X�������O�j�T����",50);
        if(halfmp)//�ޯ௵�D�D��ĪG
        {
            poison.mpcon/=2; live.mpcon/=2; chance.mpcon/=2; halfmp=0;
            cout << "(�����o�ʧޯ����MP��b)" << endl;
        }
        cout << endl << "�п�ܭn�ϥΪ��ޯ� => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= poison.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << poison.name << "]!!!" << endl;
                m.poison=3;
                hp -= damage(m);
                mp -= poison.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << poison.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= live.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << live.name << "]!!!" << endl;
                excited=2;
                hp -= damage(m);
                mp -= live.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << live.mpcon << " MP)" << endl;
        }
        else if(choose==3)
        {
            if(mp >= chance.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << chance.name << "]!!!" << endl;
                chances=2;
                hp -= damage(m);
                mp -= chance.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << chance.mpcon << " MP)" << endl;
        }
        return false;
    }
};



#endif // HUNTER_H_INCLUDED
