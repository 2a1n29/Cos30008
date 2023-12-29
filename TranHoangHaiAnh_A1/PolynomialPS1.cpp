#include "Polynomial.h"

double Polynomial::operator()(double aX) const {
    double result = 0.0;
    for (int i = 0; i <= fDegree; ++i) {
        result = fCoeffs[i] * pow(aX, i) + result;
    }
    return double(result);
}

Polynomial Polynomial::getDerivative() const {
    if (fDegree <= 0) {
        return Polynomial();
    }    
    Polynomial derivative;
    derivative.fDegree = fDegree - 1;
    for (int i = 1; i <= fDegree; ++i) {
        derivative.fCoeffs[i - 1] = fCoeffs[i] * i;
    }
    return Polynomial(derivative);
}

Polynomial Polynomial::getIndefiniteIntegral() const {
    Polynomial indefintegral;
    indefintegral.fDegree = fDegree + 1;
    indefintegral.fCoeffs[0] = 0;

    for (int i = 0; i <= fDegree; ++i) {
        indefintegral.fCoeffs[i + 1] = fCoeffs[i] / (i + 1);
    }

    return Polynomial(indefintegral);
}

double Polynomial::getDefiniteIntegral(double aXLow, double aXHigh) const {
    Polynomial defintegral = getIndefiniteIntegral();
    return defintegral(aXHigh) - defintegral(aXLow);
}