#include "main_v5.h"

int today_date ;
int opration;//�ж��Ƿ��ڽ��в��� 
user_map_type user_map; 
books_map_type books_map; 


 user::user()
{

	ID = "0000000";
	
	
}

user::	user(string set_ID, string set_name){// �½��û��Ĺ��캯�� 
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
	rent_number = set_rent_number;//�������� 
	rent_record = set_rent_record; //�����¼ 
	
	rent_map_type::iterator it_rent;
	it_rent = set_rent_record.begin();
		cout << endl << "����" << endl; 
	while(it_rent != set_rent_record.end()){
		string book_ID = it_rent -> first;
		int rent_time = it_rent -> second; 	

		rent_record.insert(pair<string, int>(book_ID, rent_time));	
		it_rent ++;
	}

	
	appointment_number = set_appointment_number;
	appointment_list = set_appointment_list;  
	fine = set_fine;//������ 
	credit = set_credit; //ΥԼ���� 
	

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



int user::get_priviledge()//1 Ϊѧ�� 2 Ϊ��ʦ 
{
	char c = ID[0];
	int privilege=(int) c -48;
	return privilege; 
}



int user::get_limit_date()
{
	return 30*get_priviledge();	//ѧ�� �ɽ� 30�� ��ʦ �ɽ� 60��	
}

int user::get_limit_rent_num()
{
	return 10*get_priviledge();//ѧ�� �ɽ� 10�� ��ʦ �ɽ� 20��	
}

int user::get_limit_appointment()
{
	return 5*get_priviledge();//ѧ�� ��ԤԼ 5�� ��ʦ ��ԤԼ 10��	
}

int user::get_fine()
{
	return fine;//������ 
}

int user::get_credit()
{
	return credit;//ΥԼ���� 
} 
void user::add_appointment(string book_ID){//����delete 
	APPOINTMENT set_appointment;
	set_appointment.ID = book_ID; 
	set_appointment.available_date = -1;//��ֵ	
			
			
	appointment_list.push_back(set_appointment) ;
	appointment_number ++;		
}

void user::delete_appointment(string book_ID){//���� book ��delete 
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
	if(exist == 1){//�ҵ���¼ 
		appointment_list.erase(it_list);//�ɹ�ɾ�� 
		appointment_number --;
		cout << "�ɹ�ɾ��ԤԼ��¼" << endl; 
		//ɾ�����еļ�¼
		books_map_type ::iterator it_book  = books_map.find(book_ID);
		books * book_ptr = it_book->second;
		book_ptr->delete_appointment(ID); 
 
	}
		
}

void user::refresh_appointment ()//ˢ��ԤԼ��¼ 
{
	if (appointment_number > 0 ){
		cout << "ԤԼ�� Ϊ "<< appointment_number << endl; 
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
					if(user_it-> ID == ID){//ͼ�����ҵ��û���Ŀ
						it_list -> available_date = user_it -> available_date; 
						exist = 1;
					} 
					
					user_it++;
				}
				if(exist == 0){//û���ҵ� 
				  list <APPOINTMENT>::iterator	it_save = it_list; 
				  appointment_list.erase(it_save);	
				  appointment_number --;		
				}
				
			}else{//ͼ���¼���� ɾ�����������ԤԼ��¼ 
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
			cout << "��ѡ���ѯ��ʽ\n==========================================" << endl;
			cout << "1 ���� 2 ISBN 3 ���� 4 ������ 5 �ݲر�� 6 ����" << endl;  
			int search_type;
			cin >> search_type;
			while(search_type < 1 || search_type > 6 ){
				cout << "��������ȷ��ѡ��" << endl;
			 	cin >> search_type; 
				cin.clear();
				cin.ignore(1024,'\n');//��������� 
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
void user::return_book(string book_ID)//������� 
{
	rent_map_type::iterator find_it;
	find_it = rent_record.find(book_ID);
	if(find_it != rent_record.end()) {//�н����¼ 
		
		cout << "����ɹ�" << endl;
		int rent_date = find_it ->second; 
		rent_record.erase(find_it);//���߼�¼ɾ��
		rent_number --;
		books_map_type ::iterator book_it = books_map.find(book_ID);
		if(book_it !=  books_map.end()) {//ͼ���¼���� 
			books * book_ptr = book_it->second;//���¼�ı� 
			book_ptr->dec_rent_num();
			book_ptr->refresh_appointment(); 
			if(today_date - rent_date > get_limit_date()){
				
				int inc_fine  = book_ptr->get_price() * (today_date - rent_date -get_limit_date() )/100 ;
				cout << "����" <<inc_fine/100 << "." <<  (inc_fine % 100)/10 << inc_fine % 10 << "Ԫ"<< endl; 
				
				fine = fine+ inc_fine;
				credit ++;
			}
			
			write_log(1,user_name,book_ID);//д��־ 
		}else{
			cout << "ͼ���¼����" << endl; 
		} 

		
	}else{//1.�����ѽ����� 
		cout << "δ���Ĵ���" << endl; 
	} 

}






void user::rent_book(string book_ID)//���� 1&2 ���߿��Խ��飬�Ȿ��û��� 
{//���ж�  			//3.ͼ���Ƿ����	���ڲ���	
					//4.��û�йݲ� 
					//5.ԤԼ�ɽ裿
					//6.����ԤԼ���ɽ����У� 
					//7.û��ԤԼ �жϹݲ��� - ԤԼ���Ƿ���� 0  
					
		books_map_type::iterator find_it; 
		find_it = books_map.find(book_ID);
		if(find_it != books_map.end()){//ͼ����� 
			cout << "�ҵ�ͼ��" << endl; 
			books * ptr_book = find_it -> second; 
			
			if(ptr_book->get_in_num() > 0){//ͼ���йݲ�
				cout << "ͼ���йݲ�" << endl; 
				
				if(appointment_number > 0){//������ԤԼ��¼ 
					list <APPOINTMENT> ::iterator find_it = appointment_list.begin();
					int exist = 0, valid = 0;
					while(find_it != appointment_list.end() && exist ==0){
						if(find_it ->ID == book_ID){
							exist =1;
							if(find_it ->available_date > 0){
								valid = 1;
								appointment_list.erase(find_it) ;//ɾ����Ŀ 
								rent_number ++;
								 
								rent_record.insert(pair<string, int>(book_ID, today_date));	
								ptr_book->inc_rent_num();
								ptr_book->inc_rent_count();
								ptr_book->delete_appointment(ID);
 								cout << "����ɹ�" << endl;
								cout << "�鼮��Ϣ" << endl;
								ptr_book->show_information();
								write_log(0,user_name,book_ID);								
							}
						}else{
							find_it ++;
						}
						
					}
					if(exist == 0 ){//��������һ�� 
						if(ptr_book->get_appointment_num() < ptr_book->get_in_num()){//���Խ� 
							rent_number ++;
							rent_record.insert(pair<string, int>(book_ID, today_date));	
							ptr_book->inc_rent_num();
							ptr_book->inc_rent_count();
							write_log(0,user_name,book_ID);
							
						}else{
							cout << "ͼ�鲻�ɽ�" << endl; 
							if(appointment_number < get_limit_appointment()){
								cout << " ����ѡ��ԤԼ ԤԼ 1 ��ԤԼ 0" << endl;
								int app;
								cin >> app;
								if(app){ 
									add_appointment(book_ID);//�Դ�num++�� 
									ptr_book ->add_appointment(ID);//�Դ�num++	
								}						
							} 
	
							 
						} 						
					}else if(exist == 1 && valid== 0){
						cout << "ԤԼ��δ�ֵ�" << endl; 
					}
									
				}
				else{//����û��ԤԼ��¼ 
					if(ptr_book->get_appointment_num() < ptr_book->get_in_num()){//���Խ� 
						rent_number ++;
						rent_record.insert(pair<string, int>(book_ID, today_date));	
						ptr_book->inc_rent_num();
						ptr_book->inc_rent_count();
						cout << "����ɹ�" << endl;
						cout << "�鼮��Ϣ" << endl;
						ptr_book->show_information();
						write_log(0,user_name,book_ID);
						
					}else{
						cout << "ͼ�鲻�ɽ�" << endl; 
						if(appointment_number < get_limit_appointment()){
							cout << " ����ѡ��ԤԼ ԤԼ 1 ��ԤԼ 0" << endl;
							int app;
							cin >> app;
							if(app){ 
								add_appointment(book_ID);//�Դ�num++�� 
								ptr_book ->add_appointment(ID);//�Դ�num++	
							}						
						} 

						 
					} 
				} 

				
				
				
			
			
			}else{//ͼ���޹ݲ� //Ҳ����ԤԼ�� 
				cout << "ͼ����ڣ����޹ݲ�" << endl; 
				if(appointment_number > 0){//��ԤԼ��¼ 
					if(appointment_number < get_limit_appointment()){//����ԤԼ
					
					
					
						list <APPOINTMENT> ::iterator find_it = appointment_list.begin();
						int exist = 0, valid = 0;
						while(find_it != appointment_list.end() && exist ==0){
							if(find_it ->ID == book_ID){
								exist =1;
							
							}else{
								find_it ++;
							}
							
						}
						if(exist == 0 ){//��������һ�� 
				//�ж��Ƿ�ԤԼ�� 
							cout << " ����ѡ��ԤԼ ԤԼ 1 ��ԤԼ 0" << endl;
							int app;
							cin >> app;
							if(app){ 
								add_appointment(book_ID);//�Դ�num++�� 
								ptr_book ->add_appointment(ID);//�Դ�num++	
							}						
																				
						}else if(exist == 1 ){
							cout << "ԤԼ��δ�ֵ�" << endl; 
						}					
					
						
					} else{
						cout << "ԤԼ�����޷�ѡ��ԤԼ" << endl; 
					}				
						
				}else{//û��ԤԼ��¼����ԤԼ 

					cout << " ����ѡ��ԤԼ ԤԼ 1 ��ԤԼ 0" << endl;
					int app;
					cin >> app;
					if(app){ 
						add_appointment(book_ID);//�Դ�num++�� 
						ptr_book ->add_appointment(ID);//�Դ�num++	
					}
					
				} //û��ԤԼ��¼����ԤԼ 
			}
			
			
		}else{//ͼ�鲻���� 
			cout << "δ�ҵ�ͼ��" << endl; 
		}
		
		


} 


void user::user_information(){//��ӡ������Ϣ 

	if(get_priviledge	() == 1){
		cout << get_name() << " ͬѧ" << endl;
	}else if (get_priviledge	()== 2){
		cout << get_name() << " ��ʦ" << endl; 
	} 
	cout << "֤����:" <<  get_ID()  << endl;
	cout << "ѧԺ:" ;
	int college  = 0;

	college =  (get_ID().at(1)-'0')*10 +  (get_ID().at(2)-'0');
 	switch(college){
 		case 1: cout << "�������ѧ�뼼��ѧԺ" << endl;break;
		case 2: cout << "��Ϣ��ͨ�Ź���ѧԺ" << endl;break;
		case 3: cout << "���ӹ���ѧԺ" << endl;break;
		case 4: cout << "��ѧԺ" << endl;break;
		case 5: cout << "����ѧԺ" << endl;break; 
		default : cout << "����ѧԺ" << endl;break; 
	 }
	cout << "��������:" <<  get_limit_rent_num() <<"��"<< endl;
	cout << "��������:" <<  get_limit_date() << "��"<<endl;
	cout << "��������:" << get_rent_num() << endl; 
	if(get_rent_num()>0){
		cout << "�����¼:" << endl;
		cout <<  "ͼ��ID\t\t" <<  "��������\t" <<  "Ӧ������\t" <<  "ʣ������\t" << endl;
		rent_map_type this_book_record = get_rent_map(); 
		rent_map_type::iterator it_record ;
		it_record =this_book_record.begin();
	
		while (it_record != this_book_record.end()){
			cout << it_record->first << "\t"<< it_record->second << "\t\t" << it_record->second + get_limit_date() << "\t\t" << it_record->second + get_limit_date() - today_date  << endl;
				it_record ++; 
		}
	 	
	}

	cout << "ԤԼ����:" << appointment_number << endl; 
	if(appointment_number >0 ){
		cout <<  "ͼ��ID\t\t" <<  "״̬\t" << endl;	
		list<APPOINTMENT> ::iterator it = appointment_list.begin();
		while(it != appointment_list.end()){
			cout << it->ID  << "\t" ;
			if (it->available_date > 0 ){
				cout << "ͼ���Ѿ�Ϊ���������뾡�����" << endl; 
			} else
			{
				cout << "����ԤԼ���еȴ�" << endl; 	
			}
			it ++; 
		}
		
	}

	cout << "������:" << fine/100 << "." <<  (fine % 100)/10 << fine % 10 << "Ԫ"<< endl; 
	cout << "���ڴ���:" << credit << endl;  
 
}


void user::user_signup( ){
	int choice;




	refresh_appointment(); 	

	int cycle = 1;
	while(cycle) {

		cout<<"==========================================�û�����=========================================="<<endl;

 		user_information(); 
		cout<<"					1-����ͼ��					 "<<endl;
		cout<<"					2-����ͼ��					 "<<endl;
		cout<<"					3-�黹ͼ��					 "<<endl;
		cout<<"					4-ȡ��ԤԼ					 "<<endl;
		cout<<"					5-�����ϼ�			 		"<<endl;
		cout<<"��������Ҫ���еĲ�����-\b";
	
		cin >> choice;
		cin.clear();
		cin.ignore(1024,'\n');//��������� 
		cin.sync(); 	
		while(choice < 1 || choice > 5 ){
			cout << "��������ȷ��ѡ��" << endl;
		 	cin >> choice; 
			cin.clear();
			cin.ignore(1024,'\n');//��������� 
			cin.sync(); 			
		} 
		if(choice == 1){//���� 
			search_book();
			
		}else	if(choice == 2){//���� 
			int ava_rent_num = get_limit_rent_num() - get_rent_num();//�ɽ����� 
			if(ava_rent_num >0){//1.���߿ɽ��� 
				cout << "������ͼ��ID" << endl;
				string book_ID; 
				cin >> book_ID;//2.�����ѽ����� 
				rent_map_type::iterator find_it = rent_record.find(book_ID);
				if(find_it == rent_record.end()){//1&2 ���߿��Խ��飬�Ȿ��û��� 
					rent_book( book_ID);

				}else{
					cout << "���ѽ��Ĵ��飬�����ظ�����"  << endl; 
				} 

					
			}else{
				cout << "���Ѵﵽ��������,���Ȼ����ٽ��顣" << endl; 
			}
			
		}else if(choice == 3){//����
			cout << "������ͼ��ID" << endl;
			string book_ID; 
			cin >> book_ID;

			return_book( book_ID);
		}else if(choice == 4){
			if(appointment_number > 0){
				cout << "������Ҫɾ��ԤԼ��ͼ����� " << endl; 
				string book_ID;
				cin >> book_ID;
			 	delete_appointment(book_ID);
			}else{
				cout << "��û��ԤԼ��¼" << endl; 
			}

		
		}else if (choice == 5){
			cycle = 0;
		}
	}

	
	
	
}


void search_by_name(){
	cout << "����������" << endl; 
	cout << "������������" ;
	string  find_book_name;
	cin >> find_book_name; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.begin();
	while(find_it  != books_map.end()){
		string::size_type count=COUNT_KMP(find_it->second->get_name(),find_book_name);//KMP���� 
		if(count > 0){
			cout << "�ҵ�����Ҫ���ͼ��" << endl;
			find_it->second->show_information();
			exist = 1;
		}
		find_it ++;  
	} 
	
	if(exist == 0){
		cout << "��ѯʧ��" << endl; 
	} 
	 
}

void user_interface(){

	string user_ID; 

	
	cout << "����������֤����:-------\b\b\b\b\b\b\b" ;
	cin >> user_ID ; 
 	cout << "����֤������:" <<user_ID <<endl;
		
	user_map_type::iterator find_it;	
	
	user_map_type::iterator it_find;
	it_find = user_map.find( user_ID );
 	if (it_find != user_map.end()){
		cout << "���ѳɹ���½ϵͳ" <<endl; 
		user * user_ptr = it_find->second; 
  		user_ptr->user_signup()	;	
  	}else{
		cout << "��������ȷ��֤���Ż�ͨ������Ա����������Ϣ\n---------------------------------------" << endl; 
       	
	}		//����*	
	


}
void search_by_ISBN(){
	cout << "��ISBN����" << endl; 
	cout << "������ISBN��" ;
	string  find_book_ISBN;
	cin >> find_book_ISBN; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.begin();
	while(find_it  != books_map.end()){
		string::size_type count=COUNT_KMP(find_it->second->get_isbn(),find_book_ISBN);//KMP���� 
		if(count > 0){
			cout << "�ҵ�����Ҫ���ͼ��" << endl;
			find_it->second->show_information();
			exist = 1;
		}
		find_it ++;  
	} 
	
	if(exist == 0){
		cout << "��ѯʧ��" << endl; 
	} 
} 

void search_by_author(){
	cout << "�����߲���" << endl; 
	cout << "���������ߣ�" ;
	string  find_book_author;
	cin >> find_book_author; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.begin();
	while(find_it  != books_map.end()){
		string::size_type count=COUNT_KMP(find_it->second->get_author(),find_book_author);//KMP���� 
		if(count > 0){
			cout << "�ҵ�����Ҫ���ͼ��" << endl;
			find_it->second->show_information();
			exist = 1;
		}
		find_it ++;  
	} 
	
	if(exist == 0){
		cout << "��ѯʧ��" << endl; 
	} 

} 
void search_by_press(){
	cout << "�����������" << endl; 
	cout << "����������磺" ;
	string  find_book_press;
	cin >> find_book_press; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.begin();
	while(find_it  != books_map.end()){
		string::size_type count=COUNT_KMP(find_it->second->get_press(),find_book_press);//KMP���� 
		if(count > 0){
			cout << "�ҵ�����Ҫ���ͼ��" << endl;
			find_it->second->show_information();
			exist = 1;
		}
		find_it ++;  
	} 
	
	if(exist == 0){
		cout << "��ѯʧ��" << endl; 
	} 
} 
void search_by_ID(){
	cout << "��ͼ���Ų���" << endl; 
	cout << "������ͼ���ţ�" ;
	string  find_book_ID;
	cin >> find_book_ID; 
	int exist = 0; 
	books_map_type::iterator find_it = books_map.find(find_book_ID);
	if(find_it  != books_map.end()){

		cout << "�ҵ�����Ҫ���ͼ��" << endl;
		find_it->second->show_information();
		exist = 1;

	} 
	
	if(exist == 0){
		cout << "��ѯʧ��" << endl; 
	} 
} 



void estab_user_index()//20170422 ���ļ������û�����
{


	ifstream  fin_user("user_record.txt");
	while(!fin_user.eof()){//������ȡ�ļ��е����� 
		string user_ID;
		string user_name;
		string s_rent_number;//�ַ�����ʽ�Ľ������� 
		int rent_number; //�������� 
		string book_ID; //ͼ����� 
		string s_rent_time;//�ַ�����ʽ�Ľ���ʱ�� 
		int rent_time;//����ʱ�� 
	
		string s_appointment_num; 
		int appointment_num;
	
		string s_set_fine;
		int set_fine;
		string s_set_credit;
		int set_credit;
		list<APPOINTMENT> set_appointment_list;
		
		int i,j;//ѭ������ 
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


		
		for(i = 0 ;i < rent_number; i++)//���ݽ���������ȡͼ��id�ͽ���ʱ�� 
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




		for(i = 0 ;i < appointment_num ; i++)//���ݽ���������ȡͼ��id�ͽ���ʱ�� 
		{
			APPOINTMENT set_appointment;
			string s_appointment_available_date;
			getline (fin_user, set_appointment.ID);
			set_appointment.available_date = -1;//��ֵ	
			
			
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
     			cout << "���Զ����ڴ����" << endl;
				cout << "֤����:" << it_find->first << endl; 
				cout << "����:" << it_find->second->get_name() << endl; 
							
				cout << "��������:" << it_find->second->get_rent_num() << endl; 
				cout << "�����¼:" << endl;
				rent_map_type this_book_record = (it_find->second)->get_rent_map(); 
				rent_map_type::iterator it_record ;
				it_record =this_book_record.begin();

				while (it_record != this_book_record.end()){
					cout << "����ID:" << it_record->first << endl;
					cout << "��������:" << it_record->second << endl;
					cout << "Ӧ������:" << it_record->second + it_find->second->get_limit_date() << endl;
					cout << "������" << today_date << "��" << endl; 
					cout << "ʣ������" << it_record->second + it_find->second->get_limit_date() - today_date  << endl;
					it_record ++; 

				}
 
				cout << "ԤԼ����:" << it_find->second-> get_appointment_num() << endl; 
				
				cout << "��������:" << it_find->second-> get_limit_rent_num() << endl;
				cout << "��������:" << it_find->second-> get_limit_date() << endl;
				cout << "������:" << it_find->second->get_fine() << endl ; 
				cout << "���ڴ���:" << it_find->second->get_credit() << endl;  
 				
        }else{
        	
            	cout << "no" << endl;//����
        
		}		//����*






				

	}
		


	fin_user.close(); 

}



//16:00 д�� 
void record_user_index(){//������ д���ļ� 
 
	ofstream fout("user_record.txt");//Ϊ��ֹ��������ʱ��������ļ� 
	user_map_type::iterator user_it;

 	user_it = user_map.begin();


 	while (user_it != user_map.end() )
 	{
		user  * user_ptr;//ָ�롣 	
		user_ptr = user_it->second ;
		

		if(user_it->first.length() == 7) {//��ֹд������¼ 
			cout << "����д�ļ����" << endl;
			fout << user_it->first << endl; //����ID
		//	fout << user_it->second << endl; //
			fout << user_ptr -> get_name() << endl;
			fout << user_ptr -> get_rent_num() << endl;//��������
	 		if( user_ptr->get_rent_num() > 0){//������Ŀ 
	 			
				rent_map_type rent_map =  user_ptr->get_rent_map();
				rent_map_type::iterator rent_it = rent_map.begin();
				while (rent_it != rent_map.end()){
					fout << rent_it->first << endl;//����ID 
					fout << rent_it->second << endl;
					rent_it ++;
				}		
		 	}
			fout << user_ptr-> get_appointment_num()  << endl;	 		
			list <APPOINTMENT> this_list = user_ptr -> get_appointment_list();
			cout << "����list" << endl; 
			list <APPOINTMENT>::iterator it_list ;
			it_list =this_list.begin();
		
			while (it_list != this_list.end()){
					fout << it_list -> ID << endl;//ֻ��ӡ���ID 
					it_list ++; 
			} 	 		 


			
			//ͼ���¼
				 
	 		fout << user_ptr-> get_fine() << endl;	
			fout << user_ptr-> get_credit()  << endl;			
		}

		user_it ++;// 

	 }
	fout.close();

		
	
}

