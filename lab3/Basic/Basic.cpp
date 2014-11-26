/*-----------------------------------------------------------------------
** File Name: Basic.cpp
** ID:5130379059
** Name: Jin Jianian
** Created Time: 2014年11月21日 星期五 17s时55分03秒
** ----------------------------------------------------------------------
** BASIC Interpreter: a very simple one using codes from RPN's homework.
*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define KEYNUM 12
string keywords[KEYNUM] = {"run","clear","quit","list","help","if","goto","then","end","input","print","let"};	
map<string,int> vals;	/*use to store variables*/

bool IsWrong = false;	/*use to judge whether expression is wrong*/
bool Jmp_to_begin = false;	/*use to judge meeting a GOTO or THEN*/

/**************some useful functions**************/
bool IsKeyword(string s){
/*to judge whether string s is keyword*/
	for(int i = 0; i < KEYNUM; i++)
		if(s == keywords[i]) return true;
	return false;
}
bool IsEqual(string s1, string s2){
/*judge whether s1 is partly same as s2*/
	if(s2 == "run" ||s2 == "clear" || s2 == "quit" || s2 == "list" || s2 == "help")
		if(s1.size() != s2.size()) return false;
	for(int i = 0 ; i < s2.size(); i++){
		if(s1[i] != s2[i]) return false;
	}
	return true;
}
string NoSpace(string test){
/*return string with no space*/
	string tested = "";
	for(int i = 0; i < test.size(); i++){
		if(test[i] != ' ') tested += test[i];
	}
	return tested;
}
string lower(string s){
/*return string all in lower case*/
	string temp = s;
	for(int i = 0; i < s.size();i++){
		if(s[i]>='A' && s[i] <= 'Z')
			temp[i] = s[i] - 'A' + 'a';
		else	temp[i] = s[i];
		//cout << temp[i];
	}
	//cout << endl;
	return temp;
}
bool valid(string s){
/*judge if INPUT a valid number, '-' for negative one*/
	for(int i = 0; i < s.size(); i++){
		if((s[i] < '0' || s[i] > '9') 
			&& (s[i] != '-' )) 
			return false;
	}
	return true;
}

/*************** expression tree ******************/
struct Tree{
	string var;
	Tree* Left;
	Tree* Right;
	Tree(string s){
	/*To build a expression tree ---- same to Homework7*/
		int pos = -1;
		int times = 0;  
		bool flag = true;
		/*first move away the useless brackets*/
		for(int i = 0; i < s.size()-2; i++){
			if(s[i] == '(') times++;
			if(s[i] == ')') times--;
			if(times == 0) {
				break;
			}
		}
		if(times) {
			s = s.substr(1,s.size() - 2);
			times = 0;
		}
		/*Then find the correct operand*/
		for(int i = s.size() - 1; i >= 0; i--){
			if(s[i] == ')' ) times++;
			if(s[i] == '(' ) times--;
			if(!times && ( s[i] == '-' || s[i] == '+')){
				pos = i;
				break;
			}
			if(!times && flag && ( s[i] == '*' || s[i] == '/')){
				pos = i;
				flag = false;
			}
		}	
		if(pos == -1){
			var = s;
			Left = NULL;
			Right = NULL;
		}else{
		/*do this recursively*/
			Left = new Tree(s.substr(0,pos));
			int length = s.size()-1-pos;
			Right = new Tree(s.substr(pos + 1, length));
			var = s[pos];
		}
	}
	int eval(const Tree* root){
	/*return answer for an expression*/
		int i;
		int result;
		if(root->Left == NULL && root->Right == NULL){
			if(root->var[0] < '0' || root->var[0] > '9') {
				IsWrong = false;
				if(vals.find(lower(root->var)) == vals.end() ){
					cout << "VARIABLE NOT DEFINED\n"; 
					IsWrong = true;
				}
				else result = vals[lower(root->var)];
			}else result = atoi(root->var.c_str());
			return result;
		}

		switch(root->var[0]){
			case '+':
				return eval(root->Left) + eval(root->Right);
				break;
			case '-':
				return eval(root->Left) - eval(root->Right);
				break;
			case '*':
				return eval(root->Left) * eval(root->Right);
				break;
			case '/':
			{
				int left = eval(root->Left);
				int right = eval(root->Right);
				if(right == 0)  {cout << "DIVIDE BY ZERO\n";right = 1;IsWrong = true;}
				return left / right;
				break;
			}
		}
	}
};

