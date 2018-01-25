/*******************************************************************************
*FileName:admin.cpp // �ļ���
*Author:Li Ziqian //����
*Version: 1.0//�汾
*Date:2017/4/3 //�������
*Description:����Ա��½���� 
*Function List:admin_page��admin_choices 
*History:1.2017/4/4���������ļ���������⣬��ַ��д��//����֪��Ϊʲô 
*******************************************************************************/

#include<fstream>
#include<cstdlib>//�൱��stdlib.h  
#include<iostream>
#include<cstring>
#include<string>
#include "main_v5.h"


using namespace std;

void admin_page()
{

	string s,password;
	int i;

	ifstream p_file("password.txt");
	if(!p_file)
		{
		cerr<<"open password.txt failed"<<endl;
		exit(1);
	}

	getline (p_file, password);
//	cout << password << endl;
	p_file.close();

restart:
	cout << "���������Ա����:------\b\b\b\b\b\b";
	cin >> s;
//	cout << s << endl;

	if(password == s)
	{ 
		cout<<"��¼�ɹ���"<<endl;
		admin_choices();
	}
	else {
		int ch;
		cout<<"���������������������룡"<<endl;
		cout<<"���������������� 1 �������� 2"<<endl;
		cin>>ch;
		if(ch==1) 
			{	return;}
		goto restart;
	}
}
void admin_choices()
{
	int choice;
	admin admin_cur;
	cout<<"==========================================����Ա����=========================================="<<endl;
	int cycle = 1;
	while(cycle){
		cout<<"					1-����ͼ��					 "<<endl;
		cout<<"					2-ɾ��ͼ��					 "<<endl;
		cout<<"					3-�����û�					 "<<endl;
		cout<<"					4-ɾ���û�					 "<<endl;
		cout<<"					5-����ͼ��			 "<<endl;
		cout<<"					6-�����û�			 "<<endl;
		cout<<"					7-�˳�			 "<<endl;
		reput:
		cout<<"��������Ҫ���еĲ�����-\b";
		cin>>choice;
		switch(choice){
			case 1:admin_cur.add_books();break;
			case 2:admin_cur.delete_books();break;
			case 3:admin_cur.add_user();break;
			case 4:admin_cur.delete_user();break;
			case 5:admin_cur.search_book();break; 
			case 6:admin_cur.search_user();break;
			case 7:cycle = 0;break; 
			default:{cout<<"����������������룡"<<endl;
			        cin.clear();
			        goto reput;
				} 
		}	
	}

}

