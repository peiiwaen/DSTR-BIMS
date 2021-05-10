#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <stack>
#include <vector>
using namespace std;

//////////////////////////// End of top sections ////////////////////////////

struct Books {
private:

public:  
	ofstream booksFile;
	stringstream streambP;
	void addBooks();
	void readFromFileToList();
	void displayAllBooks();
	void sortBooks();
	void deleteBooks();
	Books* next;
	bool searchFound = false, genreFound = false;
	void searchBooks();
	void filterBooks();
	void updateBooks();
	void deductBooks(string i, int p);
	void clearBookList();
	int lineCount;
	string title;
	string ISBN;
	string author;
	string publisher;
	float bP = 0.00;
	string genre;
	string date;
	int stock = 0;
};

struct Purchase {
private:
	int noLine = 0;
	int purchaseQty = 0, typesOfBooks = 0, numberOfComma = 0;
	float pricePerBook = 0.00, totalPricePerBook = 0.00, totalPriceNoTax = 0.00, tax = 0.00, totalFinalPrice = 0.00;
	string purchaseDate, purchaseID = "PID-", purchaseISBN = "";

	//temp string
	string sPurchaseQty, sPricePerBook, sTotalPricePerBook, sPurchaseISBN;

	stack<string> booksISBNs;
	stack<int> purchaseQuantity;
	stack<string> booksPricePP;
	stack<string> totalPricePP;
public:
	ofstream purchaseFile;
	stringstream streampP;
	stringstream streamtpPP;
	stringstream totalPriceOfEachBooks;
	stringstream totalFinal;
	stringstream taxPrice;
	string idIncrement();
	void addPurchase();
	void viewAllPurchase();
	void clearPurchaseList();
	void readPurchaseIntoList();
	void viewPurchaseDetail();
	void sortPurchase(); //not yet
	void countNumberOfComma(string s);
	Purchase* next;
	bool purchaseFound = false;
};


//////////////////////////// End of Structures ////////////////////////////

struct Books* head = NULL;
struct Books* temp = NULL;
struct Purchase* head2 = NULL;

//////////////////////////////////////////////////////////////////////////

//source code: https://ideone.com/r3SlQL + https://stackoverflow.com/questions/27934034/get-current-time-in-mm-dd-yyyy-in-c

