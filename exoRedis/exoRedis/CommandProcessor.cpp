
#include "CommandProcessor.h"

#include <iostream>

CommandProcessor::CommandProcessor()
{	
	ConstructCmd();
	configManager = ConfigManager::getInstance();
}

void CommandProcessor::ConstructCmd()
{
	cmd.push_back("GET");
	cmd.push_back("SET");
	cmd.push_back("SAVE");
	cmd.push_back("ZADD");
	cmd.push_back("ZCARD");
	cmd.push_back("ZCOUNT");
	cmd.push_back("ZRANGE");
}

bool CommandProcessor::ProcessCMD(const std::string& inputCMD)
{
	command = GetCMD(inputCMD);
	bool res = validateCMD(command);
	return res;
}

bool CommandProcessor::validateCMD(const std::string& inputCMD)
{
	bool res = false;
	std::vector<std::string>::iterator it = std::find(cmd.begin(), cmd.end(), inputCMD);
	if (it != cmd.end())
	{
		res = true;
	}

	return res;
}

std::string CommandProcessor::GetCMD(const std::string& inputCMD)
{
	return (inputCMD.substr(0, inputCMD.find_first_of(" ")));
}

void CommandProcessor::executeCMD(const std::string& inputCMD)
{  
	std::string cmd = GetCMD(inputCMD);

	if (!cmd.compare("GET"))
	{
		executeGetCmd(inputCMD);
	}
	else if (!cmd.compare("SET"))
	{
		executeSetCmd(inputCMD);
	}
	else if (!cmd.compare("SAVE"))
	{
		executeSaveCmd();
	}
	else if (!cmd.compare("ZADD"))
	{
	}
	else if (!cmd.compare("ZCARD"))
	{
	}
	else if (!cmd.compare("ZCOUNT"))
	{
	}
	else if (!cmd.compare("ZRANGE"))
	{
	}
}

void CommandProcessor::executeGetCmd(const std::string& inputCMD)
{	
	TokanizeCmd(inputCMD);
}

void CommandProcessor::executeSetCmd(const std::string& inputCMD)
{
	TokanizeCmd(inputCMD);	  	
	configManager->updateMap(cmdTokens.at(1), cmdTokens.at(2));
}

void CommandProcessor::executeSaveCmd()
{
	std::vector< std::string> mapString = configManager->getMap();
	for (auto& strVec : mapString)
	{
		configManager->WriteToFile(strVec);
	}	   	
}

void CommandProcessor::TokanizeCmd(const std::string& inputCMD, const std::string& delimiters)
{
	cmdTokens.clear();

	// Skip delimiters at beginning.
	std::string::size_type lastPos = inputCMD.find_first_not_of(delimiters, 0);

	// Find first "non-delimiter".
	std::string::size_type pos = inputCMD.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		cmdTokens.push_back(inputCMD.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = inputCMD.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = inputCMD.find_first_of(delimiters, lastPos);
	}
}