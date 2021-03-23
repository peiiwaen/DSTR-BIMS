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
	void writeTo();
	void getBook();
};

void Books::writeTo() {
	//set new stream, set it to 2 dp, input double/float to stream, change stream to string
  //source code: http://www.cplusplus.com/reference/iomanip/setprecision/
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

void Books::getBook() {

	cout << "Enter new book details" << endl;

	cout << "Book title: ";
	getline(cin, title);
	cout << "ISBN: ";
	cin >> ISBN;

	//solved. Ref: http://www.cplusplus.com/forum/beginner/39549/ (cin.ignore())
	cin.ignore();
	cout << "Author: ";
	getline(cin, author);

	cout << "Publisher: ";
	getline(cin, publisher);

	cout << "Book price: ";
	cin >> bP;

	cout << "Stock: ";
	cin >> stock;
	while (stock < 0) {
		cout << "Please enter number of stock (0 or more): ";
		cin >> stock;
	}

	cout << "Genre: ";
	cin >> genre;

}

int main () {

	cout << "Welcome to Kinokuniya Book Inventory Management System!" << endl;
	cout << "///////////////////////////////////////////////////////" << endl;

	Books book;

	book.getBook();
	book.writeTo();
}