string getDate() {
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
	string bookDetail = title + "|" + ISBN + "|" + author + "|" + publisher + "|" + bookPrice + "|" + to_string(stock) + "|" + genre + "|" + getDate();

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
void Books::updateBooks() {


	int updateChoice;
	int updateCategory;

	string ISBNs;
	string bPs;
	string stocks;
	string line;
	int lineNo = 0;
	string tempBookDetails;
	bool yesUpdate = false;
	string newPriceStr;
	string newBookDetails;
	stringstream streamnP;

	cout << "*--------------------------------------------------*" << endl;
	cout << "Are you sure you want to update this book?\n1.Yes\n2.No\nEnter choice:";
	cin >> updateChoice;
	while (updateChoice < 0 || updateChoice > 2) {
		cout << "Invalid value! Please enter correct update choice:\n1.Yes\n2.No\nEnter choice:";
		cin >> updateChoice;
	}

	if (updateChoice == 1) {

		//create new file name tempBooks to store all the data that is not deleted
		ofstream tempBooksFile("tempBooks.txt");
		//must close the file once it is done created
		tempBooksFile.close();

		ifstream booksFile("books.txt");

		cout << "Update choices:\n1. Update stock\n2. Update price\n3. Update both\n4. Exit\nEnter choice: ";
		cin >> updateCategory;
		cout << endl;

		while (updateCategory < 1 || updateCategory > 4) {
			cout << "ERROR! Value entered not recognized!\nUpdate choices:\n1. Update stock\n2. Update price\n3. Update both\n4. Exit\nEnter choice: ";
			cin >> updateCategory;
			cout << endl;
		}

		if (updateCategory == 4) { /*main()*/ }

		if (booksFile.is_open()) {

			while (getline(booksFile, line)) {
				stringstream ss(line);
				getline(ss, title, '|');
				getline(ss, ISBNs, '|');
				getline(ss, author, '|');
				getline(ss, publisher, '|');
				getline(ss, bPs, '|');
				getline(ss, stocks, '|');
				getline(ss, genre, '|');
				getline(ss, date, '|');

				//starts checking if book to be deleted matches with the data of the row
				if (ISBN != ISBNs) {
					if (lineNo == 0) {
						tempBooksFile.open("tempBooks.txt");
						tempBooksFile << line << endl;
						tempBooksFile.close();
					}
					else {
						//append: write new line
						tempBooksFile.open("tempBooks.txt", ios::app);
						//if file is open
						if (tempBooksFile.is_open()) {
							tempBooksFile << line << endl;
							tempBooksFile.close();
						}
						else {
							cout << "Fail to open file." << endl;
						}
					}
				}
				else {
					switch (updateCategory) {
						//update stock
						int newstock;
						float newprice;
						
					case 1:
						cout << "Enter current value of stock to update: ";
						cin >> newstock;
						cout << endl;
						while (newstock < 0) {
							cout << "\nERROR! Value is negative!\nEnter new number of book stocked: ";
							cin >> newstock;
							cout << endl;
						}
						newBookDetails = title + "|" + ISBNs + "|" + author + "|" + publisher + "|" + bPs + "|" + to_string(newstock) + "|" + genre + "|" + date;
						break;
						//update price
					case 2:
						cout << "Enter current value of price to update: ";
						cin >> newprice;
						cout << endl;
						while (newprice < 0) {
							cout << "\nERROR! Value is negative!\nEnter new price of book stocked: ";
							cin >> newprice;
							cout << endl;
						}
						streamnP << fixed << setprecision(2) << newprice;
						newPriceStr = streamnP.str();
						newBookDetails = title + "|" + ISBNs + "|" + author + "|" + publisher + "|" + newPriceStr + "|" + stocks + "|" + genre + "|" + date;
						break;
						//update both
					case 3:
						cout << "Enter current value of stock to update: ";
						cin >> newstock;
						cout << endl;
						while (newstock < 0) {
							cout << "\nERROR! Value is negative!\nEnter new number of book stocked: ";
							cin >> newstock;
							cout << endl;
						}
						cout << "Enter current value of price to update: ";
						cin >> newprice;
						cout << endl;
						while (newprice < 0) {
							cout << "\nERROR! Value is negative!\nEnter new price of book stocked: ";
							cin >> newprice;
							cout << endl;
						}
						streamnP << fixed << setprecision(2) << newprice;
						newPriceStr = streamnP.str();
						newBookDetails = title + "|" + ISBNs + "|" + author + "|" + publisher + "|" + newPriceStr + "|" + to_string(newstock) + "|" + genre + "|" + date;
						break;
					}
					//append: write new line
					tempBooksFile.open("tempBooks.txt", ios::app);
					//if file is open
					if (tempBooksFile.is_open()) {
						tempBooksFile << newBookDetails << endl;
						tempBooksFile.close();
					}
					else {
						cout << "Fail to open file." << endl;
					}
					yesUpdate = true;
				}

				lineNo++;
			}
			tempBooksFile.close();
			// end of while
		}
		else {
			cout << "Failed to open book" << endl;
		}
	}

	booksFile.close();

	if (yesUpdate == true) {
		remove("books.txt");
		rename("tempBooks.txt", "books.txt");
		cout << "*--------------- Successfully updated book. ---------------*" << endl;
		clearBookList();
	}
	else {
		cout << "*--------------- Book update cancelled. ---------------*" << endl;
	}

}

//////////////////////////// end of updateBooks ////////////////////////////
void Books::deductBooks(string i, int p) {

	string ISBNs;
	string stocks;
	string bPs;
	string line;
	int lineNo = 0;
	string tempBookDetails;
	
	string newBookDetails;

		//create new file name tempBooks to store all the data that is not deleted
		ofstream tempBooksFile("tempBooks.txt");
		//must close the file once it is done created
		tempBooksFile.close();

		ifstream booksFile("books.txt");


		if (booksFile.is_open()) {

			while (getline(booksFile, line)) {
				stringstream ss(line);
				getline(ss, title, '|');
				getline(ss, ISBNs, '|');
				getline(ss, author, '|');
				getline(ss, publisher, '|');
				getline(ss, bPs, '|');
				getline(ss, stocks, '|');
				getline(ss, genre, '|');
				getline(ss, date, '|');

				//starts checking if book to be deleted matches with the data of the row
				if (i != ISBNs) {
					if (lineNo == 0) {
						tempBooksFile.open("tempBooks.txt");
						tempBooksFile << line << endl;
						tempBooksFile.close();
					}
					else {
						//append: write new line
						tempBooksFile.open("tempBooks.txt", ios::app);
						//if file is open
						if (tempBooksFile.is_open()) {
							tempBooksFile << line << endl;
							tempBooksFile.close();
						}
						else {
							cout << "Fail to open file." << endl;
						}
					}
				}
				else {
					
						//update stock
					int newstock = stoi(stocks) - p;

						newBookDetails = title + "|" + ISBNs + "|" + author + "|" + publisher + "|" + bPs + "|" + to_string(newstock) + "|" + genre + "|" + date;
	
					//append: write new line
					tempBooksFile.open("tempBooks.txt", ios::app);
					//if file is open
					if (tempBooksFile.is_open()) {
						tempBooksFile << newBookDetails << endl;
						tempBooksFile.close();
					}
					else {
						cout << "Fail to open file." << endl;
					}
					
				}

				lineNo++;
			}
			tempBooksFile.close();
			// end of while
		}
		else {
			cout << "Failed to open book" << endl;
		}
	

	booksFile.close();

		remove("books.txt");
		rename("tempBooks.txt", "books.txt");
		clearBookList();
	
}
//////////////////////////// end of deductBooks ////////////////////////////



void Books::readFromFileToList() {

	clearBookList();

	ifstream booksFile("books.txt");
	lineCount = 0;
	string ISBNs;
	string bPs;
	string stocks;
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

			lineCount++;

			streambP << fixed << setprecision(2) << bPs;
			string bookPrice = streambP.str();

			

			//use new instead of malloc, if not wont be able to read string //checkout this source https://www.programmersought.com/article/87014391850/ 
			//+ https://www.geeksforgeeks.org/new-vs-malloc-and-free-vs-delete-in-c/#:~:text=malloc()%3A%20It%20is%20a,%E2%80%9Cmalloc()%E2%80%9D%20does%20not.
			/*struct Books* new_Book = (struct Books*)malloc(sizeof(struct Books));*/

			struct Books* new_Book = new Books;

			new_Book->ISBN = ISBNs; 
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

void Books::displayAllBooks() {


	int noBooks = 0;
	struct Books* ptr;
	ptr = head;
	cout << "*--------------- Book List ---------------*" << endl;

	cout << endl;
	cout << setw(40) << right << "Book Title";
	cout << setw(16) << right << "\t ISBN";
	cout << setw(30) << right << "\t Author";
	cout << setw(30) << right << "\t Publisher";
	cout << setw(12) << right << "\t Price";
	cout << setw(5) << right << "\t Stock";
	cout << setw(15) << right << "\t Genre";
	cout << setw(13) << right << "\t Date" << endl;;

	while (ptr != NULL) {
		noBooks++;


		cout << setw(40) << ptr->title;
		cout << setw(21) << ptr->ISBN;
		cout << setw(34) << ptr->author;
		cout << setw(35) << ptr->publisher;
		cout << setw(7) << "RM" << fixed << setprecision(2) << ptr->bP;
		cout << setw(8) <<  ptr->stock;
		cout << setw(16) << ptr->genre;
		cout << setw(15) << ptr->date;

		cout << endl;
		/*cout << ptr->title << "|" << ptr->ISBN << "|" << ptr->author << "|" << ptr->publisher << "|" << ptr->bP << "|" << ptr->stock << "|" << ptr->genre << "|" << ptr->date << endl;\*/
		/*cout << "*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*" << endl;*/
		ptr = ptr->next;
	}

	if (noBooks != 0) {
		cout << endl;
		cout << "*--------------------------------------------------*" << endl;
		cout << endl;
		cout << "Done displaying all books. There are a total of " << noBooks << " different books inside the database." << endl;
		cout << endl;
	}
	else {
		cout << "*--------------------------------------------------*" << endl;
		cout << endl;
		cout << "There are no books inside the database. Please insert new book details." << endl;
		cout << endl;
	}

	clearBookList();

}

//////////////////////////// end of displayList ////////////////////////////

void Books::clearBookList() {
	struct Books* current = head;

	//clear linked list
	while (head != NULL) {
		current = current->next;

		delete head;

		head = current;
	}
}

//////////////////////////// end of clearBookList ////////////////////////////

void Purchase::clearPurchaseList() {
	struct Purchase* current = head2;

	//clear linked list
	while (head2 != NULL) {
		current = current->next;

		delete head2;

		head2 = current;
	}
}

//////////////////////////// end of clearPurchaseList ////////////////////////////

void Books::sortBooks() {

	ifstream booksFile("books.txt");

	string ISBNs;
	string bPs;
	string stocks;
	int numberOfLines = 1;
	int numberOfCol = 8;
	string line;
	int lineCount = 0;


	if (booksFile.is_open()) {

		string** a = new string * [numberOfLines];

		while (getline(booksFile, line)) {

			stringstream ss(line);
			getline(ss, title, '|');
			getline(ss, ISBNs, '|');
			getline(ss, author, '|');
			getline(ss, publisher, '|');
			getline(ss, bPs, '|');
			getline(ss, stocks, '|');
			getline(ss, genre, '|');
			getline(ss, date, '|');

			for (int i = 0; i < numberOfLines; i++) {
				a[i] = new string[numberOfCol];
			}

			for (int i = 0; i < numberOfLines; i++) {

				a[i][0] = title;
				a[i][1] = ISBNs;
				a[i][2] = author;
				a[i][3] = publisher;
				a[i][4] = bPs;
				a[i][5] = stocks;
				a[i][6] = genre;
				a[i][7] = date;

			}

			lineCount++;

			//if you want to check if it did write into the array 
			for (int i = 0; i < numberOfLines; i++) {
				for (int j = 0; j < numberOfCol; j++) {
					cout << a[i][j] << "|";
				}
				cout << endl;
			}

		}

		cout << lineCount;

	}
}



//////////////////////////// end of readFromFileToArray  ////////////////////////////

void Books::deleteBooks() {

	int deleteChoice;

	string ISBNs;
	string bPs;
	string stocks;
	string line;
	int lineNo = 0;
	string tempBookDetails;
	bool yesDelete = false;

	cout << "*--------------------------------------------------*" << endl;
	cout << "Are you sure you want to delete this book?\n1.Yes\n2.No\nEnter choice:";
	cin >> deleteChoice;
	while (deleteChoice < 0 || deleteChoice > 2) {
		cout << "Invalid value! Please enter correct delete choice:\n1.Yes\n2.No\nEnter choice:";
		cin >> deleteChoice;
	}

	if (deleteChoice == 1) {

		//create new file name tempBooks to store all the data that is not deleted
		ofstream tempBooksFile("tempBooks.txt");
		//must close the file once it is done created
		tempBooksFile.close();

		ifstream booksFile("books.txt");

		if (booksFile.is_open()) {

		while (getline(booksFile, line)) {
			stringstream ss(line);
			getline(ss, title, '|');
			getline(ss, ISBNs, '|');
			getline(ss, author, '|');
			getline(ss, publisher, '|');
			getline(ss, bPs, '|');
			getline(ss, stocks, '|');
			getline(ss, genre, '|');
			getline(ss, date, '|');


			//starts checking if book to be deleted matches with the data of the row
				if (ISBN != ISBNs) {
					if (lineNo == 0) {
						tempBooksFile.open("tempBooks.txt");
						tempBooksFile << line << endl;
						tempBooksFile.close();
					}
					else {
						//append: write new line
						tempBooksFile.open("tempBooks.txt", ios::app);
						//if file is open
						if (tempBooksFile.is_open()) {
							tempBooksFile << line << endl;
							tempBooksFile.close();
						}
						else {
							cout << "Fail to open file." << endl;
						}
					}
				}
				else {
					yesDelete = true;
				}
	
			lineNo++;
		}
		tempBooksFile.close();
		// end of while
	}
		else {
			cout << "Failed to open book" << endl;
		}
}

	booksFile.close();

	if (yesDelete == true) {
		remove("books.txt");
		rename("tempBooks.txt", "books.txt");
		cout << "*--------------- Successfully deleted book. ---------------*" << endl;
	}
	else {
		cout << "*--------------- Deletion of book cancelled. ---------------*" << endl;
	}
	
}

//////////////////////////// end of deleteBooks  ////////////////////////////

void Books::searchBooks()
{
	searchFound = false;
	genreFound = false;
	int searchType;
	string I;
	string T;
	cout << "*--------------- Search Book ---------------*\nEnter the category you would like to search for book:\n1. Title\n2. ISBN\n3. Exit\nEnter your choice: ";
	cin >> searchType;
	cout << "*--------------------------------------------------*" << endl;

	//Validation
	while (searchType < 1 || searchType > 3)
	{
		cout << "ERROR! Value entered is out of bound!\n*--------------- Search Book ---------------*\nEnter the category you would like to search for book:\n1. Title\n2. ISBN\n3. Exit\nEnter your choice: ";
		cin >> searchType;
		cout << "*--------------------------------------------------*" << endl;
	}

	if (searchType == 3) { /*main()*/ }

	//readFromFileToList() function done, so directly access the link list
	
	struct Books* ptr = head;

	switch (searchType)
	{
	case 1:
		cout << "Enter the title of book to search: ";
		cin.ignore();
		getline(cin, T);
		while (ptr != NULL)
		{
			if (ptr->title != T)
			{
				ptr = ptr->next;
			}
			else {
				cout << "*--------------- Book Found! ---------------*" << endl;
				cout << ptr->title << "|" << ptr->ISBN << "|" << ptr->author << "|" << ptr->publisher << "|" << ptr->bP << "|" << ptr->stock << "|" << ptr->genre << "|" << ptr->date << endl;
				ISBN = ptr->ISBN;
				searchFound = true;
				ptr = NULL;
			}
		}



		break;
	case 2:
		cout << "Enter the ISBN of book to search: ";
		cin >> I;
		while (ptr != NULL)
		{
			if (ptr->ISBN != I) {
				ptr = ptr->next;
			}
			else {
				cout << "*--------------- Book Found! ---------------*" << endl;
				cout << ptr->title << "|" << ptr->ISBN << "|" << ptr->author << "|" << ptr->publisher << "|" << ptr->bP << "|" << ptr->stock << "|" << ptr->genre << "|" << ptr->date << endl;
				ISBN = ptr->ISBN;
				searchFound = true;
				ptr = NULL;
			}
		}


		break;
	}

}

//////////////////////////// end of searchBooks ////////////////////////////

void Books::filterBooks()
{
	int filterType;
	string G;
	cout << "*--------------- Filter Book ---------------*\nEnter the genre of books you would like to filter: ";
	cin.ignore();
	getline(cin, G);
	cout << endl;

	//readFromFileToList() function done, so directly access the link list
	struct Books* ptr = head;
	while (ptr != NULL)
	{
		if (ptr->genre == G)
		{
			cout << ptr->title << "|" << ptr->ISBN << "|" << ptr->author << "|" << ptr->publisher << "|" << ptr->bP << "|" << ptr->stock << "|" << ptr->genre << "|" << ptr->date << endl;
			cout << "*--------------------------------------------------*" << endl;
			genreFound = true;
			ptr = ptr->next;
			
		}
		else {
			ptr = ptr->next;
		}
	}
}

//////////////////////////// end of filterBooks ////////////////////////////

string Purchase::idIncrement() {

	ifstream purchaseFile("purchases.txt");
	string ID;
	string IDConst;
	string IDNumber;
	int numberIncrement;
	string finalID;
	string newID;
	string line;

	if (purchaseFile.is_open()) {

		if (purchaseFile.peek() == ifstream::traits_type::eof()) {

			numberIncrement = 1;
			finalID = to_string(numberIncrement);
			newID = purchaseID + finalID;
			return newID;

		}
		else {
			while (getline(purchaseFile, line)) {
				stringstream ss(line);
				getline(ss, ID, '|');
				//PID-1
				stringstream ss2(ID);
				getline(ss2, IDConst, '-');
				getline(ss2, IDNumber, '-');
			}

			numberIncrement = stoi(IDNumber);
			numberIncrement++;
			finalID = to_string(numberIncrement);
			newID = purchaseID + finalID;
			return newID;
		}

	}

}

//////////////////////////// end of idIncrement  ////////////////////////////

void Purchase::addPurchase() {

	Books b;
	b.readFromFileToList();

	cout << "*--------------- Add New Purchase --------------*" << endl;

	cout << "Enter total number of book types: ";
	cin >> typesOfBooks;
	

	while (typesOfBooks == 0) {
		cout << "\nERROR! Value is negative!\nEnter total number of book types: ";
		cin >> typesOfBooks;
	}


	while (typesOfBooks > b.lineCount) {
		cout << "\nERROR! Value is invalid!\nEnter total number of book types: ";
		cin >> typesOfBooks;
	}


	for (int i = 0; i < typesOfBooks; i++) {
		b.readFromFileToList();
		bool searchFound = false;

		cout << "*--------------- Book " << i+1 << " --------------*" << endl;

		cout << "Enter ISBN of book: ";
		cin >> purchaseISBN;

		struct Books* ptr = head;

		//search ISBN of book (must match with books that exists)
		while (ptr != NULL)
		{
			if (ptr->ISBN != purchaseISBN) {
				ptr = ptr->next;
			}
			else {
				searchFound = true;
				booksISBNs.push(purchaseISBN);

				//bookPrice
				pricePerBook = ptr->bP;
				streamtpPP << fixed << setprecision(2) << pricePerBook;
				booksPricePP.push(streamtpPP.str());

				//purchaseQty
				cout << "Enter number of books purchased: ";
				cin >> purchaseQty;
				while (purchaseQty <= 0)
				{
					cout << "\nERROR! Purchase is invalid!\nEnter number of book purchased: ";
					cin >> purchaseQty;
				}
				while (purchaseQty > ptr->stock) {
					cout << "ERROR! Purchase is invalid!\nEnter number of book purchased: ";
					cin >> purchaseQty;
				}
				purchaseQuantity.push(purchaseQty);

				//deduct Books
				b.deductBooks(purchaseISBN, purchaseQty);

				ptr = NULL;
			}
		}

		while (searchFound == false) {
			cout << "Invalid book ISBN. Please enter the correct ISBN: ";
			cin >> purchaseISBN;
			struct Books* ptr = head;

			//search ISBN of book (must match with books that exists)
			while (ptr != NULL)
			{
				if (ptr->ISBN != purchaseISBN) {
					ptr = ptr->next;
				}
				else {
					searchFound = true;
					booksISBNs.push(purchaseISBN);
					ptr = NULL;
				}
			}
		}

		//to be removed if we can 
		/*cout << "Enter price of book: ";*/
		//cin >> pricePerBook;
		/*pricePerBook = ptr->bP;
		streamtpPP << fixed << setprecision(2) << pricePerBook;
		booksPricePP.push(streamtpPP.str());*/

		//cout << "Enter number of books purchased: ";
		//cin >> purchaseQty;
		//	while (purchaseQty < 0)
		//	{
		//		cout << "\nERROR! Value is negative!\nEnter number of book purchased: ";
		//		cin >> purchaseQty;
		//		//
		//	}
		//purchaseQuantity.push(purchaseQty);

			//calculate total price of the book itself
			totalPricePerBook = purchaseQty * pricePerBook;
			totalPriceOfEachBooks << fixed << setprecision(2) << totalPricePerBook;
			totalPricePP.push(totalPriceOfEachBooks.str());

			//need to clear stringstream: https://stackoverflow.com/questions/20731/how-do-you-clear-a-stringstream-variable
			totalPriceOfEachBooks.str(string());
			streamtpPP.str(string());
	}

	string totalEachBook;
	string booksBought;
	string booksNumber;
	string eachBookPrice;


	//place data into string
	while (!totalPricePP.empty()) {
		//if size of stack is not 1 (not the last item) then add "," behind the item, if it is the last item, dont add
		if (booksISBNs.size() != 1) {
			booksBought = booksBought + booksISBNs.top() + ",";
			booksISBNs.pop();
		}
		else {
			booksBought = booksBought + booksISBNs.top();
		booksISBNs.pop();
		}
	
		if (purchaseQuantity.size() != 1) {
			booksNumber = booksNumber + to_string(purchaseQuantity.top()) + ',';
			purchaseQuantity.pop();
		}
		else {
			booksNumber = booksNumber + to_string(purchaseQuantity.top());
			purchaseQuantity.pop();
		}
		

		if (totalPricePP.size() != 1) {
			totalEachBook = totalEachBook + totalPricePP.top() + ",";
			totalPriceNoTax = totalPriceNoTax + stof(totalPricePP.top());
			totalPricePP.pop();
		}
		else {
			totalEachBook = totalEachBook + totalPricePP.top();
			totalPriceNoTax = totalPriceNoTax + stof(totalPricePP.top());
			totalPricePP.pop();
		}

		if (booksPricePP.size() != 1) {
			eachBookPrice = eachBookPrice + booksPricePP.top() + ',';
			booksPricePP.pop();
		}
		else {
			eachBookPrice = eachBookPrice + booksPricePP.top();
			booksPricePP.pop();
		}
		
	}

	//adding tax
	tax = totalPriceNoTax * 0.06;
	totalFinalPrice = tax + totalPriceNoTax;
	
	//Set the final price to 2 dc, then convert to string for storing
	totalFinal << fixed << setprecision(2) << totalFinalPrice;
	taxPrice << fixed << setprecision(2) << tax;
	string finalPrice = totalFinal.str();
	string finalTax = taxPrice.str();


	//purchase date
	purchaseDate = getDate();

	string purchaseDetail = idIncrement() + "|" + booksBought + "|" + booksNumber + "|" + eachBookPrice +"|" + totalEachBook + "|" + finalTax + "|" + finalPrice + "|" + purchaseDate;
	/*cout << purchaseDetail;*/

	//append: write new line
	purchaseFile.open("purchases.txt", ios::app);

	//if file is open
	if (purchaseFile.is_open()) {
		purchaseFile << purchaseDetail << endl;

		cout << "*--------------- Successfully added new purchase --------------*" << endl;

		purchaseFile.close();
	}
	else {
		cout << "Fail to open file." << endl;
	}

}

//////////////////////////// end of addPurchase  ////////////////////////////

void Purchase::countNumberOfComma(string s) {
	string stringToCheck = s;
	char checkCharacter = ',';
	int count = 0;

	for (int i = 0; i < stringToCheck.size(); i++)
	{
		if (stringToCheck[i] == checkCharacter)
		{
			++count;
		}
	}

	numberOfComma = count;

}

//////////////////////////// end of countNumberOfComma  ////////////////////////////


void Purchase::viewAllPurchase() {

	int noPurchases = 0;
	struct Purchase* ptr = head2;
	ptr = head2;

	cout << "*------------------------------ Purchase List ------------------------------*" << endl;

	while (ptr != NULL)
	{

		//store as string
		string strISBN = ptr->sPurchaseISBN;
		string strQty = ptr->sPurchaseQty;
		string strPrice = ptr->sPricePerBook;
		string strTotal = ptr->sTotalPricePerBook;

		//create vector
		vector<string> strbooksISBNs;
		vector<string> strpurchaseQuantity;
		vector<string> strbooksPricePP;
		vector<string> strtotalPricePP;

		//make each variable (which is a line with delimiter comma into a stringstream
		stringstream ss1(strISBN);
		stringstream ss2(strQty);
		stringstream ss3(strPrice);
		stringstream ss4(strTotal);

		//source code: https://www.geeksforgeeks.org/program-to-parse-a-comma-separated-string-in-c/
		//keep pushing the substr

		//ISBN
		while (ss1.good()) {
			string substr;
			getline(ss1, substr, ',');
			strbooksISBNs.push_back(substr);
		}

		//Qty
		while (ss2.good()) {
			string substr;
			getline(ss2, substr, ',');
			strpurchaseQuantity.push_back(substr);
		}

		//price per book
		while (ss3.good()) {
			string substr;
			getline(ss3, substr, ',');
			strbooksPricePP.push_back(substr);
		}

		//totalpriceperbook
		while (ss4.good()) {
			string substr;
			getline(ss4, substr, ',');
			strtotalPricePP.push_back(substr);
		}
		
			cout << "*----------------------------------- " << purchaseID << " -----------------------------------*" << endl;
			cout << endl;
			cout << "\t Book ISBN";
			cout << "\t Quantity";
			cout << "\t Price Per Book";
			cout << "\t\t   Total Price Per Book" << endl;


			for (size_t i = 0; i < strbooksISBNs.size(); i++) {
				cout << "    " << strbooksISBNs[i];
				cout << "\t\t" << strpurchaseQuantity[i];
				cout << "\t\tRM" << strbooksPricePP[i];
				cout << "\t\t\t\tRM" << strtotalPricePP[i];
				cout << endl;
			}

			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t";
			cout << "Tax   : RM" << ptr->tax << endl;
			cout << "\t\t\t\t\t\t\t\t\t";
			cout << "Total : RM" << ptr->totalFinalPrice << endl;
			cout << "\t\t\t\t\t\t\t\t\t";
			cout << "Date  : " << ptr->purchaseDate << endl;
			cout << endl;

			noPurchases++;
			ptr = ptr -> next;
		
	}

	if (noPurchases != 0) {
		cout << "*---------------------------------------------------------------------------*" << endl;
		cout << "Done displaying all purchases. There are a total of " << noPurchases << " purchases inside the database." << endl;
		cout << "*---------------------------------------------------------------------------*" << endl;
	}
	else {
		cout << "*---------------------------------------------------------------------------*" << endl;
		cout << "There are no purchases inside the database. Please insert new purchase details." << endl;
		cout << "*---------------------------------------------------------------------------*" << endl;
	}

}

//////////////////////////// end of viewAllPurchase  ////////////////////////////

void Purchase::readPurchaseIntoList() {

	clearPurchaseList();

	ifstream purchaseFile("purchases.txt");

	string purchaseISBNs;
	string purchaseQtys;
	string pricePerBooks;
	string totalPricePerBooks;
	string taxs;
	string totalFinalPrices;
	int noPurchases = 0;

	string line;

	if (purchaseFile.is_open()) {

		while (getline(purchaseFile, line)) {
			stringstream ss(line);
			getline(ss, purchaseID, '|');
			getline(ss, purchaseISBNs, '|');
			getline(ss, purchaseQtys, '|');
			getline(ss, pricePerBooks, '|');
			getline(ss, totalPricePerBooks, '|');
			getline(ss, taxs, '|');
			getline(ss, totalFinalPrices, '|');
			getline(ss, purchaseDate, '|');


			//store into linkedlist

			struct Purchase* new_Purchase = new Purchase;

			new_Purchase->purchaseID = purchaseID;
			new_Purchase->sPurchaseISBN = purchaseISBNs;
			new_Purchase->sPurchaseQty = purchaseQtys;
			new_Purchase->sPricePerBook = pricePerBooks;
			new_Purchase->sTotalPricePerBook = totalPricePerBooks; //stof = string to float
			new_Purchase->tax = stof(taxs);
			new_Purchase->totalFinalPrice = stof(totalFinalPrices);
			new_Purchase->purchaseDate = purchaseDate;

			new_Purchase->next = NULL;

			if (head2 == NULL) {
				head2 = new_Purchase;
			}
			else {
				Purchase* last2 = head2;
				while (last2->next != NULL) {
					last2 = last2->next;
				}
				last2->next = new_Purchase;
			}
		}
	}
}

//////////////////////////// end of readPurchaseIntoList  ////////////////////////////

void Purchase::viewPurchaseDetail() {


	purchaseFound = false;
	string searchID;

	struct Purchase* ptr = head2;
	ptr = head2;

	
		cout << "Enter the purchase record ID to search: ";
		cin >> searchID;
		
		while (ptr != NULL)
		{

			//store as string
			string strISBN = ptr->sPurchaseISBN;
			string strQty = ptr->sPurchaseQty;
			string strPrice = ptr->sPricePerBook;
			string strTotal = ptr->sTotalPricePerBook;

			//create vector
			vector<string> strbooksISBNs;
			vector<string> strpurchaseQuantity;
			vector<string> strbooksPricePP;
			vector<string> strtotalPricePP;

			//make each variable (which is a line with delimiter comma into a stringstream
			stringstream ss1(strISBN);
			stringstream ss2(strQty);
			stringstream ss3(strPrice);
			stringstream ss4(strTotal);

			//source code: https://www.geeksforgeeks.org/program-to-parse-a-comma-separated-string-in-c/
			//keep pushing the substr

			//ISBN
			while (ss1.good()) {
				string substr;
				getline(ss1, substr, ',');
				strbooksISBNs.push_back(substr);
			}

			//Qty
			while (ss2.good()) {
				string substr;
				getline(ss2, substr, ',');
				strpurchaseQuantity.push_back(substr);
			}

			//price per book
			while (ss3.good()) {
				string substr;
				getline(ss3, substr, ',');
				strbooksPricePP.push_back(substr);
			}

			//totalpriceperbook
			while (ss4.good()) {
				string substr;
				getline(ss4, substr, ',');
				strtotalPricePP.push_back(substr);
			}


			if (ptr->purchaseID != searchID)
			{
				ptr = ptr->next;
			}
			else {
				cout << "*--------------- Purchase Found! ---------------*" << endl;
				cout << "*----------------------------------- " << ptr->purchaseID << " -----------------------------------*" << endl;
				cout << endl;
				cout << "\t Book ISBN";
				cout << "\t Quantity";
				cout << "\t Price Per Book";
				cout << "\t\t   Total Price Per Book" << endl;


				for (size_t i = 0; i < strbooksISBNs.size(); i++) {
					cout << "    " << strbooksISBNs[i];
					cout << "\t\t" << strpurchaseQuantity[i];
					cout << "\t\tRM" << strbooksPricePP[i];
					cout << "\t\t\t\tRM" << strtotalPricePP[i];
					cout << endl;
				}

				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t";
				cout << "Tax   : RM" << ptr->tax << endl;
				cout << "\t\t\t\t\t\t\t\t\t";
				cout << "Total : RM" << ptr->totalFinalPrice << endl;
				cout << "\t\t\t\t\t\t\t\t\t";
				cout << "Date  : " << ptr->purchaseDate << endl;
				cout << endl;

				purchaseFound = true;
				ptr = NULL;
			}
		}

}


//////////////////////////// end of viewPurchaseDetails ////////////////////////////



int main() {

	//declareables 
	Books books;
	Purchase purchase;

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
			books.readFromFileToList();
			books.displayAllBooks();
			cout << "*--------------------------------------------------*" << endl;
			cout << "Back to Inventory Menu" << endl;
			goto InventoryMenu;
			break;
		case 3:
			books.readFromFileToList();
			books.searchBooks();
			if (books.searchFound == true)
			{
				cout << "*--------------------------------------------------*" << endl;
				cout << "Would you like to update or delete this book?\n1. Update\n2. Delete\n3. Exit\nEnter choice: ";
				cin >> choice;

				//Validate
				while (choice < 1 || choice > 3)
				{
					cout << "ERROR! Value entered is out of bound!\n\nWould you like to update or delete this book?\n1. Update\n2. Delete\n3. Exit\nEnter choice: ";
					cin >> choice;
				}

				//Switch case
				switch (choice)
				{
				case 1:
					books.updateBooks();
					cout << "*--------------------------------------------------*" << endl;
					goto InventoryMenu;
					break;
				case 2:
					books.deleteBooks();
					goto InventoryMenu;
					break;
				case 3:
					goto InventoryMenu;
					break;
				}
			}
			else
			{
				cout << "*--------------------------------------------------*" << endl;
				cout << "ERROR! Book not found!\nWould you like to add this new book?\n1. Yes\n2. No\nEnter choice: ";
				cin >> choice;
				if (choice == 1)
				{
					books.addBooks();
					cout << "*--------------------------------------------------*" << endl;
				}
				goto InventoryMenu;
			}
			break;
		case 4:
			books.readFromFileToList();
			books.filterBooks();
			if (books.genreFound == false) { cout << "ERROR! Genre not found!\n*--------------------------------------------------*" << endl; }
			goto InventoryMenu;
			break;
		case 5:
			books.sortBooks();
			break;
		case 6:
			goto MainMenu;
			break;
		}

		break;

		////////////////////////////////// End of Inventory Section //////////////////////////////

	case 2:

		PurchaseMenu: 
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
			purchase.addPurchase();
			cout << "*--------------------------------------------------*" << endl;
			cout << "Would you like to add more purchase? \n1. Yes\n2. No\nEnter choice: ";
			cin >> choice;
			while (choice == 1) {
				purchase.addPurchase();
				cout << "*--------------------------------------------------*" << endl;
				cout << "Would you like to add more books? \n1. Yes\n2. No\nEnter choice: ";
				cin >> choice;
			}
			goto PurchaseMenu;
			break;
		case 2:
			purchase.readPurchaseIntoList();
			purchase.viewAllPurchase();
			goto PurchaseMenu;
			break;
		case 3:
			break;
		case 4:
			purchase.readPurchaseIntoList();
			purchase.viewPurchaseDetail();
			if (purchase.purchaseFound == true) {
				cout << "*-------------------------Purchase record with same purchase ID has been found.-------------------------*" << endl;
			}
			else {
				cout << "*-------------------------Purchase record with same purchase ID does not exist.-------------------------*" << endl;
				cout << "Would you like to add new purchase record?\n1. Yes\n2. No\nEnter choice: ";
				cin >> choice;
				while (choice < 1 || choice > 2) {
					cout << "Invalid value! Please enter correct value. \nWould you like to add new purchase record?\n1. Yes\n2. No\nEnter choice: ";
					cin >> choice;
				}

				if (choice == 1) {
					purchase.addPurchase();
				}
				else {
					goto PurchaseMenu;
				}
			}
			goto PurchaseMenu;
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

//place functions after main so can call main function
