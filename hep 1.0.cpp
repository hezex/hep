#include "global.hpp"
#include "point.hpp" 
using namespace std;
int n;
string tmp,demo;
FILE *wng,*crr;
char wrong[1000005],correct[1000005];
int wlen,clen,start,wt,tpn,tl,line,ac;
point p[10000005];
double score;
bool allspace;
int main(int argc,char *argv[])
{
	setcolor(CTC_BW);
	cout<<"hep[Version 1.0 Build 1013] is a application for APP debug under Windows(TM) by CMD.exe\n";
	cout<<"Type \'hep -?\' or \'hep -help\' to get more infomation\n";
	cout<<"Developer: hezex | DP: DEV-C++ | Tech: CMD.exe\n";
	if(argc==2)
	{
		if(!strcmp(argv[1],"-?")||!strcmp(argv[1],"-help")||!strcmp(argv[1],"-help--en-us")||!strcmp(argv[1],"-?--en-us"))
		{
			print_from_file("help.txt");
			return 0;
		}
		else if(!strcmp(argv[1],"-help--cn-zh")||!strcmp(argv[1],"-?--cn-zh"))
		{
			print_from_file("help cn-zh.txt");
			return 0;
		}
		else if(!strcmp(argv[1],"-clear")) return call_bat("del_ud.bat"),0;
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
			else call_bat("del_ud.bat");
		}
		else
		{
			if(strcmp(argv[5],"-clear")) tl=atoi(argv[5]);
			else call_bat("del_ud.bat");
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
		p[tpn].setid(tpn);
		p[tpn].settimelimit(tl);
		p[tpn].run(demo.data());
	}
	cout<<"Program End Successfully\n";
	cout<<"Testing Point Result:\n";
	for(int i=1;i<=tpn;i++)
	{
		p[i].print();
		cout<<' ';
		if(!p[i].getstate()) ac++;
		if(i%10==0) cout<<endl;
	}
	score=ac*1.0/tpn*100;
	cout<<"RESULT: "<<(int)(score+0.5)<<endl;
end:
	setcolor(0x07);
	return 0;
}
