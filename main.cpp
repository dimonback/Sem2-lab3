#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int euclide(int, int);

class Fraction
{
private:
    int nom, den, sign, intPart;
    void GetIntPart();
public:
    Fraction(char*);
    friend Fraction operator / (int, Fraction);
    Fraction(int n=0, int m=1): nom(n), den(m) {};
    Fraction operator <= (Fraction const);
    operator char*();
    operator double();
    void reduce();
};

Fraction::Fraction(char* s)
{
    char* p = strchr(s,'/');
    den=1;
    if(p!=NULL)
    {
        *p++ = '\0';
        den = atoi(p);
    }
    nom = atoi(s);
}

Fraction Fraction::operator <= (Fraction a)
{
    if (double(*this) > double(a))
        return a;
    return *this;
}

void Fraction::GetIntPart()
{
    if(nom >= den)
    {
        intPart += (nom / den);
        nom %= den;
    }
}


Fraction::operator double()
{
    double res = (double)sign * (intPart * den + nom) / den;
    return res;
}

Fraction::operator char* ()
{
    static char s[32];
    sprintf(s, "%d/%d", nom, den);
    return s;
}

void Fraction::reduce()
{
    int gcd;
    gcd = euclide(abs(nom), den);
    nom /= gcd;
    den /= gcd;
    return;
}

int euclide(int n, int m)
{
    int r = 1;
    while (n != 0)
    {
        r = m % n;
        m = n;
        n = r;
    }
    return(m);
}


int main(int argc,char* argv[])
{
    Fraction y;
    Fraction x1(argv[1]);
    Fraction x2(argv[2]);
    x1.reduce();
    x2.reduce();
    x1=double(x1);
    x2=double(x2);
    y=(x1<=x2);
    cout << (char*)y <<endl;
}
