#include "term.h"

//#define d_bug_t
//#define d_bug_tt

term::term()
{
    next = NULL;
}

term::term(const term& x)
{
    copy(x);
}


term::term(const fraction &c, const fraction &p_x, const fraction &ln_p)
{
    coeff =  c;
    power_x = p_x;
    ln_power = ln_p;

    if(!valid())
        throw INVALID;
}

term::~term()
{
    next = NULL;
}

term& term::operator=(const term&other)
{
    if(this != &other)
        copy(other);
    return *this;
}

fraction term::evaluate(fraction &x)
{
    int a_temper_tantrum=2;


    if(power_x<(long long int)0 && x==(long long int)0)           //I don't think the program ever evaluates true at this if stmnt
    {
        cout<<"cannot divide by zero!"<<endl;
        throw a_temper_tantrum;
    }

    fraction answer, bla, bly;


    if(ln_power==(long long int)0)
    {
        bla=x^power_x;
        answer = coeff*(bla);

        //cout<<"x="<<x<<"     x^power_x="<<bla<<endl<<"power_x="<<power_x<<endl;
    }
    else
    {
        fraction ln_x = ln_f(x);

        bla=x^power_x;
        bly=ln_x^ln_power;

        answer = coeff*(bla)*(bly);
    }

#ifdef d_bug_t
    cout<<"inside term eval="<<answer<<endl;
    cout<<"power_x="<<power_x<<endl;
    cout<<"x="<<x<<endl;
#endif

    return answer;
}

term term::derivative()
{
#ifdef d_bug_t
    cout<<"current term's power is:   "<<power_x<<"  ********************************"<<endl;
#endif
    term temprairie;
    fraction pow_x=power_x;
    fraction pow_ln=ln_power;
    fraction coef=coeff;
    fraction blah((long long int)1, (long long int)1);      //added second term 4/17/14; however, I don't think that it really matters
    fraction pow_xk=power_x-blah;
    fraction pow_lnk=ln_power-blah;

#ifdef d_bug_t
    cout<<"current term's power -1 is:   "<<pow_xk<<"  ********************************"<<endl;
#endif

    if(power_x!=(long long int)0 && ln_power == (long long int)0)
    {
    temprairie.coeff = pow_x*coef;
    temprairie.power_x = pow_xk;
    }
    else if(power_x==(long long int)0 && ln_power != (long long int)0)
    {
        temprairie.coeff = pow_ln*coef;
        temprairie.ln_power = pow_lnk;
        temprairie.power_x = pow_xk;
    }
    /*else if(ln_power!=(long long int)0)
    {
        temprairie.coeff = pow_x*coef;
        temprairie.power_x = pow_xk;
        temprairie.ln_power = ln_power;

        term ln_temp;

        ln_temp.ln_power = pow_lnk;

        ln_temp.coeff = pow_ln*coef;
        ln_temp.power_x = power_x;

        return ln_temp + temprairie;
    }*/
    else
        temprairie.coeff=(long long int)0;



#ifdef d_bug_t
    cout<<endl<<"in term class, deriv function, term derivative was just found to be: ";
    temprairie.print_da_term();
    cout<<endl;
#endif

    return temprairie;
}

term term::integral()
{
#ifdef d_bug_tt
    cout<<"         INSIDE TERM integral() and power_x ="<<power_x<<endl<<endl;
#endif
    term temp;

    fraction pow_x=power_x;
    fraction integrated_coeff;
    fraction coef=coeff;
    fraction neg_one((long long int)-1, (long long int)1), zzz((long long int)0, (long long int)1);
    fraction one((long long int)1, (long long int)1);

    if(pow_x==neg_one)
    {
        temp.setTerm(coef, zzz, one);
        return temp;
    }
    else
    {
#ifdef d_bug_tt
        cout<<"<<sigh>> ?   "<<coeff<<"X^"<<pow_x<<"   ?   "<<endl;  //running into lots of errors here, don't know why !?!?! 4/16/14
#endif                                                               //4/17/14 issues fixed.. there was one in IBP, one chain rule, and an error in term class

        temp.setTerm(zzz, zzz, zzz);                //added this 4/17/15; however, I am inclined to think that it doesn't do anything
#ifdef d_bug_tt
        cout<<"BANG   ";
#endif

        //pow_x=pow_x + (long long int)1;
        pow_x=pow_x + one;          //dashed out the dude above 4/17/14... maybe this will work when that didn't?
                                    //HOLY SHIT ^^^ that fixed it!!! but WHYYYYYYYYYYYYYY?

        integrated_coeff = pow_x;

#ifdef d_bug_tt
        cout<<"BOOM! "<<endl;
        cout<<"coef="<<coef<<"  /and integrated_coeff="<<integrated_coeff<<endl;
#endif

        integrated_coeff = coef/integrated_coeff;

#ifdef d_bug_tt
        cout<<"<<urggs>> ?  "<<coeff<<"X^"<<pow_x<<"   ?   "<<endl; //added 4/17, tring to fix bug

        cout<<"<double urggs> ? "<<integrated_coeff<<"X^"<<pow_x<<" ! "<<endl; //added 4/17.5
#endif

        temp.setTerm(integrated_coeff, pow_x, zzz);

#ifdef d_bug_tt
        cout<<"oy vay   ? "<<integrated_coeff<<"X^"<<pow_x<<"   ?   "<<endl;

        cout<<"want to return the following from TERM integ... : "<<temp<<endl<<endl;

        cout<<"note: term is piece by piece : "<<temp.getCoeff()<<"X^"<<temp.x_getPower()<<"ln(x)^"<<temp.ln_getPower()<<endl;
#endif

        return temp;
    }

}

