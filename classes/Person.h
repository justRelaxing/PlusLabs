#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <memory>

#include "../enums/Status.h"

class Person {

public:
	Person(const std::string& name, const std::string& password, Status status);

public:
	std::string getName();
	std::string getPassword();
	Status getStatus();

public:
	bool VerifyName(const std::string name, std::vector<std::string>& existingNames);

private:
	std::string m_name;
	std::string m_password;
	Status m_status;
};

#endif // !PERSON_H