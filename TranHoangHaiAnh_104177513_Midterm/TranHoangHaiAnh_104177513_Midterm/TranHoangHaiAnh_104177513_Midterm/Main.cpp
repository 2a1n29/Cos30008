#include <iostream>

using namespace std;

//#define P1
//#define P2
//#define P3
//#define P4

#ifdef P1
#include "KeyProvider.h"
int runP1(string argv[2])
{
	cout << "Testing KeyProvider with \"" << argv[0]
		<< "\" and \"" << argv[1] << "\"" << endl;
	KeyProvider lKeyWord(argv[0]);
	string& lMessage = argv[1];
	for (char c : lMessage)
	{
		if (isalpha(c))
		{
			cout << *lKeyWord;
			lKeyWord << c;
		}
		else
		{
			cout << ' ';
		}
	}
	cout << "\n";
	for (char c : lMessage)
	{
		cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
	}
	cout << "\nCompleted" << endl;
	return 0;
}
#endif

#ifdef P2
#include "Vigenere.h"
int runP2(string argv[2])
{
	Vigenere lSrambler(argv[0]);
	string lMessage = argv[1];
	// Test encoding
	cout << "Encoding \"" << lMessage
		<< "\" using \"" << lSrambler.getCurrentKeyword() << "\"" << endl;
	for (char c : lMessage)
	{
		cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
	}
	cout << "\n";
	string lEncodedMessage;
	for (char c : lMessage)
	{
		lEncodedMessage += lSrambler.encode(c);
	}
	cout << lEncodedMessage << "\nCompleted" << endl;
	// Test decoding
	lSrambler.reset();
	cout << "Decoding \"" << lEncodedMessage
		<< "\" using \"" << lSrambler.getCurrentKeyword() << "\"" << endl;
	for (char c : lEncodedMessage)
	{
		cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
	}
	cout << "\n";
	string lDecodedMessage;
	for (char c : lEncodedMessage)
	{
		lDecodedMessage += lSrambler.decode(c);
	}
	cout << lDecodedMessage << "\nCompleted" << endl;
	return 0;
}
#endif

#ifdef P3
#include "iVigenereStream.h"
int runP3(string argv[2])
{
	iVigenereStream lInput([](Vigenere& aCipherProvider, char aCharacter)
		{
			return aCipherProvider.decode(aCharacter);
		}, argv[0], argv[1].c_str());
	if (!lInput.good())
	{
		cerr << "Cannot open input file: " << argv[1] << endl;
		return 2;
	}
	cout << "Decoding \"" << argv[1] << "\" using \"" << argv[0] << "\"." << endl;
	char lCharacter;
	while (lInput >> lCharacter)
	{
		cout << lCharacter;
	}
	lInput.close();
	cout << "Completed." << endl;
	return 0;
}
#endif

#ifdef P4
#include "VigenereForwardIterator.h"
int runP4(string argv[2])
{
	iVigenereStream lInput([](Vigenere& aCipherProvider, char aCharacter)
		{
			return aCipherProvider.encode(aCharacter);
		}, argv[0], argv[1].c_str());
	if (!lInput.good())
	{
		cerr << "Cannot open input file: " << argv[1] << endl;
		return 2;
	}
	cout << "Forward Iterator Encoding \"" << argv[1]
		<< "' using \"" << argv[0] << "\"." << endl;
	for (char c : VigenereForwardIterator(lInput))
	{
		cout << c;
	}
	lInput.close();
	cout << "Completed." << endl;
	return 0;
}
#endif

int main() {
	string string_1[] = { "Relations", "To be, or not to be: that is the question:" };
	string string_2[] = { "Relations", "sample_3.txt" };
	string string_3[] = { "Relations", "sample_4.txt" };

#ifdef P1
	runP1(string_1);
#endif

#ifdef P2
	runP2(string_1);
#endif

#ifdef P3
	runP3(string_2);
#endif

#ifdef P4
	runP4(string_3);
#endif
}