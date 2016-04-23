#include "expression.h"

//#define d_bug_e
//#define d_bug_ee

expression::expression()
{
    myExpression = NULL;
}

expression::~expression()
{
    zero();
}

expression::expression(const expression &other)
{
    copy(other);
}

expression& expression::operator=(const expression &other)
{
    if(this != &other)
    {
        zero();
        copy(other);
    }
    return *this;
}


expression& expression::operator<<(term &input)
{
#ifdef d_bug_e
    cout<<"made it to << operator in expression class"<<endl;
#endif
    term *newTerm = new term(input);

    term *thenext = myExpression;

    term *theprev;
    theprev= new term;
#ifdef d_bug_e
    cout<<"hi ";
#endif
    theprev->setLink(myExpression);
#ifdef d_bug_e
    cout<<"hi ";
#endif
    if(thenext==NULL)
    {
#ifdef d_bug_e
        cout<<"thenext==NULL in << op"<<endl;
#endif
        newTerm->setLink(NULL);
        myExpression= newTerm;
        return *this;
    }
#ifdef d_bug_e
     cout<<"hi ho ";
#endif

    while(thenext!=NULL)
    {
#ifdef d_bug_e
         cout<<"hi the ln power of newTerm is  "<<newTerm->ln_getPower()<<endl;
#endif
        if(newTerm->x_getPower()>(thenext->x_getPower()))
        {
            newTerm->setLink(thenext);
            theprev->setLink(newTerm);

            if(thenext==myExpression)
                myExpression= newTerm;

            return *this;
        }
        else if(newTerm->x_getPower()==thenext->x_getPower() && newTerm->ln_getPower()>(thenext->ln_getPower()))
        {
            newTerm->setLink(thenext);
            theprev->setLink(newTerm);

            if(thenext==myExpression)
                myExpression= newTerm;

            return *this;
        }
        else if(newTerm->x_getPower()==thenext->x_getPower() && newTerm->ln_getPower()==(thenext->ln_getPower()))
        {

            fraction co_eff_a, co_eff_b, co_eff_c, pow_pow_x, pow_pow_LN;

            pow_pow_x=newTerm->x_getPower();

            pow_pow_LN=newTerm->ln_getPower();

#ifdef d_bug_e
            cout<<endl<<"pow ln: "<<pow_pow_LN<<endl<<endl;
#endif

            co_eff_a=newTerm->getCoeff();
            co_eff_b=thenext->getCoeff();
            co_eff_c=co_eff_a+co_eff_b;


            thenext->setTerm(co_eff_c, pow_pow_x, pow_pow_LN);

#ifdef d_bug_e
            cout<<endl<<"ln power in line 103 expression is: "<<pow_pow_LN<<endl;
            cout<<"that term is: ";
            thenext->print_da_term();
            cout<<endl;
#endif

            return *this;
        }

        if(thenext->link()==NULL)
        {
#ifdef d_bug_e
            cout<<"resetting NULL b/c thenext->link()==NULL in << op"<<endl;
#endif

            thenext->setLink(newTerm);

            newTerm->setLink(NULL);
            return *this;
        }

        theprev=thenext;
        thenext=thenext->link();


    }



#ifdef d_bug_e
    cout<<"leaving operator << class in expression"<<endl;
#endif

    return *this;
}

expression& expression::operator<<(string &input)       //this function doesn't look like it was even functional originally 01/04/14
{
    cout<<"WTF"<<endl;
    cout<<"WTF"<<endl;

    term nextTerm;
    char buf;
    int coeffa, powaa;
    stringstream ss;
    ss<<input;
    while(ss>>buf)
    {
        cout<<"inside expression operator <<"<<endl;    //I'm not sure what this function does 01/04/14
    }
        *this<<nextTerm;
    return *this;
}

expression& expression::operator>>(string &output)      //does this function work? 01/04/14
{
    cout<<"this function does something!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!line164"<<endl<<endl<<endl;
    stringstream ss;
    term *head = this->myExpression;
    while(head)
    {
        ss<<*head;
        head = head->link();
    }
    ss>>output;
    return *this;
}

fraction expression::evaluate_ND(fraction &x) //I see now that I didn't need to have two seperate evaluate functions 01/04/14
{
    fraction running_ans, temp_ans;

    for(term *pointinger=myExpression; pointinger!=NULL; pointinger=pointinger->link())
    {

#ifdef d_bug_e
        cout<<"inside evaluate exprsn w term:"<<*pointinger<<endl;
#endif

        temp_ans=(*pointinger).evaluate(x);

#ifdef d_bug_e
        cout<<"power of x : "<<pointinger->x_getPower()<<endl;
        cout<<"temp ans="<<temp_ans<<endl;
#endif

        running_ans=running_ans+temp_ans;
    }

    return running_ans;

}


