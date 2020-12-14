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
	bool IsNestedTag;
public:
	Tag(string tagName, vector<TagAttribute> attributes, bool isNested = false) :attributes(attributes), tagName(tagName), IsNestedTag(isNested){};
	Tag(string tagName) :tagName(tagName) {};
	void AddNestedTag(Tag tag)
	{
		nestedTags.push_back(tag);
	}
	bool IsNestedTagsEmpty()
	{
		return nestedTags.size() < 1;
	}
	void SetIsNestedTag(bool b)
	{
		IsNestedTag = b;
	}
	const bool GetIsNestedTag()const
	{
		return IsNestedTag;
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

