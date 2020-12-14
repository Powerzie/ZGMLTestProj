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
	int SearchRequestedValues(vector<Tag> tags,int startFrom=0)
	{
		string currentRequestWord = "";
		int currentTag = 0;
		for (int a = startFrom;a < requests.length();a++)
		{
			if (requests[a] == '.' )
			{
				a++;
				currentTag = 0;
				for (;currentTag < tags.size();++currentTag)
				{
					if (tags[currentTag].GetTagName() == currentRequestWord)
					{
						if (!tags[currentTag].IsNestedTagsEmpty())
						{
						a =	SearchRequestedValues(tags[currentTag].GetNestedTags(), a);
						
						break;
						}
						else
							cout << "Not Found!"<<endl;
					}
				}
				currentTag = 0;
				currentRequestWord = "";
		    }
			if (requests[a] == '~')
			{
				a++;
				if (tags[currentTag].GetTagName() == currentRequestWord)
				{
					currentRequestWord = "";
					while (requests[a] != '\n' && a != requests.length())
					{
						currentRequestWord += requests[a];
						a++;
			     	}
					a += 1;

					auto attributes = tags[currentTag].GetTagAttributes();
					for (int c = 0;c < attributes.size();c++)
					{
						if (attributes[c].GetTagName() == currentRequestWord)
						{
							cout << attributes[c].GetAttributeValue()<<endl;
							if (tags[currentTag].GetIsNestedTag())
								return a;
							else
								break;
						}
						else
							if (c == attributes.size()-1)
							{
								cout << "Not Found!" << endl;
							}
					}
					
				}
				currentRequestWord = "";
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

