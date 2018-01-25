#include "main_v5.h"
void write_log(int type, string user_name, string book_ID){//写日志 第一位 0 为 借 1 为 还  
	ofstream fout((book_ID+".txt").c_str(),ios::app);
	string operate_type;
	if(type == 0){
		operate_type = "借阅"; 
	}else{
		operate_type = "归还"; 
	} 
	
	fout << today_date << "日\t" << user_name<< "\t" << operate_type << endl;
	fout.close();	
	
	
	
} 
