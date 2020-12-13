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
	vector<Tag> tags;
	shared_ptr<ZGMLReader> fileReader;
	string requests;
public:
	ZGML()
	{
		fileReader = make_shared<ZGMLReader>();
		requests = fileReader->GetFileRequests();
		//Tags = fileReader->
	}
	void ShowTags(vector<Tag> tags)
	{
		for (int a = 0;a < (int)(tags.capacity());a++)
		{
			if(!tags[a].IsNestedTagsEmpty())
			{
				ShowTags(tags[a].GetNestedTags());
			}
			auto attributes = tags[a].GetTagAttributes();
			for (int b = 0;b < (int)(attributes.capacity());b++)
			{
				cout << attributes[b].GetTagName() +" "+ attributes[b].GetAttributeValue() << endl;
			}
		}
	}
	void SearchRequestedValues(vector<Tag> tags,int startFrom=1)
	{
		string currentRequestWord = "";
		int currentTag = 0;
		for (int a = startFrom;a < requests.length();a++)
		{
			if(requests[a]=='.')
			{
				for (;currentTag < tags.size();currentTag++)
				{
					if (tags[currentTag].GetTagName() == currentRequestWord)
					{
						if (!tags[currentTag].IsNestedTagsEmpty())
						{
							SearchRequestedValues(tags[currentTag].GetNestedTags(), ++a);
						}
						else
							cout << "Not Found!";
					}
				}
		    }
			if (requests[a] == '~')
			{
				currentRequestWord = "";
				while (requests[a] != '\n')
				{
					a++;
					currentRequestWord += requests[a];
				}

				auto attributes = tags[currentTag].GetTagAttributes();
				for (int c = 0;c < attributes.size();c++)
				{
					if (attributes[c].GetTagName() == currentRequestWord)
					{
						cout << attributes[c].GetAttributeValue();
					}
				}
				cout << "Not Found!";
			}

			

			currentRequestWord += requests[a];
		}

	}
	void RunProgram()
	{
		tags = fileReader->GetTags();
		//ShowTags(tags);
		SearchRequestedValues(tags);
	}
	
};

