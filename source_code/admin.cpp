/*******************************************************************************
*FileName:admin.cpp // 文件名
*Author:Li Ziqian //作者
*Version: 1.0//版本
*Date:2017/4/3 //完成日期
*Description:管理员登陆界面 
*Function List:admin_page和admin_choices 
*History:1.2017/4/4中午解决了文件读入的问题，地址得写成//还不知道为什么 
*******************************************************************************/

#include<fstream>
#include<cstdlib>//相当于stdlib.h  
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
	cout << "请输入管理员密码:------\b\b\b\b\b\b";
	cin >> s;
//	cout << s << endl;

	if(password == s)
	{ 
		cout<<"登录成功！"<<endl;
		admin_choices();
	}
	else {
		int ch;
		cout<<"输入密码有误！请重新输入！"<<endl;
		cout<<"返回主界面请输入 1 继续输入 2"<<endl;
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
	cout<<"==========================================管理员界面=========================================="<<endl;
	int cycle = 1;
	while(cycle){
		cout<<"					1-增加图书					 "<<endl;
		cout<<"					2-删减图书					 "<<endl;
		cout<<"					3-增加用户					 "<<endl;
		cout<<"					4-删减用户					 "<<endl;
		cout<<"					5-查找图书			 "<<endl;
		cout<<"					6-查找用户			 "<<endl;
		cout<<"					7-退出			 "<<endl;
		reput:
		cout<<"请输入您要进行的操作：-\b";
		cin>>choice;
		switch(choice){
			case 1:admin_cur.add_books();break;
			case 2:admin_cur.delete_books();break;
			case 3:admin_cur.add_user();break;
			case 4:admin_cur.delete_user();break;
			case 5:admin_cur.search_book();break; 
			case 6:admin_cur.search_user();break;
			case 7:cycle = 0;break; 
			default:{cout<<"输入错误，请重新输入！"<<endl;
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
	string book_ID;//书的ID 
	char book_ID_cur[9]; 
	string book_name_cur;//书名
	string author_cur;//作者
	string press_cur;//出版社
	string isbn_cur;//ISBN号 
	int time_cur;//购入时间 
	int price_cur;//价格
	int num_cur;//书的总数 
	int i;
	int ch; 
     putin:
	cout<<"请输入书名：------\b\b\b\b\b\b";
	cin>>book_name_cur;
	cout<<"请输入作者：------\b\b\b\b\b\b";
	cin>>author_cur;
	cout<<"请输入出版社：------\b\b\b\b\b\b";
	cin>>press_cur;
	cout<<"请输入ISBN号：------\b\b\b\b\b\b";
	cin>>isbn_cur;
//	cout<<"请输入购入时间：------\b\b\b\b\b\b";
	time_cur = today_date; 
	cout<<"请输入单价（单位为分）：------\b\b\b\b\b\b";
	cin>>price_cur;
	cout<<"请输入购入数量：------\b\b\b\b\b\b";
	cin>>num_cur;
	//生成新购入图书的流水号
	cout<<"请输入图书的类型："<<endl;
     cout <<"		01马列主义毛邓思想			02哲学\n"
          <<"		03社会科学总论				04政治、法律\n"
	    	<<"		05军事					06经济\n"
	    	<<"		07文化、科学、教育、体育		08语言、文字\n"
	    	<<"		09文学					10艺术\n"
	    	<<"		11历史、地理				12自然科学总论\n"
	    	<<"		13数理科学和化学			14天文学、地球科学\n"
	    	<<"		15生物科学				16医药、卫生\n"
	    	<<"		17农业科学				18工业技术\n"
	    	<<"		19交通运输				20航空、航天\n"
	    	<<"		21环境科学、安全科学			22综合性图书\n"
	    	<<endl; 
 	cin>> book_ID_cur[0] >> book_ID_cur[1];
	cout<< "请输入出版社类型：---\b\b\b";
	cout<<"		01国内出版社		02国外出版社"<<endl;//应该和上一步一样都列出来让管理员进行选择
 	cin>> book_ID_cur[2] >> book_ID_cur[3];
 	cin.clear();
 	for(i=4;i<9;i++){
	 	book_ID_cur[i]='0'+rand()%10 ;
	 }
	book_ID =  book_ID_cur;
//查重	
	
	books_map_type::iterator it_find;
	it_find = books_map.find( book_ID );
	while(it_find!= books_map.end()){//编号重复 
	 	for(i=4;i<9;i++){
		 	book_ID_cur[i]='0'+rand()%10 ;
		 }
		book_ID =  book_ID_cur;
		it_find = books_map.find( book_ID );
	}

	
 	cout << "新增图书的序号应为：" ; 
	
	cout << book_ID << endl; 
	
	
 //下面就得把存到数组里的东西存到文件里面去了
	books * new_book_ptr = new books;
	*  new_book_ptr = books(book_ID,book_name_cur,author_cur,press_cur,isbn_cur,time_cur,price_cur,num_cur);	
	books_map.insert(pair<string, books*>(book_ID, new_book_ptr));
	
	 record_books_index() ; 


   //books_information[kinds_of_books]=&a;
	ofstream books_out("books_information.txt");
//	books_out.write((char*)&a,sizeof(a));
  	putagain:
 	cout << "继续导入图书请按1，按0回到管理员初始界面 --\b\b";
	cin >> ch;
	cin.clear();
	cin.ignore(1024,'\n');//清除缓存区 
	cin.sync(); 
	switch(ch){
		case 0: return;break;
		case 1: goto putin;break;
		default:cout<<"输入错误，请重新输入!"<<endl;
		goto putagain;
		}
} 
void admin::delete_books()
{
//	cout<<"调用delete_books"; 
	cout << "请输入要删除的书的ID" << endl;
	string delete_book_ID;
	cin >> delete_book_ID;
	books_map_type::iterator it_find;
	it_find = books_map.find( delete_book_ID );
 	if (it_find != books_map.end()){	
 		string book_name;
 		book_name = it_find->second-> get_name();
	  	if(it_find->second-> get_rent_num() == 0){//图书全部在馆 
		 	books_map.erase(it_find);
	 		cout << "图书删除成功" << endl; 	  	
	  	}
	  	else{
	  		cout << "图书外借中，无法进行删除操作" << endl; 
	  	}

 	}
 	else{
 		cout << "查无此书" << endl; 
	 }
	 

}
void admin::add_user()
{
//	cout<<"调用add_user";				
	cout << "请输入用户的学号或工号:";
	string add_user_ID;
	cin >> add_user_ID;
	user_map_type::iterator it_find;
	it_find = user_map.find( add_user_ID );
 	if (it_find != user_map.end()){	
 		cout << "此用户已在图书馆注册。" << endl; 		
 	}
 	else{
 		cout << "请输入用户的姓名" << endl; 
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
//	cout<<"调用delete_user";
	cout << "请输入要删除的用户的ID" << endl;
	string delete_user_ID;
	cin >> delete_user_ID;
	user_map_type::iterator it_find;
	it_find = user_map.find( delete_user_ID );
 	if (it_find != user_map.end()){	
 		string delete_user_name;
 		delete_user_name = it_find->second-> get_name();
	  	if(it_find->second-> get_rent_num() == 0){//图书全部在馆 
		 	user_map.erase(it_find);
	 		cout << "用户"<< delete_user_name << "删除成功" << endl; 	  	
	  	}
	  	else{
	  		cout << "用户" << delete_user_name << "仍有图书尚未归还，无法进行删除操作" << endl; 
	  	}

 	}
 	else{
 		cout << "查无此人" << endl; 
	 }


}

void admin::search_user()
{
	cout << "请输入要查找的用户的ID" << endl;
	string find_user_ID;
	cin >> find_user_ID;
	user_map_type::iterator it_find;
	it_find = user_map.find( find_user_ID );
 	if (it_find != user_map.end()){	
 		it_find->second->user_information();

 	}
 	else{
 		cout << "查无此人" << endl; 
	 }

}

