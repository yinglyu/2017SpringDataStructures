#include "main_v5.h"

int today_date ;
int opration;//判断是否在进行操作 
user_map_type user_map; 
books_map_type books_map; 


 user::user()
{

	ID = "0000000";
	
	
}

user::	user(string set_ID, string set_name){// 新建用户的构造函数 
	ID = set_ID;
	user_name = set_name;
	rent_number = 0;
	appointment_number = 0;
	credit = 0;
	fine = 0; 
} 


user::	user(string set_ID, string set_name, int set_rent_number, rent_map_type  set_rent_record, int set_appointment_number, list<APPOINTMENT> set_appointment_list, int set_fine,int set_credit){
	int i,j;
	ID = set_ID; 
	user_name =set_name;
	rent_number = set_rent_number;//借书数量 
	rent_record = set_rent_record; //借书记录 
	
	rent_map_type::iterator it_rent;
	it_rent = set_rent_record.begin();
		cout << endl << "构造" << endl; 
	while(it_rent != set_rent_record.end()){
		string book_ID = it_rent -> first;
		int rent_time = it_rent -> second; 	

		rent_record.insert(pair<string, int>(book_ID, rent_time));	
		it_rent ++;
	}

	
	appointment_number = set_appointment_number;
	appointment_list = set_appointment_list;  
	fine = set_fine;//罚款金额 
	credit = set_credit; //违约次数 
	

}

string user:: get_ID()
{

	return ID;
} 
string user:: get_name()
{

	return user_name;	
}

int user::get_rent_num()
{
	return rent_number;
}




rent_map_type user::get_rent_map()
{
	return rent_record;
}

int  user::get_appointment_num()
{
	return appointment_number;
}



list<APPOINTMENT>   user::get_appointment_list()
{
	return appointment_list;
}



int user::get_priviledge()//1 为学生 2 为教师 
{
	char c = ID[0];
	int privilege=(int) c -48;
	return privilege; 
}



int user::get_limit_date()
{
	return 30*get_priviledge();	//学生 可借 30天 老师 可借 60天	
}

int user::get_limit_rent_num()
{
	return 10*get_priviledge();//学生 可借 10本 老师 可借 20本	
}

int user::get_limit_appointment()
{
	return 5*get_priviledge();//学生 可预约 5本 老师 可预约 10本	
}

int user::get_fine()
{
	return fine;//罚款金额 
}

int user::get_credit()
{
	return credit;//违约次数 
} 
void user::add_appointment(string book_ID){//独立delete 
	APPOINTMENT set_appointment;
	set_appointment.ID = book_ID; 
	set_appointment.available_date = -1;//初值	
			
			
	appointment_list.push_back(set_appointment) ;
	appointment_number ++;		
}

void user::delete_appointment(string book_ID){//驱动 book 的delete 
	list <APPOINTMENT>::iterator it_list ;
		
	it_list =appointment_list.begin();
	int i = 0, exist = 0 ;
	while (it_list != appointment_list.end() && i< appointment_number && exist == 0){
		if(it_list->ID == book_ID) {
			exist = 1;
		}
		else{
			it_list++;
		}
	} 
	if(exist == 1){//找到记录 
		appointment_list.erase(it_list);//成功删除 
		appointment_number --;
		cout << "成功删除预约记录" << endl; 
		//删除书中的记录
		books_map_type ::iterator it_book  = books_map.find(book_ID);
		books * book_ptr = it_book->second;
		book_ptr->delete_appointment(ID); 
 
	}
		
}

void user::refresh_appointment ()//刷新预约记录 
{
	if (appointment_number > 0 ){
		cout << "预约数 为 "<< appointment_number << endl; 
		list <APPOINTMENT>::iterator it_list ;
		
		it_list =appointment_list.begin();
		int i = 0;
		while (it_list != appointment_list.end() && i< appointment_number){
			i++;
			string book_ID =  it_list -> ID;
			books_map_type::iterator book_it;
			book_it = books_map.find(book_ID);
			if(book_it != books_map.end()){
				books* book_ptr = book_it->second;
				book_ptr->refresh_appointment();
				list <APPOINTMENT> book_appointment_list = book_ptr->get_appointment_list(); 
				list <APPOINTMENT>::iterator user_it = book_appointment_list.begin();//
				int exist = 0;
				while(user_it != book_appointment_list.end() && exist == 0){
					if(user_it-> ID == ID){//图书中找到用户条目
						it_list -> available_date = user_it -> available_date; 
						exist = 1;
					} 
					
					user_it++;
				}
				if(exist == 0){//没有找到 
				  list <APPOINTMENT>::iterator	it_save = it_list; 
				  appointment_list.erase(it_save);	
				  appointment_number --;		
				}
				
			}else{//图书记录错误 删除读者这里的预约记录 
			  list <APPOINTMENT>::iterator	it_save = it_list; 
			  appointment_list.erase(it_save);
			  appointment_number --;	
			}
			it_list ++; 
		} 	
	}

}

