
#include "CommandProcessor.h"

CommandProcessor::CommandProcessor()
{	 
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

void CommandProcessor::ProcessCMD(std::string& inputCMD)
{
	command = inputCMD.substr(0, inputCMD.find_first_of(" "));
	bool res = validateCMD(command);
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