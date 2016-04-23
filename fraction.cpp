#include "fraction.h"

//#define d_bug_f

fraction::fraction()
{
    numerator = 0;
    denominator = 1;
}

fraction::fraction( long long int n, long long int d)
{
    makeNew(n,d);

#ifdef d_bug_f
    cout<<"fraction constructor called"<<endl;
#endif
}

fraction::fraction(long long int n)
{
    long long int d=1;

    makeNew(n,d);
}

/*
fraction::fraction(const long long int &n, const long long int &d)
{
    makeNew(n,d);

#ifdef d_bug_f
    cout<<"fraction constructor called"<<endl;
#endif
}
*/

fraction::fraction(double v)
{
    //cout<<"dub init"<<v<<endl;
    doubleInitialize(v);
}

fraction::fraction(const fraction &other)
{
    numerator = other.numerator;
    denominator = other.denominator;
}

fraction& fraction::operator=(const fraction &other)
{
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

fraction& fraction::operator+=(fraction &other)
{
    return *this + other;
}

fraction& fraction::operator-=(fraction &other)
{
    return *this - other;
}

fraction& fraction::operator*=(fraction &other)
{
    return *this * other;
}

fraction& fraction::operator/=(fraction &other)
{

    if(other == (long long int)0)
        throw DIV_BY_ZERO;
    return *this / other;
}

fraction fraction::operator^=(fraction &other)  //modified return type from fraction&
{
    return *this ^ other;
}

fraction& fraction::operator=(long long int other)
{
    numerator = other;
    denominator = (long long int)1;
    return *this;
}

fraction& fraction::operator+=(long long int other)
{
    return *this + other;
}

fraction& fraction::operator-=(long long int other)
{
    return *this - other;
}

fraction& fraction::operator*=(long long int other)
{
    return *this * other;
}

fraction& fraction::operator/=(long long int other)
{
    if(other == (long long int)0)
        throw DIV_BY_ZERO;
    return (*this) / other;
}

fraction& fraction::operator^=(long long int other)
{
    return *this ^ other;
}

fraction& fraction::operator=(double other)
{
#ifdef d_bug_f
    cout<<"ass-op= double called, go to double init next ..."<<endl;
#endif

    doubleInitialize(other);
    return *this;
}

fraction& fraction::operator+=(double other)
{
    return *this + other;
}

fraction& fraction::operator-=(double other)
{
    return *this - other;
}

fraction& fraction::operator*=(double other)
{
    return *this * other;
}

fraction& fraction::operator/=(double other)
{
    if(other == (long long int)0)
        throw DIV_BY_ZERO;
    return (*this) / other;
}

fraction& fraction::operator^=(double other)
{
    return *this ^ other;
}

void fraction::doubleInitialize(double d)
{
#ifdef d_bug_f
    cout<<"Inside double initialize !!!"<<endl;
#endif

    bool neggger=false;

    if(d<0.)
    {
        d=d*(-1.);
        neggger=true;

    }

    ifstream in_strm;
    ofstream out_strm;

#ifdef d_bug_f
    cout<<"made it here1"<<endl;
#endif

    out_strm.open("double_num.dat");

#ifdef d_bug_f
    cout<<"d= "<<d<<endl;
#endif

    out_strm<<setprecision(15)<<d;

#ifdef d_bug_f
    cout<<"d= "<<d<<endl;
#endif

    out_strm.close();

#ifdef d_bug_f
    cout<<"made it here2"<<endl;
#endif


    in_strm.open("double_num.dat");
    string dumber;
    char buf;
    while(in_strm>>buf)
    {
#ifdef d_bug_f
        cout<<"made it here3"<<endl;
        //out_strm<<buf;        //<--don't remember what that dude is for, but haven't needed since I forgot why i wrote it
#endif



        dumber+=buf;
    }
    //^changed double long long into string

    in_strm.close();

#ifdef d_bug_f
    cout<<"*dumber = "<<dumber<<endl;

cout<<"made it here4"<<endl;
#endif


char char_version[dumber.size()];
//char array



int pos;
pos=dumber.find_first_of('.');
//^keep track of decimal polong long int

string number=dumber;


#ifdef d_bug_f
cout<<"number = "<<number<<endl;
#endif

if(pos>=0)
number.erase(pos, 1);
string nummer=number;

int after_decimal;
if(pos>0)
    after_decimal=number.size()-pos;
else
    after_decimal=0;



#ifdef d_bug_f
cout<<"####length of string is "<<number.size()<<endl;

cout<<"number = "<<number<<endl;

cout<<"decimal after length="<<after_decimal<<endl;

cout<<"pos="<<pos<<endl;
#endif

if(number.size()>=15)
{
strcpy(char_version, number.c_str());
//^copys string to char array

 int j=0;
 int i;                                     //CHANGED BACK INTO STANDARD int
 int q;

//super tripple for loop.
//k loops the size of the pattern to be searching
//j loops through i looking for the pattern
// i is the slot that j looks for
for(long long int k=3; k<7; k++)
{
    for(j=0; j<(dumber.size()-3); j++)
    {
#ifdef d_bug_f
        cout<<"j="<<j<<"!"<<endl;
#endif

        long long int seq=0, num;
        //setting the sequence to look for
        for(int z=0; z<k; z++)
        {
#ifdef d_bug_f
            cout<<"seq= "<<seq<<endl;
#endif

            int w = j + z;                                      //changed back to int
            if(w<(dumber.size()-3))
            {

#ifdef d_bug_f
            cout<<"inside if line 262(ish) and w n then seq n then char_version[w]= "<<w<<"  "<<seq<<"  "<<char_version[w]<<endl;
#endif
                num=atoint(char_version[w]);

                seq= seq*10 + num;                              //need to type cast the *10?

            }

        }
#ifdef d_bug_f
        cout<<"sequence to be compared = "<<seq<<endl;
#endif

        for(i=0; i<(dumber.size()-3); i++)
        {
#ifdef d_bug_f
            cout<<"k="<<k<<", j="<<j<<", i="<<i<<endl;
#endif

            long long int comparer=0, comparer2=0, comparer3=0, num2, num3, num4;
            //comparing the spots in the seaching loops with the sequence pattern
            for(int y=0; y<k; y++)
            {
                if(i+y<dumber.size()-3)
                {
                    num2=atoint(char_version[i+y]);

                    comparer= comparer*10 + num2;

                }
            }

            //if true, then looks for a pattern after the pattern... needs to be done with recursion me thinks
            if(seq==comparer && i!=j)
            {
#ifdef d_bug_f
                cout<<"seq==comparer :-)"<<endl;
#endif
                for(int y=0; y<k; y++)
                {
                    if(i+k+y<dumber.size()-3)
                    {
                        num3=atoint(char_version[i+k+y]);

                        comparer2= comparer2*10 + num3;

                    }
                }

                if(seq==comparer2 && i!=j)
                {
#ifdef d_bug_f
                    cout<<"seq==comparer2 :-)"<<endl;
#endif
                    for(int y=0; y<k; y++)
                    {
                        q=i+2*k+y;

                        if(q<dumber.size()-3)
                        {
                            num4=atoint(char_version[q]);

                            comparer3= comparer3*10 + num4;
                        }
                    }

                    if(seq==comparer3 || (seq==comparer2 && k>4))
                    {
#ifdef d_bug_f
                        if(seq==comparer3)
                            cout<<"seq==comparer3 :-)"<<endl;
                        else if(seq==comparer2 && k>4)
                            cout<<"too large a k, but seq==comparer2"<<endl;
#endif
                        long long int multiply_by_flag=1;
                        for(int v=1; v< j+k; v++)
                            multiply_by_flag*=10;

                        long long int dd= d*multiply_by_flag;
                        //^dd=the first number of pattern
#ifdef d_bug_f
                        cout<<"d="<<d<<endl;
                        cout<<"variable dd="<<dd<<endl;
#endif
                        int dif= j-pos;
#ifdef d_bug_f
                        cout<<"dif:"<<dif<<endl;
#endif
                        long long int ddd=1, counter=1;

                        if(dif>0)
                        for(long long int v=0; v< dif; v++)
                        {
#ifdef d_bug_f
                            cout<<"the dif is:"<<dif<<endl;
#endif
                        counter*=10;
                        ddd=counter;
                        }
#ifdef d_bug_f
                        else if(dif==0)
                            cout<<"dif==0"<<endl;
#endif
                        else
                        {
                            //cout<<"pattern starts before decimal point"<<endl;            //pattern recognition works everywhere :)
                            break;
                        }

                        ddd*=d;
                        //^=value of 10x numbers preceding begining of pattern

                        long long int big_dif= dd-ddd;
                        long long int denom = multiply_by_flag-counter;

                        ;
#ifdef d_bug_f
                        cout<<"seq was/is= "<<seq<<"!!!!!!"<<endl;
#endif
                        numerator = big_dif;
                        denominator = denom;

                        //reduce();
#ifdef d_bug_f
                        cout<<"fraction="<<numerator<<"/"<<denominator<<endl;
#endif

                        if(neggger)
                        {
                            numerator=numerator*(long long int)(-1);

                        }

                        reduce();

                        return;


                        //^starting to implement the algorithm to change a repeating decimal long long into a fraction



                    }

                }
            }


        }
    }

}
}
#ifdef d_bug_f
cout<<"Inside old school double initialize"<<endl;
#endif

    long long int topp, bottom = 1;

    strcpy(char_version, nummer.c_str());

#ifdef d_bug_f
cout<<"nummerlength=   "<<nummer.length()<<" : "<<nummer<<endl;
cout<<char_version[3]<<endl;
#endif

    topp= atoint(char_version[0]);

    for(int v=1; v<nummer.size(); v++)
    {
        topp= topp*10 + atoint(char_version[v]);
    }

    for(int v=0; v<after_decimal; v++)
        bottom=bottom*10;

    numerator = topp;
    denominator = bottom;
    //if(sign)
    //    numerator *= -1;
    reduce();

    if(neggger)
        numerator=numerator*(long long int)(-1);

}

void fraction::display()
{
    cout<<numerator<<"/"<<denominator;
}

long long int& fraction::num()
{
    return numerator;
}

long long int& fraction::denom()
{
    return denominator;
}


void fraction::newValue(long long int n, long long int d)
{
    makeNew(n,d);
}

void fraction::makeNew(long long int n, long long int d)
{
#ifdef d_bug_f
    cout<<"inside fraction make new: n= "<<n<<", d="<<d<<endl;

#endif

    if(d == 0)
        throw INVALID_FRACTION;
    numerator = n;
    denominator = d;
    if(d==1)
        return;
    reduce();
}

void fraction::reduce()
{
#ifdef d_bug_f
    cout<<"inside fraction reduce"<<endl;
#endif

    long long int div = gcd(abs(numerator),abs(denominator));
    numerator /= div;
    denominator /= div;
#ifdef d_bug_f
    cout<<"half way through fraction reduce"<<endl;
#endif
    if(denominator < (long long int)0)                  //added the long long int here and on the two below on 9/16/13
    {
        numerator *= (long long int)-1;
        denominator *= (long long int)-1;
    }
#ifdef d_bug_f
    cout<<"made it through fraction reduce :)"<<endl;
#endif
}

long long int fraction::gcd(long long int p, long long int q)
{

    return q == (long long int)0 ? p : gcd(q, p%q);
}


ostream& operator<<(ostream &out, fraction &x)
{
    out<<x.numerator<<"/"<<x.denominator;
    return out;
}

istream& operator>>(istream &in, fraction &x)
{
    char junk;
    x.numerator = 0;
    x.denominator = 1;
    if(in>>x.numerator)
      if(in>>junk)
          in>>x.denominator;
    return in;
}


fraction& operator+(fraction &x, fraction &y)
{
    static fraction ans;
    ans.numerator = x.numerator*y.denominator + x.denominator*y.numerator;
    ans.denominator = x.denominator*y.denominator;
    ans.reduce();
    return ans;
}


fraction& operator-(fraction &x, fraction &y)
{
    static fraction ans;
    ans.numerator = x.numerator*y.denominator - x.denominator*y.numerator;
    ans.denominator = x.denominator*y.denominator;
    ans.reduce();
    return ans;
}


fraction& operator*(fraction &x, fraction &y)
{
    static fraction ans;
    ans.numerator = x.numerator*y.numerator;
    ans.denominator = x.denominator*y.denominator;
    ans.reduce();
    return ans;
}


fraction& operator/(fraction &x, fraction &y)
{
    static fraction ans;
    if(y == (long long int)0)
        throw DIV_BY_ZERO;
    ans.numerator = x.numerator*y.denominator;
    ans.denominator = x.denominator*y.numerator;
    ans.reduce();
    return ans;
}

fraction operator^(fraction &x, fraction &y)
{
    double yValue = (double)y.numerator / (double)y.denominator,
           xValue = (double)x.numerator / (double)x.denominator;
    double ans;

    ans = pow(xValue, yValue);

#ifdef d_bug_f
    cout<<"ans="<<ans<<endl;

    cout<<"power="<<yValue<<endl;
#endif

    fraction answer(ans); //removed staticness 1/10/14

#ifdef d_bug_f
    cout<<"frac optr^ = "<<answer<<endl<<"x (lhs)="<<x<<endl<<"y (rhs)="<<y<<endl;
#endif

    return answer;
}

bool operator==(const fraction &x, const fraction &y)
{
    return x.numerator*y.denominator == x.denominator*y.numerator;
}

bool operator<=(const fraction &x,const  fraction &y)
{
    return x.numerator*y.denominator <= x.denominator*y.numerator;
}


bool operator<(const fraction &x, const fraction &y)
{
    return x.numerator*y.denominator < x.denominator*y.numerator;
}


bool operator>(const fraction &x,const  fraction &y)
{
    return !(x <= y);
}


bool operator>=(const fraction &x,const  fraction &y)
{
    return !(x < y);
}


bool operator!=(const fraction &x,const  fraction &y)
{
    return !(x == y);
}


//For Integers

fraction& operator+(fraction &x, long long int y)
{
    long long int k = 1;
    fraction temp(y, k);
    static fraction ans = x + temp;
    return ans;
}

fraction& operator-(fraction &x, long long int y)
{
    fraction temp(y);
    static fraction ans = x - temp;
    return ans;
}

fraction& operator*(fraction &x, long long int y)
{
    fraction temp(y);
    static fraction ans = x * temp;
    return ans;
}

fraction& operator/(fraction &x, long long int y)
{
    fraction temp(y);
    if(y == (long long int)0)
        throw DIV_BY_ZERO;
    static fraction ans = x / temp;
    return ans;
}

fraction& operator^(fraction &x, long long int y)
{
    fraction temp(y);
    static fraction ans = x ^ temp;
    return ans;
}

fraction& operator+(long long int x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp + y;
    return ans;
}

fraction& operator-(long long int x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp - y;
    return ans;
}

fraction& operator*(long long int x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp * y;
    return ans;
}

fraction& operator/(long long int x, fraction &y)
{
    fraction temp(x);
    if(y == (long long int)0)
        throw DIV_BY_ZERO;
    static fraction ans = temp / y;
    return ans;
}

fraction& operator^(long long int x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp ^ y;
    return ans;
}

//For doubles and  float

fraction& operator+(fraction &x, double y)
{
    fraction temp(y);
    static fraction ans = x + temp;
    return ans;
}

fraction& operator-(fraction &x, double y)
{
    fraction temp(y);
    static fraction ans = x - temp;
    return ans;
}

fraction& operator*(fraction &x, double y)
{
    fraction temp(y);
    static fraction ans = x * temp;
    return ans;
}

fraction& operator/(fraction &x, double y)
{
    fraction temp(y);
    if(y == (long long int)0)
        throw DIV_BY_ZERO;
    static fraction ans = x / temp;
    return ans;
}

fraction& operator^(fraction &x, double y)
{
    fraction temp(y);
    static fraction ans = x ^ temp;
    return ans;
}

fraction& operator+(double x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp + y;
    return ans;
}

fraction& operator-(double x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp - y;
    return ans;
}

fraction& operator*(double x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp * y;
    return ans;
}
fraction& operator/(double x, fraction &y)
{
    fraction temp(x);
    if(y == (long long int)0)
        throw DIV_BY_ZERO;
    static fraction ans = temp / y;
    return ans;
}

fraction& operator^(double x, fraction &y)
{
    fraction temp(x);
    static fraction ans = temp ^ y;
    return ans;
}

//Comparison operators -- fraction to integer and visa versa

bool operator==(const fraction &x, long long int y)
{
    fraction temp(y);
    return x == temp;
}

bool operator<=(const fraction &x,long long int y)
{
    fraction temp(y);
    return x <= temp;
}

bool operator<(const fraction &x,long long int y)
{
    fraction temp(y);
    return x < temp;
}

bool operator>(const fraction &x, long long int y)
{
    fraction temp(y);
    return x > temp;
}

bool operator>=(const fraction &x,long long int y)
{
    fraction temp(y);
    return x >= temp;
}

bool operator!=(const fraction &x,long long int y)
{
    fraction temp(y);
    return x != temp;
}

bool operator==(long long int x,const fraction &y)
{
    fraction temp(x);
    return temp == y;
}
bool operator<=(long long int x,const  fraction &y)
{
    fraction temp(x);
    return temp <= y;
}

bool operator<(long long int x,const  fraction &y)
{
    fraction temp(x);
    return temp < y;
}

bool operator>(long long int x, const fraction &y)
{
    fraction temp(x);
    return temp > y;
}
bool operator>=(long long int x,const  fraction &y)
{
    fraction temp(x);
    return temp >= y;
}

bool operator!=(long long int x, const fraction &y)
{
    fraction temp(x);
    return y != temp;
}

//Comparison operators -- fraction to double and visa versa

bool operator==(const fraction &x, double y)
{
    fraction temp(y);
    return x == temp;
}

bool operator<=(const fraction &x,double y)
{
    fraction temp(y);
    return x <= temp;
}

bool operator<(const fraction &x,double y)
{
    fraction temp(y);
    return x < temp;
}

bool operator>(const fraction &x, double y)
{
    fraction temp(y);
    return x > temp;
}

bool operator>=(const fraction &x,double y)
{
    fraction temp(y);
    return x >=temp;
}

bool operator!=(const fraction &x,double y)
{
    fraction temp(y);
    return x != temp;
}

bool operator==(double x,const fraction &y)
{
    fraction temp(x);
    return temp == y;
}

bool operator<=(double x,const  fraction &y)
{
    fraction temp(x);
    return temp <= y;
}

bool operator<(double x,const  fraction &y)
{
    fraction temp(x);
    return temp < y;
}

bool operator>(double x, const fraction &y)
{
    fraction temp(x);
    return temp > y;
}

bool operator>=(double x,const  fraction &y)
{
    fraction temp(x);
    return temp >= y;
}


bool operator!=(double x, const fraction &y)
{
    fraction temp(x);
    return temp != y;
}


fraction& aabs(fraction &x)
{
    fraction j((long long int)-1, (long long int)1);    //4/17/14 changed from type integer to type fraction --- WORKS!!! :-)

    if(x > (long long int)0)
        return x;
    else
        return x * j;
    //return x > 0 ? x :  x * -1 ;
}

void fraction::make_numer_neg()
{
    numerator=numerator*(long long int)(-1);
}

 void fraction::set_term(long long int n, long long int d)
 {
     numerator=n;
     denominator=d;
 }

 long long int fraction::atoint(char car)
 {
     if(car==48)
         return 0;
     else if(car==49)
         return 1;
     else if(car==50)
         return 2;
     else if(car==51)
         return 3;
     else if(car==52)
         return 4;
     else if(car==53)
         return 5;
     else if(car==54)
         return 6;
     else if(car==55)
         return 7;
     else if(car==56)
         return 8;
     else if(car==57)
         return 9;
     else
     {
         cout<<"error in atolong long int func... exiting... ("<<car<<":not allowed)"<<endl;
         exit(1);
     }
 }
