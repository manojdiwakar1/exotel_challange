
#include "ExoRedis.h"

exoRadis::exoRadis(const std::string& filePath) 
{
	configManager = ConfigManager::getInstance();
	configManager->SetFilePath(filePath);
}


exoRadis::~exoRadis()
{	
} 

void exoRadis::ProcessCMD(const std::string& inputCMD)
{
	if (comndProcessor.ProcessCMD(inputCMD))
	{
		executeCMD(inputCMD);
	}
	else
	{
	}
}

void exoRadis::executeCMD(const std::string& inputCMD)
{	
	comndProcessor.executeCMD(inputCMD);
}

void exoRadis::LoadDataFromFile()
{
	configManager->ReadFromFile();
}