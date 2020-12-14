#include "ZGMLReader.h"

string ZGMLReader::GetTagNameFromString(int tagStart)
{
	string tagName = "";
	for (size_t a = tagStart;a < fileTags.length();a++)
	{
		if (fileTags[a] == ' ')
			return tagName;
		tagName += fileTags[a];
	}
	return "";
}

vector<TagAttribute> ZGMLReader::getTagAttributes(int tagStart)
{
	vector<TagAttribute> attributes;
	string attributeName = "";
	string attributeValue = "";
	for (int a = tagStart + 1;fileTags[a] != '>';a++)
	{
		if (fileTags[a] == ' ')
		{
			if (fileTags[a + 1] == '=')
			{
				a += 4;
				while (fileTags[a] != '"')
				{
					attributeValue += fileTags[a];
					a++;
				}
				attributes.push_back(TagAttribute(attributeName, attributeValue));
				attributeName = "";
				attributeValue = "";
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

int ZGMLReader::SearchTagEnd(string tagName)
{
	return (int)(fileTags.find(tagName));

}

vector<Tag> ZGMLReader::GetTags()
{
	int  tagStart = 0;
	int  tagEnd = 0;
	int lastTagEnd = 0;
	int tagDescriptionEnd = 0;
	int lastTagDescriptionEnd = 0;
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

		currentTagName = GetTagNameFromString((fileTags.length() + 1) - str.length());

		tagEnd = SearchTagEnd("</" + currentTagName + '>');


		tagDescriptionEnd = (str.find_first_of('>')) + 2;

		if (tagEnd > lastTagEnd)
		{
			tags.push_back(Tag(currentTagName, getTagAttributes((fileTags.length() + 1) - str.length())));
		}
		else
		{
			auto attr = getTagAttributes((fileTags.length() + 1) - str.length());
			tags.back().AddNestedTag(Tag(currentTagName, attr, true));
		}
		lastTagDescriptionEnd = tagDescriptionEnd;
		lastTagEnd < tagEnd ? lastTagEnd = tagEnd : lastTagEnd;
		tagStart = tagDescriptionEnd;

	}
	return tags;
}//Building tags from fileTagsString

ZGMLReader::ZGMLReader()
{
	textFilePath = "ZGML.txt";
	fileTags = "";
	fileRequests = "";
	requestsQuantity = 0;
	tagRows = 0;
	ReadZGMLFile();
}

void ZGMLReader::ReadZGMLFile()
{
	ifstream stream;
	try
	{
		stream.open(textFilePath);

		int currentRow = 0;
		int rowSize = 0;
		char c = ' ';

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
						stream.close();
						return;
					}
				}
				if (currentRow == tagRows + 1)
					continue;

			}
			if (currentRow == 0)
			{
				bool isSecondNumber = false;
				while (c != '\n')
				{
					if (c == ' ')
					{
						isSecondNumber = true;
						stream.get(c);
						continue;
					}
					!isSecondNumber ? tagRows = tagRows * 10 + (c - '0') : requestsQuantity = requestsQuantity * 10 + (c - '0');
					stream.get(c);

				}
				currentRow++;
				continue;
			}

			if (currentRow <= tagRows)
			{
				fileTags += c;
				if (rowSize > maxRowWidth)
				{
					cout << "Tag row width must be less than 200\n";
					stream.close();
					return;
				}

			}
			else
			{
				fileRequests += c;
				if (rowSize > maxRequestWidth)
				{
					cout << "Request width must be less than 200\n";
					stream.close();
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
}
const string ZGMLReader::GetFileRequests() const
{
	return fileRequests;
}