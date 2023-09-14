#include "Person.h"

Person::Person(const std::string& name, const std::string& password, Status status) :
	m_name(name), m_password(password), m_status(status) {}

bool Person::VerifyName(const std::string name, std::vector<std::string>& existingNames) {

	for (const std::string& existingName : existingNames)
		if (name == existingName)
			return false;

	return true;
}

std::string Person::getName() {
	return m_name;
}

std::string Person::getPassword() {
	return m_password;
}

Status Person::getStatus() {
	return m_status;
}
