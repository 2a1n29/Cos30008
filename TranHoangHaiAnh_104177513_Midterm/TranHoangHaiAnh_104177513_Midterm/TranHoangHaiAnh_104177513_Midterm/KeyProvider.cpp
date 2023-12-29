#include "KeyProvider.h"

// Constructor
KeyProvider::KeyProvider(const std::string& aKeyword) : fKeyword(new char[aKeyword.length()]), fSize(aKeyword.length()), fIndex(0)
{
    // Initialize the KeyProvider object with the provided keyword
    initialize(aKeyword);
}

// Destructor
KeyProvider::~KeyProvider()
{
    // Release the allocated memory for the keyword
    delete[] fKeyword;
}

// Initialize method to set up the keyword
void KeyProvider::initialize(const std::string& aKeyword)
{
    // Calculate the length of the provided keyword
    size_t aKeywordLength = aKeyword.length();

    // Release any previously allocated memory for the keyword
    delete[] fKeyword;

    // Reset index and size, and allocate memory for the keyword
    fIndex = 0;
    fSize = aKeywordLength;
    fKeyword = new char[fSize];

    // Convert each character in the keyword to uppercase
    for (size_t i = 0; i < fSize; i++)
    {
        fKeyword[i] = toupper(aKeyword[i]);
    }
}

// Overloaded dereference operator (*) to get the current character
char KeyProvider::operator*() const
{
    return fKeyword[fIndex];
}

// Overloaded left shift operator (<<) to add a key character
KeyProvider& KeyProvider::operator<<(char aKeyCharacter)
{
    // Convert the key character to uppercase and assign it to the current index
    fKeyword[fIndex] = toupper(aKeyCharacter);

    // Move to the next index
    fIndex++;

    // Reset the index to 0 if it exceeds the size
    if (fIndex >= fSize)
    {
        fIndex = 0;
    }

    // Return the updated KeyProvider object
    return *this;
}
