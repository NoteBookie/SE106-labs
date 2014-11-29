/*
** ----------------------------------------------------------------
** ID:5130379059
** Name: Jin Jianian
** ----------------------------------------------------------------
** Expression Tree : change Infix expression into suffix expression.
** 
** I use a simple binary tree. First move away the useless brackets,
** then I will choose the right pos to be the root of tree, and its
** right and left to be its children. Finally, recursively do so. 
** ----------------------------------------------------------------
*/
#include <iostream>
#include <string>
using namespace std;

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
	void print_tree(){
	/*postorder traversal -- here comes the suffix expression*/
		if(Left != NULL)	Left->print_tree();
		if(Right != NULL)	Right->print_tree();
		cout << var << ' ';
	}
};

string NoSpace(string test){
	string tested = "";
	for(int i = 0; i < test.size(); i++){
		if(test[i] != ' ') tested += test[i];
	}
	return tested;
}

int main(){
	string a;
	while(getline(cin,a)){
		if(a == "quit") break;
		string test = NoSpace(a);
		Tree *rpn = new Tree(test);
		rpn->print_tree();
		cout << endl;
	}
}
