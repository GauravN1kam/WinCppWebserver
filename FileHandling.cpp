#include "FileHandling.h"
#include "JsonDataHandler.h"


void returnBody(std::vector<StudentData>& studentDataVec, std::string filename)
{
	std::vector<std::string>JSONDATAVec = JSONToString(filename);
	for (const auto& str : JSONDATAVec)
	{
		std::istringstream iss(str);
		int TheColon = 0;
		StudentData stdata;
		for (std::string payload; std::getline(iss, payload);)
		{
			std::string key = "";
			std::string value = "";
			TheColon = 0;
			for (int i = 0; i < payload.size(); i++)
			{
				if (payload[i] == ' ')
				{
					continue;
				}
				else if (payload[i] == ':') {
					TheColon = 1;
					continue;
				}
				else {
					switch (TheColon)
					{
					case 0: if (payload[i] != '"' && payload[i] != ',')
					{
						key += payload[i];
					}
						  break;
					case 1:
						if (payload[i] != '"' && payload[i] != ',')
						{
							value += payload[i];
						}
						break;
					default:
						break;
					}
				}
			}
			
			if (key == "Name")
			{
				stdata.name = value;
			}
			else if (key == "City")
			{
				stdata.city = value;
			}
			else {
				stdata.email = value;
			}
		}
		studentDataVec.push_back(stdata);
	}
}