void user::search_book()
{
	
	int cycle = 1;
	while(cycle){
			cout << "请选择查询方式\n==========================================" << endl;
			cout << "1 书名 2 ISBN 3 作者 4 出版社 5 馆藏编号 6 返回" << endl;  
			int search_type;
			cin >> search_type;
			while(search_type < 1 || search_type > 6 ){
				cout << "请输入正确的选项" << endl;
			 	cin >> search_type; 
				cin.clear();
				cin.ignore(1024,'\n');//清除缓存区 
				cin.sync(); 		
			} 		 
			switch(search_type){
				case 1: search_by_name(); break;
				case 2: search_by_ISBN(); break;
				case 3: search_by_author(); break;
				case 4: search_by_press(); break;
				case 5: search_by_ID(); break;
				case 6: cycle = 0 ; break; 
				default :cout << "No way!" <<endl; break; 
			}		
		
	}



}
void user::return_book(string book_ID)//还书操作 
{
	rent_map_type::iterator find_it;
	find_it = rent_record.find(book_ID);
	if(find_it != rent_record.end()) {//有借书记录 
		
		cout << "还书成功" << endl;
		int rent_date = find_it ->second; 
		rent_record.erase(find_it);//读者记录删除
		rent_number --;
		books_map_type ::iterator book_it = books_map.find(book_ID);
		if(book_it !=  books_map.end()) {//图书记录存在 
			books * book_ptr = book_it->second;//书记录改变 
			book_ptr->dec_rent_num();
			book_ptr->refresh_appointment(); 
			if(today_date - rent_date > get_limit_date()){
				
				int inc_fine  = book_ptr->get_price() * (today_date - rent_date -get_limit_date() )/100 ;
				cout << "罚款" <<inc_fine/100 << "." <<  (inc_fine % 100)/10 << inc_fine % 10 << "元"<< endl; 
				
				fine = fine+ inc_fine;
				credit ++;
			}
			
			write_log(1,user_name,book_ID);//写日志 
		}else{
			cout << "图书记录出错" << endl; 
		} 

		
	}else{//1.不在已借书中 
		cout << "未借阅此书" << endl; 
	} 

}