/*************** BASIC Interpreter ****************/
class Interpreter{
private:
	map<int,string> codes;
public:
	Interpreter(){};

	void execve(){
	/*use to keep a command line*/
		string s;
		while(getline(cin,s)){
			string n = lower(s);
			if(IsEqual(n,"run")) 	run();	else 
			if(IsEqual(n,"clear"))	clear();else 
			if(IsEqual(n,"quit"))  	exit(0);else 
			if(IsEqual(n,"list"))  	list();	else 
			if(IsEqual(n,"help"))  	help();	else 
			if(n == "")				continue;else
									judge_if_now(s);
		}
		return;
	}

	void clear(){
		codes.clear();
		vals.clear();
	}

	void help(){
		cout << "Name:Jin Jianian\n" << "No:5130379059\n" << "Don't stay up too late :D\n";
		return;
	}

	void list(){
		for(map<int,string>::iterator i = codes.begin();i != codes.end();i++){
			if(i->second != "") cout << i->first << " " << i->second << endl;
		}
		return;
	}

	int expression(string s){
	/*input a string, return the value of this expression*/
		string test = NoSpace(s);
		Tree* rpn = new Tree(test);
		return rpn->eval(rpn);	
	}

	bool boolean(string s){
	/*input a string, return the result of comparation*/
		int i;
		for(i = 0; i < s.size(); i++){
			if(s[i] == '>' || s[i] == '<' || s[i] == '=')  break;
		}
		string s1 = NoSpace(s.substr(0,i));  	string s2 = NoSpace(s.substr(i+1));
		Tree* t1 = new Tree(s1);	        	Tree* t2 = new Tree(s2);
		int num = t1->eval(t1) - t2->eval(t2);
		if((num == 0 && s[i] == '=') || (num < 0 && s[i] == '<') || (num > 0 && s[i] == '>'))
			return true;
		return false;
	}

	void handler(string s){
	/*handler OUTSIDE commands*/
		string test = lower(s);
		
		if(IsEqual(test,"let ")){
			int i;
			for(i = 4; i < s.size(); i++){
				if (s[i] == '=') break;
			}
			if(i == s.size() - 1) {cout << "SYNTAX ERROR\n";return;}
			string var_name = lower(NoSpace(s.substr(4,i-4)))	;
			int var_value = expression(s.substr(i+1));
			if(IsKeyword(var_name))	{
				cout << var_name <<": ONE OF KEYWORD \n";
				return;
			}
			else if(var_name[0] >= '0' && var_name[0] <= '9')
				cout <<"Variable cannot start by a number\n";
			else{
				vals[var_name] = var_value;
			}
		}else 
		
		if(IsEqual(test,"print ")){
			string p = s.substr(6);
			int ans = expression(p);
			if(!IsWrong)
				cout << expression(p) << endl;
			else return;
		}else 

		if(IsEqual(test,"input ")){
			string var_name = s.substr(6);
			string s;
			int var_value;
			cout << " ? ";
			while(getline(cin,s)){
				if(valid(s)){
					var_value = atoi(s.c_str());
					break;
				}  
				cout << "INVALID NUMBER\n ? ";
			} 	 
			if(IsKeyword(var_name))	{
				cout << var_name <<": ONE OF KEYWORD \n";
				return;
			}
			else if(var_name[0] >= '0' && var_name[0] <= '9')
				cout << var_name <<" cannot start by a number\n";
			else{
				vals[var_name] = var_value;
			}
		}else
			cout << "SYNTAX ERROR\n";

		return;
	}

