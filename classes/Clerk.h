#ifndef CLERK_H
#define CLERK_H

#include <string>

#include "Person.h"
#include "Customer.h"

class Clerk : public Person {

public:
	Clerk(const std::string& name, const std::string& password);

public:
	bool registerClerk(const std::string& name, const std::string& password);
	std::shared_ptr<Clerk> loginClerk(const std::string& name, const std::string& password);

private:
	std::vector<std::string> m_customers;
};

#endif // !CLERK_H