void user::rent_book(string book_ID)//条件 1&2 读者可以借书，这本书没借过 
{//需判断  			//3.图书是否存在	存在才行	
					//4.有没有馆藏 
					//5.预约可借？
					//6.不在预约不可借书中？ 
					//7.没有预约 判断馆藏数 - 预约数是否大于 0  
					
		books_map_type::iterator find_it; 
		find_it = books_map.find(book_ID);
		if(find_it != books_map.end()){//图书存在 
			cout << "找到图书" << endl; 
			books * ptr_book = find_it -> second; 
			
			if(ptr_book->get_in_num() > 0){//图书有馆藏
				cout << "图书有馆藏" << endl; 
				
				if(appointment_number > 0){//读者有预约记录 
					list <APPOINTMENT> ::iterator find_it = appointment_list.begin();
					int exist = 0, valid = 0;
					while(find_it != appointment_list.end() && exist ==0){
						if(find_it ->ID == book_ID){
							exist =1;
							if(find_it ->available_date > 0){
								valid = 1;
								appointment_list.erase(find_it) ;//删除条目 
								rent_number ++;
								 
								rent_record.insert(pair<string, int>(book_ID, today_date));	
								ptr_book->inc_rent_num();
								ptr_book->inc_rent_count();
								ptr_book->delete_appointment(ID);
 								cout << "借书成功" << endl;
								cout << "书籍信息" << endl;
								ptr_book->show_information();
								write_log(0,user_name,book_ID);								
							}
						}else{
							find_it ++;
						}
						
					}
					if(exist == 0 ){//不存在这一条 
						if(ptr_book->get_appointment_num() < ptr_book->get_in_num()){//可以借 
							rent_number ++;
							rent_record.insert(pair<string, int>(book_ID, today_date));	
							ptr_book->inc_rent_num();
							ptr_book->inc_rent_count();
							write_log(0,user_name,book_ID);
							
						}else{
							cout << "图书不可借" << endl; 
							if(appointment_number < get_limit_appointment()){
								cout << " 可以选择预约 预约 1 不预约 0" << endl;
								int app;
								cin >> app;
								if(app){ 
									add_appointment(book_ID);//自带num++； 
									ptr_book ->add_appointment(ID);//自带num++	
								}						
							} 
	
							 
						} 						
					}else if(exist == 1 && valid== 0){
						cout << "预约尚未轮到" << endl; 
					}
									
				}
				else{//读者没有预约记录 
					if(ptr_book->get_appointment_num() < ptr_book->get_in_num()){//可以借 
						rent_number ++;
						rent_record.insert(pair<string, int>(book_ID, today_date));	
						ptr_book->inc_rent_num();
						ptr_book->inc_rent_count();
						cout << "借书成功" << endl;
						cout << "书籍信息" << endl;
						ptr_book->show_information();
						write_log(0,user_name,book_ID);
						
					}else{
						cout << "图书不可借" << endl; 
						if(appointment_number < get_limit_appointment()){
							cout << " 可以选择预约 预约 1 不预约 0" << endl;
							int app;
							cin >> app;
							if(app){ 
								add_appointment(book_ID);//自带num++； 
								ptr_book ->add_appointment(ID);//自带num++	
							}						
						} 

						 
					} 
				} 

				
				
				
			
			
			}else{//图书无馆藏 //也可能预约过 
				cout << "图书存在，但无馆藏" << endl; 
				if(appointment_number > 0){//有预约记录 
					if(appointment_number < get_limit_appointment()){//可以预约
					
					
					
						list <APPOINTMENT> ::iterator find_it = appointment_list.begin();
						int exist = 0, valid = 0;
						while(find_it != appointment_list.end() && exist ==0){
							if(find_it ->ID == book_ID){
								exist =1;
							
							}else{
								find_it ++;
							}
							
						}
						if(exist == 0 ){//不存在这一条 
				//判断是否预约过 
							cout << " 可以选择预约 预约 1 不预约 0" << endl;
							int app;
							cin >> app;
							if(app){ 
								add_appointment(book_ID);//自带num++； 
								ptr_book ->add_appointment(ID);//自带num++	
							}						
																				
						}else if(exist == 1 ){
							cout << "预约尚未轮到" << endl; 
						}					
					
						
					} else{
						cout << "预约已满无法选择预约" << endl; 
					}				
						
				}else{//没有预约记录可以预约 

					cout << " 可以选择预约 预约 1 不预约 0" << endl;
					int app;
					cin >> app;
					if(app){ 
						add_appointment(book_ID);//自带num++； 
						ptr_book ->add_appointment(ID);//自带num++	
					}
					
				} //没有预约记录可以预约 
			}
			
			
		}else{//图书不存在 
			cout << "未找到图书" << endl; 
		}
		
		


} 


