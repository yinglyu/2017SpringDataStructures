
#include "main_v5.h"
void estab_books_index()//20170422 从文件创建用户容器
{


	ifstream  fin_books("books_record.txt");
	while(!fin_books.eof()){//逐条读取文件中的内容 


	
		string book_ID;//书的ID  长度为9 
		string book_name;//书名 长度为30 
		string book_author;//作者 长度为 
		string book_press;//出版社 长度为30 
		string book_isbn;//ISBN号  长度为15 
		string s_book_year; 
		int book_year;//购入时间 
		string s_book_price;
		int book_price;//价格
		string s_total_num;
		int total_num;//书的总数
		string s_rent_num;
		int rent_num;//借出去的数量
		string s_rent_count;
		int rent_count;//统计借阅总人次数
		string s_appointment_num;
		int appointment_num;//目前记录的预约人数量 
		list <APPOINTMENT> set_appointment_list;
		
		int i,j;//循环变量 
		stringstream stream;





		cout << "Verify the file." << endl;
		getline (fin_books, book_ID);
		
		getline (fin_books, book_name);

		getline (fin_books, book_author);

		getline (fin_books, book_press);

		getline (fin_books, book_isbn);
		
		getline (fin_books, s_book_year) ;
		stream.clear();
		stream << s_book_year;
		stream >> book_year;
		stream.clear();

		getline (fin_books, s_book_price) ;
		stream.clear();
		stream << s_book_price;
		stream >> book_price;;
		stream.clear();

		getline (fin_books, s_total_num) ;
		stream.clear();
		stream << s_total_num;
		stream >> total_num;;
		stream.clear();

		getline (fin_books, s_rent_num) ;
		stream.clear();
		stream << s_rent_num;
		stream >> rent_num;;
		stream.clear();


		getline (fin_books, s_rent_count) ;
		stream.clear();
		stream << s_rent_count;
		stream >> rent_count;;
		stream.clear();
		

				

		getline (fin_books, s_appointment_num );
		stream.clear();
		stream << s_appointment_num;
		stream >> appointment_num;		

		for(i = 0 ;i < appointment_num ; i++)//根据借书数量读取图书id和借书时间 
		{
			APPOINTMENT set_appointment;
			string s_appointment_available_date;
			getline (fin_books, set_appointment.ID);
			getline (fin_books, s_appointment_available_date );
			stream.clear();
			stream << s_appointment_available_date;
			stream >> set_appointment.available_date;	
			
			
			set_appointment_list.push_back(set_appointment) ;	
			//cout  << set_appointment.available_date;
		}



		books * new_books_ptr = new books;
		*  new_books_ptr =books( book_ID, book_name, book_author, book_press, book_isbn, book_year, book_price, total_num , rent_num, rent_count, appointment_num, set_appointment_list);
		books_map.insert(pair<string, books*>(book_ID, new_books_ptr));
		
		list <APPOINTMENT> this_list = new_books_ptr->get_appointment_list();
		
		//测试list 
/*		cout << "测试list" << endl; 
		list <APPOINTMENT>::iterator it_list ;
		it_list =this_list.begin();

				while (it_list != this_list.end()){
					cout << it_list -> user_ID << endl;
					cout << it_list -> available_date << endl;
					it_list ++; 

				}
*/


				

	}
		


	fin_books.close(); 

}



void record_books_index(){//从容器 写入文件 
 
	ofstream fout("books_record.txt");
	books_map_type::iterator books_it;

 	books_it = books_map.begin();


 	while (books_it != books_map.end())
 	{
		books  * books_ptr;//指针。 	
		books_ptr = books_it->second ;
		

		if(books_it->first.length() == 9){
			cout << "测试写文件情况" << endl;
			fout << books_it->first << endl; //图书ID
		//	fout << books_it->second << endl; //
			fout << books_ptr -> get_name() << endl;
			fout << books_ptr -> get_author() << endl;		
			fout << books_ptr -> get_press() << endl;
			fout << books_ptr -> get_isbn() << endl;
			fout << books_ptr -> get_time() << endl;
			fout << books_ptr -> get_price() << endl;
			fout << books_ptr -> get_total_num() << endl;
			fout << books_ptr -> get_rent_num() << endl;
			fout << books_ptr -> get_count_num() << endl;
			fout << books_ptr -> get_appointment_num() << endl;
			if ( books_ptr -> get_appointment_num()!= 0)
			{//遍历 
	
				list <APPOINTMENT> this_list = books_ptr -> get_appointment_list();
				cout << "测试list" << endl; 
				list <APPOINTMENT>::iterator it_list ;
				it_list =this_list.begin();
		
				while (it_list != this_list.end()){
						fout << it_list -> ID << endl;
				//		cout << it_list -> ID << endl;
						fout << it_list -> available_date << endl;
				//		cout << it_list -> available_date << endl;
						it_list ++; 
				} 
	
	
				 
				 
			} 			
		}

	 		 


		books_it ++;// 

	 }
	fout.close();

		
	
}




