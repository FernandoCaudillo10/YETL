#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

string dec2bi(int dec);
int used = 0;
int func = 0;

unordered_map<string, int> functions;
	
unordered_map<string, string> opcode {    
		{"entra", dec2bi(1)},
		{"saca", dec2bi(2)},
		{"para", dec2bi(3)},
		{"suma", dec2bi(4)},
		{"menos",dec2bi(5)},
		{"dividir",dec2bi(6)},
		{"por", dec2bi(7)},
		{"modelo", dec2bi(8)},
		{"salta", dec2bi(9)},
		{"agua", dec2bi(13)},
		{"enpuja", dec2bi(10)},
		{"despuja", dec2bi(11)},
		{"salta", dec2bi(12)},
		{"save", dec2bi(14)}
		};

ofstream fout("bin.txt");

void opcodeF(string entry, int x);
void isDigit(string entry);
void isMem(string entry);
void padding();

int main(){
	string info;

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
			if(count == 0){
				if(opcode.count(word) == 1)
					opcodeF(word,used);
				else
					cout << "Syntax error in line: " << used << endl;
			}
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
		bin = to_string(dec%2) +bin;	
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
		entry.substr(0,entry.length()-1);
		functions[entry] = ++func;
		fout << dec2bi(func);
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
	if(entry[0] == 'r' || entry[0] == 'R'){	
		string temp;
		if(isdigit(entry[1])){
			int x = entry[1]-'0';
			temp = dec2bi(x-1);	
			temp[0] = '1';
			fout << temp;
		}
		else
			cout << "Syntax Error in line " << used << ". Expected integer 1-7\n";
	}		
}
