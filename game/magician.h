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
        cout << "�п�J�A���m�W => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "�A�A�����F�@�W�k�v!" << endl;
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
        cout << ">>�A�Ϊk�N�����F�ĤH!" << endl;
        m.hp -= (rand()%(atk-lowatk+1))+lowatk;
       hp -= damage(m);
    }
    bool skill(monster &m)
    {
        if(noskill>=0){
            cout << ">>�A���J[����]���A�A���^�X�L�k�ϥΧޯ�!" << endl;
            return false;
        }
        int choose=0;
        skills snow(1,"�N�s�s����","��Ĥ�y���ֶq�ˮ`�A�ë���ĤH���2�^�X",40);
        skills god(2,"�k���Ȧ�","3�^�X���L�k�Ĩ�����ʧ@�A�é�C�^�X�^�_HP",60);
        skills curse(3,"�ݦ�A�G","���Ӧۤv�{�� 25% ��HP�A�����Ĥ�{���� 50% HP",100);
        if(halfmp)//�ޯ௵�D�D��ĪG
        {
            snow.mpcon/=2; god.mpcon/=2; curse.mpcon/=2; halfmp=0;
            cout << "(�����o�ʧޯ����MP��b)" << endl;
        }
        cout << endl << "�п�ܭn�ϥΪ��ޯ� => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= snow.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << snow.name << "]!!!" << endl;
                m.freeze+=2;
                m.hp -= (rand()%(lowatk))+1;
                hp -= damage(m);
                mp -= snow.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << snow.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= god.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << god.name << "]!!!" << endl;
                protect+=3;
                hp -= damage(m);
                mp -= god.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << god.mpcon << " MP)" << endl;
        }
        else if(choose==3){
            if(mp >= curse.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << curse.name << "]!!!" << endl;
                m.hp *= 0.5;
                hp *= 0.75;
                hp -= damage(m);
                mp -= curse.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << curse.mpcon << " MP)" << endl;
        }
        return false;
    }
};

#endif // MAGICIAN_H_INCLUDED
