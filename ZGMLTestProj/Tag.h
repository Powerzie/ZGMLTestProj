#pragma once
#include "TagAttribute.h"
#include<iostream>
#include <vector>

using std::string;
using std::shared_ptr;
using std::vector;


class Tag
{
private:
	vector<shared_ptr<TagAttribute>> attributes;
	shared_ptr<Tag> nestedTag = nullptr;
	string tagName;
public:
	Tag(string tagName, vector<shared_ptr<TagAttribute>> attributes):attributes(attributes), tagName(tagName) {};
	Tag(string tagName) :tagName(tagName) {};
	void SetNestedTag(Tag tag)
	{
		nestedTag = make_shared<Tag>(tag);
	}
	bool isHaveNestedEmpty()
	{
		return this->nestedTag == nullptr;
	}
	
	Tag& GetNestedTag()
	{
		return *nestedTag;
	}
	string GetTagName()const
	{
		return tagName;
	}
};

