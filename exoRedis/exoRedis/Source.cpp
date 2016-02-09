#include <iostream>
#include "ExoRedis.h"

int main(int argc, char* argv[])
{
   // argument validation 
	if (argc < 2) 
	{
		// Tell the user how to run the program
		std::cerr << "Usage: " << argv[0] << " FILE_PATH" << std::endl;
		return 1;
	}

	std::string filePath(argv[1]); 
	exoRadis exor(filePath);

	std::string lcmd;
	std::getline(std::cin, lcmd);
	std::cout << " cmd : " << lcmd << "\n";

	exor.ProcessCMD(lcmd);

	return 0;
}