#include "main_v5.h"

int main(int argc, char *argv[])
{
	estab_user_index();	
	estab_books_index();
	set_today_date();
	opration = 0;
	HANDLE h_thread_time,h_thread_library;

	h_thread_time=CreateThread(NULL,0,time_move,NULL ,0,NULL);//在无操作时推进日期 
	h_thread_library=CreateThread(NULL,0,library,NULL ,0,NULL);//用户界面 


	
	Sleep(200000000);	
	CloseHandle(h_thread_time);
	CloseHandle(h_thread_library);



	return 0;
}

DWORD WINAPI time_move(LPVOID pPararneter){
	while(opration >= 0) {//程序仍在运行
		if(opration == 0){//没有用户操作 
			today_date ++;
			cout << endl << "今天是" << today_date <<  "日" << endl ;
		} 
		Sleep(10000);
	} 

}

DWORD WINAPI library(LPVOID pPararneter){
	system("cls");
	
	cout << "LyuYing & LiZiqian 2017/5/22 21:56" << endl;
	int character = 0;//身份 
		
	while(character < 3){

		opration = 0;
		cout << "1 用户登录 2 管理员登录 3 退出系统" << endl;
	
		cin >> character; 
		cin.clear();
		cin.ignore(1024,'\n');//清除缓存区 
		cin.sync(); 
		while(character > 3 || character < 1){
			cout << "请输入正确的选项" << endl;
		 	cin >> character; 
			cin.clear();
			cin.ignore(1024,'\n');//清除缓存区 
			cin.sync(); 
		}
		
		if(character == 1){//有用户操作 
			opration = 1;	
			user_interface();	
			
		} else if(character == 2){
			opration = 1;
			admin_page(); 
			
		}		
		record_books_index();
		record_user_index();
		record_today_date();
	} 

	opration = -1;//程序结束 


	return 0;	
}



void set_today_date()
{
		
	stringstream stream;
	ifstream  fin("today_date.txt");
	string s_today_date;
	getline (fin, s_today_date);
	stream.clear();
	stream << s_today_date;
	stream >> today_date;
	fin.close();
}

void record_today_date()
{
	ofstream fout("today_date.txt");//为防止出错，测试时存入必用文件 	
	fout << today_date; 

	fout.close();
}