// 01/04/14 for some reason I when I made these evaluate functions originally I didn't make use of the fact that I already made evaluate
// functions in the term class.  I started to recode these for ln, but then realized it should be easier to use the term class.
// I'm leaving the funcs commented out for now, because I know that they worked in the past, and i don't remember if there was a reason
// that I coded the funcs below the way I did, or if I simply forgot that I coded the term class dudes.
/*
fraction expression::evaluate_N(fraction &x)
{
#ifdef d_bug_e
    cout<<"made it to expression evaluate"<<endl;
#endif

    fraction temp_cof, temp_pow;

    double evalu, cof_x, powa_x, temp_ans=0.;

    double top, bot;

    top=x.num();
    bot=x.denom();

    evalu=top/bot;

#ifdef d_bug_e
    cout<<"evaluation value of "<<top<<"/"<<bot<<" is being stored as "<<evalu<<endl;
#endif



    for(term *pointinger=myExpression; pointinger!=NULL; pointinger=pointinger->link())
    {
#ifdef d_bug_e
        cout<<"made it to while loop in expression evaluate"<<endl;
#endif
        temp_pow=pointinger->x_getPower();
        top=temp_pow.num();
        bot=temp_pow.denom();
        powa= top/bot;

        if(temp_pow<(long long int)0 && evalu==0.)
        {
            cout<<"\t= 0"<<endl;
            int a_fit=1000;
            throw a_fit;
        }

#ifdef d_bug_e
        cout<<"the power is "<<powa<<endl;
#endif
        temp_cof=pointinger->x_getCoeff();
        top=temp_cof.num();
        bot=temp_cof.denom();
        cof=top/bot;
#ifdef d_bug_e
        cout<<"the coeffici is "<<cof<<endl;
#endif
        temp_ans=temp_ans + (cof*pow(evalu, powa));
#ifdef d_bug_e
        cout<<"temporary running answer is: "<<temp_ans<<endl;
#endif
        //pointinger=pointinger->link();

    }
#ifdef d_bug_e
    cout<<"exited while loop in expression evaluate"<<endl;
#endif

    fraction ans(temp_ans);


    return ans;
}


fraction expression::evaluate_D(fraction &x)
{
#ifdef d_bug_e
    cout<<"made it to expression evaluate"<<endl;
#endif

    fraction temp_cof, temp_pow;

    double evalu, cof, powa, temp_ans=0.;

    double top, bot;

    top=x.num();
    bot=x.denom();

    evalu=top/bot;

#ifdef d_bug_e
    cout<<"evaluation value of "<<top<<"/"<<bot<<" is being stored as "<<evalu<<endl;
#endif



    for(term *pointinger=myExpression; pointinger!=NULL; pointinger=pointinger->link())
    {
#ifdef d_bug_e
        cout<<"made it to while loop in expression evaluate"<<endl;
#endif
        temp_pow=pointinger->x_getPower();
        top=temp_pow.num();
        bot=temp_pow.denom();
        powa= top/bot;

        if(temp_pow<(long long int)0 && evalu==0.)
        {
            cout<<"Error:  division by zero"<<endl;
            int a_fit=1000;
            throw a_fit;
        }

#ifdef d_bug_e
        cout<<"the power is "<<powa<<endl;
#endif
        temp_cof=pointinger->x_getCoeff();
        top=temp_cof.num();
        bot=temp_cof.denom();
        cof=top/bot;
#ifdef d_bug_e
        cout<<"the coeffici is "<<cof<<endl;
#endif
        temp_ans=temp_ans + (cof*pow(evalu, powa));
#ifdef d_bug_e
        cout<<"temporary running answer is: "<<temp_ans<<endl;
#endif
        //pointinger=pointinger->link();

    }
#ifdef d_bug_e
    cout<<"exited while loop in expression evaluate"<<endl;
#endif

    fraction ans(temp_ans);

    return ans;
}
*/

