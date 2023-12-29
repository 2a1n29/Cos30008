#include "IntVector.h"
#include "SortableIntVector.h"
#include "ShakerSortableIntVector.h"
#include <stdexcept>

// Constructor: Copy argument array
ShakerSortableIntVector::ShakerSortableIntVector(const int inputArray[], size_t numberOfElements)
    : SortableIntVector(inputArray, numberOfElements) {}

// Cocktail Shaker Sort
void ShakerSortableIntVector::sort(Comparable orderFunction) {
    // Initialize left and right indices, and a swapped flag
    bool swappedCheck;
    int left = 0;
    int right = size() - 1;
    
    // Continue sorting as long as there are elements to swap
    do {
        swappedCheck = false;

        // Bubble sort from left to right
        for (int a = left; a < right; ++a) {
            if (orderFunction(get(a), get(a + 1))) {
                swap(a, a + 1);
                swappedCheck = true;
            }
        }

        // If no elements were swapped in the first pass, break out of the loop
        if (!swappedCheck) break;

        // Decrease the right index and reset the swapped flag
        --right;
        swappedCheck = false;

        // Bubble sort from right to left
        for (int b = right - 1; b >= left; --b) {
            if (orderFunction(get(b), get(b + 1))) {
                swap(b, b + 1);
                swappedCheck = true;
            }
        }

        // Increase the left index
        ++left;
    } while (swappedCheck);  // Repeat the process if elements were swapped in the last pass
}