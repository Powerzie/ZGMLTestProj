#pragma once
#include "TagAttribute.h"
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
	void AddNestedTag(Tag tag);
	
	bool IsNestedTagsEmpty();
	
	void SetIsNestedTag(bool b);
	
	const bool GetIsNestedTag()const;
	
	vector<Tag> GetNestedTags();


	string GetTagName()const;

	vector<TagAttribute> GetTagAttributes();
	
};

