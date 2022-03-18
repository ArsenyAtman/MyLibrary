#include <cstring>

#include "File.h"

AFile::AFile()
{
	// ...
}

AFile::AFile(const AString& Path, const EFileMode Mode) : AFile()
{
	Open(Path, Mode);
}

AFile::AFile(const AFile& File)
{
	Open(File.GetFilePath(), File.GetFileMode());
}

AFile::AFile(AFile&& File)
{
	this->FilePath = File.FilePath;
	this->FilePointer = File.FilePointer;
	this->FileMode = File.FileMode;
}

AFile::~AFile()
{
	Close();
}

AFile& AFile::operator = (const AFile& File)
{
	Open(File.GetFilePath(), File.GetFileMode());

	return *this;
}

AFile& AFile::operator = (AFile&& File)
{
	this->FilePath = File.FilePath;
	this->FilePointer = File.FilePointer;
	this->FileMode = File.FileMode;

	return *this;
}

bool AFile::Open(const AString& Path, const EFileMode Mode)
{
	Close();

	switch (Mode)
	{
	case EFileMode::ReadOnly:
		fopen_s(&FilePointer, Path, "rb");
		break;

	case EFileMode::WriteOnly:
		fopen_s(&FilePointer, Path, "ab");
		break;

	case EFileMode::ReadWrite:
		fopen_s(&FilePointer, Path, "ab+");
		break;

	case EFileMode::ClearAndWriteOnly:
		fopen_s(&FilePointer, Path, "wb");
		break;

	case EFileMode::ClearAndReadWrite:
		fopen_s(&FilePointer, Path, "wb+");
		break;
	}

	if (FilePointer)
	{
		SetReadWritePosition(0);
		FileMode = Mode;
		FilePath = Path;
	}

	return FilePointer;
}

void AFile::Close()
{
	if (FilePointer != nullptr)
	{
		SetReadWritePosition(0);
		fclose(FilePointer);
		FilePointer = nullptr;
		FileMode = EFileMode::Closed;
		FilePath = "";
	}
}

int AFile::WriteBytes(const TArray<char>& Bytes)
{
	char* Buffer = new char[Bytes.GetLength()];
	for (int i = Bytes.GetLength() - 1; i >= 0; --i)
	{
		Buffer[i] = Bytes[i];
	}
	int Result = fwrite(Buffer, sizeof(char), Bytes.GetLength(), FilePointer);
	delete[] Buffer;
	return Result;
}

TArray<char> AFile::ReadBytes(const int CountOfBytes) const
{
	char* Buffer = new char[CountOfBytes];
	int Result = fread(Buffer, sizeof(char), CountOfBytes, FilePointer);
	TArray<char> Bytes = TArray<char>(Result);
	for (int i = 0; i < Result; ++i)
	{
		Bytes.Add(Buffer[i]);
	}
	delete[] Buffer;
	return Bytes;
}

EFileMode AFile::GetFileMode() const
{
	return FileMode;
}

long AFile::GetFileSize() const
{
	int CurrentPosition = ftell(FilePointer);
	fseek(FilePointer, 0, SEEK_END);
	int FileSize = ftell(FilePointer);
	fseek(FilePointer, CurrentPosition, SEEK_SET);
	return FileSize;
}

const AString& AFile::GetFilePath() const
{
	return FilePath;
}

int AFile::SetReadWritePosition(int Position) const
{
	return fseek(FilePointer, Position, SEEK_SET);
}

int AFile::GetReadWritePosition() const
{
	if (FilePointer != nullptr)
	{
		return ftell(FilePointer);
	}
	else
	{
		return -1;
	}
}

bool AFile::FileExists(const AString& Path)
{
	FILE* TestFile = nullptr;
	fopen_s(&TestFile, Path, "r");
	if (TestFile != nullptr)
	{
		fclose(TestFile);
		return true;
	}
	else
	{
		return false;
	}
}
