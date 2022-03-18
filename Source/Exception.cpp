#include "Exception.h"

AException::AException(AString Description)
{
	this->Description = Description;
}

AString AException::ToString()
{
	return Description;
}
