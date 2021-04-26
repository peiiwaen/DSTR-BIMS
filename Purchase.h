#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <stdlib.h>
using namespace std;

#pragma once
struct Purchase {
private:
	int purchaseISBN, purchaseQty;
	float pricePerB = 0.00, totalPricePerB = 0.00, totalPurchasePrice = 0.00, tax = 0.06;
	string purchaseDate;
public:
	ofstream purchaseFile;
	stringstream streampP;
	void addPurchase();
	Purchase* next;
};
void Purchase::addPurchase() {
	//set new stream, set it to 2 dp, input double/float to stream, change stream to string
  //source code: http://www.cplusplus.com/reference/iomanip/setprecision/

	cout << "*--------------- Add New Purchase --------------*" << endl; // 15s -, front and back 

	//solved. Ref: http://www.cplusplus.com/forum/beginner/39549/ (cin.ignore())
	/*cin.ignore();
	cout << "Enter title of book: ";
	getline(cin, title);*/
	cout << "Enter ISBN of book: ";
	cin >> purchaseISBN;
	cout << "Enter quantity of book: ";

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

	purchaseDate = getDate();

	streambP << fixed << setprecision(2) << bP;
	string bookPrice = streambP.str();
	string bookDetail = title + "|" + to_string(ISBN) + "|" + author + "|" + publisher + "|" + bookPrice + "|" + to_string(stock) + "|" + genre + "|" + getDate();

	//append: write new line
	purchaseFile.open("purhcases.txt", ios::app);

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

