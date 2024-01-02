#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>
using namespace std;



//main struct
struct additem {
	string name;
	double price;
};

std::vector<additem> items;

int listsize;

struct forbill {
	string name;
	double price;
	int peice;
};

//file handle strating
void addFITS() {
	fstream myitemfile;
	myitemfile.open("itemtext.txt", ios::in);
	if(myitemfile.is_open()) {
		items.clear();
		string line;
		while(getline(myitemfile, line)) {
			additem fileitem;
			size_t commaPos = line.find(",");
			fileitem.name = line.substr(0, commaPos);
			fileitem.price = std::stod(line.substr(commaPos + 1));
			items.push_back(fileitem);
		}
	}
	listsize = items.size();
	myitemfile.close();
}



//main array



struct myarr2 {
	string newname;
	double packprice;
};


std::vector<myarr2> packages;
std::vector<forbill> billIt;

void addFPTS() {
	fstream mypackfile;
	mypackfile.open("packagestext.txt", ios::in);
	if(mypackfile.is_open()) {
		packages.clear();
		string line;
		myarr2 packageitem;
		while(getline(mypackfile, line)) {
			size_t commaPos = line.find(",");
			packageitem.newname = line.substr(0, commaPos);
			packageitem.packprice = std::stod(line.substr(commaPos + 1));
			packages.push_back(packageitem);
		}
	}
	mypackfile.close();
}


//void additems(){
// 	while(true){
//		int loopbreak;
//		cout<<"How many items you went add?: ";
//		cin>>loopbreak;
//		if(loopbreak <= 0){ //check input
//			cout<<"invalid input";
//			additems();
//
//		}else{
//		//adding logic
//			for(int i = 1; i <= loopbreak; i++){
//				cout << "Enter the item name: ";
//      	 		string newItemName;
//       	 		cin >> newItemName;
//
//        		cout << "Enter the item price: ";
//        		double newItemPrice;
//        		cin >> newItemPrice;
//
//				items[listsize].name =  newItemName;
//				items[listsize].price =  newItemPrice;
//				listsize++;
//
//			}
//			cout<<"\n----Adding success----\n";
//		}
//		break;
//	}
//
//
//}

void additems() {
	cout<<"\n";
	while(true) {
		string newItemName;
		cout << "\t\tEnter the item name(For end type 'done'): ";

		cin >> newItemName;
		if(newItemName == "done") {
			break;
		}

		string inputvalue;
		cout << "\t\tEnter the item price: ";
		cin >> inputvalue;
		try {
			double newItemPrice = std::stod(inputvalue);
//			std::cout << "Converted double value: " << newItemPrice << std::endl;
			fstream mywritefile;
			mywritefile.open("itemtext.txt", ios::app);
			if(mywritefile.is_open()) {
				mywritefile << newItemName << "," << newItemPrice<<"\n";
				mywritefile.close();
			}
			addFITS();
		} catch (const std::exception& e) {
			std::cout << "\n\t\tInvalid input. Not a valid double." << std::endl;
			continue;
		}




	}
	cout<<"\n\t\t--- Adding successfull ---\n";
}


//adding new packages
void addpackages() {
	cout<<"\n";
	while(true) {
		cout << "\t\tEnter the new Package Name(For end type 'done'): ";
		string newPackname;
		cin >> newPackname;
		if(newPackname == "done") {
			break;
		}

		cout << "\t\tEnter the Package Price: ";
		double newPackprice;
		cin >> newPackprice;

		fstream mywritefile;
		mywritefile.open("packagestext.txt", ios::app);
		if(mywritefile.is_open()) {
			mywritefile << newPackname << "," << newPackprice<<"\n";
			mywritefile.close();
		}
		addFPTS();

	}
	cout<<"\n\t\t----Adding success----\n";
}





