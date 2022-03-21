#pragma once

#include "../String/Stringable.h"
#include "../String/String.h"

class AException : public IStringable
{
public:

	AException(AString Description = AString());

	virtual AString ToString();

protected:

	AString Description = AString();
};
