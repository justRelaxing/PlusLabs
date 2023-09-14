#include "Clerk.h"
#include "Database.h"

Clerk::Clerk(const std::string& name, const std::string& password) : 
	Person(name, password, Status::IsClerk) {}

bool Clerk::registerClerk(const std::string& name, const std::string& password) {

	Database* database = Database::GetInstance();

	std::vector<std::string> names = database->getNames();

	if (!VerifyName(name, names))
		return false;

	database->addClerk(name, password);
	database->updateDatabase();

	return true;
}

std::shared_ptr<Clerk> Clerk::loginClerk(const std::string& name, const std::string& password) {

	Database* database = Database::GetInstance();

	if (!database->checkCorrectDetails(name, password))
		return nullptr;

	return database->getClerk(name);
}