#include "IntVector.h"
#include "SortableIntVector.h"
#include <stdexcept>

// Constructor: copy argument array
SortableIntVector::SortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements)
    : IntVector(aArrayOfIntegers, aNumberOfElements) {}  // Call the base class constructor

// Bubble sort
void SortableIntVector::sort(Comparable aOrderFunction) {
    // Outer loop iterates over each element
    for (int a = 0; a < size() - 1; a++) {
        // Inner loop for comparing adjacent elements
        for (int b = 0; b < size() - a - 1; b++) {
            // If elements are in the wrong order, swap them
            if (!aOrderFunction(get(b), get(b + 1))) {
                swap((b), (b + 1));
            }
        }
    }
}
