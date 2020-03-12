// EclipseReaderCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

#include "EclipseReader.h"
using namespace std;
 

int main()
{
	{
//get a list of keywords (similar to Pete's c# code) 
		string file = "D:\\GPMTESTS\\PALEOV3_0.X0000";
		map<string, KeywordDescription> keywords = EclipseReader::GetKeywords(file);

		for(auto it = keywords.begin(); it!= keywords.end(); it++)
		{
			std::cout << keywords[ it->first  ] << std::endl;
		}

//load one array 
		std::string key = "TOTSTRXY";
		vector<float> values;
		bool success = EclipseReader::LoadEclipseDataArray<float>(key, file, values);

//print the array 
		if (success)
		{
			std::for_each(values.begin(), values.end(), [&](float value) {std::cout << value << std::endl; });
		}

//load and print another array (type guessed by the vector type)
		if( EclipseReader::LoadEclipseDataArray("ROCKDISY", file, values))
		{
			std::for_each(values.begin(), values.end(), [&](float value) {std::cout << value << std::endl; });
		}

//try to load and print an array that doesnt exist  
		if (EclipseReader::LoadEclipseDataArray("$$$$$$$$", file, values))
		{
			std::for_each(values.begin(), values.end(), [&](float value) {std::cout << value << std::endl; });
		}
		else 
		{
			cout << "This array doesnt exist. False was returned. No exceptions propagate" << std::endl;
		}
	}



	int option = 1;

	if (option == 0)
	{
		//this file is weird. Why? 
		string file1 = "D:\\Projects\\Programming\\GPM\\GPMAPI\\EclipseReaderCSharp\\TEST.X0000";
		string file2 = "D:\\Projects\\Programming\\GPM\\GPMAPI\\PetrelProjects\\TestNumbering.sim\\TWOELEMENTEXPERIMEN2\\TWOELEMENTEXPERIMEN2.X0000";
		string file3 = "D:\\Projects\\Programming\\GPM\\GPMAPI\\PetrelProjects\\VerySimple.sim\\CASE1\\CASE1.X0000";


		//TEST 1, FILE3
		//STRAINXX MUST BE 0.0001
		//STRAINYY MUST BE 0.0004
		{
			map<string, KeywordDescription> keywords = EclipseReader::GetKeywords(file3);
			//try to laod the strain_xx 
			std::vector<float> floats;
			std::vector<float> ints;
			std::map<string, KeywordDescription>::iterator it1 = keywords.find("STRAINXX");
			EclipseReader::LoadEclipseDataArray<float>(it1->second, file3, floats);
			for (size_t n = 0; n < floats.size(); n += 3550)
				std::cout << floats[n] << std::endl;

			std::getchar();

			std::map<string, KeywordDescription>::iterator it2 = keywords.find("STRAINYY");
			EclipseReader::LoadEclipseDataArray<float>(it2->second, file3, floats);
			for (size_t n = 0; n < floats.size(); n += 3550)
				std::cout << floats[n] << std::endl;



		}
	}


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
