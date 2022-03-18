#pragma once

#include "Stringable.h"
#include "String.h"

class AException : public IStringable
{
public:

	AException(AString Description = AString());

	virtual AString ToString();

protected:

	AString Description = AString();
};
