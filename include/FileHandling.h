#pragma once
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>

struct StudentData {
public:
	std::string name;
	std::string email;
	std::string city;
};


void returnBody(std::vector<StudentData>& Vec, std::string filename);