void viewitem() {
	string viewchoice;
	cout << "\n\t\t1. Manu details press (M)\n";
	cout << "\t\t2. Packages details press (P)\n";
	cout << "\t\t3. To exit press (exit)\n\n";
	cout << "\t\tEnter your choice: ";
	cin>>viewchoice;
	if(viewchoice == "M") {
		cout<<"\n\t\t---Menu items---\n";
		cout << "\t\tItem name\t\tItem Price\n\n";
		for(int i = 0; i < items.size(); i++) {
			cout<<"\t\t"<<items[i].name<<"\t\t\t"<<items[i].price<<"\n";
		}
		viewitem();
	} else if(viewchoice == "P") {
		cout<<"\n\t\t---Packages Details---\n";
		for(int i = 0; i < packages.size(); i++) {
			cout<<"\t\t"<<packages[i].newname<<"\t\t\t"<<packages[i].packprice<<"\n";
		}
		viewitem();
	} else if(viewchoice == "exsit") {
		return;
	} else {
		cout<<"\n\t\t--- Wrong Position ---\n";
		viewitem();
	}

	return;
}


void searchitem() {
	cout<<"\n\n\t\tEnter item you went search: ";
	string searchitemN;
	string avalibility;
	int iti;
	cin>>searchitemN;
	for(int i = 0; i < listsize; i++) {
		if(items[i].name == searchitemN) {
			avalibility = "yes";
			iti = i;
		}
		
	}
	if(avalibility == "yes") {
		cout<<"\n\t\tSearch item is: " << items[iti].name << " Item price is: $"<< items[iti].price <<"\n";
		cout<<"\n\t\t--- This procudet avalible ---\n";
	} else {
		cout<<"\n\t\t--- This procudet unavalible ---\n";
	}

}


//string login(){
//	string username;
//	string password;
//	cout<<"Enter the username: ";
//	cin>>username;
//	cout<<"Enter the password: ";
//	cin>>password;
//	if(username == "dd" && password == "cc"){
//		return "success";
//	}else{
//		return "unsuccess";
//	}
//
//}



void makeBill() {
	fstream billfile;
	double totleadditems[100];
	int billItemIndex = 0;
	double totle = 0;
	int peice;
	cout<<"\n";
	cout << "\t\tItemName\t\tItemPrice\n\n";
	for(int i = 0; i < items.size(); i++) {
		cout<<"\t\t"<<items[i].name<<"\t\t\t"<<items[i].price<<"\n";
	}
	while(true) {
		string additem;
		string avalibility;
		int itemindex;
		int stopcode;
		
		cout<<"\n\t\tEnter item name(For end type 'done'): ";
		cin>>additem;

		if(additem == "done") {
			billfile.open("bill.txt", ios::out);
			if(billfile.is_open()) {


				cout<<"\n\n\t\t------------ Bill Summary ------------\n\n";
				cout<<"\t\tItem Name\tItem Price\tQuntity\n";
				billfile << "------------ Bill Summary ------------" << endl;
				billfile <<"Item Name\tItem Price\tQuntity\n" << endl;
				for(int i = 0; i < billItemIndex; i++) {

					cout<<"\t\t"<<billIt[i].name<<"\t\t"<<billIt[i].price<<"\t\t"<<billIt[i].peice<<"\n";
					billfile<<billIt[i].name<<"\t\t"<<billIt[i].price<<"\t\t"<<billIt[i].peice<< "\n" << endl;

					//				if(billfile.is_open()){
					//					billfile <<
					//				}


				}
				cout<<"\n\n\t\tYour full bill is $"<<totle<<"\n\n";
				billfile<<"\n\nYour full bill is $"<<totle<<"\n\n" << endl;
				cout<<"\n\n\t\t------------ Thank you ! -------------\n\n\n";
				billfile<<"\n\n------------ Thank you ! -------------" << endl;

				//open with Notepad
				const char* filePath = "bill.txt";

				// open Notepad with the file
				std::string command = "notepad.exe " + std::string(filePath);

			
				int result = system(command.c_str());

	
				if (result == 0) {
					std::cout << "\n\n\t\tBill successfully print\n\n" << std::endl;
				} else {
					std::cerr << "\n\nError opening the file with Notepad.\n\n" << std::endl;
				}
				break;
			}
		} else {

			for(int i = 0; i < listsize; i++) {
				if(items[i].name == additem) {
					avalibility = "yes";
					itemindex = i;
				}

			}
			if(avalibility == "yes") {
				forbill billitmss;
				cout<<"\t\tHow many peices?: ";

				cin>>peice;
				stopcode = 404;
				string typenamee;
				typenamee = typeid(peice).name();


				totleadditems[billItemIndex] = items[itemindex].price * peice;
				billitmss.name = items[itemindex].name;
				billitmss.price = items[itemindex].price;
				billitmss.peice = peice;
				billIt.push_back(billitmss);
				totle = totle + totleadditems[billItemIndex];
				billItemIndex++;



			} else {
				cout<<"\n\t\t--- This procudet unavalible ----\n";
				if(stopcode == 404) {
					cout << "\t\t--- wrong position ----\n";
					break;
				}
				continue;

			}

		}
	}


}


