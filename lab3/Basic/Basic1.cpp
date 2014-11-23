/*-----------------------------------------------------------------------
** File Name: Basic1.cpp
** ID:5130379059
** Name: Jin Jianian
** Created Time: 2014年11月21日 星期五 17时55分03秒
** ----------------------------------------------------------------------
*/
#include<iostream>

using namespace std;
void lower(string s){

}
class Interpreter(){
private:
	int status;
	map<string,int> vals;
	map<int,string> codes;
public:
	Interpreter();
	void execve(){
		string s;
		while(getline(cin,s)){
			string n = lower(s);
			if(n == "RUN") run();
			else if(n == "CLEAR") clear();
			else if(n == "QUIT")  quit();
			else if(n == "LIST")  list();
			else if(n == "HELP")  help();
			else handler();
		}
	}
	void handler(){
		if(with number) store into MAP-codes;
		else handler right now;
	}
	void run(){
		get codes from MAP-codes;
		handler right now;
	}
}
