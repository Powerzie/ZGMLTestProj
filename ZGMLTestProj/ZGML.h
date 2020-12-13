#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <regex>
#include"tag.h"
#include"ZGMLReader.h"

using namespace std;

class ZGML
{
private:
	vector<shared_ptr<Tag>> tags;
	shared_ptr<ZGMLReader> fileReader;
public:
	ZGML()
	{
		fileReader = make_shared<ZGMLReader>();
		tags = fileReader->GetTags();
		//Tags = fileReader->
	}
	void ShowTags()
	{
		shared_ptr<Tag> nestedTag;
		for (int a = 0;a < (int)(tags.capacity());a++)
		{
			cout << tags[a]->GetTagName();
			nestedTag = make_shared<Tag>(tags[a]->GetNestedTag());
				while (nestedTag!=nullptr)
				{
					if (!nestedTag->isHaveNestedEmpty())
					{
						nestedTag = make_shared<Tag>(nestedTag->GetNestedTag());
						cout << nestedTag->GetTagName();
					}
				}
		}
	}
	
};

