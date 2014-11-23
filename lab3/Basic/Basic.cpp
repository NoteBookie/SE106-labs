/*-----------------------------------------------------------------------
** File Name: Basic.cpp
** ID:5130379059
** Name: Jin Jianian
** Created Time: 2014年11月11日 星期二 23时10分16秒
** ----------------------------------------------------------------------
*/
#include <iostream>
#include "TokenScanner.h"
#define CODE 1
#define COMMANDS 2
using namespace std;

class Interpreter{
private:
	int status;
	map of values;
	map of codes;
public:
	Interpreter();
	void init(stdin){
		int number;
		string commands;
		if(cin >> number) {
			status = CODE;
			string exp;
			getline(cin,exp);
			insert into a map.
		}else{
			status = COMMANDS;
			getline(cin,commands);
			if(commands == "RUN") run();
			else if(commands == "CLEAR") clear();
			else if(commands == "QUIT") quit();
			else if(commands == "LIST") list();
			else if(commands == "HELP") help();
		}
	}
	void quit(){
		exit(0);
	}
	void list(){
		print codes;
	}
	void help(){
		print help;
	}
	void run(){
		execute();	
	}
	void execute(){
		get codes;
		if let : then pushback name and val into a map;
		if print : then find the val of that name;put it on stdout;
		if input : then wait stdin input a val;
		if end: return; 
	}
	
}

Expression(string){
	change string into an int.
}
