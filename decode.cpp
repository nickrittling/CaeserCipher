#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "unistd.h"


int findKey(const std::vector<std::string>& word, std::string input)
{
	std::string delimiter = " ";
	int start = 0;
   	int end = input.find(delimiter);
	std::vector<std::string> sep;
   	while (end != -1) 
	{
        	sep.push_back(input.substr(start, end - start));
        	start = end + delimiter.size();
        	end = input.find(delimiter, start);
    	}
        //for(auto it : sep) std::cout<<it<<" ";
	std::vector<int> key {0,0,0};
	for(int i = 0; i < 3; i++)
	{
		for(int k = 0; k < 26; k++){
			//std::cout<<sep[i]<<" ";
			//key[i]++;
			//std::vector<std::string>::iterator it;
			//it = std::find (word.begin(), word.end(), sep[i]);
 	 		if (std::find(word.begin(), word.end(), sep[i]) != word.end())
			{
    				//std::cout << "Element found in myints: " << '\n';
				//std::cout << "key is " << key[i] << std::endl;
				break;
			}
  			//else
    			//std::cout << "Element not found in myints\n";
			for(int j = 0; j < sep[i].size(); j++)
			{
				if(sep[i][j] +1 > 90)
				{
					sep[i][j] = 65;
				}
				else sep[i][j]++;

			}
			key[i]++;
		}
	}

	for(int i = 0; i < key.size() -1; i++)
	{
		//std::cout<<key[i] << std::endl;
		if(key[i] != key[i+1])
		{
			std::cout<<"something wrong happened\n";
			exit(1);
		}
	}


	return key[0];
}//end findKey

void decode(std::string input)
{
	//loads encoded text
	std::ifstream infile;
	if(input != "")
	{
		infile.open(input);
		if(!infile) std::cout << "File not found\n";
	}
	else
	{
		infile.open("encode.txt");
		if(!infile) std::cout << "File not found\n";
	}
	std::string line;
	std::vector<std::string> ans;
	while(getline (infile, line))
	{
		ans.push_back(line);
	}
	//for(auto it : ans) std::cout << it << std::endl;

	//load dictionary
	std::ifstream wordsIn;
	wordsIn.open("words.txt");
	if(!wordsIn) std::cout << "File not found\n";
	std::vector<std::string> dict;
	while(getline (wordsIn, line))
	{
		dict.push_back(line);
	}
	wordsIn.close();

	//open decode.txt for output
	std::ofstream of;
	of.open("decode.txt", std::fstream::out);
	if(!of) std::cout<<"File decode not found\n";
	
	//take a sentence and find key
	int key = findKey(dict, ans[0]);

	//decode with key
	for(int i = 0; i < ans.size(); i++)
	{
		for(int j = 0; j < ans[i].size(); j++)
		{
			if(ans[i][j] == ' ') continue;
			else if(ans[i][j] + key > 90)
			{
				ans[i][j] = ans[i][j] + key - 26;
			}
			else
			{
				ans[i][j] += key;
			}
		}

		of << ans[i] << std::endl;

	}


}//end decode

int main(int argc, char** argv)
{
	//-i input from filename
	//-d location of dictionary
	//-o output filename
	//parse options using getopt
	std::string input = "";
	for(;;)
	{
		switch(getopt(argc, argv, "i:do?h"))
		{
			case 'i':
				input = optarg;
				//std::cout << "l = " << l << std::endl;
				continue;
			case 'd':
				std::cout << "The dictionary is located at  "
					<< "/home/runner/Caesar-Cipher-1-comp-339-439-ds-6/include"
					//get_current_dir_name() 
					<< std::endl;
				continue;
			case 'o':
				std::cout<<"output file is named encode.txt\n";
				continue;
			case '?':
			case 'h':
			default :
				std::cout << "-i input filename\n"
					  << "-d location of dictionary\n"
					  << "-o output filename\n";
			case -1:
			break;
		}//end switch
		break;
	}//end for
	 
	//open decode.txt for output
	std::ofstream of;
	of.open("decode.txt", std::fstream::out);
	if(!of) std::cout<<"File not found\n";
	
	decode(input);
	return 0;
}//end main
