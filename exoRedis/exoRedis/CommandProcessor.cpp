
#include "CommandProcessor.h"

#include <iostream>
#include <cmath>

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
		executeZaddCmd(inputCMD);
	}
	else if (!cmd.compare("ZCARD"))
	{
		executeZcardCmd(inputCMD);
	}
	else if (!cmd.compare("ZCOUNT"))
	{
		executeZcountCmd(inputCMD);
	}
	else if (!cmd.compare("ZRANGE"))
	{
		executeZrangeCmd(inputCMD);
	}
}

void CommandProcessor::executeGetCmd(const std::string& inputCMD)
{	
	TokanizeCmd(inputCMD);

	//using mutimap
	std::multimap<int, std::string> mMapVal = configManager->getKeyValue(cmdTokens.at(1));
	for (auto& av : mMapVal)
	{
		std::cout << "\n value : " << av.second<<"\n";
		break;
	}
}

void CommandProcessor::executeSetCmd(const std::string& inputCMD)
{
	TokanizeCmd(inputCMD);	  	
	configManager->updateMap(cmdTokens.at(1), cmdTokens.at(2));
}

void CommandProcessor::executeSaveCmd()
{
	std::string mapString = configManager->getMap();
	configManager->WriteToFile(mapString);   
}


void CommandProcessor::executeZaddCmd(const std::string& inputCMD)
{
	TokanizeCmd(inputCMD);

	if (configManager->getKey(cmdTokens.at(1)))
	{
		std::multimap<int, std::string> mapValueString;
		for (unsigned int i = 2; i < cmdTokens.size(); i += 2)
		{
			int key = std::stoi(cmdTokens[i]);
			std::pair<int, std::string> mapPair(key, cmdTokens[i + 1]);
			mapValueString.insert(mapPair);
		}

		configManager->updateMap(cmdTokens.at(1), mapValueString);
	}
	else
	{
		std::cerr << "\n Key : " << cmdTokens.at(1) << " not found \n";
	}
	
}

void CommandProcessor::executeZcardCmd(const std::string& inputCMD)
{ 
	TokanizeCmd(inputCMD);

	if (configManager->getKey(cmdTokens.at(1)))
	{
		std::multimap<int, std::string> mapValueString = configManager->getKeyValue(cmdTokens.at(1));
		std::cout << "\n " << mapValueString.size() << "\n";
	}
	else
	{
		std::cerr << "\n Key : " << cmdTokens.at(1) << " not found \n";
	}
}

void CommandProcessor::executeZrangeCmd(const std::string& inputCMD)
{
	TokanizeCmd(inputCMD);
	std::vector<std::string> scoreValue = configManager->KeyRange(cmdTokens.at(1), cmdTokens.at(2), cmdTokens.at(3));

	for (auto & sv : scoreValue)
	{
		std::cout << "\n " << sv;
	}
	std::cout << "\n ";
}

void CommandProcessor::executeZcountCmd(const std::string& inputCMD)
{
	TokanizeCmd(inputCMD);
	int keyCount = 0;

	if (!cmdTokens.at(2).compare("-inf") && cmdTokens.at(3).compare("-inf"))
	{
		std::string cmd = "ZCARD " + cmdTokens.at(1);
		executeZcardCmd(cmd);
	}
	if (IsValidInt(cmdTokens.at(2).c_str()) && IsValidInt(cmdTokens.at(3).c_str()))
	{
		keyCount = configManager->KeyCount(cmdTokens.at(1), cmdTokens.at(2), cmdTokens.at(3));
		std::cout << "\n " << keyCount << "\n";
	}
}

bool CommandProcessor::IsValidInt(const char* x)
{
	bool Checked = true;
	int i = 0;

	if (x[i] == '-' || x[i] == '+')
	{
		i++;
	}

	do
	{
		if (isdigit(x[i]))
		{
			i++;
			Checked = true;
		}
		else
		{
			i++;
			Checked = false;
			break;
		}
	} while (x[i] != '\0');

	return Checked;	 
}


void CommandProcessor::TokanizeCmd(const std::string& inputCMD, const std::string& delimiters)
{
	cmdTokens.clear();

	// Skip delimiters at beginning.
	std::string::size_type lastPos = inputCMD.find_first_not_of(delimiters, 0);

	std::string::size_type pos = inputCMD.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		cmdTokens.push_back(inputCMD.substr(lastPos, pos - lastPos));

		lastPos = inputCMD.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = inputCMD.find_first_of(delimiters, lastPos);
	}
}
