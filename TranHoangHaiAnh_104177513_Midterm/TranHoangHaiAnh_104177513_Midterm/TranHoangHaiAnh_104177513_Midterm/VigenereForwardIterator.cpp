#include "VigenereForwardIterator.h"

// Constructor
VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream) : fIStream(aIStream), fCurrentChar(0), fEOF(false)
{
    // Check if the input stream is in a valid state
    bool validInput = fIStream;
    if (validInput)
    {
        // Read the first character from the input stream
        fIStream >> fCurrentChar;

        // Check if the end of the file is reached
        bool isEndOfFile = fIStream.eof();
        if (isEndOfFile)
        {
            fEOF = true;
        }
    }
}

// Dereference operator to get the current character
char VigenereForwardIterator::operator*() const
{
    return fCurrentChar;
}

// Pre-increment operator to advance the iterator to the next character
VigenereForwardIterator& VigenereForwardIterator::operator++()
{
    // Check if the input stream is in a valid state
    bool validInput = fIStream;
    if (validInput)
    {
        // Read the next character from the input stream
        fIStream >> fCurrentChar;

        // Check if the end of the file is reached
        bool isEndOfFile = fIStream.eof();
        if (isEndOfFile)
        {
            fEOF = true;
        }
    }
    return *this;
}

// Post-increment operator to advance the iterator to the next character
VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
    // Create a copy of the current iterator
    VigenereForwardIterator _this = *this;

    // Advance the iterator to the next character
    (_this)++;

    // Return the copy of the iterator before the increment
    return _this;
}

// Equality operator to compare with another iterator
bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
    // Compare the end-of-file status
    bool result = (fEOF == aOther.fEOF);
    return result;
}

// Inequality operator to compare with another iterator
bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
    // Invert the result of the equality comparison
    bool result = !(*this == aOther);
    return result;
}

// Get the iterator pointing to the beginning
VigenereForwardIterator VigenereForwardIterator::begin() const
{
    return *this;
}

// Get the iterator pointing to the end
VigenereForwardIterator VigenereForwardIterator::end() const
{
    // Create a copy of the current iterator and mark it as end-of-file
    VigenereForwardIterator _this = *this;
    _this.fEOF = true;
    return _this;
}
