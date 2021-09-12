#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED
#include<string>
#include"player.h"

class skills{
public:
    string name,info;
    int num,mpcon;
    skills(int nu, string n, string i, int mc):num(nu),name(n),info(i),mpcon(mc)
    {
        cout << nu << "." << n << "¡G" << i << "(®ø¯Ó MP " << mpcon << ")" << endl;
    }
};


#endif // SKILL_H_INCLUDED
