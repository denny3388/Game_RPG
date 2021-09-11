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
        cout << "遊戲開始!" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "(1戰士 / 2法師 / 3占卜師 / 4刺客 / 5獵人)" << endl;
        cout << "請選擇你的職業 => ";
        while(Class!="1" && Class!="2" && Class!="3" && Class!="4" && Class!="5")
            cin >> Class;

        if(Class == "1")
        {
            warrior p;
            name = p.name;
            classes = "戰士";
            battle(lv,p,next);
        }
        else if(Class == "2")
        {
            magician p;
            name = p.name;
            classes = "法師";
            battle(lv,p,next);
        }
        else if(Class == "3")
        {
            fortune p;
            name = p.name;
            classes = "占卜師";
            battle(lv,p,next);
        }
        else if(Class == "4")
        {
            assassin p;
            name = p.name;
            classes = "刺客";
            battle(lv,p,next);
        }
        else if(Class == "5")
        {
            hunter p;
            name = p.name;
            classes = "獵人";
            battle(lv,p,next);
        }
        cout << "----------------------------------------------------------" << endl;
        cout << "遊戲結束..." << endl;
        cout << "最佳成績為 stage " << lv << endl;
        again = yorn("再試一次? (y/n) => ");

        //輸出至排行榜
        string gradeyn = yorn("是否記錄此次成績? (y/n) => ");
        if(gradeyn=="y") output(name,classes,lv);
        cout << endl;
    }

    //計算遊戲時間
    END = clock();
    int totalsec = (END-START)/1000;
    minute = totalsec/60;
    sec = totalsec>60?totalsec%60:totalsec;
    cout << "本次遊戲共花了 " << minute << " 分 " << sec << " 秒 " << endl;
};