void user::user_information(){//打印读者信息 

	if(get_priviledge	() == 1){
		cout << get_name() << " 同学" << endl;
	}else if (get_priviledge	()== 2){
		cout << get_name() << " 老师" << endl; 
	} 
	cout << "证件号:" <<  get_ID()  << endl;
	cout << "学院:" ;
	int college  = 0;

	college =  (get_ID().at(1)-'0')*10 +  (get_ID().at(2)-'0');
 	switch(college){
 		case 1: cout << "计算机科学与技术学院" << endl;break;
		case 2: cout << "信息与通信工程学院" << endl;break;
		case 3: cout << "电子工程学院" << endl;break;
		case 4: cout << "理学院" << endl;break;
		case 5: cout << "人文学院" << endl;break; 
		default : cout << "其他学院" << endl;break; 
	 }
	cout << "借书上限:" <<  get_limit_rent_num() <<"本"<< endl;
	cout << "借书期限:" <<  get_limit_date() << "天"<<endl;
	cout << "借书数量:" << get_rent_num() << endl; 
	if(get_rent_num()>0){
		cout << "借书记录:" << endl;
		cout <<  "图书ID\t\t" <<  "借书日期\t" <<  "应还日期\t" <<  "剩余天数\t" << endl;
		rent_map_type this_book_record = get_rent_map(); 
		rent_map_type::iterator it_record ;
		it_record =this_book_record.begin();
	
		while (it_record != this_book_record.end()){
			cout << it_record->first << "\t"<< it_record->second << "\t\t" << it_record->second + get_limit_date() << "\t\t" << it_record->second + get_limit_date() - today_date  << endl;
				it_record ++; 
		}
	 	
	}

	cout << "预约数量:" << appointment_number << endl; 
	if(appointment_number >0 ){
		cout <<  "图书ID\t\t" <<  "状态\t" << endl;	
		list<APPOINTMENT> ::iterator it = appointment_list.begin();
		while(it != appointment_list.end()){
			cout << it->ID  << "\t" ;
			if (it->available_date > 0 ){
				cout << "图书已经为您保留，请尽快借阅" << endl; 
			} else
			{
				cout << "仍在预约队列等待" << endl; 	
			}
			it ++; 
		}
		
	}

	cout << "罚款金额:" << fine/100 << "." <<  (fine % 100)/10 << fine % 10 << "元"<< endl; 
	cout << "逾期次数:" << credit << endl;  
 
}


void user::user_signup( ){
	int choice;




	refresh_appointment(); 	

	int cycle = 1;
	while(cycle) {

		cout<<"==========================================用户界面=========================================="<<endl;

 		user_information(); 
		cout<<"					1-查找图书					 "<<endl;
		cout<<"					2-借阅图书					 "<<endl;
		cout<<"					3-归还图书					 "<<endl;
		cout<<"					4-取消预约					 "<<endl;
		cout<<"					5-返回上级			 		"<<endl;
		cout<<"请输入您要进行的操作：-\b";
	
		cin >> choice;
		cin.clear();
		cin.ignore(1024,'\n');//清除缓存区 
		cin.sync(); 	
		while(choice < 1 || choice > 5 ){
			cout << "请输入正确的选项" << endl;
		 	cin >> choice; 
			cin.clear();
			cin.ignore(1024,'\n');//清除缓存区 
			cin.sync(); 			
		} 
		if(choice == 1){//查书 
			search_book();
			
		}else	if(choice == 2){//借书 
			int ava_rent_num = get_limit_rent_num() - get_rent_num();//可借数量 
			if(ava_rent_num >0){//1.读者可借书 
				cout << "请输入图书ID" << endl;
				string book_ID; 
				cin >> book_ID;//2.不在已借书中 
				rent_map_type::iterator find_it = rent_record.find(book_ID);
				if(find_it == rent_record.end()){//1&2 读者可以借书，这本书没借过 
					rent_book( book_ID);

				}else{
					cout << "您已借阅此书，不可重复借阅"  << endl; 
				} 

					
			}else{
				cout << "您已达到借书上限,请先还书再借书。" << endl; 
			}
			
		}else if(choice == 3){//还书
			cout << "请输入图书ID" << endl;
			string book_ID; 
			cin >> book_ID;

			return_book( book_ID);
		}else if(choice == 4){
			if(appointment_number > 0){
				cout << "请输入要删除预约的图书编码 " << endl; 
				string book_ID;
				cin >> book_ID;
			 	delete_appointment(book_ID);
			}else{
				cout << "您没有预约记录" << endl; 
			}

		
		}else if (choice == 5){
			cycle = 0;
		}
	}

	
	
	
}


void search_by_name(){
	cout << "按书名查找" << endl; 
	cout << "请输入书名：" ;
	string  find_book_name;
	cin >> find_book_name; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.begin();
	while(find_it  != books_map.end()){
		string::size_type count=COUNT_KMP(find_it->second->get_name(),find_book_name);//KMP查找 
		if(count > 0){
			cout << "找到符合要求的图书" << endl;
			find_it->second->show_information();
			exist = 1;
		}
		find_it ++;  
	} 
	
	if(exist == 0){
		cout << "查询失败" << endl; 
	} 
	 
}

