#include "String.h"

#include "Exception.h"

AString::AString(const char* String)
{
	if (String != nullptr)
	{
		int Size = 0;
		while (String[Size] != '\0')
		{
			++Size;
		}

		ArrayOfChars = new char[Size + 1];
		StringLength = Size;

		for (int i = Size; i >= 0; --i)
		{
			ArrayOfChars[i] = String[i];
		}
	}
}

AString::AString(const char Char)
{
	StringLength = 1;
	ArrayOfChars = new char[StringLength + 1];
	ArrayOfChars[0] = Char;
	ArrayOfChars[1] = '\0';
}

AString::AString(const AString& String)
{
	this->StringLength = String.StringLength;

	this->ArrayOfChars = new char[this->StringLength + 1];
	for (int i = this->StringLength; i >= 0; --i)
	{
		ArrayOfChars[i] = String.ArrayOfChars[i];
	}
}

AString::AString(AString&& String) noexcept
{
	this->StringLength = String.StringLength;
	this->ArrayOfChars = String.ArrayOfChars;

	String.ArrayOfChars = nullptr;
}

AString& AString::operator = (const AString& String)
{
	if (this == &String)
	{
		return *this;
	}

	delete[] ArrayOfChars;

	this->StringLength = String.StringLength;

	this->ArrayOfChars = new char[this->StringLength + 1];
	for (int i = this->StringLength; i >= 0; --i)
	{
		ArrayOfChars[i] = String.ArrayOfChars[i];
	}

	return *this;
}

AString& AString::operator = (AString&& String) noexcept
{
	if (this == &String)
	{
		return *this;
	}

	delete[] ArrayOfChars;

	this->StringLength = String.StringLength;
	this->ArrayOfChars = String.ArrayOfChars;

	String.ArrayOfChars = nullptr;

	return *this;
}

bool AString::operator == (const AString& String) const
{
	if (this == &String)
	{
		return true;
	}

	if (this->GetLength() != String.GetLength())
	{
		return false;
	}

	for (int i = this->GetLength() - 1; i >= 0; --i)
	{
		if ((*this)[i] != String[i])
		{
			return false;
		}
	}

	return true;
}

AString AString::Split(int StartIndex, int EndIndex) const
{
	int NewStringSize = EndIndex - StartIndex + 2;

	if (NewStringSize >= 0 && (StartIndex >= 0 && StartIndex < this->GetLength()) && (EndIndex >= 0 && EndIndex < this->GetLength()))
	{
		char* NewString = new char[NewStringSize];
		for (int i = NewStringSize - 2; i >= 0; --i)
		{
			NewString[i] = (*this)[StartIndex + i];
		}

		NewString[NewStringSize - 1] = '\0';

		AString ResultString(NewString);

		delete[] NewString;

		return ResultString;
	}
	else
	{
		throw AException("Exception thrown: Incorrect range.");
	}
}

AString::~AString()
{
	
	delete[] ArrayOfChars;
}

char& AString::GetCharByIndex(const int Index) const
{
	if (Index >= 0 && Index < this->GetLength() && ArrayOfChars != nullptr)
	{
		return ArrayOfChars[Index];
	}
	else
	{
		throw AException("Exception thrown: String index out of range.");
	}
}

AString AString::ConcatWith(const AString& String2) const
{
	const int FirstStringSize = this->GetLength();
	const int SecondStringSize = String2.GetLength();
	int NewStringSize = FirstStringSize + SecondStringSize;
	char* NewString = new char[NewStringSize + 1];
	
	NewString[NewStringSize] = '\0';

	int i = NewStringSize - 1;

	while (i >= FirstStringSize)
	{
		NewString[i] = String2[i - FirstStringSize];
		--i;
	}

	while (i >= 0)
	{
		NewString[i] = (*this)[i];
		--i;
	}

	AString ResultString(NewString);

	delete[] NewString;

	return ResultString;
}
