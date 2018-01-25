/*********************************************************************************
*FileName:main.h // �ļ���
*Author:Li Ziqian //����
*Version: 3.0//�汾
*Date:2017/4/3 //�������
*Description:books,user��Ķ��� 
*Function List: //��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��

*History://�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸��߼��޸����ݼ��
//	user:������Ա 

	get_rent_num() 
	int rent_number;
	char ** rent_book_ID;//���10�� ÿ��9λ 


	class admin://����״������������  
		public user//�����̳е����� 
Date:2017/4/3 Programer:Lyu Ying 
// 
//	user:��Ա 
	ID
	user_name
	char ��Ϊ string
	���� 
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
//���캯������������û����д 




typedef  map <string, int> rent_map_type;//�ؼ���stringΪͼ���ţ� intΪ����ʱ�� ��������¼ 
typedef struct {
	string ID;//��ID
	int available_date;// ͼ��Ϊ�û���������ʼʱ�� ������û��ͼ��黹 ��Ϊ-1 
	 
}APPOINTMENT;


class user
{
	
	
	public:
 		user();
 		user (string set_ID,string set_name); 
		user (string set_ID, string set_name, int set_rent_number, rent_map_type  set_rent_record,int set_appointment_number,list<APPOINTMENT> set_appointment_list, int set_fine,int set_credit);
	 	string get_ID();
	 	string get_name();
	 	void rent_book(string book_ID);//������� 
	 	void return_book(string book_ID);//������� 
	 	void search_book();//������� 
		void user_signup();
		void user_information();
	 	void have_rent();//�����ѽ������� 
	 	
	 	rent_map_type get_rent_map();	 	
	 	int get_rent_num();//�������� 
	 	int get_in_num();//�ݲ��� 
	 	int get_appointment_num() ;
	 	list <APPOINTMENT> get_appointment_list();
	    int get_priviledge();//  ����֤���� ����Ȩ������
	/*��*/   int get_limit_date();//  ����Ȩ������  ���ؽ�������
	/*��*/   int  get_limit_rent_num();// ����Ȩ������  ���ؽ������� 
	/*��*/   int  get_fine();// 
	/*��*/   int  get_credit();// 
		int get_limit_appointment();// ����Ȩ������  ����ԤԼ������ 
		void refresh_appointment ();//ˢ��ԤԼ��¼ 
		void add_appointment(string book_ID); 
		void delete_appointment(string book_ID);
	    virtual ~user() {};   
	   
	private:

		string user_name;//ʹ���ߵ�����
	
		int rent_number;
		rent_map_type rent_record;
		// vector<string,int> rent_vector;
		int appointment_number;//ԤԼ�鼮���� 
		int fine;//������
		int credit;//���ż�¼ ÿ����һ������1 
		list <APPOINTMENT> appointment_list; //��¼ԤԼ����Ŀ�� 
		
	protected:
	 	string ID;//ʹ���ߵ�ID	
		
};


class books
{
	public:
		books();//default
		books(string set_ID, string set_name, string set_author, string set_press, string set_isbn, int set_year, int set_price, int set_total_num);//����ͼ�� 
		books(string set_ID, string set_name, string set_author, string set_press, string set_isbn, int set_year, int set_price, int set_total_num ,int set_rent_num, int set_rent_count, int set_appointment_num, list<APPOINTMENT> set_appointment_list);//����ͼ�� 

	/////////////////////////////////////get_private
		string get_name(); 
		string get_author();
		string get_press();
		string get_isbn(); 
		int get_time();
		int get_price(); //��λΪ�� 
		int get_total_num();
		int get_rent_num();
		int get_in_num();//�ڹ����� 
	 	int get_count_num();
		int get_appointment_num();
		int get_rent_rate(); 
	 	list <APPOINTMENT> get_appointment_list();
		void show_information(); 
		
	/////////////////////////////////////set_private
		void dec_rent_num();//�����ѽ�ͼ���� 
		void inc_rent_num();//���ӽ������ 
		
		void inc_rent_count();//���ӽ��������� 
		
		void add_appointment(string ID);//����ԤԼ��Ŀ 
		void delete_appointment(string ID); //����ԤԼ��Ŀ 
		void refresh_appointment ();//ˢ��ԤԼ��¼ 
		
		
	 	void rent_book();//������� 
	 	void return_book();//������� 
	 	void search_book();//������� 
	 	void have_rent();//�����ѽ������� 

	//////////////////////////////private 
	private:
		string book_ID;//���ID  ����Ϊ9 
		string book_name;//���� ����Ϊ30 
		string book_author;//���� ����Ϊ 
		string book_press;//������ ����Ϊ30 
		string book_isbn;//ISBN��  ����Ϊ15 
		int book_time;//����ʱ�� 
		int book_price;//�۸�
		int total_num;//�������
		int rent_num;//���ȥ������
		int rent_count;//ͳ�ƽ������˴���
		int appointment_num;//Ŀǰ��¼��ԤԼ������ 
		list <APPOINTMENT> appointment_list;
		//��һλΪԤԼ�˵�ID  �ڶ�λΪ ԤԼ�˿��Խ���Ŀ�ʼʱ�䡣��������˻����ܽ��飬������Ϊ-1 
	 	

	 
};





class admin:
	public user

//admin��̳���user�� 
{
	public:
		admin();
		void add_books();
		void delete_books();
		void add_user();
		void delete_user();
		void show(admin &admin_user);//�г��鼮��Ϣ
		void search_user();

	private:	
}; 



typedef  map <string, user *> user_map_type;//�ؼ���stringΪ֤���ţ�user*Ϊ������ָ��
typedef  map <string, int> rent_map_type;//�ؼ���stringΪͼ���ţ� intΪ����ʱ�� ��������¼ 
typedef  map <string, books *>  books_map_type;//�ؼ���stringΪͼ���ţ�book*Ϊ������ָ�� 



void estab_user_index();
void estab_books_index(); 
void user_interface();

void record_user_index();
void record_books_index();
void record_today_date();
void set_today_date();
void user_information( user *user_ptr);//��ӡ������Ϣ 
void search_by_name();
void search_by_ISBN(); 
void search_by_author();
void search_by_press(); 
void search_by_ID(); 




extern user_map_type user_map; 
extern books_map_type books_map; 
extern int today_date;
extern int opration;

void admin_choices();//����Ա���� 
void admin_page(); //����Աҳ�� 
DWORD WINAPI time_move(LPVOID pPararneter);//ʱ�����߳� 
DWORD WINAPI library(LPVOID pPararneter);//ͼ���ҳ����� 


void NEXT(const string&T,vector<int>&next) ;//KMP next
string::size_type COUNT_KMP(const string&S, const string&T);//KMP count 

void write_log(int type, string user_name, string book_ID);//д��־ ��һλ 0 Ϊ �� 1 Ϊ ��  


