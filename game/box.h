#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED
#define NUM_OF_ITEMS 15

class item{
public:
    int num;
    string name,info;
    item(int nu,string n,string i){
        num=nu; name=n; info=i;
    }
    void get(){
        cout << ">>�A�o��F [" << name << "] !" << info << "!" << endl;
    }
    virtual void use(player&) = 0;
};

class smallhppotion : public item{
public:
    smallhppotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.hp+=100;
        if(p.hp>p.maxhp) p.hp=p.maxhp;
    }
};
class bighppotion : public item{
public:
    bighppotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.hp+=250;
        if(p.hp>p.maxhp) p.hp=p.maxhp;
    }
};
class smallmppotion : public item{
public:
    smallmppotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.mp+=100;
        if(p.mp>p.maxmp) p.mp=p.maxmp;
    }
};
class bigmppotion : public item{
public:
    bigmppotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.mp+=200;
        if(p.mp>p.maxmp) p.mp=p.maxmp;
    }
};

class magicbook : public item{
public:
    magicbook(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.halfmp=1;
    }
};

class bomb : public item{
public:
    bomb(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.hp-=20;
    }
};
class stapotion : public item{
public:
    stapotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.sta+=2;
    }
};
class strpotion : public item{
public:
    strpotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.str+=2;
    }
};
class intepotion : public item{
public:
    intepotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.inte+=2;
    }
};
class dexpotion : public item{
public:
    dexpotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.dex+=2;
    }
};
class superpotion : public item{
public:
    superpotion(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.recover2max();
    }
};
class cross : public item{
public:
    cross(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.weak = p.slow = p.poison = p.noskill = 0;
    }
};
class bigbomb : public item{
public:
    bigbomb(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.hp-=100;
    }
};
class nuclear : public item{
public:
    nuclear(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.hp=0;;
    }
};
class invisiblecloak : public item{
public:
    invisiblecloak(int nu,string n,string i):item(nu,n,i){}
    void use(player& p){
        get();
        p.invisible=1;
    }
};

void box(player& p){
    //yes or no
    string yn = yorn("�A�o�{�F�@���_�c!�n���}��? (y/n) => ");
    if(yn=="n") return;

    //all items
    smallhppotion smallhp(0,"�p���ͩR�Ĥ�","HP�p�T�^�_");
    bighppotion bighp(1,"�j���ͩR�Ĥ�","HP�j�T�^�_");
    smallmppotion smallmp(2,"�p���]�O�Ĥ�","MP�p�T�^�_");
    bigmppotion bigmp(3,"�j���]�O�Ĥ�","MP�j�T�^�_");
    magicbook mabo(4,"�ޯ௵�D","�U���ϥΧޯ�MP���Ӵ�b");
    bomb bo(5,"���u","HP�p�T���");
    stapotion stap(6,"��O�Ĥ�","��O�p�T����");
    strpotion strp(7,"�O�q�Ĥ�","�O�q�p�T����");
    intepotion intep(8,"���O�Ĥ�","���O�p�T����");
    dexpotion dexp(9,"�ӱ��Ĥ�","�ӱ��p�T����");
    superpotion superp(10,"�W���Ĥ�","HP�MMP�^�_�̤ܳj��");
    cross cr(11,"���t�Q�r�[","�����Ҧ��t�����A");
    bigbomb bigbo(12,"�������u","HP�j�T���");
    nuclear nu(13,"��l�u","HP�k�s");
    invisiblecloak incl(14,"���Τ��O","�j�׼ĤH�U�@������");

    //choose items
    int mode = (rand()%NUM_OF_ITEMS+1)%NUM_OF_ITEMS;
//    mode = 14;
    if(mode==smallhp.num)smallhp.use(p);
    else if(mode==bighp.num)bighp.use(p);
    else if(mode==smallmp.num)smallmp.use(p);
    else if(mode==bigmp.num)bigmp.use(p);
    else if(mode==mabo.num)mabo.use(p);
    else if(mode==bo.num)bo.use(p);
    else if(mode==stap.num){stap.use(p); p.update();}
    else if(mode==strp.num){strp.use(p); p.update();}
    else if(mode==intep.num){intep.use(p); p.update();}
    else if(mode==dexp.num){dexp.use(p); p.update();}
    else if(mode==superp.num){superp.use(p);}
    else if(mode==cr.num){cr.use(p);}
    else if(mode==bigbo.num){bigbo.use(p);}
    else if(mode==nu.num){nu.use(p);}
    else if(mode==incl.num){incl.use(p);}
}

#endif // BOX_H_INCLUDED
