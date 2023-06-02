#include "src/hash.h"
#include <fstream>
#include <filesystem>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	int argc = __argc;
	char** argv = __argv;
	std::vector<std::filesystem::directory_entry> files;
	for (int i = 0; i < argc-1; ++i)
	{
		if (!strcmp(argv[i], "--file"))
		{
			std::filesystem::directory_entry f(argv[i + 1]);
			files.push_back(f);
		}

		if (!strcmp(argv[i],"--directory"))
		{
			for (const auto &f:std::filesystem::recursive_directory_iterator(argv[i+1]))
			{
				if (!f.is_directory())
				{
					files.push_back(f);
				}
			}
		}
	}

	size_t size = 0;
	for (const auto& f : files)
	{
		size += f.file_size();
	}

	char* buffer = new char[size];

	size_t index = 0;

	for(const auto &f : files)
	{
		std::ifstream fin(f.path(), std::ios::in | std::ios::binary);
		if (!fin.is_open())
		{
			break;
		}

		size_t s = f.file_size();
		fin.read(buffer + index,s);
		
		index += s;
		fin.close();
	}

	key k = { 0x5f,0x5f,0x4c,0x79,0x75,0x74,0x61,0x79,0x61,0x5a,0x58,0x43,0x42,0x72,0x69,0x67,0x61,0x64,0x61,0x5f,0x4b,0x4b,0x53,0x4f,0x2d,0x30,0x32,0x2d,0x32,0x32,0x5f,0x5f };
	Gost kuznechik(k);

	block result = kuznechik.Hash(buffer, size);
	std::string output = result.ToString();

	size_t len = output.size() + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	if (hMem)
	{
		memcpy(GlobalLock(hMem), output.c_str(), len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}

	delete[] buffer;

	return EXIT_SUCCESS;
}