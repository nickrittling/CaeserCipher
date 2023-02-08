#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "unistd.h"

std::string encode(int key, int l)
{
	//open words.txt for words input
        std::ifstream infile;
        infile.open("words.txt");
        if(!infile) std::cout<<"File not found\n";
	//vector of strings to hold words
        std::vector<std::string>words;
        std::string line;
        while(getline (infile, line))
        {
                words.push_back(line);
        }
        infile.close();
	//input random words and encode with key
        std::string sen = "";
        //std::string a = ""; //debug string
	int length = l > 3 ? l : 3;
        for(int i = 0; i < length; i++)
        {
                std::string temp = "";
                temp += words[(std::rand() % words.size())];
                //a += temp;
                //a += " ";
                for(int j = 0; j < temp.length(); j++)
                {
                        if(temp[j] + key > 90)
                        {
                                temp[j] = temp[j] + key - 90 + 65;
                        }
                        else
                        {
                                temp[j] += key;
                        }
                }
                sen += temp;
                sen += ' ';
                temp = "";
        }
	return sen;
}//end encode


int main(int argc, char** argv)
{
	//-n num of lines of text
	//-l length minimum word length
	//-d location of dictionary 
	//-o output filename
	//parse options using getopt
	int n = 1, l = 0;
	for(;;)
	{
		switch(getopt(argc, argv, "n:l:do"))
		{
			case 'n':
				n = std::stoi(optarg);
				n = n > 1 ? n : 1;
				std::cout << "\nn = " << n << std::endl;
				continue;
			case 'l':
				l = std::stoi(optarg);
				std::cout << "l = " << l << std::endl;
				continue;
			case 'd':
				std::cout << "The dictionary is located at  "<< get_current_dir_name() << std::endl;
				continue;
			case 'o':
				std::cout<<"output file is named encode.txt\n";
				continue;
			case '?':
			case 'h':
			default :
				std::cout << "-n number of lines of text\n"
					  << "-l length minimum word length\n"
					  << "-d location of dictionary\n"
					  << "-o output filename\n";
			case -1:
			break;
		}//end switch
		break;
	}//end for

	//seed random with time
	std::srand(std::time(nullptr));

	//open words.txt for words input
	/*std::ifstream infile;
	infile.open("words.txt");
	if(!infile) std::cout<<"File not found\n";
	*/

	//open encode.txt for output
	std::ofstream of;
	of.open("encode.txt", std::fstream::out);
	if(!of) std::cout<<"File not found\n";

	/*
	//vector of strings to hold words
	std::vector<std::string>words;
	std::string line;
	while(getline (infile, line))
	{
		words.push_back(line);
	}
	infile.close();
	*/

	//random key
	int key = std::rand() % 26;
	
	/*
	//input random words and encode with key
	std::string sen = "";
	//std::string a = ""; //debug string
	for(int i = 0; i < 3; i++)
	{
		std::string temp = "";
		temp += words[(std::rand() % words.size())];
		//a += temp;
		//a += " ";
		for(int j = 0; j < temp.length(); j++)
		{
			if(temp[j] + key > 90)
			{
				temp[j] = temp[j] + key - 90 + 65;
			}
			else
			{
				temp[j] += key;
			}
		}
		sen += temp;
		sen += ' ';
		temp = "";
	}
	*/
	//std::cout << "key = " << key << std::endl;
	//std::cout << "original sentence: " << a << std::endl;
	//std::cout << "encoded sentence:  " << sen;
	//output number of sentences based on n
	while(n-- > 0)
	{
		of << encode(key,l) << std::endl;
	};

	
	return 0;
}
