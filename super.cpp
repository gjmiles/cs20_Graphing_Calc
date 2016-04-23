#include "super.h"
#include "term.h"

//#define d_bug_s

using namespace std;

super::super()
{
#ifdef d_bug_s
    cout<<"default constructor called"<<endl;
#endif

    fraction zero((long long int)0, (long long int)1), one((long long int)1, (long long int)1);
#ifdef d_bug_s
    cout<<"fractions set in super default constructor"<<endl;
#endif

    term t, b;
    expression tt, bb;

    t.setTerm(zero, zero, zero);            //added third parameter 1/14/14
    b.setTerm(one, zero, zero);             //added third parameter 1/14/14

#ifdef d_bug_s
    cout<<"made it here in super default constructr"<<endl;
#endif

    tt<<t;
    bb<<b;

#ifdef d_bug_s
    cout<<"made it there in super default constructr"<<endl;
#endif

    numerator=tt;
    denominator=bb;

}

super::super(expression numer)
{
    fraction zero(0, 1), one(1, 1);
    term b;
    expression bb;

    b.setTerm(one, zero, zero);               //added third parameter 1/14/14
    bb<<b;

    numerator=numer;
    denominator=bb;
}

super::~super()
{
    //numerator.zero();
    //denominator.zero();
    numerator.~expression();
    denominator.~expression();

}

super::super(const super &other)
{
#ifdef d_bug_s
    cout<<"entered copy constructor"<<endl;
#endif

    numerator=other.numerator;
    denominator=other.denominator;

}

super& super::operator=(const super &other)
{
#ifdef d_bug_s
    cout<<"entered super assignments opperator"<<endl;
#endif

if(this != &other)                  //added this if stmnt 1/15/14
{
    numerator=other.numerator;
    denominator=other.denominator;
}

return *this;
}

super operator*(const super &x, const super &y)
{
    expression top, bot;
    super tempo;

    top=(x.numerator)*(y.numerator);
    bot=(x.denominator)*(y.denominator);
    tempo.numerator=top;
    tempo.denominator=bot;

    return tempo;
}

super operator+(const super &x, const super &y)
{
#ifdef d_bug_s                                                   //***********************
    cout<<"made it to super +"<<endl;
#endif

    expression top_x, top_y, topper, bot;
    super tempo;

    expression a, b, c, d;

    a=x.numerator;
    b=x.denominator;
    c=y.numerator;
    d=y.denominator;

#ifdef d_bug_s
    cout<<endl<<"x_num="<<a<<"   and x_dnm="<<b<<endl;
    cout<<"y_num="<<c<<"   and y_dnm="<<d<<endl<<endl;
#endif

    top_x=(x.numerator)*(y.denominator);                    //*****I think the buf is happening somewhere around here 1/15/14
    top_y=(y.numerator)*(x.denominator);

#ifdef d_bug_s
    cout<<"defined numers in super +"<<endl;

    cout<<"inside super + and exp_x= "<<top_x<<" and exp_y= "<<top_y<<endl;
#endif

    topper=top_x+top_y;

#ifdef d_bug_s
    cout<<"added numers in super +"<<endl;
#endif

    bot=(x.denominator)*(y.denominator);

#ifdef d_bug_s
    cout<<"multiplied denoms in super +"<<endl;
#endif

    tempo.numerator=topper;
    tempo.denominator=bot;

#ifdef d_bug_s
    cout<<"made it through super +!!"<<endl;
#endif

    return tempo;
}

super operator-(const super &x, const super &y)
{
#ifdef d_bug_s
    cout<<"made it to super -"<<endl;
#endif

    expression top_x, top_y, topper, bot;
    super tempo;

    top_x=(x.numerator)*(y.denominator);
    top_y=(y.numerator)*(x.denominator);

#ifdef d_bug_s
    cout<<"defined numers in super -"<<endl;
#endif

    topper= top_x-top_y;

#ifdef d_bug_s
    cout<<"minused numers in super -"<<endl;
#endif

    bot=(x.denominator)*(y.denominator);

#ifdef d_bug_s
    cout<<"multiplied denoms in super -"<<endl;
#endif

    tempo.numerator=topper;
    tempo.denominator=bot;

#ifdef d_bug_s
    cout<<"made it through super -!!"<<endl;
#endif

    return tempo;
}

super operator/(const super &x, const super &y)
{
    expression top, bot;
    super tempo;

    top=(x.numerator)*(y.denominator);
    bot=(x.denominator)*(y.numerator);
    tempo.numerator=top;
    tempo.denominator=bot;

    return tempo;
}