void term::setTerm(fraction &c, fraction &p_x, fraction &p_ln)
{
#ifdef d_bug_t
    cout<<"set term called"<<endl;
#endif

  //  cout<<"!@#$%^&*()___inside setTerm and the term will be :::  "<<c<<"X^"<<p_x<<"LN(x)^"<<p_ln<<endl;

    coeff = c;
    power_x = p_x;
    ln_power = p_ln;

   // cout<<"!@#$%^&*()___inside setTerm and the term is :::  "<<coeff<<"X^"<<power_x<<"LN(x)^"<<ln_power<<endl;

#ifdef d_bug_t
    cout<<"current x term: "<<coeff<<"x^"<<power_x<<endl;
    cout<<"current ln term: "<<"ln(x)^"<<ln_power<<endl;
#endif
}

void term::setLink(term *nex_lnk)
{
    next = nex_lnk;
}

fraction& term::getCoeff()
{
    return coeff;
}


fraction& term::x_getPower()
{
    return power_x;
}


fraction& term::ln_getPower()
{
    return ln_power;
}

term*& term::link()
{
    return next;
}

void term::copy(const term& x)
{
    coeff = x.coeff;
    power_x = x.power_x;
    ln_power= x.ln_power;

    next = NULL;                    //   1/15/14 : why does next = NULL ? vs. next = x.next ?? (I forget)
}

bool term::valid()
{
    return coeff.denom() != 0 && power_x.denom() != 0 && ln_power.denom() != 0;
}


term operator+(term& x, term& y)
{
    if(x.power_x != y.power_x || x.ln_power != y.ln_power)
        throw CANNOT_HAPPEN;
    term ans(x.coeff + y.coeff, x.power_x, x.ln_power);
    return ans;
}


term operator-(term& x, term& y)
{
    if(x.power_x != y.power_x || x.ln_power != y.ln_power)
        throw CANNOT_HAPPEN;
    term ans(x.coeff - y.coeff, x.power_x, x.ln_power);
    return ans;
}


term operator*(term& x, term& y)
{
#ifdef d_bug_t
    cout<<"********inside term * and xln="<<x.ln_power<<" and yln="<<y.ln_power<<endl;
#endif

    fraction x__pow=x.power_x + y.power_x;
    fraction ln_pow=x.ln_power + y.ln_power;

#ifdef d_bug_t
    cout<<"ln pow is when calced sep=  "<<ln_pow<<endl;
#endif

    term ans(x.coeff * y.coeff, x__pow, ln_pow);  //x.power_x + y.power_x, x.ln_power + y.ln_power  //1/15/14 changed to how is cur
                                                  //this fixed the bug that I have been trying to find for the last week or so!!!
#ifdef d_bug_t
        cout<<"full term is:  ";
        ans.print_da_term();
        cout<<endl;
#endif

    return ans;
}

ostream& operator<<(ostream& out, term &other)
{
 //   cout<<"in weird operator func term line 237 (now 268)"<<endl;

    if(other.coeff < (long long int)0)
        out<<"- ";
    else
        cout<<"+ ";
    out<<aabs(other.coeff);  //  out<<aabs(other.coeff_x*other.ln_coeff)  //I'm confused here why I put if statements here if
    if(other.power_x != (long long int)0)                                   //the func below (>>) does in>> irregardless...
      out<<"X^"<<other.power_x;                                             //^01/03/14  -- will need to modify one way or another

    if(other.ln_power != (long long int)0)
      out<<"ln(X)^"<<other.ln_power;
    return out;
}


istream& operator>>(istream& in, term &other)               //***Need to modify once I understand where this func gets called 01/03/14
{
    cout<<"in weird operator func term line 255"<<endl;
    char junk;
    in>>other.coeff>>junk>>junk>>other.power_x;
    return in;
}


