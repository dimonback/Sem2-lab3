#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int euclide(int, int);

class Fraction
{
private:
    int nom, den, sign,intPart;
    double res;
    
public:
    
    Fraction(char*);
    friend Fraction operator / (int, Fraction);
    Fraction(int n=0, int m=1): nom(n), den(m) {intPart=0};
    bool operator <= (Fraction);
    operator char*();
    operator double();
    void reduce();
};

Fraction::Fraction(char* s)    //принимаем и обрабатываем дробь
{
    intPart=0;
    char* p = strchr(s,'/');
    den=1;
    if(p!=NULL)
    {
        *p++ = '\0';
        den = atoi(p);
        if (den==0)
        {
            cout<< "Деление на ноль" << endl;
            exit(-1);
        }
    }
    nom = atoi(s);
}

bool Fraction::operator <= (Fraction a)
{
    if (double(*this) > double(a))
        return false;
    return true;
}

Fraction::operator double()   //перевод дроби в вещественное число типа double для последующего сравнения
{
     sign = (nom<0)?-1:1;
    if(fabs(nom) >= den)
    {
        intPart += fabs(nom / den);
        nom %= den;
    }
     res = (double)sign * (intPart * den + fabs(nom)) / den;
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
    //char tempstr1[32], tempstr2[32];
    Fraction x1(argv[1]);
    Fraction x2(argv[2]);
    //cin >> tempstr1;
    //cin >> tempstr2;
    //Fraction x1(tempstr1);
    //Fraction x2(tempstr2);
    
    x1.reduce();
    x2.reduce();
    if (x1<=x2)
        cout << (char*)x1 <<endl;
    else
        cout << (char*)x2 <<endl;
}
