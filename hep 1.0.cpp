#include <iostream>
#include <cstdio>
#include <windows.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#define CTC_BG 0x0a
#define CTC_BR 0x0c
#define CTC_BW 0x07
#define CTC_PW 0x5f
#define CTC_RW 0x4f
#define CTC_GW 0x2f
using namespace std;
void setcolor(char c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
int n;
string tmp,demo;
FILE *wng,*crr;
char wrong[1000005],correct[1000005];
int wlen,clen,start,wt,tpn,tl,line,ac;
int state[1000005]; //0:AC 1:WA 2:TLE 3:RE 4:UKE
int color[5]={CTC_GW,CTC_RW,CTC_BW,CTC_PW,CTC_BW};
char sign[5][16]={"[AC]","[WA]","[TLE]","[RE]","[UKE]"};
double score;
bool allspace;
void copyrightdata(int number)
{
	demo="copy data.in .\\UnacceptedData\\data";
	demo+=to_string(number);
	demo+=".in";
	system(demo.data());
}
void clean()
{
	system("del data.in");
	system("del wrong.out");
	system("del correct.out");
}
int main(int argc,char *argv[])
{
	setcolor(CTC_BW);
	cout<<"hep[Version 1.0 Build 1013] is a application for APP debug under Windows(TM) by CMD.exe\n";
	cout<<"Type \'hep -?\' or \'hep -help\' to get more infomation\n";
	cout<<"Developer: hezex | DP: DEV-C++ | Tech: CMD.exe\n";
	if(argc==2)
	{
		if(!strcmp(argv[1],"-?")||!strcmp(argv[1],"-help"))
		{
			cout<<"Options:\n";
			cout<<"4/5 argv for simple tests\n";
			cout<<"[argv1]		The standard program (need .exe)\n";
			cout<<"[argv2]		The wrong program\n";
			cout<<"[argv3.1]	The data maker program\n";
			cout<<"[argv3.2]	The data folder with data file names. For example, .\\TestData\\data (no suffix input but the suffixes of data must be .in)\n";
			cout<<"[argv4]		Number of datas\n";
			cout<<"(argv5)		Time Limit\n";
			cout<<"Especially note for argv3.2. The data file name may be \".\\TestData\\data1.in\" and \".\\TestData\\data2.in\"\n";
			cout<<"But you only need to input \".\\Test Data\\data\" and this program will do with the rest things\n";
			cout<<"Note that the suffix numbers of the data files MUST be consecutive from 1\n\n";
			cout<<"\'-\' options:\n";
			cout<<"-?/-help		Get more information about hep.exe\n";
			cout<<"-clear		Delete every file in folder \"UnacceptedData\". This argv MUST be the last one\n";
			return 0;
		}
		else if(!strcmp(argv[1],"-clear")) return system("del /S /Q .\\UnacceptedData\\*.*"),0;
		else
		{
			cout<<"Unknow option on argv 1. Check your input again\n";
			cout<<"If you want to know more information, input \"hep -help\" or \"hep -?\"\n";
			return 0;
		}
	}
	if(argc<4)
	{
		setcolor(CTC_BR);
		cout<<"You should input 4 options for the check\n";
		goto end;
	}
	n=atoi(argv[4]);
	tl=1000;
	if(argc>5)
		if(argc>6)
		{
			tl=atoi(argv[5]);
			if(strcmp(argv[6],"-clear"))
			{
				cout<<"Unknow option on argv 6. Check your input again\n";
				cout<<"If you want to know more information, input \"hep -help\" or \"hep -?\"\n";
				return 0;
			}
			else system("del /S /Q .\\UnacceptedData\\*.*");
		}
		else
		{
			if(strcmp(argv[5],"-clear")) tl=atoi(argv[5]);
			else system("del /S /Q .\\UnacceptedData\\*.*");
		}
	for(int i=1;i<=n;i++)
	{
		setcolor(CTC_BW);
		cout<<"Testing Point #"<<++tpn<<":\n";
		tmp=argv[3];
		if(tmp.find('\\')!=tmp.npos)
		{
			demo="copy "+tmp+to_string(i)+".in data.in";
			system(demo.data());
		}
		else{demo=tmp+">data.in";system(demo.data());}
		tmp=argv[1];demo=tmp+"<data.in>correct.out";system(demo.data());
		tmp=argv[2];demo=tmp+"<data.in>wrong.out";
		start=clock();
		system(demo.data());
		wt=clock()-start;
		wng=fopen("wrong.out","r");
		if(wng==NULL)
		{
			state[tpn]=4;
			setcolor(CTC_BW);
			cout<<"[UKE]";
			setcolor(CTC_BR);
			cout<<"Could not generate the answer of wrong\n";
			copyrightdata(tpn);
			fclose(wng);
			clean();
			continue;
		}
		crr=fopen("correct.out","r");
		if(crr==NULL)
		{
			state[tpn]=4;
			setcolor(CTC_BW);
			cout<<"[UKE]";
			setcolor(CTC_BR);
			cout<<"Could not generate the answer of correct\n";
			copyrightdata(tpn);
			clean();
			fclose(wng);
			fclose(crr);
			continue;
		}
		state[tpn]=line=0;
		while(true)
		{
			fgets(wrong,1000005,wng);
			fgets(correct,1000005,crr);
			line++;
			wlen=strlen(wrong);
			clen=strlen(correct);
			allspace=true;
			for(int i=0;i<max(wlen,clen);i++)
			{
				if(wrong[i]!=' '&&wrong[i]!='\n'&&wrong[i]!='\0') allspace=false;
				if(wrong[i]==correct[i]) continue;
				else
				{
					if(wrong[i]==' '&&correct[i]=='\0') continue;
					if(wrong[i]=='\0'&&correct[i]==' ') continue;
					if(wrong[i]=='\t'&&correct[i]=='\0') continue;
					if(wrong[i]=='\0'&&correct[i]=='\t') continue;
					if(wrong[i]==' '&&correct[i]=='\t') continue;
					if(wrong[i]=='\t'&&correct[i]==' ') continue;
					if(wrong[i]==' '&&correct[i]=='\n') continue;
					if(wrong[i]=='\n'&&correct[i]==' ') continue;
					if(wrong[i]=='\0'&&correct[i]=='\n') continue;
					if(wrong[i]=='\n'&&correct[i]=='\0') continue;
					state[tpn]=1;
					break;
				}
			}
			if(state[tpn]) break;
			if(feof(wng)&&feof(crr)) break;
		}
		if(allspace||wt>2200)
		{
			state[tpn]=3;
			setcolor(CTC_PW);
			cout<<"[RE]";
			setcolor(CTC_BW);
			cout<<endl<<endl;
			continue;
		}
		if(wt>tl)
		{
			state[tpn]=2;
			setcolor(CTC_BW);
			cout<<"[TLE]";
			setcolor(CTC_BW);
			cout<<endl<<endl;
			continue;
		}
		if(state[tpn])
		{
			setcolor(CTC_RW);cout<<"[WA]";
			setcolor(CTC_BW);cout<<"on Line "<<line;
			cout<<"\n";
			copyrightdata(tpn);
		}
		else
		{
			setcolor(CTC_GW);cout<<"[AC]";
			setcolor(CTC_BW);cout<<"\nCongratulations!\n";
		}
		cout<<"Runtime:"<<wt<<"ms\n";
		cout<<"\n";
		fclose(wng);
		fclose(crr);
	}
	cout<<"Program End Successfully\n";
	cout<<"Testing Point Result:\n";
	for(int i=1;i<=tpn;i++)
	{
		setcolor(color[state[i]]);
		cout<<sign[state[i]];
		setcolor(CTC_BW);
		cout<<' ';
		if(!state[i]) ac++;
		if(i%10==0) cout<<endl;
	}
	score=ac*1.0/tpn*100;
	cout<<"RESULT: "<<(int)(score+0.5)<<endl;
end:
	setcolor(0x07);
	return 0;
}
