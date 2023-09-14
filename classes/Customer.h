#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include <numeric>

#include "Person.h"
#include "Book.h"

class Customer : public Person {

public:
	Customer(const std::string& name, const std::string& password);
	Customer(const std::string& name, const std::string& password, std::vector<std::string> books);

public:
	void removeBook();
	void calculatePrice();
	
public:
	void addBook();
	std::vector<std::string> getBooks();
	void printBooks();

public:
	bool registerCustomer(const std::string& name, const std::string& password);
	std::shared_ptr<Customer> loginCustomer(const std::string& name, const std::string& password);

private:
	std::vector<std::string> m_bookCart;
};

#endif // !CUSTOMER_H