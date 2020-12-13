#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <regex>
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

	void BuildTags()
	{
		string query = "";
		int tagStart = 0;
		int  tagEnd = 0;

		while (tagEnd != -1)
		{
			//query = fileRequests.substr(from, fileRequests.length());
			tagStart = fileTags.find_first_of({ '<' });
			cout << "</" + GetTagNameFromString(tagStart + 1) + '>';
			tagEnd = fileTags.find_last_of("</"+ GetTagNameFromString(tagStart+1)+'>');
			tagStart += tagEnd + 1;
			cout << tagEnd;
		}


	}//Building tags from fileTagsString
	string GetTagNameFromString(int tagStart)
	{
		string tagName = "";
		for (int a = tagStart;a < fileTags.length();a++)
		{
			if (fileTags[a] == ' ')
				return tagName;
			tagName += fileTags[a];
		}
	}

public:
	ZGMLReader()
	{
		textFilePath = "ZGML.txt";
		fileTags = "";
		fileRequests = "";
		requestsQuantity = 0;
		tagRows = 0;
	}
	void RunProg()
	{
		ReadZGMLFile();
		BuildTags();
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
	

};

