#include "KeyProvider.h"
#include "Vigenere.h"

// Initialize Vigenere encryption/decryption table
void Vigenere::initializeTable()
{
    for (char row = 0; row < CHARACTERS; row++)
    {
        char lChar = 'B' + row;

        for (char column = 0; column < CHARACTERS; column++)
        {

            if (lChar > 'Z')
                lChar = 'A';

            fMappingTable[row][column] = lChar++;
        }
    }
}

// Constructor
Vigenere::Vigenere(const std::string& aKeyword) : fKeyword(aKeyword), fKeywordProvider(KeyProvider(aKeyword))
{
    // Initialize the Vigenere table
    initializeTable();
}

// Get the current keyword based on the Vigenere cipher
std::string Vigenere::getCurrentKeyword()
{
    std::string theCurrentKeyword;

    for (size_t i = 0; i < fKeyword.length(); i++)
    {
        // Append the current character from the keyword
        theCurrentKeyword += *fKeywordProvider;

        // Update the keyword for the next character
        fKeywordProvider << *fKeywordProvider;
    }

    return theCurrentKeyword;
}

// Reset the Vigenere cipher to its initial state
void Vigenere::reset()
{
    fKeywordProvider.initialize(fKeyword);
}

// Encode a character using the Vigenere cipher
char Vigenere::encode(char aCharacter)
{
    char encodedChar = aCharacter;
    bool isAlphabet = isalpha(encodedChar);

    if (isAlphabet)
    {
        char upperACharacter = toupper(aCharacter);
        char fMappingTableRow = *fKeywordProvider - 'A';
        char fMappingTableColumn = upperACharacter - 'A';

        // Perform the Vigenere encryption
        encodedChar = fMappingTable[fMappingTableRow][fMappingTableColumn];

        // Update the keyword for the next character
        fKeywordProvider << aCharacter;

        // Convert to lowercase if the original character was lowercase
        bool isLowered = islower(aCharacter);
        if (isLowered)
        {
            encodedChar = tolower(encodedChar);
        }
    }

    return encodedChar;
}

// Decode a character using the Vigenere cipher
char Vigenere::decode(char aCharacter)
{
    char decodedChar = aCharacter;
    bool isAlphabet = isalpha(decodedChar);

    if (isAlphabet)
    {
        char upperACharacter = toupper(aCharacter);
        char fMappingTableRow = *fKeywordProvider - 'A';

        // Find the corresponding column in the Vigenere table for decryption
        for (char i = 0; i < 26; ++i)
        {
            if (fMappingTable[fMappingTableRow][i] == upperACharacter)
            {
                char fMappingTableColumn = i + 'A';
                decodedChar = fMappingTableColumn;

                // Update the keyword for the next character
                fKeywordProvider << fMappingTableColumn;

                break;
            }
        }

        // Convert to lowercase if the original character was lowercase
        bool isLowered = islower(aCharacter);
        if (isLowered)
        {
            decodedChar = tolower(decodedChar);
        }
    }

    return decodedChar;
}
