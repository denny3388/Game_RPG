#ifndef FORTUNE_H_INCLUDED
#define FORTUNE_H_INCLUDED

class fortune : public player
{
public:
    fortune(int h=250,int m=300,int a=15)
    {
        bhp=h; bmp=m; batk=a;
        update();
        recover2max();
        cout << "�п�J�A���m�W => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "�A�A�����F�@�W�e�R�v!" << endl;
        getability();
        getstatus();
    }
    void update()
    {
        maxhp = bhp*(1+sta/50.0);
        maxmp = bmp*(1+inte/40.0);
        miss = dex*0.2+sta*0.1+1;
        if(miss>maxmiss)miss=maxmiss;
        atk = batk*(1+inte/50.0);
        lowatk = atk*0.2;
    }
    void attack(monster &m)
    {
        int d = (rand()%(atk-lowatk+1))+lowatk;

        cout << ">>�A�θܳN�����F�ĤH!";
        if(good)
        {
            d*=3;
            cout << "(����e�R���G�v�T�A���������ˮ`�j�T����)";
        }
        else if(bad){
            d/=3;
            cout << "(����e�R���G�v�T�A���������ˮ`�j�T�U��)";
        }
        cout << endl;
        m.hp -= d;
        hp -= damage(m);

        good=0; bad=0;
    }
    bool skill(monster &m)
    {
        if(noskill>=0){
            cout << ">>�A���J[����]���A�A���^�X�L�k�ϥΧޯ�!" << endl;
            return false;
        }
        int choose=0;
        skills sleep(1,"�ʯv�N","�ϼĤ賴�J�V�áA���^�X�������ˮ`�N�ۤv�Ө�",40);
        skills talk(2,"�T�o���ꤧ��","���A���������A2�^�X�Ĥ�����O�j�T���",30);
        skills draw(3,"�R�B�e�R","���ۤv�e�R�A���G�H���X�{�A�Y���u�N�v�h�U�������ˮ`�j�T���ɡA�Y���u���v�h�U�������ˮ`�j�T�U��",60);
        if(halfmp)//�ޯ௵�D�D��ĪG
        {
            sleep.mpcon/=2; talk.mpcon/=2; draw.mpcon/=2; halfmp=0;
            cout << "(�����o�ʧޯ����MP��b)" << endl;
        }
        cout << endl << "�п�ܭn�ϥΪ��ޯ� => ";
        while(choose!=1&&choose!=2&&choose!=3)
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
        if(choose==3)
        {
            if(good||bad){cout << ">>�������e�R���G��椧��~�i�H�A���e�R!" << endl; return false;}
            if(mp >= draw.mpcon)
            {
                cout << ">>" << name << " �ϥΧޯ�[" << draw.name << "]!!!" << endl;
                if(rand()%100+1<=50){
                    cout << ">>�e�R���G�O�u�N�v�A�U�������ˮ`�j�T����!" << endl;
                    good++;
                }
                else{
                    cout << ">>�e�R���G�O�u���v�A�U�������ˮ`�j�T�U��!" << endl;
                    bad++;
                }
                hp -= damage(m);
                mp -= draw.mpcon;
                return true;
            }
            else
                cout << ">>�A�� MP ����!(�ݭn " << draw.mpcon << " MP)" << endl;
        }
        return false;
    }

};


#endif // FORTUNE_H_INCLUDED
