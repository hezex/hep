#pragma once

#include"global.hpp"

const int forma_err=1;

void hep_error(int err){
		if(err==forma_err){
			puts("Forma Error\nPlease read the help carefully!");
			exit(0);
		}
		return;
}
struct option{
	
	//是否需要help or clean 
	bool help=false,cl=false;
	char *c[11];//储存命令 
	int cnt;//data文件个数
	int time;//时间限制 
	char correct[300];//对拍程序
	char wrong[300];//原程序
	char maker[300];//数据制造 
	
	bool is_number(char s[]){
		for(int i=0;i<strlen(s);i++)
			if(!isdigit(s[i]))
				return false;
		return true;
	}
	
	bool is_exe(char s[]){
		char *it=&s[strlen(s)-1];
		if(*it=='e'){
			it--;
			if(*it=='x'){
				it--;
				if(*it=='e'){
					it--;
					if(*it=='.')
						return true;
				}
			}
		}
		return false;
	} 
	
	inline void update_data(int len){
		if(len<5||!is_exe(c[1])||!is_exe(c[2])||!is_exe(c[3])||!is_number(c[4]))
			hep_error(forma_err);
		cnt=atoi(c[4]);
		if(len>5){
			if(!is_number(c[5]))
				hep_error(forma_err);
			time=atoi(c[5]);
		}
		return;
	}
	
	bool find_clear(int len,char *argv[]){
		for(int i=0;i<len;i++)
			if(!strcmp(argv[i],"/clear")||!strcmp(argv[i],"-clear")){
				for(int j=i;j<len-1;j++)
					swap(argv[i],argv[i+1]);
				return true;
			}
		return false;
	}
	
	option(int len,char *argv[]){
		for(int i=0;i<len;i++)
			c[i]=argv[i];
		if(!strcmp(argv[1],"-?")||!strcmp(argv[1],"-help")||!strcmp(argv[1],"/?")||!strcmp(argv[1],"-help")){
			help=true;
			if(len!=2)
				hep_error(forma_err);
		}else{
			cl=find_clear(len,c);
			update_data(len);
		}
		return;
	}
};