books::books(){
	
}
books::books(string set_ID,string set_name,string set_author,string set_press,string set_isbn,int set_time,int set_price,int set_total_num)//新增图书 
{

	book_ID =set_ID ;	
	book_name =set_name ;
	book_author =set_author ;
	book_press = set_press ;
	
	book_isbn =set_isbn ;

	book_time= set_time;
	book_price= set_price;
	total_num= set_total_num;
	rent_num=0;
	rent_count=0;
	appointment_num= 0;
}

books::books(string set_ID, string set_name, string set_author, string set_press, string set_isbn, int set_time, int set_price, int set_total_num ,int set_rent_num, int set_rent_count, int set_appointment_num, list<APPOINTMENT> set_appointment_list){
	book_ID = set_ID ;	
	book_name = set_name ;
	book_author = set_author ;
	book_press = set_press ;
	
	book_isbn =set_isbn ;

	book_time = set_time;
	book_price = set_price;
	total_num = set_total_num;
	rent_num = set_rent_num;
	rent_count = set_rent_count;
	appointment_num = set_appointment_num;
	appointment_list= set_appointment_list;
	
	

} 


string books::get_name(){
	return  book_name; 
} 
string books::get_author(){
	return book_author; 
} 
string books::get_press(){
	return book_press; 
}
string books::get_isbn(){
	return book_isbn;
}
int books::get_time(){
	return book_time;
}
int books::get_price(){
	return book_price;
} //单位为分 	int books::get_total_num();
int books::get_total_num(){
	return total_num;
}

int books::get_rent_num(){
	return rent_num;
}

int books::get_in_num(){
	return total_num - rent_num;
} 

int books::get_count_num(){
	return rent_count;
}


int books::get_appointment_num(){
	return appointment_num;	
} 


list<APPOINTMENT> books::get_appointment_list(){
	return appointment_list;

}
int books::get_rent_rate(){
	return rent_count;
} 



	/////////////////////////////////////set_private
void books::inc_rent_num(){
	rent_num  ++;
}//更改已借图书数 

void books::dec_rent_num(){
	rent_num  --;
}//更改已借图书数 


void books::inc_rent_count(){
	rent_count++;

}//增加借阅总人数 


void books::add_appointment(string ID){//确定没有这个条目才调用 



	APPOINTMENT set_appointment;
	set_appointment.ID = ID; 
	set_appointment.available_date = -1;
	
	
	appointment_list.push_back(set_appointment) ;	
	appointment_num ++;

}


void books::delete_appointment(string ID){
	int exist = 0;
	list <APPOINTMENT>::iterator it_list ;
	it_list = appointment_list.begin();
	
	while (it_list != appointment_list.end() && !exist){
		if(it_list -> ID == ID){//找到条目 
			appointment_list.erase(it_list);
			exist = 1;
			appointment_num --; //预约数减少 
		}

		it_list ++; 
	} 

}

void books::refresh_appointment(){
	//根据 图书馆藏数，预约人数，预约过期情况，删除条目，更改可以借书的开始时间
	
	//1.删除预约过期或者不合理条目
	
	int finish = 0;//遍历到未开始保留的条目 
	list <APPOINTMENT>::iterator it_list ;
	it_list = appointment_list.begin();
	int i =0;
	while (it_list != appointment_list.end() && !finish && i< appointment_num	){
		i++;
		if(it_list -> available_date == -1){//遍历到未开始保留的条目 
			finish = 1;
		}
		else if(it_list -> available_date < today_date - 3 ){//找到条目 
			appointment_list.erase(it_list);
			appointment_num --; //预约数减少 
		}

		it_list ++; 
	} 	
	//2.根据馆藏数n，给前n个预约条目中 借书开始时间小于0的，置为今天 
	i = 0;// 记录遍历到第几个条目
	int in_num = get_in_num(); //记录馆藏数 
	it_list = appointment_list.begin();
	
	while (it_list != appointment_list.end() && i < in_num){
		if(it_list -> available_date == -1){//遍历到未开始保留的条目 
			it_list -> available_date = today_date;//从今天开始 为该读者保留图书 
		}
		i ++; 
		it_list ++; 
	} 			
	 
}

void books::show_information(){
	cout << "图书编号："  << book_ID << endl;
	cout << "    书名："  << book_name << endl;
	cout << "    作者："  << book_author << endl;
	cout << "  出版社："  << book_press << endl;
	cout << "    ISBN："  << book_isbn << endl;
	cout << "购入时间："  << book_time << "日 "<< endl;
	cout << "购入价格："  << book_price/100 << "." <<  (book_price % 100)/10 << book_price % 10 << "元"<< endl; 
	cout << "图书总数："  << total_num << endl;
	cout << "在馆数量："  << get_in_num () << endl;
	cout << "  借阅率："  << get_rent_rate () << endl;
	cout<<"=================================================================================="<<endl;


}


