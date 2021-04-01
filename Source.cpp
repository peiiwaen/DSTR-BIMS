#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

class Books {
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
	void getBook();
};

void Books::addBooks() {
	//set new stream, set it to 2 dp, input double/float to stream, change stream to string
  //source code: http://www.cplusplus.com/reference/iomanip/setprecision/

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

int main() {
	int choice;
	cout << "Welcome to Kinokuniya Book Inventory Management System!" << endl;
	cout << "///////////////////////////////////////////////////////" << endl;
	cout << "Which section do you want to access:\n1. Inventory\n2. Purchase" << endl;
	cin >> choice;



	while (choice !=1 && choice !=2)
	{
		cout << "ERROR! Value entered not recognized!\nWhich section do you want to access:\n1. Inventory\n2. Purchase" << endl;
		cin >> choice;
	}



	switch (choice)
	{
	case 1:
		cout << "Welcome to Inventory section of Kinokuniya Book Inventory Management System!" << endl;
		cout << "////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "Which section do you want to access:\n1. Add Books\n2. View Books\n3. Search Books \n4. Filter Books\n5. Sort Books" << endl;
		cin >> choice;



		while (choice < 1 || choice > 5)
		{
			cout << "ERROR! Value entered not recognized!\nWhich section do you want to access:\n1. Add Books\n2. View Books\n3. Search Books \n4. Filter Books\n5. Sort Books" << endl;
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
			break;
		}
		break;
	case 2:
		cout << "Welcome to Purchase section of Kinokuniya Book Inventory Management System!" << endl;
		cout << "///////////////////////////////////////////////////////////////////////////" << endl;
		cout << "Which section do you want to access:\n1. Add Purchase\n2. View All Purchase\n3. Sort Purchase\n4. View Purchase Detail" << endl;
		cin >> choice;



		while (choice < 1 || choice > 4)
		{
			cout << "Which section do you want to access:\n1. Add Purchase\n2. View All Purchase\n3. Sort Purchase\n4. View Purchase Detail" << endl;
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
		}



		break;
	}



	Books book;




	book.addBooks();
}