#define _CRT_SECURE_NO_WARNINGS //source: https://stackoverflow.com/questions/22450423/how-to-use-crt-secure-no-warnings (if not cant use localtime since its depreciated. Need to use localtime_s instead
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <stdlib.h>
using namespace std;

//////////////////////////// End of top sections ////////////////////////////

struct Books {
private:

public:
	string title;
	int ISBN;
	string author;
	string publisher;
	float bP;
	string genre;
	string date;
	int stock = 0;
	ofstream booksFile;
	stringstream streambP;
	void addBooks();
	void readFromFile();
	void displayList();
	string getDate();
	Books* next;
};

//////////////////////////// End of Book Struc ////////////////////////////

struct Books* head = NULL;

//////////////////////////////////////////////////////////////////////////

//source code: https://ideone.com/r3SlQL + https://stackoverflow.com/questions/27934034/get-current-time-in-mm-dd-yyyy-in-c

string Books::getDate() {
	const int MAXLEN = 80;
	char s[MAXLEN];
	time_t t = time(0);
	strftime(s, MAXLEN, "%m/%d/%Y", localtime(&t));
	return s;
}

//////////////////////////// End of getDate ////////////////////////////

void Books::addBooks() {
	//set new stream, set it to 2 dp, input double/float to stream, change stream to string
  //source code: http://www.cplusplus.com/reference/iomanip/setprecision/

	cout << "*--------------- Add New Books --------------*" << endl; // 15s -, front and back

	//solved. Ref: http://www.cplusplus.com/forum/beginner/39549/ (cin.ignore())
	cin.ignore();
	cout << "Enter title of book: ";
	getline(cin, title);
	cout << "Enter ISBN of book: ";
	cin >> ISBN;
	cin.ignore();
	cout << "Enter author of book: ";
	getline(cin, author);
	cout << "Enter publisher of book: ";
	getline(cin, publisher);
	cout << "Enter price of book: ";
	cin >> bP;
	cout << "Enter number of book stocked: ";
	cin >> stock;
	while (stock < 0)
	{
		cout << "\nERROR! Value is negative!\nEnter number of book stocked: ";
		cin >> stock;
	}
	cout << "Enter genre of book: ";
	cin >> genre;
	
	date = getDate();

	streambP << fixed << setprecision(2) << bP;
	string bookPrice = streambP.str();
	string bookDetail = title + "|" + to_string(ISBN) + "|" + author + "|" + publisher + "|" + bookPrice + "|" + to_string(stock) + "|" + genre + "|" + getDate();

	//append: write new line
	booksFile.open("books.txt", ios::app);

	//if file is open
	if (booksFile.is_open()) {
		booksFile << bookDetail << endl;
		cout << "Successfully added new book" << endl;
		booksFile.close();
	}
	else {
		cout << "Fail to open file." << endl;
	}
	
}

//////////////////////////// end of AddBook ////////////////////////////

void Books::readFromFile() {

	ifstream booksFile("books.txt");

	string titles;
	string ISBNs;
	string authors;
	string publishers;
	string bPs;
	string stocks;
	string genres;
	
	string line;

	if (booksFile.is_open()) {

		while (getline(booksFile,line)) {
			stringstream ss(line);
			getline(ss, title, '|'); 
			getline(ss, ISBNs, '|');
			getline(ss, author, '|');
			getline(ss, publisher, '|');
			getline(ss, bPs, '|');
			getline(ss, stocks, '|');
			getline(ss, genre, '|');
			getline(ss, date, '|');

			//use new instead of malloc, if not wont be able to read string //checkout this source https://www.programmersought.com/article/87014391850/ 
			//+ https://www.geeksforgeeks.org/new-vs-malloc-and-free-vs-delete-in-c/#:~:text=malloc()%3A%20It%20is%20a,%E2%80%9Cmalloc()%E2%80%9D%20does%20not.
			/*struct Books* new_Book = (struct Books*)malloc(sizeof(struct Books));*/

			struct Books* new_Book = new Books;

			new_Book->ISBN = stoi(ISBNs); //stoi = string to integer
			new_Book->title = title;
			new_Book->author = author;
			new_Book->publisher = publisher;
			new_Book->bP = stof(bPs); //stof = string to float
			new_Book->stock = stoi(stocks);
			new_Book->genre = genre;
			new_Book->date = date;

			new_Book->next = NULL;

			if (head == NULL) {
				head = new_Book;
			}
			else {
				Books* last = head;
				while (last->next != NULL) {
					last = last->next;
				}
				last->next = new_Book;
			}
			
		}

		booksFile.close();
	}

	else {
		cout << "Fail to open file." << endl;
	}
}

//////////////////////////// end of readFromFile ////////////////////////////

