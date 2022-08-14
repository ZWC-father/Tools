#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include<cctype>
#define re register
using namespace std;
const int N=10000005;
ifstream ans,out;
string ansfile,outfile;
string str[N],pat[N];
void WA(){cerr<<"\nWrong Answer!"<<endl;exit(1);}
void open(){
	ans.open(ansfile),out.open(outfile);
	if(ans.is_open()&&out.is_open()){
		cerr<<"Read answer from "<<ansfile<<endl;
		cerr<<"Read output from "<<outfile<<endl;
	}else{
		if(!ans.is_open())cerr<<"Can't open answer file!"<<endl;
		if(!out.is_open())cerr<<"Can't open output file!"<<endl;
		exit(-1);
	}
}
void work(){
	re int totstr=0,totpat=0;
	re int igstr=0,igpat=0;
	re int errors=0;
	while(getline(ans,str[++totstr]));
	totstr--;
	cerr<<"Read "<<totstr<<" lines from answer."<<endl;
	while(getline(out,pat[++totpat]));
	totpat--;
	cerr<<"Read "<<totpat<<" lines from output."<<endl;
	while(totstr){
		if(str[totstr].empty())totstr--,igstr++;
		else{
			bool flag=0;
			for(re int i=0;i<str[totstr].size();i++){
				if(isgraph(str[totstr][i])){
					flag=1;
					break;
				}
			}
			if(flag)break;
			totstr--,igstr++;
		}
	}
	if(igstr>0)cerr<<"Warning: ignore "<<igstr<<" empty lines in answer file."<<endl;
	while(totpat){
		if(pat[totpat].empty())totpat--,igpat++;
		else{
			bool flag=0;
			for(re int i=0;i<pat[totpat].size();i++){
				if(isgraph(pat[totpat][i])){
					flag=1;
					break;
				}
			}
			if(flag)break;
			totpat--,igpat++;
		}
	}
	if(igpat>0)cerr<<"Warning: ignore "<<igpat<<" empty lines in output file."<<endl;
	if(totstr!=totpat){
		cerr<<"\nExpect "<<totstr<<" lines,but read "<<totpat<<" lines."<<endl;
		WA();
	}
	cerr<<"Start checking!"<<endl;
	for(re int i=1;i<=totstr;i++){
		while(str[i].size()&&!isgraph(str[i].back()))str[i].pop_back();
		while(pat[i].size()&&!isgraph(pat[i].back()))pat[i].pop_back();
		if(str[i].size()!=pat[i].size()||str[i]!=pat[i]){
			cerr<<"\nAt line "<<i<<"\nExpect:\n"<<str[i]<<"\nBut find:\n"<<pat[i]<<endl;
			errors++;
		}
		if(errors>=10){
			if(i==totstr)break;
			cerr<<"\nTo many errors,checking canceled!"<<endl;
			WA();
		}
	}
	if(errors){
		cerr<<"\nFound "<<errors<<" error(s)."<<endl;
		WA();
	}
}
int main(int argc,const char *argv[]){
	if(argc>=3){
		ansfile=argv[1];
		outfile=argv[2];
	}else{
		cerr<<"No enough parameters!"<<endl;
		cerr<<"Usage:checker.exe [answer file] [output file]"<<endl;
		exit(-1);
	}
	open();
	work();
	cerr<<"\nAccepted!"<<endl;
	return 0;
}
