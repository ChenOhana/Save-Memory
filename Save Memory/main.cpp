#include <windows.h>
#include <stdio.h>

int countLetter(PCHAR pBuffer, int size, LPCSTR letter); //return how many times a letter appears in string

int main()
{
	HANDLE hFile;
	LPSTR pBuffer;
	DWORD fileSize;
	HANDLE hMapFile;
	SYSTEM_INFO systemInfo;
	LPCSTR pFileName = "gibrish.bin";
	int count = 0;
	int remainder = 0;
	int filePointer = 0;
	int bufferNumber = 0;
	int memoryBufferSize = 0;

	GetSystemInfo(&systemInfo);
	memoryBufferSize = systemInfo.dwAllocationGranularity;

	hFile = CreateFileA(
		pFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	fileSize = GetFileSize(hFile, NULL);

	hMapFile = CreateFileMappingA(
		hFile,
		NULL,
		PAGE_READONLY,
		0,
		0,
		NULL);
	
	while (filePointer <= (fileSize - memoryBufferSize)) 
	{
		pBuffer = (LPSTR)MapViewOfFile(
			hMapFile,
			FILE_MAP_READ,
			0,
			filePointer,
			memoryBufferSize);

		count += countLetter(pBuffer, memoryBufferSize, "A");
		bufferNumber++;
		filePointer = memoryBufferSize * bufferNumber;
		UnmapViewOfFile(pBuffer);
		Sleep(100);
	}
	remainder = fileSize - filePointer;

	pBuffer = (LPSTR)MapViewOfFile(
		hMapFile,
		FILE_MAP_READ,
		0,
		filePointer,
		remainder);

	count += countLetter(pBuffer, remainder, "A");
	printf("%d\n", count);
	UnmapViewOfFile(pBuffer);
	CloseHandle(hMapFile);
	CloseHandle(hFile);

	system("pause");

	return 0;
}

/*
Function will return how many times a letter exists in string/buffer.
Input: buffer, size of buffer, letter to search
Output: count
*/

int countLetter(PCHAR pBuffer, int size, LPCSTR letter)
{
	int count = 0;

	for (int i = 0; i < size; i++) 
	{
		if (pBuffer[i] == *letter)
		{
			count++;
		}
	}

	return count;
}