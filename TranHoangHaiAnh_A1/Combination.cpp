#include "Combination.h"

using namespace std;    

size_t Combination::getN() const { return fN; }
size_t Combination::getK() const { return fK; }
Combination::Combination(size_t aN, size_t aK) : fN(aN), fK(aK) {}
unsigned long long Combination::operator()() const {
    unsigned long long result = fN;
    if (fK > fN) {
        return 0;
    }
    if (fK == 0) {
        return 1;
    }
    for (size_t i = 2; i <= fK; ++i) {
        result = (result * (fN - i + 1)) / i;
    }
    return unsigned long long(result);
}