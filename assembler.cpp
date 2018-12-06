#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

typedef void (*func)();

string dec2bi(int dec);

int main(){
	string info;
	
	ifstream fin("test.txt");

	if(fin.fail()){
		cout << "Where is the file? I can't see";
		exit(1);
	}
	

	while(fin >> info){
		cout << info << endl;
	}
	
	fin.close();

	return 0;	
}

string dec2bi(int dec){
	string bin;
	
	if(dec == 0)
		return "0000000000000000";
	
	while(dec/2 != 0)
	{
		bin = to_string(dec %2) +bin;	
		dec = dec/2;
	}

	bin = "1" + bin;

	while(bin.size() < 16)
		bin = "0" + bin;

	return bin;
}
