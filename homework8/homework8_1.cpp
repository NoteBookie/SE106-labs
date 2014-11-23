/*-----------------------------------------------------------------------
** File Name: homework8_1.cpp
** ID:5130379059
** Name: Jin Jianian
** Created Time: 2014年11月23日 星期日 19时34分38秒
** ----------------------------------------------------------------------
*/
#include<iostream>
#include<fstream>
using namespace std;

int find(int c,int A[],int s,int e){
	for(int i = s; i <= e; i++){
		if(A[i] == c) return i;
	}
}
void postorder(int pre[],int pre_s,int pre_e,int in[],int in_s,int in_e, ofstream* ofs){
	if(in_s > in_e) return;
	if(in_s == in_e) { *ofs << in[in_s] << " "; return;}
	int root = pre[pre_s];
	int root_in = find(root,in,in_s,in_e);

	postorder(pre, pre_s+1, pre_s+root_in-in_s , in , in_s , root_in-1,ofs);
	postorder(pre, pre_s+root_in-in_s+1, pre_e, in, root_in+1, in_e,ofs);
	*ofs << root << " ";
}

int main(int argc, char* argv[]){
	if(argc != 3) {
		cout << "wrong arguments." << endl;
	}
	int n;
	string input = argv[1];
	string output = argv[2];
	ifstream ifs(input.c_str());
	ofstream ofs(output.c_str());
	ifs >> n;
	for(int t = 0; t < n; t++){
		int length;
		ifs >> length;
		int A[length],B[length];
		for(int l = 0; l < length; l++){
			int num;
			ifs >> num;
			A[l] = num;
		}
		for(int l = 0; l < length; l++){
			int num;
			ifs >> num;
			B[l] = num;
		}
		postorder(A,0,length-1,B,0,length-1,&ofs);
		ofs << endl;
	}
}