admin::admin()
{
	
} 
void admin::add_books()
{
	string book_ID;//���ID 
	char book_ID_cur[9]; 
	string book_name_cur;//����
	string author_cur;//����
	string press_cur;//������
	string isbn_cur;//ISBN�� 
	int time_cur;//����ʱ�� 
	int price_cur;//�۸�
	int num_cur;//������� 
	int i;
	int ch; 
     putin:
	cout<<"������������------\b\b\b\b\b\b";
	cin>>book_name_cur;
	cout<<"���������ߣ�------\b\b\b\b\b\b";
	cin>>author_cur;
	cout<<"����������磺------\b\b\b\b\b\b";
	cin>>press_cur;
	cout<<"������ISBN�ţ�------\b\b\b\b\b\b";
	cin>>isbn_cur;
//	cout<<"�����빺��ʱ�䣺------\b\b\b\b\b\b";
	time_cur = today_date; 
	cout<<"�����뵥�ۣ���λΪ�֣���------\b\b\b\b\b\b";
	cin>>price_cur;
	cout<<"�����빺��������------\b\b\b\b\b\b";
	cin>>num_cur;
	//�����¹���ͼ�����ˮ��
	cout<<"������ͼ������ͣ�"<<endl;
     cout <<"		01��������ë��˼��			02��ѧ\n"
          <<"		03����ѧ����				04���Ρ�����\n"
	    	<<"		05����					06����\n"
	    	<<"		07�Ļ�����ѧ������������		08���ԡ�����\n"
	    	<<"		09��ѧ					10����\n"
	    	<<"		11��ʷ������				12��Ȼ��ѧ����\n"
	    	<<"		13�����ѧ�ͻ�ѧ			14����ѧ�������ѧ\n"
	    	<<"		15�����ѧ				16ҽҩ������\n"
	    	<<"		17ũҵ��ѧ				18��ҵ����\n"
	    	<<"		19��ͨ����				20���ա�����\n"
	    	<<"		21������ѧ����ȫ��ѧ			22�ۺ���ͼ��\n"
	    	<<endl; 
 	cin>> book_ID_cur[0] >> book_ID_cur[1];
	cout<< "��������������ͣ�---\b\b\b";
	cout<<"		01���ڳ�����		02���������"<<endl;//Ӧ�ú���һ��һ�����г����ù���Ա����ѡ��
 	cin>> book_ID_cur[2] >> book_ID_cur[3];
 	cin.clear();
 	for(i=4;i<9;i++){
	 	book_ID_cur[i]='0'+rand()%10 ;
	 }
	book_ID =  book_ID_cur;
//����	
	
	books_map_type::iterator it_find;
	it_find = books_map.find( book_ID );
	while(it_find!= books_map.end()){//����ظ� 
	 	for(i=4;i<9;i++){
		 	book_ID_cur[i]='0'+rand()%10 ;
		 }
		book_ID =  book_ID_cur;
		it_find = books_map.find( book_ID );
	}

	
 	cout << "����ͼ������ӦΪ��" ; 
	
	cout << book_ID << endl; 
	
	
 //����͵ðѴ浽������Ķ����浽�ļ�����ȥ��
	books * new_book_ptr = new books;
	*  new_book_ptr = books(book_ID,book_name_cur,author_cur,press_cur,isbn_cur,time_cur,price_cur,num_cur);	
	books_map.insert(pair<string, books*>(book_ID, new_book_ptr));
	
	 record_books_index() ; 


   //books_information[kinds_of_books]=&a;
	ofstream books_out("books_information.txt");
//	books_out.write((char*)&a,sizeof(a));
  	putagain:
 	cout << "��������ͼ���밴1����0�ص�����Ա��ʼ���� --\b\b";
	cin >> ch;
	cin.clear();
	cin.ignore(1024,'\n');//��������� 
	cin.sync(); 
	switch(ch){
		case 0: return;break;
		case 1: goto putin;break;
		default:cout<<"�����������������!"<<endl;
		goto putagain;
		}
} 
void admin::delete_books()
{
//	cout<<"����delete_books"; 
	cout << "������Ҫɾ�������ID" << endl;
	string delete_book_ID;
	cin >> delete_book_ID;
	books_map_type::iterator it_find;
	it_find = books_map.find( delete_book_ID );
 	if (it_find != books_map.end()){	
 		string book_name;
 		book_name = it_find->second-> get_name();
	  	if(it_find->second-> get_rent_num() == 0){//ͼ��ȫ���ڹ� 
		 	books_map.erase(it_find);
	 		cout << "ͼ��ɾ���ɹ�" << endl; 	  	
	  	}
	  	else{
	  		cout << "ͼ������У��޷�����ɾ������" << endl; 
	  	}

 	}
 	else{
 		cout << "���޴���" << endl; 
	 }
	 

}
void admin::add_user()
{
//	cout<<"����add_user";				
	cout << "�������û���ѧ�Ż򹤺�:";
	string add_user_ID;
	cin >> add_user_ID;
	user_map_type::iterator it_find;
	it_find = user_map.find( add_user_ID );
 	if (it_find != user_map.end()){	
 		cout << "���û�����ͼ���ע�ᡣ" << endl; 		
 	}
 	else{
 		cout << "�������û�������" << endl; 
 		string add_user_name;
 		cin >> add_user_name;  
		user * new_user_ptr = new user;
		*  new_user_ptr = user(add_user_ID,add_user_name); 
		user_map.insert(pair<string, user*>(add_user_ID, new_user_ptr));
		record_user_index(); 
	 }

}
void admin::delete_user()
{
//	cout<<"����delete_user";
	cout << "������Ҫɾ�����û���ID" << endl;
	string delete_user_ID;
	cin >> delete_user_ID;
	user_map_type::iterator it_find;
	it_find = user_map.find( delete_user_ID );
 	if (it_find != user_map.end()){	
 		string delete_user_name;
 		delete_user_name = it_find->second-> get_name();
	  	if(it_find->second-> get_rent_num() == 0){//ͼ��ȫ���ڹ� 
		 	user_map.erase(it_find);
	 		cout << "�û�"<< delete_user_name << "ɾ���ɹ�" << endl; 	  	
	  	}
	  	else{
	  		cout << "�û�" << delete_user_name << "����ͼ����δ�黹���޷�����ɾ������" << endl; 
	  	}

 	}
 	else{
 		cout << "���޴���" << endl; 
	 }


}

void admin::search_user()
{
	cout << "������Ҫ���ҵ��û���ID" << endl;
	string find_user_ID;
	cin >> find_user_ID;
	user_map_type::iterator it_find;
	it_find = user_map.find( find_user_ID );
 	if (it_find != user_map.end()){	
 		it_find->second->user_information();

 	}
 	else{
 		cout << "���޴���" << endl; 
	 }

}

