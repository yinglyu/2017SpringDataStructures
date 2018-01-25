/*********************************************************************************
*FileName:main.h // 文件名
*Author:Li Ziqian //作者
*Version: 3.0//版本
*Date:2017/4/3 //完成日期
*Description:books,user类的定义 
*Function List: //主要函数列表，每条记录应包含函数名及功能简要说明

*History://修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
//	user:新增成员 

	get_rent_num() 
	int rent_number;
	char ** rent_book_ID;//最多10个 每个9位 


	class admin://由形状类派生矩形类  
		public user//更正继承的声明 
Date:2017/4/3 Programer:Lyu Ying 
// 
//	user:成员 
	ID
	user_name
	char 改为 string
	增加 
	user(string set_ID, string set_name, int set_rent_number,  char ** set_rent_book_ID);
// 
**********************************************************************************/  

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream> 
#include <map> 
#include <sstream>
#include <windows.h> 
#include <vector>
#include <list>

using namespace std;
//构造函数和析构函数没具体写 




typedef  map <string, int> rent_map_type;//关键字string为图书编号， int为借书时间 保存借书记录 
typedef struct {
	string ID;//用ID
	int available_date;// 图书为用户保留的起始时间 ，若还没有图书归还 则为-1 
	 
}APPOINTMENT;


class user
{
	
	
	public:
 		user();
 		user (string set_ID,string set_name); 
		user (string set_ID, string set_name, int set_rent_number, rent_map_type  set_rent_record,int set_appointment_number,list<APPOINTMENT> set_appointment_list, int set_fine,int set_credit);
	 	string get_ID();
	 	string get_name();
	 	void rent_book(string book_ID);//借书操作 
	 	void return_book(string book_ID);//还书操作 
	 	void search_book();//查书操作 
		void user_signup();
		void user_information();
	 	void have_rent();//查找已借数操作 
	 	
	 	rent_map_type get_rent_map();	 	
	 	int get_rent_num();//借书数量 
	 	int get_in_num();//馆藏数 
	 	int get_appointment_num() ;
	 	list <APPOINTMENT> get_appointment_list();
	    int get_priviledge();//  根据证件号 返回权限类型
	/*新*/   int get_limit_date();//  根据权限类型  返回借书期限
	/*新*/   int  get_limit_rent_num();// 根据权限类型  返回借书上限 
	/*新*/   int  get_fine();// 
	/*新*/   int  get_credit();// 
		int get_limit_appointment();// 根据权限类型  返回预约书上限 
		void refresh_appointment ();//刷新预约记录 
		void add_appointment(string book_ID); 
		void delete_appointment(string book_ID);
	    virtual ~user() {};   
	   
	private:

		string user_name;//使用者的姓名
	
		int rent_number;
		rent_map_type rent_record;
		// vector<string,int> rent_vector;
		int appointment_number;//预约书籍本数 
		int fine;//罚款金额
		int credit;//诚信记录 每逾期一次增加1 
		list <APPOINTMENT> appointment_list; //记录预约的数目。 
		
	protected:
	 	string ID;//使用者的ID	
		
};


class books
{
	public:
		books();//default
		books(string set_ID, string set_name, string set_author, string set_press, string set_isbn, int set_year, int set_price, int set_total_num);//新增图书 
		books(string set_ID, string set_name, string set_author, string set_press, string set_isbn, int set_year, int set_price, int set_total_num ,int set_rent_num, int set_rent_count, int set_appointment_num, list<APPOINTMENT> set_appointment_list);//新增图书 

	/////////////////////////////////////get_private
		string get_name(); 
		string get_author();
		string get_press();
		string get_isbn(); 
		int get_time();
		int get_price(); //单位为分 
		int get_total_num();
		int get_rent_num();
		int get_in_num();//在馆数量 
	 	int get_count_num();
		int get_appointment_num();
		int get_rent_rate(); 
	 	list <APPOINTMENT> get_appointment_list();
		void show_information(); 
		
	/////////////////////////////////////set_private
		void dec_rent_num();//更改已借图书数 
		void inc_rent_num();//增加借出数量 
		
		void inc_rent_count();//增加借阅总人数 
		
		void add_appointment(string ID);//增加预约条目 
		void delete_appointment(string ID); //减少预约条目 
		void refresh_appointment ();//刷新预约记录 
		
		
	 	void rent_book();//借书操作 
	 	void return_book();//还书操作 
	 	void search_book();//查书操作 
	 	void have_rent();//查找已借数操作 

	//////////////////////////////private 
	private:
		string book_ID;//书的ID  长度为9 
		string book_name;//书名 长度为30 
		string book_author;//作者 长度为 
		string book_press;//出版社 长度为30 
		string book_isbn;//ISBN号  长度为15 
		int book_time;//购入时间 
		int book_price;//价格
		int total_num;//书的总数
		int rent_num;//借出去的数量
		int rent_count;//统计借阅总人次数
		int appointment_num;//目前记录的预约人数量 
		list <APPOINTMENT> appointment_list;
		//第一位为预约人的ID  第二位为 预约人可以借书的开始时间。如果借书人还不能借书，就设置为-1 
	 	

	 
};





class admin:
	public user

//admin类继承于user类 
{
	public:
		admin();
		void add_books();
		void delete_books();
		void add_user();
		void delete_user();
		void show(admin &admin_user);//列出书籍信息
		void search_user();

	private:	
}; 



typedef  map <string, user *> user_map_type;//关键字string为证件号，user*为书对象的指针
typedef  map <string, int> rent_map_type;//关键字string为图书编号， int为借书时间 保存借书记录 
typedef  map <string, books *>  books_map_type;//关键字string为图书编号，book*为书对象的指针 



void estab_user_index();
void estab_books_index(); 
void user_interface();

void record_user_index();
void record_books_index();
void record_today_date();
void set_today_date();
void user_information( user *user_ptr);//打印读者信息 
void search_by_name();
void search_by_ISBN(); 
void search_by_author();
void search_by_press(); 
void search_by_ID(); 




extern user_map_type user_map; 
extern books_map_type books_map; 
extern int today_date;
extern int opration;

void admin_choices();//管理员操作 
void admin_page(); //管理员页面 
DWORD WINAPI time_move(LPVOID pPararneter);//时间轴线程 
DWORD WINAPI library(LPVOID pPararneter);//图书馆页面进程 


void NEXT(const string&T,vector<int>&next) ;//KMP next
string::size_type COUNT_KMP(const string&S, const string&T);//KMP count 

void write_log(int type, string user_name, string book_ID);//写日志 第一位 0 为 借 1 为 还  


