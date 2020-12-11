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
public:
	Tag(vector<TagAttribute> attributes):attributes(attributes) {};
};

