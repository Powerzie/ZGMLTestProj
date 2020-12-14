#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"TagAttribute.h"
#include"Tag.h"

using std::vector;
using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::endl;
using std::ifstream;
using std::exception;

class ZGMLReader
{
private:
	string textFilePath;
	string fileTags;
	string fileRequests;
	int requestsQuantity;
	int tagRows;

	const int maxRowWidth = 200;
	const int maxRequestWidth = 200;

	string GetTagNameFromString(int tagStart);
	
	vector<TagAttribute> getTagAttributes(int tagStart);
	
	int SearchTagEnd(string tagName);
	

public:
	vector<Tag> GetTags();
	

	ZGMLReader();
	
	
	void ReadZGMLFile();
	
	const string GetFileRequests()const;
	
	

};

