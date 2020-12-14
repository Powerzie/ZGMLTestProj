#include "ZGML.h"

ZGML::ZGML()
{
	fileReader = make_shared<ZGMLReader>();
	requests = fileReader->GetFileRequests();
}

void ZGML::ShowTags(vector<Tag> tags)
{
	for (int a = 0;a < (int)(tags.capacity());a++)
	{
		if (!tags[a].IsNestedTagsEmpty())
		{
			ShowTags(tags[a].GetNestedTags());
		}
		auto attributes = tags[a].GetTagAttributes();
		for (int b = 0;b < (int)(attributes.capacity());b++)
		{
			cout << attributes[b].GetAttributeTagName() + " " + attributes[b].GetAttributeValue() << endl;
		}
	}
}

int ZGML::SearchRequestedValues(vector<Tag> tags, int startFrom)
{
	string currentRequestWord = "";
	int currentTag = 0;
	string tmpRequestWord = "";
	for (int a = startFrom;a <= requests.length();a++)
	{
		if (requests[a] == '.')
		{
			a++;
			currentTag = 0;
			for (;currentTag < tags.size();++currentTag)
			{
				if (tags[currentTag].GetTagName() == currentRequestWord)
				{
					if (!tags[currentTag].IsNestedTagsEmpty())
					{
						a = SearchRequestedValues(tags[currentTag].GetNestedTags(), a);

						break;
					}
				}
			}
			currentTag = 0;
			currentRequestWord = "";
		}
		if (requests[a] == '~')
		{
			bool isFinded = false;
			a++;
			tmpRequestWord = currentRequestWord;

			currentRequestWord = "";
			while (requests[a] != '\n' && a != requests.length())
			{
				currentRequestWord += requests[a];
				a++;
			}
			a += 1;
			for (int f = 0;f < tags.size();f++)
			{
				if (tags[f].GetTagName() == tmpRequestWord)
				{
					auto attributes = tags[f].GetTagAttributes();
					for (int c = 0;c < attributes.size();c++)
					{
						if (attributes[c].GetAttributeTagName() == currentRequestWord)
						{
							cout << attributes[c].GetAttributeValue() << endl;
							isFinded = true;
							if (tags[f].GetIsNestedTag())
								return a;
							else
								break;

						}
						else
							if (c == (attributes.size() - 1))
							{
								cout << "Not Found!" << endl;
								break;
							}
					}

				}

			}
			if (!isFinded)
				cout << "Not Found!" << endl;

			currentRequestWord = "";
		}

		currentRequestWord += requests[a];
	}

}

void ZGML::RunProgram()
{
	tags = fileReader->GetTags();
	SearchRequestedValues(tags);
}
