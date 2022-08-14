#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define re register
const int N=1005;
FILE *ans,*out;
char str[2][N];
void WA(){printf("\nStatus: Wrong Answer!\n");exit(1);}
void open(char *ansfile,char *outfile){
	bool flag=0;
	if(ans=fopen(ansfile,"r"))printf("Read answer from %s\n",ansfile);
	else flag=1,printf("Can't open output file!\n");
	if(out=fopen(outfile,"r"))printf("Read output from %s\n",outfile);
	else flag=1,printf("Can't open answer file!\n");
	if(flag)exit(-1);
}
inline bool read(FILE *stream,bool op,int &len){
	char tmp;len=0;
	memset(str[op],0,sizeof str[op]);
	if(fscanf(stream,"%[^\n]%c",str[op]+1,&tmp)==EOF)return 0;
	len=strlen(str[op]+1);
	return 1;
}
inline void modify(bool op,int &len){
	while(len&&!isgraph(str[op][len]))str[op][len--]=0;
}
void work(){
	re int tot=0,errors=0;
	re int lenans=0,lenout=0;
	while(read(ans,0,lenans)){
		tot++;
		modify(0,lenans);
		if(read(out,1,lenout)){
			modify(1,lenout);
			if(!lenans&&!lenout)continue;
			if(lenans!=lenout||strcmp(str[0]+1,str[1]+1)){
				printf("\nAt line %d\n",tot);
				printf("Expect:\n%s\nBut read:\n%s\n",str[0]+1,str[1]+1);
				errors++;
			}
		}else{
			do{
				modify(0,lenans);
				if(lenans){
					printf("\nAt line %d\nExpect:\n%s\nBut read nothing.\n",tot,str[0]+1);
					printf("\nChecking terminated!\n");
					WA();	
				}
				tot++;
			}while(read(ans,0,lenans));
		}
		if(errors>=10){
			printf("\nToo many errors!\n");
			if(read(ans,0,lenans))printf("Checking terminated!\n");
			WA();
		}
	}
	while(read(out,1,lenout)){
		tot++;
		modify(1,lenout);
		if(lenout){
			printf("\nFind extra character in output file at line %d\n",tot);
			WA();
		}
	}
	if(errors)WA();
}
int main(int argc,char *argv[]){
	if(argc<3){
		printf("No enough parameters!\n");
		printf("Usage:checker.exe [answer file] [output file]\n");
		exit(-1);
	}
	open(argv[1],argv[2]);
	work();
	printf("\nStatus: Accepted!\n");
	return 0;
}
