#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
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
	int stock = 0;
	ofstream booksFile;
	stringstream streambP;
	void addBooks();
	void readFromFile();
	void displayList();

	Books* next;
};

//////////////////////////// End of Book Struc ////////////////////////////

struct Books* head = NULL;

//////////////////////////////////////////////////////////////////////////

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

	streambP << fixed << setprecision(2) << bP;
	string bookPrice = streambP.str();
	string bookDetail = title + "|" + to_string(ISBN) + "|" + author + "|" + publisher + "|" + bookPrice + "|" + to_string(stock) + "|" + genre;

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

//void Books::insertBookToList(string t, int i, string a, string p, float b, int s, string g) {
//
//	struct Books* new_Book = (struct Books*)malloc(sizeof(struct Books));
//
//	new_Book->title = t;
//	new_Book->ISBN = i;
//	new_Book->author = i;
//	new_Book->publisher = p;
//	new_Book->bP = b;
//	new_Book->stock = s;
//	new_Book->genre = g;
//
//	new_Book->next = NULL;
//
//	if (head == NULL) {
//		head = new_Book;
//	}
//	else {
//		Books* last = head;
//		while (last->next != NULL) {
//			last = last->next;
//		}
//		last->next = new_Book;
//	}
//}

//////////////////////////// end of insertBookAtList ////////////////////////////

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
	int number = 0;

	if (booksFile.is_open()) {

		while (getline(booksFile,line)) {
			stringstream ss(line);
			number++;
			getline(ss, titles, '|'); 
			getline(ss, ISBNs, '|');
			getline(ss, authors, '|');
			getline(ss, publishers, '|');
			getline(ss, bPs, '|');
			getline(ss, stocks, '|');
			getline(ss, genres, '|');

			//use new instead of malloc, if not wont be able to read string //checkout this source https://www.programmersought.com/article/87014391850/ 
			//+ https://www.geeksforgeeks.org/new-vs-malloc-and-free-vs-delete-in-c/#:~:text=malloc()%3A%20It%20is%20a,%E2%80%9Cmalloc()%E2%80%9D%20does%20not.
			/*struct Books* new_Book = (struct Books*)malloc(sizeof(struct Books));*/

			struct Books* new_Book = new Books;

			new_Book->ISBN = stoi(ISBNs); //stoi = string to integer
			new_Book->title = titles;
			new_Book->author = authors;
			new_Book->publisher = publishers;
			new_Book->bP = stof(bPs); //stof = string to float
			new_Book->stock = stoi(stocks);
			new_Book->genre = genres;

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
			
			//cout << titles + "|" + ISBNs + "|" + authors + "|" + publishers + "|" + bPs + "|" + stocks + "|" + genres << endl;
		}

		booksFile.close();
	}

	else {
		cout << "Fail to open file." << endl;
	}
}

//////////////////////////// end of readFromFile ////////////////////////////

void Books::displayList() {
	struct Books* ptr;
	ptr = head;
	while (ptr != NULL) {
		cout << "*--------------------------------------------------*" << endl;
		cout << ptr->title << "|" << ptr->ISBN << "|" << ptr->author << "|" << ptr->publisher << "|" << ptr->bP << "|" << ptr->stock << "|" << ptr->genre << endl;
		ptr = ptr->next;
	}
	
}

//////////////////////////// end of displayList ////////////////////////////

int main() {

	//declareables 
	Books books;
	int rpt;

	//Main Menu
	int choice;

	MainMenu:
	cout << "Welcome to Kinokuniya Book Inventory Management System!" << endl;
	cout << "*--------------------------------------------------*" << endl; // 50s -
	cout << "Which section do you want to access:\n1. Inventory\n2. Purchase\n3. Exit" << endl;
	cout << "Enter choice: ";
	cin >> choice;

	while (choice !=1 && choice !=2)
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
		
		Menu:
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
			cin >> rpt;
			while (rpt == 1) {
				books.addBooks();
				cout << "*--------------------------------------------------*" << endl;
				cout << "Would you like to add more books? \n1. Yes\n2. No\nEnter choice: ";
				cin >> rpt;
				}

			goto Menu;

			break;
		case 2:
			books.readFromFile();
			books.displayList();
			cout << "*--------------------------------------------------*" << endl;
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
	}

	//////////////////////////// End of Purchase Section ////////////////////////////

}