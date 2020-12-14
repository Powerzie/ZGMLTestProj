#pragma once
#include<iostream>

using std::string;
using std::shared_ptr;
using std::make_shared;

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
	
	const string& GetAttributeTagName()const
	{
		return attributeName;
	}
	const string& GetAttributeValue()const
	{
	    return attributeValue;
	}

};

