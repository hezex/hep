#pragma once

#include "global.hpp"

#define TS_AC 0
#define TS_WA 1
#define TS_TLE 2
#define TS_RE 3
#define TS_UKE 4

class point
{
		int id,state,runtime,timelimit; //0:AC 1:WA 2:TLE 3:RE 4:UKE
	public:
		point(){}
		point(int id,int tl):id(id),timelimit(tl){}
		void setid(int);
		void settimelimit(int);
		int run(const char*);
		int getstate();
		void print();
};


using namespace std;

void point::setid(int id)
{
	this->id=id;
}

void point::settimelimit(int tl)
{
	timelimit=tl;
}

int point::run(const char *runcmd)
{
	runtime=clock();
	system(runcmd);
	runtime=clock()-runtime;
	FILE *wng=fopen("wrong.out","r");
	if(wng==NULL)
	{
		state=TS_UKE;
		setcolor(CTC_BW);
		cout<<"[UKE]";
		setcolor(CTC_BR);
		cout<<"Could not generate the answer of wrong\n";
		copydata(id);
		fclose(wng);
		clean();
		return state;
	}
	FILE *crr=fopen("correct.out","r");
	if(crr==NULL)
	{
		state=TS_UKE;
		setcolor(CTC_BW);
		cout<<"[UKE]";
		setcolor(CTC_BR);
		cout<<"Could not generate the answer of correct\n";
		copydata(id);
		clean();
		fclose(wng);
		fclose(crr);
		return state;
	}
	state=TS_AC;
	int line=0,wlen,clen;
	bool allspace;
	char wrong[1000005],correct[1000005];
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
				state=1;
				break;
			}
		}
		if(state) break;
		if(feof(wng)&&feof(crr)) break;
	}
	if(allspace||runtime>2200)
	{
		state=3;
		setcolor(CTC_PW);
		cout<<"[RE]";
		setcolor(CTC_BW);
		cout<<endl<<endl;
		copydata(id);
		return state;
	}
	if(runtime>timelimit)
	{
		state=2;
		setcolor(CTC_BW);
		cout<<"[TLE] Runtime:"<<runtime<<"ms";
		setcolor(CTC_BW);
		cout<<endl<<endl;
		copydata(id);
		return state;
	}
	if(state)
	{
		setcolor(CTC_RW);cout<<"[WA]";
		setcolor(CTC_BW);cout<<"on Line "<<line;
		cout<<"\n";
		copydata(id);
	}
	else
	{
		setcolor(CTC_GW);cout<<"[AC]";
		setcolor(CTC_BW);cout<<"\nCongratulations!\n";
	}
	cout<<"Runtime:"<<runtime<<"ms\n";
	cout<<"\n";
	fclose(wng);
	fclose(crr);
}

int point::getstate()
{
	return this->state;
}

void point::print()
{
	setcolor(tpcolor[state]);
	cout<<tpsign[state];
	setcolor(0x07);
}