void user_interface(){

	string user_ID; 

	
	cout << "请输入您的证件号:-------\b\b\b\b\b\b\b" ;
	cin >> user_ID ; 
 	cout << "您的证件号是:" <<user_ID <<endl;
		
	user_map_type::iterator find_it;	
	
	user_map_type::iterator it_find;
	it_find = user_map.find( user_ID );
 	if (it_find != user_map.end()){
		cout << "您已成功登陆系统" <<endl; 
		user * user_ptr = it_find->second; 
  		user_ptr->user_signup()	;	
  	}else{
		cout << "请输入正确的证件号或通过管理员增加您的信息\n---------------------------------------" << endl; 
       	
	}		//测试*	
	


}
void search_by_ISBN(){
	cout << "按ISBN查找" << endl; 
	cout << "请输入ISBN：" ;
	string  find_book_ISBN;
	cin >> find_book_ISBN; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.begin();
	while(find_it  != books_map.end()){
		string::size_type count=COUNT_KMP(find_it->second->get_isbn(),find_book_ISBN);//KMP查找 
		if(count > 0){
			cout << "找到符合要求的图书" << endl;
			find_it->second->show_information();
			exist = 1;
		}
		find_it ++;  
	} 
	
	if(exist == 0){
		cout << "查询失败" << endl; 
	} 
} 

void search_by_author(){
	cout << "按作者查找" << endl; 
	cout << "请输入作者：" ;
	string  find_book_author;
	cin >> find_book_author; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.begin();
	while(find_it  != books_map.end()){
		string::size_type count=COUNT_KMP(find_it->second->get_author(),find_book_author);//KMP查找 
		if(count > 0){
			cout << "找到符合要求的图书" << endl;
			find_it->second->show_information();
			exist = 1;
		}
		find_it ++;  
	} 
	
	if(exist == 0){
		cout << "查询失败" << endl; 
	} 

} 
void search_by_press(){
	cout << "按出版社查找" << endl; 
	cout << "请输入出版社：" ;
	string  find_book_press;
	cin >> find_book_press; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.begin();
	while(find_it  != books_map.end()){
		string::size_type count=COUNT_KMP(find_it->second->get_press(),find_book_press);//KMP查找 
		if(count > 0){
			cout << "找到符合要求的图书" << endl;
			find_it->second->show_information();
			exist = 1;
		}
		find_it ++;  
	} 
	
	if(exist == 0){
		cout << "查询失败" << endl; 
	} 
} 
void search_by_ID(){
	cout << "按图书编号查找" << endl; 
	cout << "请输入图书编号：" ;
	string  find_book_ID;
	cin >> find_book_ID; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.find(find_book_ID);
	if(find_it  != books_map.end()){

		cout << "找到符合要求的图书" << endl;
		find_it->second->show_information();
		exist = 1;

	} 
	
	if(exist == 0){
		cout << "查询失败" << endl; 
	} 
} 



