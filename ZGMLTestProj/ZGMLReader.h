#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class ZGMLReader
{
private:
	string textFilePath ="ZGML.txt";
public:
	void ReadZGMLFile()
	{
		ifstream stream;
		try
		{
			stream.open(textFilePath);
			
			string ZGMLFileText;
			while (!stream.eof())
			{ 
				ZGMLFileText = "";
				stream>>ZGMLFileText;
				ZGMLFileText += '\n';
				cout << ZGMLFileText;
			}
		}
		catch (exception ex)
		{
			cout << ex.what();
		}
		stream.close();
	}

};

