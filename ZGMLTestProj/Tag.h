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
	shared_ptr<Tag> nestedTag;
public:
	Tag(vector<TagAttribute> attributes):attributes(attributes) {};
	void SetNestedTag(Tag &tag)
	{
		nestedTag = make_shared<Tag>(tag);
	}
	Tag& GetNestedTag()
	{
		return *nestedTag;
	}
};

