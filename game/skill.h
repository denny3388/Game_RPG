#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED
#include<string>
#include"player.h"

class skills{
public:
    string name,info,lvupinfo;
    int num,mpcon,lv=1;

    set(int nu, string n, string i, int mc, string luif){
        num=nu;
        name=n;
        info=i;
        mpcon=mc;
        lvupinfo=luif;
    }

    show(){
        cout << num << "." << name << "Lv." << lv << "¡G" << info << "(®ø¯Ó MP " << mpcon << ")" << endl;
    }

    lvup(){
        lv++;
        cout << "技能 [" << name << "] 的等級為 " << lv << "，" << lvupinfo << endl;
    }
};



#endif // SKILL_H_INCLUDED