//this is super-duper prone to running into errors... going to need to add a bunch of error catching stuff!!
// 1/11/2014 note: def need to fix this up to work w/ LN now
super operator%(const super &x, const super &y)
{
    expression x_n, x_d, y_n, y_d, zz_n, zz_d;

    super testie;

    fraction one(1, 1), zero(0, 1);
    term b;


    b.setTerm(zero, zero, zero);                //added third parameter 1/14/14
    zz_n<<b;

#ifdef d_bug_s
    cout<<"made it to f=g(h) operator! in class super!"<<endl;
#endif

    x_n=x.numerator;
    x_d=x.denominator;

    y_n=y.numerator;
    y_d=y.denominator;

#ifdef d_bug_s
    cout<<"defined numerators and denominators in op f=g(h) in class super"<<endl;
#endif

    expression temp, the_cof, blanker;
    blanker<<b;

    term co_effish;

    super owally, temper;

    bool go_neg=false;
    bool was_neg=false;

    fraction c, p, w((long long int)0);

    int p_numer;

#ifdef d_bug_s
    cout<<"about to enter for loop in f=g(h) operator! in class super"<<endl;
#endif

    for(term* xxxn=x.numerator.return_my_exp(); xxxn!=NULL; xxxn=xxxn->link())
        //for(term* yyyn=y.numerator.return_my_exp(); yyyn!=NULL; yyyn=yyyn->link())
        {

            the_cof=blanker;
            temp=y_n;
#ifdef d_bug_s
            cout<<"in 1 of 2 for loop in f=g(h) thing"<<endl;
#endif
            go_neg=false;

            p=xxxn->x_getPower();

            if(p.denom()!=(long long int)1)
            {
                int a_jelly_donut=1;
                cout<<"illegal arithmetic per this test! f=g(h) may only handle polynomial values for g"<<endl;
                throw a_jelly_donut;
            }
            p_numer=p.num();
            c=xxxn->getCoeff();
            co_effish.setTerm(c, w, w);  //added third parameter 1/14/14
            the_cof<<co_effish;
            //cout<<"the cof is  ";
            //the_cof.print_expr();
            //cout<<"******************"<<endl;

#ifdef d_bug_s
            cout<<"terms established ok in for loop"<<endl;
#endif



            if(p_numer<0)
                go_neg=true;

            while(p_numer<-1)
            {
#ifdef d_bug_s
                cout<<"in while loop for ^power="<<p_numer<<">1"<<endl;
#endif

                temp=temp*y_n;
                p_numer++;
            }

            if(go_neg)
            {

                fraction one(1, 1), zero(0, 1);
                term b;
                expression bb;

                b.setTerm(one, zero, zero); //added third parameter 1/14/14
                bb<<b;

                temper.numerator=the_cof;
                temper.denominator=temp;
            }

            //was the } for for loop here

            while(p_numer>1)
            {
#ifdef d_bug_s
                cout<<"in while loop for ^power="<<p_numer<<">1"<<endl;
#endif

                temp=temp*y_n;
                p_numer--;
            }

            if(p_numer==(-1))
            {
#ifdef d_bug_s
                cout<<"^power==1"<<endl;
#endif
                testie=testie+temper;

                was_neg=true;

                //cout<<"zzn=";
                //zz_n.print_expr();
                //zz_n= zz_n+temp;
                //cout<<"    ";
                //zz_n.print_expr();
                //cout<<endl;
#ifdef d_bug_s
                cout<<"defined zz_n=temp"<<endl;
#endif
            }

            if(p_numer==1)
            {
#ifdef d_bug_s
                cout<<"^power==1"<<endl;
#endif
               // cout<<"printing temp.expressions"<<endl;
               // temp.print_expr();
                temp=temp*the_cof;
               // cout<<"*******************"<<endl;
               // temp.print_expr();
               // cout<<"*******************"<<endl;
#ifdef d_bug_s
                cout<<"defined temp=temp*the_cof"<<endl;
#endif
               // cout<<"zzn=";
               // zz_n.print_expr();
                zz_n= zz_n+temp;
               // cout<<"    ";
               // zz_n.print_expr();
               // cout<<endl;
#ifdef d_bug_s
                cout<<"defined zz_n=temp"<<endl;
#endif
            }
            else if(p_numer==0)
            {
#ifdef d_bug_s
                cout<<"^power==0"<<endl;
#endif
                zz_n<<co_effish;
            }

    } //added bracket

#ifdef d_bug_s
    cout<<"made it out of 1 of 2 for loop"<<endl;
#endif

    for(term* xxxd=x.denominator.return_my_exp(); xxxd!=NULL; xxxd=xxxd->link())
        //for(term* yyyd=y.denominator.return_my_exp(); yyyd!=NULL; yyyd=yyyd->link())
        {
            temp=y_d;
#ifdef d_bug_s
            cout<<"begining value of y\'s denom is: ";
            temp.print_expr();

            cout<<endl<<"in 2 of 2 for loop in f=g(h) thing"<<endl;
#endif

            p=xxxd->x_getPower();
            p_numer=p.num();
            c=xxxd->getCoeff();
            co_effish.setTerm(c, w, w);        //added third parameter 1/14/14
            the_cof<<co_effish;

            while(p_numer>1)
            {
                temp=temp*y_d;
                p_numer--;
            }

            if(p_numer==1)
            {
                temp=temp*the_cof;
#ifdef d_bug_s
                cout<<"value of denom is now: ";
                temp.print_expr();
                cout<<"*****************************************"<<endl;
#endif
                zz_d=temp;
            }
            else if(p_numer==0)
            {
                zz_d<<co_effish;
            }

        }

    owally.numerator=zz_n;
    owally.denominator=zz_d;

    /*if(go_neg)
    {
      //temper.numerator=owally.denominator;
      return temper;
    }*/

    if(was_neg)
        return owally+testie;

    return owally;

}

