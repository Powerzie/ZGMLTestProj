#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <regex>
#include"TagAttribute.h"
#include"Tag.h"
using namespace std;
class ZGMLReader
{
private:
	string textFilePath;
	string fileTags;
	string fileRequests;
	int requestsQuantity;
	int tagRows;

	const int maxRowWidth = 200;
	const int maxRequestWidth = 200;

	string GetTagNameFromString(int tagStart)
	{
		string tagName = "";
		for (size_t a = tagStart;a<fileTags.length();a++)
		{
			if (fileTags[a] == ' ')
				return tagName;
			tagName += fileTags[a];
		}
	}
	vector<TagAttribute> getTagAttributes(int tagStart)
	{
		vector<TagAttribute> attributes;
		string attributeName = "";
		string attributeValue = "";
		for (int a = tagStart+1;fileTags[a]!='>';a++)
		{
			if (fileTags[a] == ' ')
			{
				if (fileTags[a+1] == '=')
				{
					a += 4;
					while (fileTags[a] != '"')
					{
						attributeValue += fileTags[a];
						a++;
					}
						attributes.push_back(TagAttribute(attributeName, attributeValue));
					attributeName = "";
				}
				else
				{
					attributeName = "";
					continue;
				}
			}
			else
			
			attributeName += fileTags[a];
		}
	
		return attributes;
	}
	int SearchTagEnd(string tagName)
	{
		return fileTags.find_last_of("</" + tagName + '>');
	}

public:
	vector<Tag> GetTags()
	{
		int  tagStart = 0;
		int  tagEnd = 0;
		int lastTagEnd = 0;
		int tagDescriptionEnd = 0;
		int lastTagescriptionEnd = 0;
		string currentTagName = "";
		vector<Tag> tags;
		string str = fileTags;

		while (tagStart != -1)
		{
			if (tagStart > str.length())
				return tags;

			str = str.substr(tagStart);

			if (str[1] == '/')
			{
				tagStart = 0;
				do
				{
					tagStart++;
				} while (str[tagStart] != '>');
				str = str.substr(++tagStart);
				tagStart = str.find_first_of('<');
				continue;
			}
			//query = fileRequests.substr(from, fileRequests.length());
			tagStart = str.find_first_of('<');

			currentTagName = GetTagNameFromString(tagDescriptionEnd + 1);

			tagEnd = SearchTagEnd("</" + currentTagName + '>');


			tagDescriptionEnd = (str.find_first_of('>')) + 2;
			
			if (tagEnd > lastTagEnd)
			{
				tags.push_back(Tag(currentTagName, getTagAttributes(tagStart)));
			}
			else
			{
				auto attr = getTagAttributes(lastTagescriptionEnd);
				tags.back().AddNestedTag(Tag(currentTagName, attr));
			}
			lastTagescriptionEnd = tagDescriptionEnd;
			lastTagEnd = tagEnd;
			tagStart = tagDescriptionEnd;

		}
		return tags;
	}//Building tags from fileTagsString

	ZGMLReader()
	{
		textFilePath = "ZGML.txt";
		fileTags = "";
		fileRequests = "";
		requestsQuantity = 0;
		tagRows = 0;
		ReadZGMLFile();
	}
	
	void ReadZGMLFile()
	{
		ifstream stream;
		try
		{
			stream.open(textFilePath);

			int currentRow = 0;
			int rowSize = 0;
			char c=' ';

			while (stream.get(c))
			{ 
				rowSize++;

				if (c == '\n')
				{
					rowSize = 0;
					++currentRow;
					if (currentRow == 1)
					{
						if (tagRows >= 1 && tagRows <= 20 && requestsQuantity >= 1 && requestsQuantity <= 20)
							continue;
						else
						{
							cout << "Wrong amount of rows or requests!!!\n";
							return;
						}
					}
				}
				if (currentRow == 0 )
				{
					if(c!=' ')
					tagRows == 0 ? tagRows = c-'0' : requestsQuantity = c - '0';


					continue;
			    }

				if (currentRow <= tagRows)
				{
					fileTags += c;
					if (rowSize > maxRowWidth)
					{
						cout << "Tag row width must be less than 200\n";
						return;
					}

				}
				else
				{
					fileRequests += c;
					if (rowSize > maxRequestWidth)
					{
						cout << "Request width must be less than 200\n";
						return;
					}

				}

			}
			
		}
		catch (exception ex)
		{
			cout << ex.what();
		}
		stream.close();
		//cout << FileTags<<endl<<FileRequests;
	}
	void SearchValues()
	{
		
		
	/*	for (int a = 0;a < requestsQuantity;a++)
		{
		}*/
	}
	string GetFileRequests()
	{
		return fileRequests;
	}
	

};

