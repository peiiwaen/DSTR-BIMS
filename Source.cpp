#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <stack>
using namespace std;

//////////////////////////// End of top sections ////////////////////////////

struct Books {
private:
	string title;
	int ISBN = 0;
	string author;
	string publisher;
	float bP = 0.00;
	string genre;
	string date;
	int stock = 0;
public:  
	ofstream booksFile;
	stringstream streambP;
	void addBooks();
	void readFromFileToList();
	void displayList();
	void sortBooks();
	Books* next;
};

struct Purchase {
private:
	int purchaseISBN = 0, purchaseQty = 0, typesOfBooks = 0;
	float pricePerBook = 0.00, totalPricePerBook = 0.00, totalPriceNoTax = 0.00, tax = 0.00, totalFinalPrice = 0.00;
	string purchaseDate, purchaseID = "PID-";
	stack<int> booksISBNs;
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
	Purchase* next;
};


//////////////////////////// End of Structures ////////////////////////////

struct Books* head = NULL;

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

void Books::readFromFileToList() {

	ifstream booksFile("books.txt");

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
	if (noBooks != 0) {
		cout << "Done displaying all books. There are a total of " << noBooks << " different books inside the database." << endl;
	}
	else {
		cout << "There are no books inside the database. Please insert new book details." << endl;
		
	}

}

//////////////////////////// end of displayList ////////////////////////////

void Books::sortBooks() {

	ifstream booksFile("books.txt");

	string ISBNs;
	string bPs;
	string stocks;
	int numberOfLines = 1;
	int numberOfCol = 8;
	string line;


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

			//if you want to check if it did write into the array 
			/*for (int i = 0; i < numberOfLines; i++) {
				for (int j = 0; j < numberOfCol; j++) {
					cout << a[i][j] << "|";
				}
				cout << endl;
			}*/

		}

		booksFile.close();
	}

	else {
		cout << "Fail to open file." << endl;
	}

}

//////////////////////////// end of readFromFileToArray  ////////////////////////////

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

	cout << "*--------------- Add New Purchase --------------*" << endl;

	cout << "Enter total number of book types: ";
	cin >> typesOfBooks;
	while (typesOfBooks < 0) {
		cout << "\nERROR! Value is negative!\nEnter total number of book types: ";
		cin >> typesOfBooks;
	}


	for (int i = 0; i < typesOfBooks; i++) {
		cout << "*--------------- Book " << i+1 << " --------------*" << endl;
		cout << "Enter ISBN of book: ";
		cin >> purchaseISBN;
		booksISBNs.push(purchaseISBN);
		cout << "Enter price of book: ";
		cin >> pricePerBook;
		streamtpPP << fixed << setprecision(2) << pricePerBook;
		booksPricePP.push(streamtpPP.str());
		cout << "Enter number of books purchased: ";
		cin >> purchaseQty;
			while (purchaseQty < 0)
			{
				cout << "\nERROR! Value is negative!\nEnter number of book purchased: ";
				cin >> purchaseQty;
			}
		purchaseQuantity.push(purchaseQty);

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
		if (booksBought.size() > 1) {
			booksBought = booksBought + to_string(booksISBNs.top());
				booksISBNs.pop();
		}
		else {
			booksBought = booksBought + to_string(booksISBNs.top()) + ",";
		booksISBNs.pop();
		}
	
		if (booksNumber.size() > 1) {
			booksNumber = booksNumber + to_string(purchaseQuantity.top());
			purchaseQuantity.pop();
		}
		else {
			booksNumber = booksNumber + to_string(purchaseQuantity.top()) + ',';
			purchaseQuantity.pop();
		}
		

		if (totalEachBook.size() > 1) {
			totalEachBook = totalEachBook + totalPricePP.top();
			totalPriceNoTax = totalPriceNoTax + stof(totalPricePP.top());
			totalPricePP.pop();
		}
		else {
			totalEachBook = totalEachBook + totalPricePP.top() + ",";
			totalPriceNoTax = totalPriceNoTax + stof(totalPricePP.top());
			totalPricePP.pop();
		}

		if (eachBookPrice.size() > 1) {
			eachBookPrice = eachBookPrice + booksPricePP.top();
			booksPricePP.pop();
		}
		else {
			eachBookPrice = eachBookPrice + booksPricePP.top() + ",";
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