expression expression::derivative()
{
    expression ans;

    term *pointinger = myExpression;
    term temp, term_deriv, x_t, ln_t;
    fraction x_f, ln_f, ccf, zz((long long int)0, (long long int)1);
    fraction x1, x2, ln2, c1, c2;

    while(pointinger!=NULL)
    {
        temp=*pointinger;

#ifdef d_bug_ee
        cout<<"CURRENT TERM=";
        temp.print_da_term();
        cout<<endl<<endl;
#endif


        if(temp.x_getPower()==(long long int)0 && temp.ln_getPower()==(long long int)0)         //2/6/14 not sure why I have this stmnt
        {                                                                                       //^doesn't look like it does anything
            if(pointinger->link()==NULL)
                return ans;
            else
            {
                pointinger=pointinger->link();
                temp=*pointinger;
            }

        }

        if(temp.x_getPower()!=(long long int)0 && temp.ln_getPower()!=(long long int)0)         //added 2/7/14 (chain rule)
        {
#ifdef d_bug_ee                                                                                   //^previously was mistakenly inside term class
            cout<<"INSINDE CHAIN RULE DEALIO ln.367"<<endl;
#endif

            x_f=temp.x_getPower();
            ln_f=temp.ln_getPower();
            ccf=temp.getCoeff();

            x_t.setTerm(ccf, x_f, zz);
            ln_t.setTerm(ccf, zz, ln_f);

            x_t=x_t.derivative();
            ln_t=ln_t.derivative();

#ifdef d_bug_ee
            cout<<"x_t="<<x_t<<endl;
            cout<<"ln_t="<<ln_t<<endl;
#endif
            x1=x_t.x_getPower();
            x2=ln_t.x_getPower();

            //ln2=ln_t.x_getPower();                //4/16 mistake here? <<---yes, that's a mistake
            ln2=ln_t.ln_getPower();                 //4/16 fix of mistake?  (4/17 fixed chain rule issue, but still have issues 4/17 i.e. ibp)

#ifdef d_bug_ee
            cout<<"#* ln2= ln386== "<<ln2<<endl;
#endif

            c1=x_t.getCoeff();
            c2=ln_t.getCoeff();     //Error was here!!! had x_t twice... hahaha; i think I thought that wouldn't affect it.  4/17

            x2= x2+x_f;

            x_t.setTerm(c1, x1, ln_f);
            ln_t.setTerm(c2, x2, ln2);

            ans<<x_t;
            ans<<ln_t;

        }
        else
        {
#ifdef d_bug_ee
            cout<<"INSIDE ELSE YALLLLLLLLLLLLLLLLLLLLL BEACHES"<<endl;
            ans.print_expr();
            cout<<endl;
#endif

            term_deriv=temp.derivative();

#ifdef d_bug_ee
            cout<<">>>>>";
            term_deriv.print_da_term();
            cout<<endl;
#endif

            ans<<term_deriv;

        }
#ifdef d_bug_ee
        cout<<"ans:"<<endl;
        ans.print_expr();
        cout<<endl;
#endif

            pointinger=pointinger->link();

#ifdef d_bug_e
        cout<<endl<<"term deriv was just: ";
        term_deriv.print_da_term();
        cout<<endl;
#endif
    }
#ifdef d_bug_ee
    cout<<"returning expression: ";
    ans.print_expr();
    cout<<"   *****   "<<endl;
#endif

    return ans;
}

expression expression::integral()
{
    expression ans, ibp_anz, extr;

    term *pointinger = myExpression;
    term temp, term_ingral;

    term t;
    fraction zero((long long int)0, (long long int)1), one((long long int)1, (long long int)1);
    t.setTerm(zero, zero, zero);            //added 4/15/14
    ans<<t;
    extr<<t;                                //this dude and the dude below added 4/17/14
    ibp_anz<<t;

#ifdef d_bug_ee
    cout<<"test ans "<<ans<<endl;
#endif

    while(pointinger!=NULL)
    {
        temp=*pointinger;

        if(temp.ln_getPower()!=(long long int)0)
        {
            ibp_anz=integration_by_parts(temp);
#ifdef d_bug_ee
            cout<<"ibp ans == "<<ibp_anz<<endl;
            cout<<"ans exp == "<<ans<<endl;
            cout<<"made it out of IBP"<<endl;
#endif
            extr=ans+ibp_anz;
#ifdef d_bug_ee
            cout<<"extr created"<<endl;
#endif
            ans=extr;
#ifdef d_bug_ee
            cout<<"made it past line 227"<<endl;
#endif
        }
        else
        {
#ifdef d_bug_ee
            cout<<"inside an elseeeeeeeeeeeeee line 439"<<endl;
#endif
            term_ingral=temp.integral();
            ans<<term_ingral;
        }
#ifdef d_bug_ee
        cout<<"inside $$$ ln 433"<<endl;
#endif
        pointinger=pointinger->link();

    }

#ifdef d_bug_ee
cout<<"inside $$$ ln 437"<<endl;
#endif

    return ans;
}

