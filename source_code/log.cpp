#include "main_v5.h"
void write_log(int type, string user_name, string book_ID){//д��־ ��һλ 0 Ϊ �� 1 Ϊ ��  
	ofstream fout((book_ID+".txt").c_str(),ios::app);
	string operate_type;
	if(type == 0){
		operate_type = "����"; 
	}else{
		operate_type = "�黹"; 
	} 
	
	fout << today_date << "��\t" << user_name<< "\t" << operate_type << endl;
	fout.close();	
	
	
	
} 
