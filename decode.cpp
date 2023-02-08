#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "unistd.h"

std::string decode(std::string input)
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
	for(auto it : ans) std::cout << it << std::endl;

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
	
	//take a sentence and find key
	 
	return "aaa";

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