expression expression::integration_by_parts(term t_IBP)
{
    expression ans, u_dv, v_du, u_v;
#ifdef d_bug_ee
    cout<<"inside IBP ln 445"<<endl;
#endif

    term temp, u, v, du, dv, udv, vdu, uv;
    fraction x_f, ln_f, ccf, neg_one((long long int)-1, (long long int)1);
    fraction zzz((long long int)0, (long long int)1), one((long long int)1, (long long int)1), two((long long int)2, (long long int)1);


    term t;                                     //this and the following five lines added 4/17/14
    t.setTerm(zzz, zzz, zzz);                   // hard to tell if prog runs worse with these lines in or out
    ans<<t;                                     //4/17/14 got prog working, but I don't think these lines do anything,
    u_dv<<t;                                    //but I'm not certain.... really should make the code more consistent && efficient
    v_du<<t;
    u_v<<t;


    if(t_IBP.x_getPower()==neg_one && t_IBP.ln_getPower()==one)
    {
#ifdef d_bug_ee
        cout<<"inside IBP ln 454"<<endl;
#endif

        ccf=t_IBP.getCoeff();
        ccf=ccf/(long long int)2;
        temp.setTerm(ccf, zzz, two);

        ans<<temp;

        return ans;
    }
    else
    {
#ifdef d_bug_ee
        cout<<"inside IBP ln 467"<<endl;
#endif
        x_f=t_IBP.x_getPower();
        ln_f=t_IBP.ln_getPower();
        ccf=t_IBP.getCoeff();

        u.setTerm(ccf, zzz, ln_f);
        du=u.derivative();

        dv.setTerm(one, x_f, zzz);
        //cout<<"originally, dv   =  "<<dv<<endl;
        v=dv.integral();
#ifdef d_bug_ee
        cout<<"dv="<<dv<<"   and v="<<v<<endl;
#endif
        udv= u*dv;
#ifdef d_bug_ee
        cout<<endl<<"v= "<<v<<" and du= "<<du<<endl<<endl;
#endif
        vdu= v*du;

        uv= u*v;

#ifdef d_bug_ee
        cout<<"u*dv= "<<udv<<endl;
        cout<<"v*du= "<<vdu<<endl;
#endif
        u_dv<<udv;

        u_v<<uv;

#ifdef d_bug_ee
        cout<<"uv expression dude (ln. 519) = "<<u_v<<endl;
#endif

        if(vdu.ln_getPower()!=(long long int)0)
        {

#ifdef d_bug_ee
            cout<<"inside IBP ln 486"<<endl;
#endif

            ans= u_v - integration_by_parts(vdu);
        }
        else
        {
#ifdef d_bug_ee
            cout<<"inside IBP ln 492"<<endl;
#endif
            vdu=vdu.integral();
#ifdef d_bug_ee
            cout<<"###    vdu dude = "<<vdu<<endl;
#endif
            v_du<<vdu;
            ans= u_v - v_du;
        }
#ifdef d_bug_ee
        cout<<"inside IBP ln 499"<<endl;

        cout<<"ans now = "<<ans<<endl;
#endif

        return ans;
    }

}


void expression::copy(const expression &other)
{
    term *otherHead = other.myExpression, *end;
    if(otherHead)
    {
        term * newCopiedTerm = new term(*otherHead);
        myExpression = end = newCopiedTerm;
        /*
          So, the above is the same as
          expression = newCopiedTerm;
          end = newCopiedTerm;
        */
        otherHead = otherHead->link();
        while( otherHead)
        {
            newCopiedTerm = new term(*otherHead);
            end->link() = newCopiedTerm;
            end = end->link();
            otherHead = otherHead->link();
        }
    }
}

void expression::zero()
{
    term *bye;
    while(myExpression)
    {
        bye = myExpression;
        myExpression = myExpression->link();
        delete bye;
    }
}

ostream& operator<<(ostream &out, expression &p)
{
   // cout<<"inside << opp line 400 expression"<<endl;      //got working 1/15/14--needed *head vs. head on line 4 lines down
    term *head = p.myExpression;
    while(head)
    {
        out<<*head;
        head = head->link();
    }
    return out;
}


istream& operator>>(istream &in, expression &p)
{
    term newTerm;
    while(in>>newTerm)
        p<<newTerm;
    return in;
}

