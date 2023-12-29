#include "IntVector.h"
#include <stdexcept>

// Constructor: copy argument array
IntVector::IntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) {
    fNumberOfElements = aNumberOfElements;
    fElements = new int[fNumberOfElements];
    for (size_t a = 0; a < fNumberOfElements; a++) {
        fElements[a] = aArrayOfIntegers[a];
        fElements[a] = aArrayOfIntegers[a];
    }
}

// Destructor: release memory
IntVector::~IntVector() {
    delete[] fElements;
}

// size getter
size_t IntVector::size() const {
    return fNumberOfElements;
}

// element getter
const int IntVector::get(size_t aIndex) const {
    return (*this)[aIndex];
}

// swap two elements within the vector
void IntVector::swap(size_t aSourceIndex, size_t aTargetIndex) {
    if (aSourceIndex >= fNumberOfElements || aTargetIndex >= fNumberOfElements) {
        throw std::out_of_range("Illegal vector indices");
    }
    else {
        int swapper = fElements[aSourceIndex];
        fElements[aSourceIndex] = fElements[aTargetIndex];
        fElements[aTargetIndex] = swapper;
    }
}

// indexer
const int IntVector::operator[] (size_t aIndex) const {
    if (aIndex >= fNumberOfElements) {
        throw std::out_of_range("Illegal vector index");
    }
    else {
        return fElements[aIndex];
    }
}