term operator-(term& x)
{
    term j=x;
    fraction c, p_x, p_ln;

    c=j.getCoeff();
    p_x=j.x_getPower();
    p_ln=j.ln_getPower();

    c.make_numer_neg();

    j.setTerm(c, p_x, p_ln);

    return j;


}

string term::print_da_term()
{
    string outString = "";
    string tempOutString;
    stringstream ss;
    fraction test_xp=x_getPower();
    fraction test_lnp=ln_getPower();
    long long int txp=test_xp.num();
    long long int tlnp=test_lnp.num();

#ifdef d_bug_t
    cout<<"inside print da term"<<endl;
    cout<<"the power term is "<<txp<<endl;
    cout<<"the ln term is "<<tlnp<<endl<<endl;
    cout<<"the power term is "<<power_x<<endl;
    cout<<"the ln term is "<<ln_power<<endl<<endl;
#endif


    long long int czech_c=coeff.denom(), czech_p=power_x.denom(), czech_cn=coeff.num(), czech_pn=power_x.num();
    long long int LNczech_p=ln_power.denom(), LNczech_pn=ln_power.num();

    if(czech_cn==(long long int)0)
        return outString;

    if(czech_c==(long long int)1 && czech_cn==(long long int)1 && czech_pn!=(long long int)0)   //I forget why is this {blank}? 12/31/13
        {/*blank*/}
    else if(czech_c==(long long int)1)
    {
        ss<<abs(czech_cn);
        ss>>outString;
        cout<<abs(czech_cn);
    }
    else
    {        
        ss<<aabs(coeff);
        ss>>outString;
        cout<<aabs(coeff);
        //cout<<"   vs.  "<<this->getCoeff();
    }

    if(czech_pn==(long long int)0 && LNczech_pn==(long long int)0)
        return outString;

    if(czech_pn==(long long int)0)
        {/*blank*/}
    else if(czech_p==(long long int)1 && czech_pn==(long long int)1)
    {
        outString+="x";
        cout<<"x";
    }
    else if(czech_p==(long long int)1)
    {
        ss.clear();
        ss<<power_x.num();
        ss>>tempOutString;
        outString+="x^"+tempOutString;
        cout<<"x^"<<power_x.num();
    }
    else
    {
        ss.clear();
        ss<<power_x;
        ss>>tempOutString;
        outString+="x^"+tempOutString;
        cout<<"x^"<<power_x;
    }

    if(LNczech_pn==(long long int)0)
        {/*blank*/}
    else if(LNczech_p==(long long int)1 && LNczech_pn==(long long int)1)
    {
        outString+="Ln(x)";
        cout<<"Ln(x)";
        //cout<<"ln power was: "<<ln_power<<endl<<endl;
    }
    else if(LNczech_p==(long long int)1)
    {
        ss.clear();
        outString+="Ln(x)";
        ss<<ln_power.num();
        ss>>tempOutString;
        outString+=tempOutString;
        cout<<"Ln(x)^"<<ln_power.num();
    }
    else
    {
        ss.clear();
        outString+="Ln(x)^";
        ss<<ln_power;
        ss>>tempOutString;
        outString+=tempOutString;
        cout<<"Ln(x)^"<<ln_power;
    }

    return outString;
}

fraction term::ln_f(fraction x)
{
    double float_ver, ans;

    //cout<<"please enter a number to take the natural logarithm of"<<endl;

    //cin>>input;

    float_ver= (double)x.num()/(double)x.denom();

    if(float_ver<1.5)
        ans = ln_func(float_ver);
    else
        ans = ln_funk(float_ver);

    //ans=fabs(ans); doesn't seem to fix it 4/23/14

    fraction lnx(ans);

    return lnx;
}



double term::ln_func(double numbero)
{
    double comparo=numbero;

    int count=1;

    numbero=numbero-1;

    double numee = numbero;

    while(fabs(comparo-numbero)>.000000001) //
    {
        count++;
        comparo=numbero;

        numbero= numbero + ((pow(-1,count+1))*((pow(numee, count)/(double)count)));
        //cout<<numbero<<endl;
    }


return numbero;

}


double term::ln_funk(double numbero)
{

    cout<<"inside ln_funk"<<endl;             //****************************************************

    double comparo=numbero+.5;

    int count=1;

    double numee=1 - (double)1/numbero;

    numee = double(1)/numee;

    cout<<"numee="<<numee<<endl;

    //numbero=numbero-1;

    numbero = (double)1/numee;

    while(fabs(comparo-numbero)>.000000001) //
    {
        count++;
        comparo=numbero;

        numbero= numbero + double(1)/(count*pow(numee, count));
        cout<<numbero<<endl;

    }


return numbero;

}