fraction super::evaluate(fraction &x)
{
    fraction topper, botter;
#ifdef d_bug_s
    cout<<"made it to super evaluate"<<endl;

    cout<<"fraction was captured as "<<x.num()<<"/"<<x.denom()<<endl;
#endif

    botter=denominator.evaluate_ND(x);
    topper=numerator.evaluate_ND(x);


#ifdef d_bug_s
    cout<<"about to return in super evaluate"<<endl;
#endif

    expression lhopital_N=numerator, lhopital_D=denominator;



    while(topper==(long long int)0 && botter==(long long int)0)
    {
     lhopital_N=lhopital_N.derivative();
     lhopital_D=lhopital_D.derivative();

     botter=lhopital_D.evaluate_ND(x);
     topper=lhopital_N.evaluate_ND(x);

    }

    if(botter==(long long int)0)
    {
        cout<<"illegal division by zero"<<endl;
        //exit(1);
        int donuts=0;
        throw donuts;
    }

        return topper/botter;

}


void super::derivative(int x)
{
    super tempo;
    term *pointinger = denominator.return_my_exp();

    for(int i=0; i<x; i++)
    {
        if(pointinger->x_getPower()==(long long int)0 && pointinger->link()==NULL)
        {
#ifdef d_bug_s
            cout<<"in super derivative (reg)"<<endl;
#endif
            expression deriv=numerator.derivative();
            numerator=deriv;
        }
        else
        {
#ifdef d_bug_s
            cout<<"in super derivative (quotient rule)"<<endl;
#endif
            expression f=numerator;
            expression deriv_f=numerator.derivative();
            expression g=denominator;
            expression deriv_g=denominator.derivative();

            denominator=g*g;
            numerator=(g*deriv_f)-(f*deriv_g);
        }
    }

}

void super::integral_def(int a, int b)
{

}

void super::integral_indef(int x)
{
    //if() need to write statement to make sure denominator == 1

    numerator=numerator.integral();
}

ostream& operator<<(ostream &out, super &k)     //01/04/14 I'm not entirely sure when this is used, and if it is, how to modify it... yet
{

    cout<<"!@#$%^&*!@#$%^      inside super << oprtr"<<endl;

    term *head_n = k.numerator.return_my_exp();
    while(head_n)
    {
        out<<head_n;
        head_n = head_n->link();
    }
    term *head_d = k.denominator.return_my_exp();
    if(head_d->getCoeff()==(long long int)1 && head_d->x_getPower()==(long long int)0 && head_d->ln_getPower()==(long long int)0 && head_d->link()==NULL)
        return out;

    out<<"/";

    while(head_d)
    {
        out<<head_d;
        head_d = head_d->link();
    }
    return out;
}

 void super::set_super(expression n, expression d)
 {
     numerator=n;
     denominator=d;
 }

 string super::print_super()
 {
     string outString;
   outString = numerator.print_expr();
#ifdef d_bug_s
   cout<<"^<--printed numer?     "<<endl;
#endif
   if(denominator.return_my_exp()->getCoeff()==(long long int)1 && denominator.return_my_exp()->x_getPower()==(long long int)0 &&denominator.return_my_exp()->link()==NULL)
       return outString;

   outString+="/";
   cout<<"/";
   outString+=denominator.print_expr();
    return outString;
 }
