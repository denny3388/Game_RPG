#ifndef ASSASSIN_H_INCLUDED
#define ASSASSIN_H_INCLUDED
#include"player.h"
#include"skill.h"

class assassin : public player
{
public:
    int success = 20;//�t�����\�v
    skills kill;
    skills shadow;
    skills face;

    assassin(int h=320,int m=150,int a=20)
    {
        bhp=h; bmp=m; batk=a;
        update();
        recover2max();
        cout << "�п�J�A���m�W=> ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "�A�A�����F�@�W���!" << endl;
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
        cout << ">>�A�ηt�������F�ĤH!" << endl;
        m.hp -= (rand()%(atk-lowatk+1))+lowatk;
        hp -= damage(m);
    }
    bool skill(monster &m)
    {
        if(noskill>=0){
            cout << ">>�A���J[����]���A�A���^�X�L�k�ϥΧޯ�!" << endl;
            return false;
        }
        srand(time(NULL));
        int choose=0;
        kill.set(1,"�t��","���@�w���v�i�������˼ĤH",50);
        shadow.set(2,"�v�ê�","�è���·t���A3�^�X���j�ײv�j�T����",35);
        face.set(3,"���e�N","�ܸ˭��C�ĤH�٤ߡA3�^�X���t�������v�j�T����",40);
        if(halfmp)//�ޯ௵�D�D��ĪG
        {
            kill.mpcon/=2; shadow.mpcon/=2; face.mpcon/=2; halfmp=0;
            cout << "(�����o�ʧޯ����MP��b)" << endl;
        }
        cout << endl << "�п�ܭn�ϥΪ��ޯ� => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= kill.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << kill.name << "]!!!" << endl;
                int s = faces>0?success*2:success;
                if((rand()%100)+1 <= s)
                {
                    cout << ">>�t������!" << endl;
                    m.hp = 0;
                    m.atk();
                }
                else
                {
                    cout << ">>�t������!" << endl;
                    hp -= damage(m);
                }
                mp -= kill.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << kill.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= shadow.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << shadow.name << "]!!!" << endl;
                shade = 3;
                hp -= damage(m);
                mp -= shadow.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << shadow.mpcon << " MP)" << endl;
        }
        else if(choose==3)
        {
            if(mp >= face.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << face.name << "]!!!" << endl;
                faces = 3;
                hp -= damage(m);
                mp -= face.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << face.mpcon << " MP)" << endl;
        }
        return false;
    }
};


#endif // ASSASSIN_H_INCLUDED
