#include <iostream>
#include <signal.h>

#include "ExoRedis.h"

int main(int argc, char* argv[])
{
   // argument validation 
	if (argc < 2) 
	{
		std::cerr << "Usage: " << argv[0] << " FILE_PATH" << std::endl;
		return 1;
	}

	std::string filePath(argv[1]); 
	exoRadis exor(filePath);
	exor.LoadDataFromFile();

	std::string lcmd;

	while (	std::getline(std::cin, lcmd) )
	{
		if (!lcmd.empty())
		{
			exor.ProcessCMD(lcmd);
		}
		else
		{
			break;
		}
	}

	return 0;
}