void estab_user_index()//20170422 从文件创建用户容器
{


	ifstream  fin_user("user_record.txt");
	while(!fin_user.eof()){//逐条读取文件中的内容 
		string user_ID;
		string user_name;
		string s_rent_number;//字符串形式的借书数量 
		int rent_number; //借阅数量 
		string book_ID; //图书编码 
		string s_rent_time;//字符串形式的借书时间 
		int rent_time;//借书时间 
	
		string s_appointment_num; 
		int appointment_num;
	
		string s_set_fine;
		int set_fine;
		string s_set_credit;
		int set_credit;
		list<APPOINTMENT> set_appointment_list;
		
		int i,j;//循环变量 
		stringstream stream;
	

		rent_map_type set_rent_record; 





		cout << "Verify the file." << endl;
		getline (fin_user, user_ID);

		
		getline (fin_user, user_name);

		
		getline (fin_user, s_rent_number) ;
		stream.clear();
		stream << s_rent_number;
		stream >> rent_number;
		stream.clear();


		
		for(i = 0 ;i < rent_number; i++)//根据借书数量读取图书id和借书时间 
		{
			getline (fin_user, book_ID);

			
			getline (fin_user, s_rent_time);
			stream.clear();
			stream << s_rent_time;
			stream >> rent_time;
			

			set_rent_record.insert(pair<string, int>(book_ID, rent_time));	
		}



				

		getline (fin_user, s_appointment_num );
		stream.clear();
		stream << s_appointment_num;
		stream >> appointment_num;		




		for(i = 0 ;i < appointment_num ; i++)//根据借书数量读取图书id和借书时间 
		{
			APPOINTMENT set_appointment;
			string s_appointment_available_date;
			getline (fin_user, set_appointment.ID);
			set_appointment.available_date = -1;//初值	
			
			
			set_appointment_list.push_back(set_appointment) ;	
			//cout  << set_appointment.available_date;
		}


		getline (fin_user, s_set_fine);
		stream.clear();
		stream << s_set_fine;
		stream >> set_fine;
		getline (fin_user, s_set_credit); 
		stream.clear();
		stream << s_set_credit;
		stream >> set_credit;



		user * new_user_ptr = new user;
		*  new_user_ptr = user(user_ID, user_name, rent_number, set_rent_record, appointment_num, set_appointment_list, set_fine, set_credit);
		user_map.insert(pair<string, user*>(user_ID, new_user_ptr));

		rent_map_type::iterator rent_it , save_it; 



		
		user_map_type::iterator it_find;
		it_find = user_map.find( user_ID );
        if (it_find != user_map.end()){
     			cout << "测试读入内存情况" << endl;
				cout << "证件号:" << it_find->first << endl; 
				cout << "姓名:" << it_find->second->get_name() << endl; 
							
				cout << "借书数量:" << it_find->second->get_rent_num() << endl; 
				cout << "借书记录:" << endl;
				rent_map_type this_book_record = (it_find->second)->get_rent_map(); 
				rent_map_type::iterator it_record ;
				it_record =this_book_record.begin();

				while (it_record != this_book_record.end()){
					cout << "借书ID:" << it_record->first << endl;
					cout << "借书日期:" << it_record->second << endl;
					cout << "应还日期:" << it_record->second + it_find->second->get_limit_date() << endl;
					cout << "今天是" << today_date << "日" << endl; 
					cout << "剩余天数" << it_record->second + it_find->second->get_limit_date() - today_date  << endl;
					it_record ++; 

				}
 
				cout << "预约数量:" << it_find->second-> get_appointment_num() << endl; 
				
				cout << "借书上限:" << it_find->second-> get_limit_rent_num() << endl;
				cout << "借书期限:" << it_find->second-> get_limit_date() << endl;
				cout << "罚款金额:" << it_find->second->get_fine() << endl ; 
				cout << "逾期次数:" << it_find->second->get_credit() << endl;  
 				
        }else{
        	
            	cout << "no" << endl;//测试
        
		}		//测试*






				

	}
		


	fin_user.close(); 

}



//16:00 写完 
void record_user_index(){//从容器 写入文件 
 
	ofstream fout("user_record.txt");//为防止出错，测试时存入必用文件 
	user_map_type::iterator user_it;

 	user_it = user_map.begin();


 	while (user_it != user_map.end() )
 	{
		user  * user_ptr;//指针。 	
		user_ptr = user_it->second ;
		

		if(user_it->first.length() == 7) {//防止写入错误记录 
			cout << "测试写文件情况" << endl;
			fout << user_it->first << endl; //读者ID
		//	fout << user_it->second << endl; //
			fout << user_ptr -> get_name() << endl;
			fout << user_ptr -> get_rent_num() << endl;//借书数量
	 		if( user_ptr->get_rent_num() > 0){//借书条目 
	 			
				rent_map_type rent_map =  user_ptr->get_rent_map();
				rent_map_type::iterator rent_it = rent_map.begin();
				while (rent_it != rent_map.end()){
					fout << rent_it->first << endl;//借书ID 
					fout << rent_it->second << endl;
					rent_it ++;
				}		
		 	}
			fout << user_ptr-> get_appointment_num()  << endl;	 		
			list <APPOINTMENT> this_list = user_ptr -> get_appointment_list();
			cout << "测试list" << endl; 
			list <APPOINTMENT>::iterator it_list ;
			it_list =this_list.begin();
		
			while (it_list != this_list.end()){
					fout << it_list -> ID << endl;//只打印书的ID 
					it_list ++; 
			} 	 		 


			
			//图书记录
				 
	 		fout << user_ptr-> get_fine() << endl;	
			fout << user_ptr-> get_credit()  << endl;			
		}

		user_it ++;// 

	 }
	fout.close();

		
	
}

