#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;

class monster
{
public:
    //status
    int freeze=0,mess=0,poison=0,weak=0;
    //constitution
    int lv;
    int hp;
    int atkv;
    int lowatkv;//�̧C�����O
    int skillprob=0;
    monster(){}
    monster(int l)
    {
        lv = l;
        hp = 80+20*lv;
        atkv = 8+2*lv;
        lowatkv=0.25*atkv;
        cout <<"**********************************************************" << endl <<
             "STAGE " << lv << endl;
        cout << "�ĤH�������O�� [" << lowatkv << "~" << atkv << "]" << endl;
    }
    void getstatus()
    {
        cout << "�ĤHHP�� [" << (hp<0?0:hp) << "]" << endl;
    }
    int atk()
    {
        if(hp>0)
        {
            if(freeze>0)
            {
                cout << ">>�ĤH���J[�ᵲ]���A�A���^�X�L�k����!(�ѤU " << --freeze << " �^�X)" << endl;
                return 0;
            }
            else if(mess>0)
            {
                cout << ">>�ĤH���J[�V��]���A�A��ۤv�o�ʤF����!(�ѤU " << --mess << " �^�X)" << endl;
                hp -= (rand()%(atkv-lowatkv+1))+lowatkv;
                return 0;
            }
            else if(poison>0)
            {
                int pd = (rand()%(atkv-lowatkv+1))+lowatkv;
                int d = (rand()%(8+2*lv))+1;
                cout << ">>�ĤH���J[���r]���A�A����F" << pd << "�I�ˮ`!(�ѤU " << --poison << " �^�X)" << endl;
                cout << ">>�ĤH�o�ʤF����!" << endl;
                hp -= pd;
                return d;
            }
            else if(weak>0){
                int d = (rand()%(atkv-lowatkv+1))+lowatkv;
                cout << ">>�ĤH���J[�Z��]���A�A�����O�j�T�U��!(�ѤU " << --weak << " �^�X)" << endl;
                cout << ">>�ĤH�o�ʤF����!" << endl;
                return d/5;
            }
            else
            {
                int d = (rand()%(atkv-lowatkv+1))+lowatkv;
                cout << ">>�ĤH�o�ʤF����!" << endl;
                return d;
            }
        }
        else
        {
            cout << ">>�ĤH�Q���ˤF!" << endl;
            return 0;
        }
    }
    virtual int skill(){}
};

class bigmonster: public monster{
public:
    int maxskillprob = 40;
    bigmonster(int l){
        skillprob = 10+lv;
        if(skillprob>maxskillprob) skillprob=maxskillprob;
        lv = l;
        hp = 80+20*lv;
        atkv = 8+2*lv;
        lowatkv = 0.4*atkv;
        cout <<"**********************************************************" << endl <<
             "STAGE " << lv << endl;
        cout << "�A�I��F��^�ĤH!!!" << endl;
        cout << "�ĤH�������O�� [" << lowatkv << "~" << atkv << "]" << endl;
    }
    int skill(){
        int choose = rand()%4+1;
//        choose = 2;
        switch(choose){
            case 1:{
                cout << ">>�ĤH�ϥX[�@�r���}]!�A���J[���r]���A3�^�X�AHP������!" << endl;
                return 1; break;
            }
            case 2:{
               cout << ">>�ĤH�ϥX[����E��]!�A���J[����]���A2�^�X�A�L�k�o�ʧޯ�!" << endl;
                return 2; break;
            }

            case 3:{
                cout << ">>�ĤH�ϥX[���]�k�G]!�A���J[��z]���A3�^�X�A�����O�p�T�U��!" << endl;
                return 3; break;
            }

            case 4:{
                cout << ">>�ĤH�ϥX[��w���u]!�A���J[��w]���A3�^�X�A�j�ײv�p�T�U��!" << endl;
                return 4; break;
            }
        }
    }

    int atk()
    {
        if(hp>0)
        {
            if(freeze>0)
            {
                cout << ">>�ĤH���J[�ᵲ]���A�A���^�X�L�k����!(�ѤU " << --freeze << " �^�X)" << endl;
                return 0;
            }
            else if(mess>0)
            {
                cout << ">>�ĤH���J[�V��]���A�A��ۤv�o�ʤF����!(�ѤU " << --mess << " �^�X)" << endl;
                hp -= (rand()%(atkv-lowatkv+1))+lowatkv;
                return 0;
            }
            else if(poison>0)
            {
                int pd = (rand()%(atkv-lowatkv+1))+lowatkv;
                int d = (rand()%(8+2*lv))+1;
                cout << ">>�ĤH���J[���r]���A�A����F" << pd << "�I�ˮ`!(�ѤU " << --poison << " �^�X)" << endl;
                cout << ">>�ĤH�o�ʤF����!" << endl;
                hp -= pd;
                return d;
            }
            else if(weak>0){
                int d = (rand()%(atkv-lowatkv+1))+lowatkv;
                cout << ">>�ĤH���J[�Z��]���A�A�����O�j�T�U��!(�ѤU " << --weak << " �^�X)" << endl;
                cout << ">>�ĤH�o�ʤF����!" << endl;
                return d/5;
            }
            else
            {
                int d = (rand()%(atkv-lowatkv+1))+lowatkv;
                cout << ">>�ĤH�o�ʤF����!" << endl;
                return d;
            }
        }
        else
        {
            cout << ">>�ĤH�Q���ˤF!" << endl;
            return 0;
        }
    }
};

string yorn(string info){
    string yesorno;
    while(yesorno!="y" && yesorno!="n")
    {
        cout << info;
        cin >> yesorno;
    }
    return yesorno;
}
#endif // MONSTER_H_INCLUDED
