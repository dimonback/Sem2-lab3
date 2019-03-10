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

Fraction::Fraction(char* s)    //принимаем и обрабатываем дробь
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

Fraction Fraction::operator <= (Fraction a) //оператор, который сравнивает текущую дробь и вторую дробь, которая передается в качестве параметра
{
    if (double(*this) > double(a))
        return a;
    return *this;
}

void Fraction::GetIntPart()  //выделение целой части дроби
{
    if(nom >= den)
    {
        intPart += (nom / den);
        nom %= den;
    }
}


Fraction::operator double()   //перевод дроби в вещественное число типа double для последующего сравнения
{
    double res = (double)sign * (intPart * den + nom) / den;
    return res;
}

Fraction::operator char* () //строка
{
    static char s[32];
    sprintf(s, "%d/%d", nom, den);
    return s;
}

void Fraction::reduce() //сокращение дроби
{
    int gcd;
    gcd = euclide(abs(nom), den);
    nom /= gcd;
    den /= gcd;
    return;
}

int euclide(int n, int m) //алгоритм Евклида, необходимый для сокращения дроби
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
