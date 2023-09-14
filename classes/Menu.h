#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <conio.h>

#include "Database.h"
#include "BookShop.h"
#include "Customer.h"
#include "Clerk.h"

class Menu {

public:
	Menu();
	~Menu();

public:
	void registerCustomerMenu();
	void registerClerkMenu();
	bool loginCustomerMenu();
	bool loginClerkMenu();

public:
	void customerMenu();
	void clerkMenu();

private:
	Database* m_database;
	BookShop* m_bookshop;

	std::shared_ptr<Customer> m_customer;
	std::shared_ptr<Clerk> m_clerk;
};

#endif // !MENU_H