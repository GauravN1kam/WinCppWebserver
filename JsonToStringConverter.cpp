#include"JsonDataHandler.h"


std::vector<std::string> JSONToString(std::string filename){
	std::string line;

	std::istringstream file(filename);
	std::string buffer;
	std::vector<std::string>JSONDATAVec;
	while (std::getline(file, line))
	{
		if (line.find("{") != std::string::npos)
		{
			while (std::getline(file, line))
			{
				if (line.find("}") != std::string::npos)
				{
					JSONDATAVec.push_back(buffer);
					buffer = "";
					break;
				}
				buffer += line + "\n";
			}
		}
	}
	return JSONDATAVec;
}