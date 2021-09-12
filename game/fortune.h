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
        cout << "請輸入你的姓名 => ";
        cin >> name;
        cout << "----------------------------------------------------------" << endl;
        cout << name << "，你成為了一名占卜師!" << endl;
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

        cout << ">>你用話術攻擊了敵人!";
        if(good)
        {
            d*=3;
            cout << "(受到占卜結果影響，此次攻擊傷害大幅提升)";
        }
        else if(bad){
            d/=3;
            cout << "(受到占卜結果影響，此次攻擊傷害大幅下降)";
        }
        cout << endl;
        m.hp -= d;
        hp -= damage(m);

        good=0; bad=0;
    }
    bool skill(monster &m)
    {
        if(noskill>=0){
            cout << ">>你陷入[束縛]狀態，此回合無法使用技能!" << endl;
            return false;
        }
        int choose=0;
        skills sleep(1,"催眠術","使敵方陷入混亂，此回合的攻擊傷害將自己承受",40);
        skills talk(2,"三寸不爛之舌","說服對方放棄攻擊，2回合敵方攻擊力大幅減少",30);
        skills draw(3,"命運占卜","為自己占卜，結果隨機出現，若為「吉」則下次攻擊傷害大幅提升，若為「凶」則下次攻擊傷害大幅下降",60);
        if(halfmp)//技能秘笈道具效果
        {
            sleep.mpcon/=2; talk.mpcon/=2; draw.mpcon/=2; halfmp=0;
            cout << "(此次發動技能消耗MP減半)" << endl;
        }
        cout << endl << "請選擇要使用的技能 => ";
        while(choose!=1&&choose!=2&&choose!=3)
            cin >> choose;
        cout << endl;

        if(choose==1)
        {
            if(mp >= sleep.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << sleep.name << "]!!!" << endl;
                m.mess += 1;
                hp -= damage(m);
                mp -= sleep.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << sleep.mpcon << " MP)" << endl;
        }
        else if(choose==2)
        {
            if(mp >= talk.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << talk.name << "]!!!" << endl;
                m.weak+=2;
                hp -= damage(m);
                mp -= talk.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << talk.mpcon << " MP)" << endl;
        }
        if(choose==3)
        {
            if(good||bad){cout << ">>必須等占卜結果實行之後才可以再次占卜!" << endl; return false;}
            if(mp >= draw.mpcon)
            {
                cout << ">>" << name << " 使用技能[" << draw.name << "]!!!" << endl;
                if(rand()%100+1<=50){
                    cout << ">>占卜結果是「吉」，下次攻擊傷害大幅提升!" << endl;
                    good++;
                }
                else{
                    cout << ">>占卜結果是「凶」，下次攻擊傷害大幅下降!" << endl;
                    bad++;
                }
                hp -= damage(m);
                mp -= draw.mpcon;
                return true;
            }
            else
                cout << ">>你的 MP 不足!(需要 " << draw.mpcon << " MP)" << endl;
        }
        return false;
    }

};


#endif // FORTUNE_H_INCLUDED
