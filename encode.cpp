#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>



int main()
{
	std::ofstream of;
	of.open("encode.txt", std::ios::app);
	if(!of) std::cout<<"File not found\n";


}