void Books::displayList() {
	int noBooks = 0;
	struct Books* ptr;
	ptr = head;
	cout << "*--------------- Book List ---------------*" << endl;
	while (ptr != NULL) {
		noBooks++;
		cout << ptr->title << "|" << ptr->ISBN << "|" << ptr->author << "|" << ptr->publisher << "|" << ptr->bP << "|" << ptr->stock << "|" << ptr->genre << "|" << ptr->date << endl;\
		cout << "*--------------------------------------------------*" << endl;
		ptr = ptr->next;
	}
	cout << "Done displaying all books. There are a total of " << noBooks << " different books inside the database." <<endl;
}

//////////////////////////// end of displayList ////////////////////////////

int main() {

	//declareables 
	Books books;

	//Main Menu
	int choice;

MainMenu:
	cout << "*--------------------------------------------------*" << endl;
	cout << "Welcome to Kinokuniya Book Inventory Management System!" << endl;
	cout << "*--------------------------------------------------*" << endl; // 50s -
	cout << "Which section do you want to access:\n1. Inventory\n2. Purchase\n3. Exit" << endl;
	cout << "Enter choice: ";
	cin >> choice;

	while (choice < 1 || choice > 3)
	{
		cout << "*--------------------------------------------------*" << endl;
		cout << "ERROR! Value entered not recognized!\nWhich section do you want to access:\n1. Inventory\n2. Purchase" << endl;
		cout << "Enter choice: ";
		cin >> choice;
	}

	//////////////////////////// End of Main Menu ////////////////////////////

	switch (choice)
	{
	case 1:
		
		InventoryMenu:
		cout << "*--------------- Inventory Section ---------------*" << endl;
		cout << "Which section do you want to access:\n1. Add Books\n2. View Books\n3. Search Books \n4. Filter Books\n5. Sort Books\n6. Main Menu" << endl;
		cout << "Enter choice: ";
		cin >> choice;



		while (choice < 1 || choice > 6)
		{
			cout << "*--------------------------------------------------*" << endl;
			cout << "ERROR! Value entered not recognized!\nWhich section do you want to access:\n1. Add Books\n2. View Books\n3. Search Books \n4. Filter Books\n5. Sort Books\n6. Main Menu" << endl;
			cout << "Enter choice: ";
			cin >> choice;
		}



		switch (choice)
		{
		case 1:
			books.addBooks();
			cout << "*--------------------------------------------------*" << endl;
			cout << "Would you like to add more books? \n1. Yes\n2. No\nEnter choice: ";
			cin >> choice;
			while (choice == 1) {
				books.addBooks();
				cout << "*--------------------------------------------------*" << endl;
				cout << "Would you like to add more books? \n1. Yes\n2. No\nEnter choice: ";
				cin >> choice;
				}

			goto InventoryMenu;

			break;
		case 2:
			books.readFromFile();
			books.displayList();
			cout << "*--------------------------------------------------*" << endl;
			cout << "Back to Inventory Menu" << endl;
			goto InventoryMenu;
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			goto MainMenu;
			break;
		}

		break;

		////////////////////////////////// End of Inventory Section //////////////////////////////

	case 2:
		cout << "*--------------- Purchase Section ---------------*" << endl;
		cout << "Which section do you want to access:\n1. Add Purchase\n2. View All Purchase\n3. Sort Purchase\n4. View Purchase Detail\n5. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;



		while (choice < 1 || choice > 5)
		{
			cout << "*--------------------------------------------------*" << endl;
			cout << "ERROR! Value entered not recognized!\n1. Add Purchase\n2. View All Purchase\n3. Sort Purchase\n4. View Purchase Detail\n5. Main Menu" << endl;
			cout << "Enter choice: ";
			cin >> choice;
		}



		switch (choice)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			goto MainMenu;
			break;
		}

		break;

		//////////////////////////// End of Purchase Section ////////////////////////////
		
	case 3:
		cout << "*--------------------------------------------------*" << endl;
		cout << "Are you sure you want to exit this program? \n1. Yes\n2. No" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		while (choice < 1 || choice > 2)
		{
			cout << "*--------------------------------------------------*" << endl;
			cout << "ERROR! Value entered not recognized!\nAre you sure you want to exit this program? \n1. Yes\n2. No" << endl;
			cout << "Enter choice: ";
			cin >> choice;
		}

		switch (choice) {
		case 1:
			cout << "*--------------------------------------------------*" << endl;
			cout << "Thank you. See you next time!" << endl;
			cout << "Exiting program......" << endl;
			exit(0); //source: https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm
			break;
		case 2:
			goto MainMenu;
			break;
		}

		//////////////////////////// End of Exit ////////////////////////////

		break;

		//////////////////////////// End of Main Menu ////////////////////////////
	}
}