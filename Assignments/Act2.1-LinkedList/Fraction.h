//
// Created by jange on 26/05/2026.
//

#ifndef MYFRACTIONS_FRACTION_H
#define MYFRACTIONS_FRACTION_H

class Fraction {
    private:
        int numerator;
        int denominator;
    public:
        Fraction();
        Fraction(int, int);
        int getNumerator();
        int getDenominator();
        void setNumerator(int numerator);
        void setDenominator(int denominator);
        Fraction add(Fraction fraction);
        Fraction mult(Fraction fraction);
        void print();
        void reduce();
};


#endif //MYFRACTIONS_FRACTION_H
