#include "IVigenereStream.h"

// Constructor
iVigenereStream::iVigenereStream(Cipher aCipher, const std::string& aKeyword, const char* aFileName) : fCipherProvider(aKeyword), fCipher(aCipher)
{
    // Open the file if a filename is provided
    if (aFileName != nullptr)
    {
        open(aFileName);
    }
}

// Destructor
iVigenereStream::~iVigenereStream()
{
    // Close the file when the object is destroyed
    close();
}

// Open a file for reading
void iVigenereStream::open(const char* aFileName)
{
    // Close any previously opened file
    close();

    // Open the specified file
    fIStream.open(aFileName);
}

// Close the currently opened file
void iVigenereStream::close()
{
    // Check if the file stream is open before attempting to close it
    bool isOpenedfIStream = fIStream.is_open();
    if (isOpenedfIStream)
    {
        fIStream.close();
    }
}

// Reset the file stream to the beginning
void iVigenereStream::reset()
{
    // Seek to the start of the file
    seekstart();
}

// Check if the file stream is in a good state
bool iVigenereStream::good() const
{
    return fIStream.good();
}

// Check if the file stream is open
bool iVigenereStream::is_open() const
{
    return fIStream.is_open();
}

// Check if the end of the file has been reached
bool iVigenereStream::eof() const
{
    return fIStream.eof();
}

// Read and process a character from the file using the Vigenere cipher
iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
    // Read a character from the file
    char getChar = fIStream.get();

    // Process the character using the Vigenere cipher
    char processedChar = fCipher(fCipherProvider, getChar);

    // Assign the processed character to the output parameter
    aCharacter = processedChar;

    // Return the updated iVigenereStream object
    return *this;
}
