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
        cout << "�п�J�A���m�W => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "�A�����F�@�W�԰Ӯv!" << endl;
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
        cout << ">>�A���ɤF�ĤH!" << endl;
        m.hp -= (rand()%atk-atk/5+1)+atk/5;
        hp -= damage(m);
    }
    bool skill(monster &m)
    {
        int choose=0;

        cout << endl;
        skills sleep(1,"�ʯv�N","�ϼĤ賴�J�V��1�^�X�A�����ˮ`�N�ۤv�Ө�",30);
        skills talk(2,"�T�o���ꤧ��","���齬��a���A���������A2�^�X�Ĥ�����O�j�T���",25);
        cout << endl << "�п�ܭn�ϥΪ��ޯ� => ";
        while(choose!=1&&choose!=2)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= sleep.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << sleep.name << "]!!!" << endl;
                m.mess += 1;
                hp -= damage(m);
                mp -= sleep.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << sleep.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= talk.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << talk.name << "]!!!" << endl;
                m.weak+=2;
                hp -= damage(m);
                mp -= talk.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << talk.mpcon << " MP)" << endl;
        }
        return false;
    }

    void defense(monster &m)
    {
        cout << ">>" << name << " ���m�F!" << endl;
        hp -= (m.atk()/2);
    }
};

#endif // CONSULTANT_H_INCLUDED
