#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <map>
#include <iterator>

double withvector(std::vector<std::string> words);
double withmap(std::vector<std::string> words);

int main(int argc, char* argv[])
{
	std::vector<std::string> words{};
	std::string word;

	for(int i{1}; i<argc; i++)  //read words
	{
		word = argv[i];
		words.push_back(word);
	}

	auto tmap = withmap(words);
	auto tvector = withvector(words);

	return 0;
	
}



double withmap(std::vector<std::string> words)
{
	std::map<std::string, int> wordsmap{}; //initial map
	std::map<std::string, int> freq{}; //map with frequencies
	std::string word;

	for(auto it=words.begin(); it!=words.end(); ++it)
	{
		//wordsmap[*it]=1;
		wordsmap.insert(it, std::pair <std::string,int> (*it,1));
		std::cout << "copia" << wordsmap.size() << std::endl;/////////////////
	}

	std::cout << wordsmap.size() << std::endl;//////////////
	//for(auto it=wordsmap.begin(); it!=wordsmap.end(); ++it)///////////
		//std::cout << it -> first << std::endl;

	auto t0 = std::chrono::high_resolution_clock::now(); //start time
	for(auto it=wordsmap.begin(); it!=wordsmap.end(); ++it)
	{
		word = it -> first;
		freq[word] = wordsmap.count(word);
		//std::cout << word << " " << wordsmap.count(word) << std::endl;/////////////////
		//wordsmap.erase(word);
		//it--;
	}
	std::cout << "iyo" << std::endl;///////////////////////////	
        	
	auto t1 = std::chrono::high_resolution_clock::now(); //end time
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds> (t1-t0);

	//print words
	std::cout << "Map implementation:" << std::endl;
	for(auto it{freq.begin()};it!=freq.end();it++)
		std::cout << " +" << it -> first << " " << it -> second << std::endl;

	return elapsed.count();
}

double withvector(std::vector<std::string> words)
{
	std::vector<int> freq{}; //vector with words frequencies
	std::string word;
	
	auto t0 = std::chrono::high_resolution_clock::now(); //start time
	
	std::sort(words.begin(), words.end()); //sort words
	
	//erase duplicates
	word = "";
	for(int i{0}; i<words.size(); i++)
	{
		if(words[i] == word) //if I've seen this word, erase
		{
			words.erase(words.begin()+i);
			i--;
			freq[i]++;
		}
		else  //else, save it for future comparations
		{
			word = words[i];
			freq.push_back(1);
		}
	}

	auto t1 = std::chrono::high_resolution_clock::now(); //end time
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds> (t1-t0);

	//print words
	std::cout << "Vector implementation:" << std::endl;
	for(int i{0};i<words.size();i++)
		std::cout << " +" << words[i] << " " << freq[i] << std::endl;

	return elapsed.count();
}