expression operator+(const expression &x, const expression &y)
{
#ifdef d_bug_e
    cout<<"made it to expression +"<<endl;
#endif
    expression tempo=x;

#ifdef d_bug_e
    cout<<"defined the first term in expression +"<<endl;
#endif

    //for loop stuff was here before;

    //cout<<"x="<<x<<endl;
#ifdef d_bug_ee
    cout<<"tempo="<<tempo<<endl;
#endif

    for(term* pointinger=y.return_my_exp(); pointinger!=NULL; pointinger=pointinger->link())  //removed**************************************->link() from pointinger :-o
    {
#ifdef d_bug_e
        cout<<"inside while loop in expression +"<<endl;
#endif
#ifdef d_bug_ee
        cout<<"temp_1 exprssn = "<<tempo<<endl;
#endif
        tempo<<*pointinger;
#ifdef d_bug_ee
        cout<<"temp_2 exprssn = "<<tempo<<endl;
#endif

    }
#ifdef d_bug_e
    cout<<"made it all the way through expression +!! :-)"<<endl;
#endif
#ifdef d_bug_ee
    cout<<"about to exit/return operator+ in expression"<<endl;
#endif
    return tempo;

    //^iterates through adding coeffs together of like powers
}

expression operator-(const expression &x, const expression &y)
{
#ifdef d_bug_e
    cout<<"made it to expression -"<<endl;
#endif

    expression tempo=x;

#ifdef d_bug_e
     cout<<"defined the first term in expression -"<<endl;
#endif

    //term* pointinger=y.myExpression;

#ifdef d_bug_e
    cout<<"created a header node in expression -"<<endl;
#endif

    term neg_term;

    for(term* pointinger=y.return_my_exp(); pointinger!=NULL; pointinger=pointinger->link())
    {
#ifdef d_bug_e
        cout<<"inside while loop in expression -"<<endl;
#endif

        neg_term= -(*pointinger);

#ifdef d_bug_e
        cout<<"negatized the term"<<endl;
#endif

        tempo<<neg_term;

#ifdef d_bug_e
        cout<<"fed the neg term to an expression"<<endl;
#endif

       // pointinger=pointinger->link();
    }
#ifdef d_bug_e
    cout<<"made it all the way through expression -!! :-)"<<endl;
#endif
    return tempo;

    //^iterates though subtracting coeffs together of like powers
}

expression operator*(const expression &x, const expression &y)
{

#ifdef d_bug_e
    cout<<"$$$$$$$$  inside expression *"<<endl;
#endif

    term *pointinger_x=x.myExpression;
    term *pointinger_y=y.myExpression;

    expression tempo;
    term a, b, c;

    if(pointinger_y==NULL)
        return x;


    for(pointinger_x; pointinger_x!=NULL; pointinger_x=pointinger_x->link())
        for(pointinger_y=y.myExpression; pointinger_y!=NULL; pointinger_y=pointinger_y->link())
        {

#ifdef d_bug_e
            cout<<"      $$$$$$$$$$$$$ for loop   "<<endl;
#endif

            a=*pointinger_x;


#ifdef d_bug_e
            cout<<"*^%*^%  pointinger x = "<<a<<endl;
#endif

            b=*pointinger_y;


#ifdef d_bug_e
            cout<<"*^%*^%  pointinger y = "<<b<<endl;
#endif

            c=a*b;
            tempo<<c;
        }

    return tempo;

    //^iterates through multiplying everything together
}

//for divide, changes expression so that it has a denominator, then just flips it over and multiplies... is done in super class ;-)

term* expression::return_my_exp() const
{
    return myExpression;
}

string expression::print_expr() const
{
    string outString;
    term* headinger;
    headinger= new term;
    headinger=myExpression;

    int counter=1;

    if(headinger!=NULL)
        if(headinger->getCoeff()<(long long int)0)
        {
            outString="-";
            cout<<"-";
        }

    while(headinger!=NULL)
    {
        //cout<<"in while loop for headinger != NULL ***"<<counter<<" time"<<endl;
        outString+=headinger->print_da_term();

        if(headinger->link()!=NULL && headinger->link()->getCoeff()<(long long int)0)
        {
            outString+="-";
            cout<<" - ";
        }
        else if(headinger->link()!=NULL && headinger->link()->getCoeff()!=(long long int)0)
        {
            outString+="+";
            cout<<" + ";
        }

        if((headinger->link())== NULL)
        {
#ifdef d_bug_e
            cout<<"ending expression print func?"<<endl;
#endif
            return outString;
        }

        if(headinger->link()!=NULL)
            headinger=headinger->link();

         counter++;
    }

    cout<<"error but made it out of print expression func anyways--fix"<<endl; //hasn't couted yet
    cout<<"headinger was:";
    headinger->print_da_term();
    cout<<endl;
}