	void judge_if_now(string s){
	/*judge whether the command should be store or do it right now*/
		int num = 0;
		string n = "", code = "";
		if(s[0] >= '0' && s[0] <='9'){
			for(int i = 0; i < s.size(); i++){
				if(s[i] >= '0' && s[i] <= '9')  n += s[i];
				else break;
				//else {
				//	cout << "SYNTAX ERROR\n";
				//	return;
				//}
			}
			num = atoi(n.c_str());
			code = (s.size()!=n.size()) ? s.substr(n.size() + 1):"";
			codes[num] = code;
		}
		else{
			handler(s);
		}
		return;
	}

	int handler2(map<int,string>::iterator& iter,string s){
	/*handler INSIDE commands*/
		string test = lower(s);
		if(IsEqual(test,"let ")){
			int i;
			for(i = 4; i < s.size(); i++){
				if (s[i] == '=') break;
			}
			if(i == s.size() - 1) {cout << "SYNTAX ERROR\n";return 1;}
			string var_name = lower(NoSpace(s.substr(4,i-4)));
			int var_value = expression(s.substr(i+1));
			if(IsKeyword(var_name))	{
				cout << var_name <<": ONE OF KEYWORD \n";
				return 1;
			}
			else if(var_name[0] >= '0' && var_name[0] <= '9')
				cout << var_name <<" cannot start by a number\n";
			else{
				vals[var_name] = var_value;
			}
		}else 

		if(IsEqual(test,"print ")){
			string p = s.substr(5);
			int ans = expression(p);
			if(!IsWrong)
				cout << ans << endl;
		}else 

		if(IsEqual(test,"input ")){
			string var_name = s.substr(6);
			string s;
			int var_value;
			cout << " ? ";
			while(getline(cin,s)){
				if(valid(s)){
					var_value = atoi(s.c_str());
					break;
				}  
				cout << "INVALID NUMBER\n ? ";
			} 	 
			if(IsKeyword(var_name))	{
				cout << var_name <<": ONE OF KEYWORD \n";
				return 1;
			}
			else if(var_name[0] >= '0' && var_name[0] <= '9')
				cout << var_name <<" cannot start by a number\n";
			else{
				vals[var_name] = var_value;
			}
		}else 

		if(IsEqual(test,"goto ")){
			string point = s.substr(5);
			int n = atoi(point.c_str());
			iter = codes.find(n);
			if(iter == codes.end()) {
				cout << "LINE NUMBER ERROR\n";
				return 1;
			}
			if(iter == codes.begin())	return 2;
			iter--;
		}else 

		if(IsEqual(test,"if ")){
			int i;
			for(i = 2; i < s.size()-4 ; i++){
				int j = i;string key = "";
				while(j <= i+3) key += s[j++];
				if(key == "THEN")
					break;
			}

			string ocodes = s.substr(i+4);
			bool flag = boolean(s.substr(2,i-2));
			if(flag) {
				iter = codes.find(atoi(ocodes.c_str()));
				if(iter == codes.end()) {
					cout << "LINE NUMBER ERROR\n";
					return 1;
				}
				if(iter == codes.begin())	return 2;
				iter--;
			}	
		}else 

		if(IsEqual(test,"end")) return 1;
		else if(IsEqual(test, "rem")) return 0;
		else {
			cout << "SYNTAX ERROR\n";
			return 1;
		}
		return 0;
	}

	void run(){
	/*run INSIDE commands*/
		map<int,string>::iterator iter = codes.begin();
		while(iter != codes.end()){
			int status = handler2(iter,(iter)->second);
			iter++;
			if(status == 1)	break;
			if(status == 2) iter--;
			
		}
		//list();
	}
};

int main(){
	Interpreter i;
	i.execve();
	return 0;
}
