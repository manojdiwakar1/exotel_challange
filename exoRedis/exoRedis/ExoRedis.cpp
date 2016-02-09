
#include "ExoRedis.h"

exoRadis::exoRadis(const std::string& filePath) : configManager(filePath)
{
}


exoRadis::~exoRadis()
{	
} 

void exoRadis::ProcessCMD(std::string& inputCMD)
{
	comndProcessor.ProcessCMD(inputCMD);
}