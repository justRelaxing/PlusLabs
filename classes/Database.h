#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

#include "Customer.h"
#include "Clerk.h"

class Database {

public:
    static Database* GetInstance();
    ~Database();

private:
    Database();

public:
    void addCustomer(const std::string& name, const std::string& password);
    void addClerk(const std::string& name, const std::string& password);
    bool checkCorrectDetails(const std::string& name, const std::string& password);
    void updateDatabase();

public:
    std::vector<std::string> getNames();
    std::shared_ptr<Customer> getCustomer(const std::string& name);
    std::shared_ptr<Clerk> getClerk(const std::string& name);

private:
    static Database* m_instance;

	std::vector<std::shared_ptr<Customer>> m_customers;
    std::vector<std::shared_ptr<Clerk>> m_clerks;
};

#endif // !DATABASE_H