#include <iostream>
#include <cmath>

using namespace std;

class Fraction
{
private:
    //поля: числитель и знаменатель
    int numerator;
    int denominator;
public:
    void setNumerator(int value){numerator = value;}
    void setDenominator(int value){if(value != 0) denominator = value;}

    int getNumerator(){return numerator;}
    int getDenominator(){return denominator;}

    void print() {cout << numerator << "/" << denominator;}

    Fraction(int n, int d) {numerator = n; denominator = d!=0?d:1;}
    Fraction(int n) {numerator = n; denominator = 1;}
    Fraction() {numerator = 0; denominator = 1;}

    Fraction operator*(Fraction G) {
        Fraction F;
        F.numerator = numerator * G.numerator;
        F.denominator = denominator * G.denominator;
        return F;
    }

    bool operator==(Fraction F) {
        return ((numerator*F.denominator-F.numerator*denominator)==0);
    }
    bool operator==(double x) {
        return (fabs(double(numerator) / denominator - x)<0.001);
    }

    bool operator!=(Fraction F) {
        return ((numerator*F.denominator-F.numerator*denominator)!=0);
    }
    bool operator!=(double x) {
        return (fabs(double(numerator) / denominator - x)>=0.001);
    }

    bool operator>(Fraction F) {
        return (double(numerator)/denominator - double(F.numerator)/F.denominator > 0);
    }

    Fraction operator*=(Fraction F) {
        numerator *= F.numerator; 
        denominator *= F.denominator;
        return *this;
    }

    friend Fraction operator/(int n, Fraction F);

};

Fraction operator*(int n, Fraction F) {
    Fraction res;
    res.setNumerator(n * F.getNumerator());
    res.setDenominator(n * F.getDenominator());
    return res;
}

Fraction operator/(int n, Fraction F) {
    Fraction res;
    res.numerator = n * F.denominator;
    res.denominator = F.numerator;
    return res;
}

