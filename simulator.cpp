#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <fstream>


using namespace std;

vector<string> program;
vector<int> memory;
unordered_map<string, int> funkytown;

int PC = 0;
int stackCounter = 8;

int binaryToInt(string binary){
	bool isNeg = false;
	if(binary[0] == '1'){
		binary = binary.substr(1,binary.size()-1);
		isNeg = true;
	}
	int total = 0;
	for(int i=binary.size()-1; i>=0; i--){
		//cout << pow(2, binary.size()-1-i) << endl;
		total += (binary[i] == '1' ? pow(2, binary.size()-1-i) : 0); 
	}
	return (isNeg ? total * -1 : total);
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
void entra(string args){
	int dest = binaryToInt(args.substr(1,15));
	int input = binaryToInt(args.substr(16,16));
	if(dest > memory.size()-1){
		vector<int> temp(dest, 0);
		copy(memory.begin(), memory.end(), temp.begin());
		memory = temp;
	}
	if(input == 0){
		cin >> memory[dest];
	}
	else{
		memory[dest] = input;
	}
}
void saca(string args){
	if(args[0] == '1'){
		cout << memory[binaryToInt(args.substr(1, 15))] << endl;
	}
	else{
		cout << binaryToInt(args.substr(0,16)) << endl;
	}
}
void para(string args){
	cout << "Arriba, your program ran in a mexican second, in other words, it took 60 minutes.. optimize!" << endl;
	exit(0);
}
void suma(string args){
	string a = args.substr(0,16);
	string b = args.substr(16,16);
	string c = args.substr(32,16);
	
	int first = (a[0] == '1' ? memory[binaryToInt(a.substr(1,15))] : binaryToInt(a));
	int second = (b[0] == '1' ? memory[binaryToInt(b.substr(1,15))] : binaryToInt(b));
	
	
	memory[binaryToInt(c.substr(1, 15))] = first + second;
}
void menos(string args){
	string a = args.substr(0,16);
	string b = args.substr(16,16);
	string c = args.substr(32,16);
	
	int first = (a[0] == '1' ? memory[binaryToInt(a.substr(1,15))] : binaryToInt(a));
	int second = (b[0] == '1' ? memory[binaryToInt(b.substr(1,15))] : binaryToInt(b));

	memory[binaryToInt(c.substr(1,15))] = first - second;
}
void divide(string args){
	string a = args.substr(0,16);
	string b = args.substr(16,16);
	string c = args.substr(32,16);
	
	int first = (a[0] == '1' ? memory[binaryToInt(a.substr(1,15))] : binaryToInt(a));
	int second = (b[0] == '1' ? memory[binaryToInt(b.substr(1,15))] : binaryToInt(b));

	memory[binaryToInt(c.substr(1,15))] = first / second;
}
void por(string args){
	string a = args.substr(0,16);
	string b = args.substr(16,16);
	string c = args.substr(32,16);
	
	int first = (a[0] == '1' ? memory[binaryToInt(a.substr(1,15))] : binaryToInt(a));
	int second = (b[0] == '1' ? memory[binaryToInt(b.substr(1,15))] : binaryToInt(b));

	memory[binaryToInt(c.substr(1,15))] = first * second;

}
void modelo(string args){
	string a = args.substr(0,16);
	string b = args.substr(16,16);
	string c = args.substr(32,16);
	
	int first = (a[0] == '1' ? memory[binaryToInt(a.substr(1,15))] : binaryToInt(a));
	int second = (b[0] == '1' ? memory[binaryToInt(b.substr(1,15))] : binaryToInt(b));

	memory[binaryToInt(c.substr(1,15))] = first % second;

}
void salta(string args){
	cout << funkytown[args.substr(0,16)] << endl;
	PC = funkytown[args.substr(0,16)];
}
void enpuja(string args){
	memory[stackCounter] = binaryToInt(args.substr(0,16));
	stackCounter++;
}
void despuja(string args){
	stackCounter--;
}
void saltasi(string args){
	string a = args.substr(0,16);
	string b = args.substr(16,16);
	
	cout << memory[binaryToInt(a.substr(1,15))] << endl;
	if(binaryToInt(b.substr(1,15)) == 0 && memory[binaryToInt(a.substr(1,15))] == 0) PC++;
	else if(binaryToInt(b) == 1 && memory[binaryToInt(a.substr(1,15))] > 0) PC++;
	else if(binaryToInt(b) == 2 && memory[binaryToInt(a.substr(1,15))] < 0){
		if(memory[binaryToInt(a.substr(1,15))] < 0) PC++;
	}
}
void agua(string args){
	vector<int> m(8, 0);
	memory = m;
}
void saveStack(string args){
	memory[binaryToInt(args.substr(1,15))] = stackCounter;
}
void function(string args){
	funkytown[args.substr(0,16)] = binaryToInt(args.substr(16,16));
}
void parse(string p, vector<string> &program){
	while(p.size() != 0){
		program.push_back(p.substr(0,64));
		p.erase(p.begin(), p.begin()+64);
	}

}


// Global Variables
typedef void (*func)(string);

unordered_map<string, func> instructions{
	{dec2bi(1), entra},
	{dec2bi(2), saca},
	{dec2bi(3), para},
	{dec2bi(4), suma},
	{dec2bi(5), menos},
	{dec2bi(6), divide},
	{dec2bi(7), por},
	{dec2bi(8), modelo},
	{dec2bi(9), salta},
	{dec2bi(10), enpuja},
	{dec2bi(11), despuja},
	{dec2bi(12), saltasi},
	{dec2bi(13), agua},
	{dec2bi(14), function},
	{dec2bi(15), saveStack}
};

int main(){

	
	ifstream fin("bin.txt");

	if(fin.fail()){
		cout << "Where is the file? I can't see";
		exit(1);
	}

	string p;
	fin >> p;
	
	parse(p, program);
	agua("");
	// Start running program
	for(; PC<program.size(); PC++){
		func f = instructions[program[PC].substr(0,16)];
		(*f)(program[PC].substr(16,64-16));
	}
	
	fin.close();
	return 0;
}
