#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int euclide(int, int);

class Fraction
{
private:
    int nom, den, sign,intPart=0;
    double res;
    
public:
    
    Fraction(char*);
    friend Fraction operator / (int, Fraction);
    Fraction(int n=0, int m=1): nom(n), den(m) {};
    bool operator <= (Fraction);
    operator char*();
    operator double();
    void GetIntPart();
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

bool Fraction::operator <= (Fraction a)
{
    if (double(*this) > double(a))
        return false;
    return true;
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
     sign = (nom<0)?-1:1;
     res = (double)sign * (intPart * den + nom) / den;
    return(res);
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
    Fraction y,a,b;
    char tempstr1[32], tempstr2[32];
    //Fraction x1(argv[1]);
    //Fraction x2(argv[2]);
    cin >> tempstr1;
    cin >> tempstr2;
    Fraction x1(tempstr1);
    Fraction x2(tempstr2);
    a=x1;
    b=x2;
    x1.reduce();
    x2.reduce();
    x1.GetIntPart();
    x2.GetIntPart();
    
    if (x1<=x2)
        cout << (char*)a <<endl;
    else
        cout << (char*)b <<endl;
}
