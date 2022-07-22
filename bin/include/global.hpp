#pragma once

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

//#include "point.hpp"

int tpcolor[5]={CTC_GW,CTC_RW,CTC_BW,CTC_PW,CTC_BW};
char tpsign[5][16]={"[AC]","[WA]","[TLE]","[RE]","[UKE]"};

void setcolor(char c);
void copydata(int number);
void clean();
void print_from_file(const char *file_name);
void call_bat(const char *file_name);


using namespace std;

void setcolor(char c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void copydata(int number)
{
	string demo("copy data.in .\\UnacceptedData\\data");
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

void print_from_file(const char *file_name)
{
	string path=".\\bin\\text\\";
	path+=file_name;
	freopen(path.data(),"r",stdin);
	char c=getchar();
	while(c&&c!=EOF)
	{
		putchar(c);
		c=getchar();
	}
	fclose(stdin);
}

void call_bat(const char *file_name)
{
	string path=".\\bin\\bat\\";
	path+=file_name;
	system(path.data());
}
