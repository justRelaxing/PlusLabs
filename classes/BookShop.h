#ifndef BOOKSHOP_H
#define BOOKSHOP_H

#include <vector>
#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <conio.h>

#include "Book.h"

class BookShop {

public:
	static BookShop* GetInstance();
	~BookShop();

private:
	BookShop();

public:
	std::shared_ptr<Book> getBook(std::string name);
	std::shared_ptr<Book> getBook(int index);
	std::vector<std::shared_ptr<Book>> getBooks();
	void addBook();
	void updateBookShop();
	void printBooks();

private:
	std::vector<std::shared_ptr<Book>> m_books;

private:
	static BookShop* m_instance;
};

#endif // !BOOKSHOP_H