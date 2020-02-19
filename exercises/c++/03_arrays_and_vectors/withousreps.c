#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
	std::vector<std::string> words{};
	std::string word;

	for(int i{1}; i<argc; i++)  //read words
	{
		word = argv[i];
		words.push_back(word);
	}

	std::sort(words.begin(), words.end()); //sort words
	
	//erase duplicates
	word = "";
	for(int i{0}; i<words.size(); i++)
	{
		if(words[i] == word) //if I've seen this word, erase
		{
			words.erase(words.begin()+i);
			i--;
		}
		else  //else, save it for future comparations
			word = words[i];
	}

	//print words
	for(std::string x : words)
		std::cout << x << std::endl;

	return 0;
	
}

