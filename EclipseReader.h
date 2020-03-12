
#ifndef _ECLIPSE_READER_H 
#define _ECLIPSE_READER_H 1

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
#include <cstddef>


using namespace std;

enum
#ifdef ISDLL
	VISAGEDECKWRITEC_API
#endif
	EclipseDataFormatTypesEnum {
	MESS = 0, NONE = 0, CHAR, INT, REAL, LOGI, DOUBLE, OTHER
};



class
#ifdef ISDLL
	VISAGEDECKWRITEC_API
#endif
KeywordDescription
{

	friend std::ostream& operator<<(ostream &out,  KeywordDescription &item)
	{
		out << item.Name << " Type: " << KeywordDescription::GetTypeAsString(item) << " WordSize: " << item.WordSize << " Count: " << item.Size << " ByteLoc: " << item.ByteLocation << std::endl;
		return out;
	}

public:

	KeywordDescription* operator->() { return this; }

	KeywordDescription() { ; }

	static std::pair<EclipseDataFormatTypesEnum, int> GetTypeAndWordSize(string s)
	{
		//INTE standard (4 byte) signed integers
		//REAL single precision(4 byte) floating point reals
		//LOGI standard(4 byte) logicals
		//DOUB double precision (8 byte) floating point reals
		//CHAR characters(handled as 8 - character words
		std::transform(s.begin(), s.end(), s.begin(), ::toupper);
		EclipseDataFormatTypesEnum Type = EclipseDataFormatTypesEnum::OTHER;
		int WordSize;

		if (s.find("INT") != string::npos) { Type = EclipseDataFormatTypesEnum::INT; WordSize = 4; }
		else if (s.find("REAL") != string::npos) { Type = EclipseDataFormatTypesEnum::REAL; WordSize = 4; }
		else if (s.find("DOUB") != string::npos) { Type = EclipseDataFormatTypesEnum::DOUBLE; WordSize = 8; }
		else if (s.find("MESS") != string::npos) { Type = EclipseDataFormatTypesEnum::MESS; WordSize = 0; }
		else if (s.find("CHAR") != string::npos) { Type = EclipseDataFormatTypesEnum::CHAR; WordSize = 8; }
		else if (s.find("LOGI") != string::npos) { Type = EclipseDataFormatTypesEnum::LOGI; WordSize = 4; }
		else { Type = EclipseDataFormatTypesEnum::OTHER; WordSize = 0; }
		return pair<EclipseDataFormatTypesEnum, int>(Type, WordSize);
	}

	static std::string GetTypeAsString(const KeywordDescription &key)
	{
		std::string s = "";
		switch (key.Type)
		{
		case EclipseDataFormatTypesEnum::INT:
			s = "INT";
			break;
		case EclipseDataFormatTypesEnum::REAL:
			s = "REAL";
			break;
		case EclipseDataFormatTypesEnum::DOUBLE:
			s = "DOUBLE";
			break;
		case EclipseDataFormatTypesEnum::MESS:
			s = "MESS";
			break;
		case EclipseDataFormatTypesEnum::CHAR:
			s = "CHAR";
			break;
		case EclipseDataFormatTypesEnum::LOGI:
			s = "LOGI";
			break;

		default:
			s = "OTHER";
		}

		return s;
	}

	void SetTypeAndWordSize(string s)
	{
		pair<EclipseDataFormatTypesEnum, int> item = KeywordDescription::GetTypeAndWordSize(s);
		WordSize = item.second;
		Type = item.first;
	}

	KeywordDescription(string name, long size, string type, streampos loc)
	{
		Name = name;
		Size = size;
		SetTypeAndWordSize(type);
		ByteLocation = loc;
	}

	KeywordDescription(const KeywordDescription &key)
	{
		Name = key.Name;
		Size = key.Size;
		Type = key.Type;
		ByteLocation = key.ByteLocation;
	}

	KeywordDescription& operator==(const KeywordDescription &key)
	{
		Name = key.Name;
		Size = key.Size;
		Type = key.Type;
		ByteLocation = key.ByteLocation;
		WordSize = key.WordSize;
		return (*this);
	}

	std::string GetTypeAsString()
	{
		return KeywordDescription::GetTypeAsString(*this);
	}


	string Name;

	long Size;

	EclipseDataFormatTypesEnum Type;

	streampos ByteLocation;

	int WordSize;

};

static class
#ifdef ISDLL
VISAGEDECKWRITEC_API
#endif
EclipseReader
{
private:

	static bool is_little_endian();

	static void read_unsigned(unsigned char* word, ifstream &reader, int size);

public:

	static map<string, KeywordDescription>  GetKeywords(string fileToParse);

	template<typename T>
	static bool LoadEclipseDataArray(KeywordDescription& prop, string fileToParse, vector<T> &values)
	{
		ifstream reader(fileToParse, ios::in | ios::binary);
		if (!reader)
		{
			return false;
		}

		char *memblock = new char[sizeof(T)];
		values.resize(prop.Size);
		int count = 0, size = sizeof(T), dummy = 0;

		reader.seekg(prop.ByteLocation, std::ios::beg);
		for (long n = 0; n < prop.Size; n++)
		{
			reader.read(memblock, size);
			if (is_little_endian())
			{
				for (int i = 0; i < size / 2; i++) { std::swap(memblock[i], memblock[size - i - 1]); }
			}

			T value;
			memcpy(&value, memblock, sizeof(T));
			values[count++] = value;

			if (++dummy == 1000)
			{
				//reader.ignore(8);
				reader.read(memblock, size);
				reader.read(memblock, size);
				dummy = 0;
			}
		}

		reader.close();;
		delete[] memblock;
		return true;
	}

	template<typename T>
	static bool LoadEclipseDataArray(std::string array_name, string fileToParse, vector<T> &values)
	{
		map<string, KeywordDescription> keys = GetKeywords(fileToParse);
		if (keys.find(array_name) == keys.end())
		{
			return false;
		}

		KeywordDescription key = keys[array_name];
		return LoadEclipseDataArray<T>(key, fileToParse, values);
	}

};



#endif 

