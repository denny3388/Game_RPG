#include <iostream>
#include<string>
#include<string.h>
#include<time.h>
#include<sstream>
#include"battle.h"
#include"grade.h"

int main()
{
    double START,END,minute,sec;
    START = clock();
    srand(time(NULL));
    string again = "y";
    while(again=="y")
    {
        int lv;
        string Class="";
        string next = "y";
        string name,classes;
        cout << "�C���}�l!" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "(1�Ԥh / 2�k�v / 3�e�R�v / 4��� / 5�y�H)" << endl;
        cout << "�п�ܧA��¾�~ => ";
        while(Class!="1" && Class!="2" && Class!="3" && Class!="4" && Class!="5")
            cin >> Class;

        if(Class == "1")
        {
            warrior p;
            name = p.name;
            classes = "�Ԥh";
            battle(lv,p,next);
        }
        else if(Class == "2")
        {
            magician p;
            name = p.name;
            classes = "�k�v";
            battle(lv,p,next);
        }
        else if(Class == "3")
        {
            fortune p;
            name = p.name;
            classes = "�e�R�v";
            battle(lv,p,next);
        }
        else if(Class == "4")
        {
            assassin p;
            name = p.name;
            classes = "���";
            battle(lv,p,next);
        }
        else if(Class == "5")
        {
            hunter p;
            name = p.name;
            classes = "�y�H";
            battle(lv,p,next);
        }
        cout << "----------------------------------------------------------" << endl;
        cout << "�C������..." << endl;
        cout << "�̨Φ��Z�� stage " << lv << endl;
        again = yorn("�A�դ@��? (y/n) => ");

        //��X�ܱƦ�]
        string gradeyn = yorn("�O�_�O���������Z? (y/n) => ");
        if(gradeyn=="y") output(name,classes,lv);
        cout << endl;
    }

    //�p��C���ɶ�
    END = clock();
    int totalsec = (END-START)/1000;
    minute = totalsec/60;
    sec = totalsec>60?totalsec%60:totalsec;
    cout << "�����C���@��F " << minute << " �� " << sec << " �� " << endl;
};
