#include "Console.h"

#include <iostream>

AConsole::AConsole()
{

}

AConsole::~AConsole()
{

}

void AConsole::Print(const AString& String)
{
	std::cout << String;
}

void AConsole::PrintLine(const AString& String)
{
	std::cout << String << std::endl;
}

AString AConsole::Read()
{
	AString Value;
	bool ReadCin = true;
	while (ReadCin)
	{
		char Buffer[100] = {};
		std::cin.getline(Buffer, 100);
		AString StringBuffer = AString(Buffer);
		Value += StringBuffer;
		if (StringBuffer.GetLength() < sizeof(Buffer))
		{
			ReadCin = false;
		}
	}
	return Value;
}