#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "../enums/Binding.h"
#include "../enums/Edition.h"
#include "../enums/Quality.h"

class Book {

public:
	Book(const std::string& title, Binding binding, Edition edition, Quality paperQuality);

public:
	Binding getBinding();
	Edition getEdition();
	Quality getQuality();
	std::string getTitle();

private:
	std::string m_title;
	Binding m_binding;
	Edition m_edition;
	Quality m_quality;
};

#endif // !BOOK_H