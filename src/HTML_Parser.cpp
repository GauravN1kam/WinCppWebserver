#include "../include/HTML_Parser.h"

void HTMLToString(std::string filename, std::string& res) {
	std::fstream file;
	file.open(filename);
	std::string line;
	while (std::getline(file, line))
	{
		res += line;
	}
}