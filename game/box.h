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
        cout << ">>你得到了 [" << name << "] !" << info << "!" << endl;
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
    string yn = yorn("你發現了一個寶箱!要打開嗎? (y/n) => ");
    if(yn=="n") return;

    //all items
    smallhppotion smallhp(0,"小型生命藥水","HP小幅回復");
    bighppotion bighp(1,"大型生命藥水","HP大幅回復");
    smallmppotion smallmp(2,"小型魔力藥水","MP小幅回復");
    bigmppotion bigmp(3,"大型魔力藥水","MP大幅回復");
    magicbook mabo(4,"技能秘笈","下次使用技能MP消耗減半");
    bomb bo(5,"炸彈","HP小幅減少");
    stapotion stap(6,"體力藥水","體力小幅提升");
    strpotion strp(7,"力量藥水","力量小幅提升");
    intepotion intep(8,"智力藥水","智力小幅提升");
    dexpotion dexp(9,"敏捷藥水","敏捷小幅提升");
    superpotion superp(10,"超級藥水","HP和MP回復至最大值");
    cross cr(11,"神聖十字架","消除所有負面狀態");
    bigbomb bigbo(12,"巨型炸彈","HP大幅減少");
    nuclear nu(13,"原子彈","HP歸零");
    invisiblecloak incl(14,"隱形斗篷","迴避敵人下一次攻擊");

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
