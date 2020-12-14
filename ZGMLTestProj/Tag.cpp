#include "Tag.h"

void Tag::AddNestedTag(Tag tag)
{
	nestedTags.push_back(tag);
}

bool Tag::IsNestedTagsEmpty()
{
	return nestedTags.size() < 1;
}

void Tag::SetIsNestedTag(bool b)
{
	IsNestedTag = b;
}

const bool Tag::GetIsNestedTag() const
{
	return IsNestedTag;
}

vector<Tag> Tag::GetNestedTags()
{
	return nestedTags;
}

string Tag::GetTagName() const
{
	return tagName;
}

vector<TagAttribute> Tag::GetTagAttributes()
{
	return attributes;
}

