#ifndef EXOREDIS_H
#define EXOREDIS_H

#include "ConfigManager.h"
#include "CommandProcessor.h"

#include <algorithm>

class exoRadis
{
public:
	exoRadis(const std::string& filePath);
	~exoRadis();
	void ProcessCMD(std::string& inputCMD);

private:  	
	void TokenizeCMD(const std::string& inputCMD);

	// object containment
	ConfigManager configManager;
	CommandProcessor comndProcessor;
};

#endif