# EclipseParser
Small library to parse X files in c++. It has only 3 methods, all static. Doesnt depend on any third parties.
The lib allows to read simulation results from visage, eclipse, and intersect into c++ vectors. See example code:

EclipseReaderCpp.cpp

for an example of use

<pre>
<code>
int main()
{
	{
//get a list of keywords (similar to Pete's c# code) 
		string file = "D:\\GPMTESTS\\PALEOV3_0.X0000";
		map<string, KeywordDescription> keywords = EclipseReader::GetKeywords(file);

//print the found keys 
		std::for_each(keywords.begin(), keywords.end(), [&](std::pair<string, KeywordDescription> value) 
			{std::cout << value.second<< std::endl; });

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

</code>
</pre>

<pre><code class='language-cs'>
Console.WriteLine("Fenced code blocks ftw!");
</code></pre>