string logname;
void home() {


	if(logname == "dd") {

		cout << "\t\t==============================================\n";
		cout << "\t\t     Welcome to Bakery Management system      \n";
		cout << "\t\t         Developed by Dineth Janitha          \n";
		cout << "\t\t==============================================\n\n";
		string taskname;
		cout << "\t\t1. Add New Item(1) \n";
		cout << "\t\t2. View Items/Packages(2)\n";
		cout << "\t\t3. Search Item(3)\n";
		cout << "\t\t4. Make bill(4)\n";
		cout << "\t\t5. Add New package(5)\n";
		cout << "\t\t6. Logout(9)\n";
		cout << "\t\t7. Exit(10)\n\n";
		cout << "\t\tEnter your choice: ";

		cin>>taskname;
		if(taskname == "1") {
			additems();
			cout<<"\n";
			home();

		} else if(taskname == "2") {
			viewitem();
			cout<<"\n";
			home();

		} else if(taskname == "3") {
			searchitem();
			cout<<"\n";
			home();

		} else if(taskname == "4") {
			makeBill();
			home();
		} else if(taskname == "9") {
			logname = "kk";
			cout << "\n\t\t----  Logout success  ----\n\n";
			home();
			
		} else if(taskname == "5") {
			
			addpackages();
			cout<<"\n";
			home();

		} else if(taskname == "10") {
			return;
		} else {
			taskname = 199;
			cout<<"--Wrong position--\n";
			cout<<"\n";
			home();

		}
	}else{
		cout << "\t\t=============================\n";
		cout << "\t\t     Enter login Details      \n";
		cout << "\t\t=============================\n\n";
		string username;
		string password;
		cout<<"\t\tEnter the username: ";
		cin>>username;
		cout<<"\t\tEnter the password: ";
		cin>>password;
		if(username == "dineth" && password == "1234") {
//			std::cout << R"(
//	
//	
//		)" << '\n';
			addFITS();
			addFPTS();
			cout <<"\n\n\t\t-- Login Successfully --\n\n";
			logname = "dd";
			
			home();
		} else {
			cout <<"\n\t\t--Login Fail Try again--\n\n";
			home();
		}
	}

}


void login() {

}


int main() {
	//	string login_v = login();
//	int taskname;
//	cout<<listsize<<" items have\n";


	//login check heree
//	if(login_v == "success"){
//		cout<<"login successfull!\n\n";
//		cout<<"Welcome to the sales management system!\n";
//		home();
//	}else{
//
//		cout<<login_v<<" is your login status\n\n";
//	}

//	for(int i = 0; i < listsize; i++){
//		cout<<items[i].name<<" "<<items[i].price<<"\n";
//	}                                        

	home();
	return 0;
}