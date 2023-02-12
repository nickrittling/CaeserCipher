#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
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

	//c++ 11 standard random
	std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> gen(0, words.size());


	//input random words and encode with key
	//take random word from dictionary and put into vector
	//add key to each character within word string inside the vector
	//if the added value is greater than 90, which is Z in ASCII table
	//add the overflow to 64 to get result
        std::string sen = "";
	int length = l > 3 ? l : 3;
        for(int i = 0; i < length; i++)
        {
                std::string temp = "";
                temp += words[((int)gen(mt) % words.size())];
		//std::cout<<temp<<std::endl;
		//of << temp << " ";
                for(int j = 0; j < temp.length(); j++)
                {
                        if(temp[j] + key > 90)
                        {
                                temp[j] = temp[j] + key - 90 + 64;
                        }
                        else
                        {
                                temp[j] += key;
                        }
                }
                sen += temp;
                sen += " ";
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
				//std::cout << "\nn = " << n << std::endl;
				continue;
			case 'l':
				l = std::stoi(optarg);
				//std::cout << "l = " << l << std::endl;
				continue;
			case 'd':
				std::cout << "The dictionary is located at /home/runner/Caesar-Cipher-1-comp-339-439-ds-6/include\n";//<< get_current_dir_name() << std::endl;
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
	
	//open encode.txt for output
	std::ofstream of;
	of.open("encode.txt", std::fstream::out);
	if(!of) std::cout<<"File not found\n";
	
	//random number generator	
	std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> gen(0, 26);

	//random key
	int key = (int)gen(mt);
	
	//output number of sentences based on n
	while(n-- > 0)
	{
		of << encode(key,l) << std::endl;
	};

	
	return 0;
}
