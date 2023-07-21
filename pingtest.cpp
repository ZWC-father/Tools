#include<iostream>
#include<fstream>
#include<regex>
#include<set>
#include<time.h>
#include<unistd.h>
using namespace std;
ifstream fin;
ofstream fout;
set<string> ips;
time_t rawtime;
struct tm* timeinfo;
string gettime(){
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	string tmp=string(asctime(timeinfo));
	tmp.pop_back();
	return tmp;
}
void logit(string str){
	fout<<'['<<gettime()<<"] "<<str<<endl;
}
int main(){
	cout<<"Starting Time: "<<gettime()<<endl;
	
	fin.open("config.txt");
	if(!fin.is_open()){
		cout<<"No Config File!"<<endl;
		return 0;
	}
	string str;
	while(fin>>str){
		if(regex_match(str,regex("((25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))")))ips.insert(str);
	}
	if(ips.empty()){
		cout<<"No IP!"<<endl;
		return 0;
	}
	
	cout<<"IP list: ";
	for(const auto& ipaddr:ips)cout<<ipaddr<<' ';
	cout<<"\nStarting Log!"<<endl;
	
	fout.open(string(gettime()+".log").c_str());
	logit("Monitor Started!");
	
	bool status=0;
	while(1){
		unsigned count=0;
		for(const auto& ipaddr:ips){
			str="fping "+ipaddr+" 1>/dev/null 2>&1";
			//cout<<str<<endl;
			if(!system(str.c_str()))count++;
			else{
				if(status)logit(ipaddr+string(" is not alive."));
			}
		}
		if(count==ips.size()){
			if(!status)logit("All hosts are alive!"),status=1;
		}else if(!count){
			if(status)logit("All hosts are NOT alive!"),status=0;
		}
		sleep(60);
	}
	return 0;
}
