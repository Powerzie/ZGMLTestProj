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
	vector<TagAttribute> attributes;
	vector<Tag> nestedTags ;
	string tagName;
public:
	Tag(string tagName, vector<TagAttribute> attributes):attributes(attributes), tagName(tagName) {};
	Tag(string tagName) :tagName(tagName) {};
	void AddNestedTag(Tag tag)
	{
		nestedTags.push_back(tag);
	}
	bool IsNestedTagsEmpty()
	{
		return nestedTags.size() < 1;
	}
	
	vector<Tag> GetNestedTags()
	{
		return nestedTags;
	}
	string GetTagName()const
	{
		return tagName;
	}
	vector<TagAttribute> GetTagAttributes()
	{
		return attributes;
	}
};

