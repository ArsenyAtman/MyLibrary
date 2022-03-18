#pragma once

#include <stdio.h>

#include "String.h"
#include "Array.h"


enum class EFileMode : char
{
	ReadOnly,
	WriteOnly,
	ReadWrite,
	ClearAndWriteOnly,
	ClearAndReadWrite,
	Closed
};

class AFile
{

public:

	AFile();
	AFile(const AString& Path, const EFileMode Mode);
	AFile(const AFile& File);
	AFile(AFile&& File);

	virtual ~AFile();

	AFile& operator = (const AFile& File);
	AFile& operator = (AFile&& File);

	bool Open(const AString& Path, const EFileMode Mode);

	void Close();

	int WriteBytes(const TArray<char>& Bytes);

	TArray<char> ReadBytes(const int CountOfBytes) const;

	EFileMode GetFileMode() const;

	long GetFileSize() const;

	const AString& GetFilePath() const;

	int SetReadWritePosition(const int Position) const;

	int GetReadWritePosition() const;

	static bool FileExists(const AString& Path);

private:

	FILE* FilePointer = nullptr;
	EFileMode FileMode = EFileMode::Closed;
	AString FilePath = AString();

};
