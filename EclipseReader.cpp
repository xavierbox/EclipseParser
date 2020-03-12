#include "EclipseReader.h"


bool EclipseReader::is_little_endian()
{
	short int word = 0x0001;
	char *byte = (char *)&word;
	return(byte[0] ? true : false);
}

void EclipseReader::read_unsigned(unsigned char* word, ifstream &reader, int size)
{
	for (int i = 0; i < size; i++) reader >> word[i];
}

map<string, KeywordDescription>  EclipseReader::GetKeywords(string fileToParse)
{
	map<string, KeywordDescription> map;

	ifstream reader(fileToParse, ios::in | ios::binary);
	if (!reader)
	{
		return map;
	}
	char *memblock8 = new char[8];
	char *memblock4 = new char[4];
	//detect the number of bytes so we read all minus 8 of them
	reader.seekg(0, std::ios::end);  //go to the end of the file
	auto end = reader.tellg() - streampos(8);      //store the byte position
	reader.clear();                  //reset the file
	reader.seekg(0, std::ios::beg);  //go to the beginning again. Now we have stored the end minus 8 bytes.

	bool keep = true;
	while (keep)
	{
		//read space 4 bytes 
		reader.read(memblock4, 4);

		//read word 8 bytes 
		reader.read(memblock8, 8);

		//convert word to string
		string key_string(reinterpret_cast<char*>(memblock8), sizeof(memblock8));

		if (((key_string.find("ENDSOL") != string::npos)) || (reader.tellg() > end))
		{
			keep = false;
		}
		else
		{
			//size, 4 bytes and check endianess 
			reader.read(memblock4, 4);
			if (is_little_endian())
			{
				for (int i = 0; i < 4 / 2; i++) { std::swap(memblock4[i], memblock4[4 - i - 1]); }
			}
			int size = 0;
			memcpy(&size, memblock4, 4);

			//keyword for type. Some types have no parallel in c++ example: MESS, INTE, DOUBLEHEADetc..
			reader.read(memblock4, 4);//#, 4);
			string stype(reinterpret_cast<char*>(memblock4), sizeof(4));

			if (size > 0)
			{
				auto currentLocation = reader.tellg();
				KeywordDescription key(key_string, size, stype, currentLocation + streampos(8));
				map[key.Name] = key;

				int data_type = key.WordSize;// item.second;
				streamoff toSkip(8 + 4 + 8 * ((long)((size - 1) / (1000))) + data_type * size);
				reader.seekg(toSkip + reader.tellg(), ios::beg);
				//std::cout << "**"<<key << std::endl;
				//std::cout << "*****" << map[key.Name] << std::endl;

			}
			else
			{
				streamoff toSkip(4);
				reader.seekg(toSkip + reader.tellg(), ios::beg);
			}
		}
	}

	reader.close();
	delete[] memblock8;
	delete[] memblock4;

	return map;
}


