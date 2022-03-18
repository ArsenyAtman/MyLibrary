#pragma once

class AString
{
public:

	AString(const char* String = "");
	AString(const char Char);
	AString(const AString& String);
	AString(AString&& String) noexcept;

	AString& operator = (const AString& String);
	AString& operator = (AString&& String) noexcept;

	bool operator == (const AString& String) const;
	friend bool operator == (const char* String1, const AString& String2) { return String2 == static_cast<AString>(String1); }
	friend bool operator == (const AString& String1, const char* String2) { return String1 == static_cast<AString>(String2); }

	bool operator != (const AString& String) const { return !((*this) == String); }
	friend bool operator != (const char* String1, const AString& String2) { return String2 != static_cast<AString>(String1); }
	friend bool operator != (const AString& String1, const char* String2) { return String1 != static_cast<AString>(String2); }

	char& operator [] (const int Index) { return this->GetCharByIndex(Index); }
	char operator [] (const int Index) const { return this->GetCharByIndex(Index); }

	AString operator + (const AString& String) const { return this->ConcatWith(String); }
	AString ConcatWith(const AString& String2) const;

	AString& operator += (const AString& String) { (*this) = (*this) + String; return *this; }

	AString Split(int StartIndex, int EndIndex) const;

	int GetLength() const { return StringLength; }

	operator const char* () const { return ArrayOfChars; }

	virtual ~AString();

private:

	char& GetCharByIndex(const int Index) const;

	char* ArrayOfChars = nullptr;
	int StringLength = 0;
};
