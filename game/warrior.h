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
        cout << "�п�J�A���m�W => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "�A�A�����F�@�W�Ԥh!" << endl;
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
        cout << ">>�A�μC�����F�ĤH!" << endl;
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
        skills justice(1,"���q���C","��Ĥ�y�� 80+120% ���ˮ`",35);
        skills shield(2,"���t����","�������^�X�Ĥ�y���� 50% �ˮ`",25);
        skills rush(3,"�V���V�i","���^�X���A�ۨ���HP�Ѿl�V�֡A��Ĥ�y���ˮ`�V��",50);

        if(halfmp)//�ޯ௵�D�D��ĪG
        {
            justice.mpcon/=2; shield.mpcon/=2; rush.mpcon/=2; halfmp=0;
            cout << "(�����o�ʧޯ����MP��b)" << endl;
        }
        cout << endl << "�п�ܭn�ϥΪ��ޯ� => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= justice.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << justice.name << "]!!!" << endl;
                m.hp -= 50+1.2*atk;
                hp -= damage(m);
                mp -= justice.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << justice.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= shield.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << shield.name << "]!!!" << endl;
                int d = damage(m)/2;
                m.hp -= d;
                hp -= d;
                mp -= shield.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << shield.mpcon << " MP)" << endl;
        }
        else if(choose==3){
            if(mp >= rush.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << rush.name << "]!!!" << endl;
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
                cout << ">>�A�� MP ����!(�ݭn " << rush.mpcon << " MP)" << endl;
        }
        return false;
    }
};


#endif // WARRIOR_H_INCLUDED
