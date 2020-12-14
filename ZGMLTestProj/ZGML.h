#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"tag.h"
#include"ZGMLReader.h"

using std::shared_ptr;
using std::cout;
class ZGML
{
private:
	vector<Tag> tags;
	shared_ptr<ZGMLReader> fileReader;
	string requests;
public:
	ZGML();
	
	void ShowTags(vector<Tag> tags);
	
	int SearchRequestedValues(vector<Tag> tags, int startFrom = 0);
	
	void RunProgram();
	
	
};

