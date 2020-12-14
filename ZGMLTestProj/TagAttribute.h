#pragma once
#include<iostream>

using std::string;
class TagAttribute
{
private:
	string attributeName; 
	string attributeValue;
public:
	TagAttribute(string attributeName, string attributeValue):
		attributeName(attributeName), 
		attributeValue(attributeValue) 
	{}
	
	const string& GetAttributeTagName()const;
	
	const string& GetAttributeValue()const;
	

};

