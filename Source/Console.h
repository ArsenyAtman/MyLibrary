#pragma once

#include "String.h"

class AConsole
{
public:

	static void Print(const AString& String);
	static void PrintLine(const AString& String);

	static AString Read();

protected:

private:

	AConsole();
	virtual ~AConsole();

};
