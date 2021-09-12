#ifndef GRADE_H_INCLUDED
#define GRADE_H_INCLUDED
#include<stdlib.h>
#include<string>
#include<string.h>
#include<sstream>
#include<fstream>

string int2str(int &i){
    string s;
    stringstream ss(s);
    ss << i;
    return ss.str();
}

void output(string& name,string& classes, int& lv){
    string mid=" 的最佳成績為 stage ";
    string grade;
    grade = name + "(" + classes + ")" + mid + int2str(lv);

    ofstream file;
    file.open("grade.txt",ios::app);
    if(!file){cerr << "無法開啟檔案!" << endl;}
    file << grade << endl;
    file.close();

}


#endif // GRADE_H_INCLUDED
