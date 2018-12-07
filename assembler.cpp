#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

unordered_map<string, string> opcode {    
		{"entra", "0000000000000001"},
		{"saca", "0000000000000010"},
		{"para", "0000000000000011"},
		{"suma", "0000000000000100"},
		{"menos","0000000000000101"},
		{"dividir","0000000000000110"},
		{"por",    "0000000000000111"},
		{"modelo", "0000000000001000"},
		{"salta",  "0000000000001001"},
		{"agua",   "0000000000001010"},
		{"enpuja", "0000000000001011" },
		{"despuja", "0000000000001100"},
		{"salta", "0000000000001101"},
		{"save", "0000000000001110"}
		};
ofstream fout("bin.txt");

string dec2bi(int dec);
void opcodeF(string entry, int x);
void isDigit(string entry);
void isMem(string entry);
void padding();

int main(){
	string info;
	int used = 0;

	ifstream fin("test.txt");
	if(fin.fail()){
		cout << "Where is the file? I can't see";
		exit(1);
	}
	
	
	while(getline(fin,info)){
		stringstream buf(info);
		used++;
		string word;
		int count = 0;
		
		while(buf >> word){	
			if(count == 0)
				opcodeF(word,used);

			//dec|mem|reg
			else{
				if(isdigit(word[0])){
					isDigit(word);	
				}
				else
					isMem(word);
			}
			count++;
		}
		while(count < 4){
			padding();
			count++;
		}
	}
	

	fin.close();
	fout.close();
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

void opcodeF(string entry, int x){
	if(entry[entry.length()-1] == ':'){
		fout << opcode["save"];
		fout << dec2bi(x);
	}
	else
		fout << opcode[entry];
}

void isDigit(string entry){
	if(stoi(entry)>0)
		fout << dec2bi(stoi(entry));
	
	else{
		string temp = dec2bi(stoi(entry)*-1);
		temp[1] = '1';
		fout << temp;
	}
}

void padding(){
	for(int i=0;i<16;i++)
		fout << "0";
}

void isMem(string entry){
	if(entry[0] == 'r' || entry[0] == 'R')
	{	
		string temp;
		if(isdigit(entry[1]))
		{
			int x = entry[1]-'0';
			temp = dec2bi(x-1);	
			temp[0] = '1';
			fout << temp;
		}
	}		
}
