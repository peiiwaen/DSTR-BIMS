#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

int main () {

  ofstream booksFile;
  string title;
  int ISBN;
  string author;
  string publisher;
 float bP;
  string genre;
  int stock;

  stringstream streambP;

  cout << "Book title: ";
  getline(cin, title);
  cout << "ISBN: ";
  cin >> ISBN;
 /* cout << "Author: ";
  getline(cin, author);*/
  cout << "Book price: ";
  cin >>  bP;
  cout << "Stock: ";
  cin >> stock;
  /*
  cout << "Publisher: ";
  getline(cin, publisher);
  cout << "Genre: ";
  cin >> genre;*/

  //set new stream, set it to 2 dp, input double/float to stream, change stream to string
  //source code: http://www.cplusplus.com/reference/iomanip/setprecision/
  streambP << fixed << setprecision(2) << bP;
  string bookPrice = streambP.str();

  string fullDetail = title + "|" + to_string(ISBN) + "|" + author + "|" + bookPrice + "|" + to_string(stock);

  booksFile.open ("books.txt", ios::app);
  booksFile  << fullDetail << endl;
  booksFile.close();
  return 0;

}