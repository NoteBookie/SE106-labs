/*-----------------------------------------------------------------------
** File Name: Basic1.cpp
** ID:5130379059
** Name: Jin Jianian
** Created Time: 2014年11月21日 星期五 17时55分03秒
** ----------------------------------------------------------------------
*/
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
string NoSpace(string test){
	string tested = "";
	for(int i = 0; i < test.size(); i++){
		if(test[i] != ' ') tested += test[i];
	}
	return tested;
}
string lower(string s){
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
struct Tree{
	string var;
	Tree* Left;
	Tree* Right;
	Tree(string s){
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
	void eval(const Tree* root){
		if(root->left != NULL && root->right != NULL)
			return root->var;
		int num1 = eval(root->left);
		int num2 = eval(root->right);
		return calculate(num1,num2,root->data);
	}
	int calculate(int num,int num2,wchar_t op){
		int ret = (1<<31);
		switch(op){
		case '+':
			ret = (num + num2);
			break;
		case '-':
			ret = (num - num2);
			break;
		case '*':
			ret = (num * num2);
			break;
		case '/':
			ret = (num/num2);
			break;
		}
		return ret;
	}
};
class Interpreter{
private:
	vector<string> comments;
	map<string,float> vals;
	map<int,string> codes;
public:
	Interpreter(){};
	void execve(){
		string s;
		while(getline(cin,s)){
			string n = lower(s);
			//cout<< n <<endl;
			if(n == "run") run();
			else if(n == "clear") clear();
			else if(n == "quit")  quit();
			else if(n == "list")  list();
			else if(n == "help")  help();
			else judge_if_now(s);
		}
		return;
	}
	void clear(){
		codes.clear();
		vals.clear();
	}
	void help(){
		cout << "Name:Jin Jianian\n" << "No:5130379059\n" << "Merry Christmas :D\n";
		return;
	}
	void list(){
		for(map<int,string>::iterator i = codes.begin();i != codes.end();i++){
			if(i->second != "") cout << i->first << " " << i->second << endl;
		}
		return;
	}
	void quit(){
		exit(0);
	}
	int expression(string s){
		map<string,float>::iterator iter = vals.begin(); 
		if(s[0] >= 'a' && s[0] <= 'z') {iter = vals.find(s);return (int)iter->second;}
		else return atoi(s.c_str());
	}
	bool boolean(string s){
		return true;
	}
	void handler(string s){
		int i = 0;string key = "";
		while(i <= 2) key += s[i++];
		key = lower(key);
		if(key == "let"){
			int i;
			for(i = 4; i < s.size(); i++){
				if (s[i] == '=') break;
			}
			string var_name = s.substr(4,i-4);
			float var_value = expression(s.substr(i+1));
			vals[var_name] = var_value;
		}else if(key == "pri"){
			string p = s.substr(6);
			cout << expression(p) << endl;
		}else if(key == "inp"){
			string var_name = s.substr(6);
			float value;
			cout << "?";
			cin >> value;
			vals[var_name] = value;
		}else 
			return;
	}
	void judge_if_now(string s){
		int num = 0;
		string n = "", code = "";
		if(s[0] >= '0' && s[0] <='9'){
			for(int i = 0; i < s.size(); i++){
				if(s[i] >= '0' && s[i] <= '9')  n += s[i];
				else break;
			}
			num = atoi(n.c_str());
			//cout << num << endl;
			code = (s.size()!=n.size()) ? s.substr(n.size() + 1):"";
			//cout << code << endl;
			codes[num] = code;
		}
		else{
			handler(s);
		}
		return;
	}
	void handler2(map<int,string>::iterator& iter,string s){
		int i = 0;string key = "";
		while(i <= 2) key += s[i++];
		key = lower(key);
		if(key == "rem"){
			return;
		}else if(key == "let"){
			int i;
			for(i = 4; i < s.size(); i++){
				if (s[i] == '=') break;
			}
			string var_name = s.substr(4,i-4);
			float var_value = expression(s.substr(i+1));
			vals[var_name] = var_value;
		}else if(key == "pri"){
			string p = s.substr(6);
			cout << expression(p) << endl;
		}else if(key == "inp"){
			string var_name = s.substr(6);
			float value;
			cout <<"?";
			cin >> value;
			vals[var_name] = value;
		}else if(key == "got"){
			string point = s.substr(5);
			int n = atoi(point.c_str());
			cout <<"GOTO:" << n <<endl;
			iter = codes.find(n);
			iter--;
			return;
		}else if(key == "if "){
			int i;
			for(i = 2; i < s.size()-4 ; i++){
				int j = i;string key = "";
				while(j <= i+3) key += s[j++];
				if(key == "then")
					break;
			}
			string ocodes = s.substr(i+5);
			bool flag = boolean(s.substr(3,i-3));
			if(flag) handler2(iter,ocodes);
			return;
		}else if(key == "end") return;
		return;//wrong
	
	}
	void run(){
		//get codes from MAP-codes;
		map<int,string>::iterator iter = codes.begin();
		for(;iter != codes.end(); iter++){
			handler2(iter,iter->second);
		}
		//handler right now;
	}
};
int main(){
	Interpreter i;
	i.execve();
	return 0;
}
