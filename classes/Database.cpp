#include "Database.h"

Database* Database::m_instance {nullptr};

Database* Database::GetInstance() {

	if (m_instance == nullptr)
		m_instance = new Database();

	return m_instance;
}

Database::~Database() {}

Database::Database() {

	std::string folderPath = "accounts";
	
	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {

		if (entry.is_regular_file()) {

			std::ifstream account(entry.path());

			if (!account.is_open()) {

				std::cerr << "Wrong Account Path!";
				continue;
			}

			std::string line;
			std::string currentSection;

			std::string name, password;
			char status{};

			std::vector<std::string> books;

			while (std::getline(account, line)) {

				if (line.empty())
					continue;

				std::istringstream data(line);
				std::string key, value;

				std::getline(data, key, ':');
				std::getline(data, value);

				if (key == "status")
					status = std::stoi(value);

				else if (key == "name")
					name = value;

				else if (key == "password")
					password = value;

				switch (status) {

				case 0:

					if (key == "books") {

						if (!value.empty()) {

						std::istringstream booksData(value);
						std::string book;

						while (std::getline(booksData, book, ','))
							books.push_back(book.substr(book.find_first_not_of(' ')));
						}

						m_customers.emplace_back(std::make_shared<Customer>(name, password, books));
					}

					break;

				case 1:

					if (key == "password")
						m_clerks.emplace_back(std::make_shared<Clerk>(name, password));

					break;
				}
			}

			account.close();
		}
	}
}

void Database::addCustomer(const std::string& name, const std::string& password) {

	m_customers.emplace_back(std::make_shared<Customer>(name, password));
	updateDatabase();
}

void Database::addClerk(const std::string& name, const std::string& password) {

	m_clerks.emplace_back(std::make_shared<Clerk>(name, password));
	updateDatabase();
}

bool Database::checkCorrectDetails(const std::string& name, const std::string& password) {

	for (const auto& customer : m_customers)
		if (customer->getName() == name && customer->getPassword() == password)
			return true;

	for (const auto& clerk : m_clerks)
		if (clerk->getName() == name && clerk->getPassword() == password)
			return true;

	return false;
}

void Database::updateDatabase() {

	for (const auto& customer : m_customers) {

		std::ofstream file("accounts\\" + customer->getName() + ".txt");

		if (!file.is_open()) {

			std::cerr << "Failed to Create File: " << customer->getName() + ".txt" << std::endl;
			continue;
		}

		file << "status:" << static_cast<int>(customer->getStatus()) << std::endl
			 << "name:" << customer->getName() << std::endl
			 << "password:" << customer->getPassword() << std::endl
			 << "books:";

		for (const auto& book : customer->getBooks())
			file << book << ",";

		file << std::endl;

		file.close();
	}

	for (const auto& clerk : m_clerks) {

		std::ofstream file("accounts\\" + clerk->getName() + ".txt");

		if (!file.is_open()) {

			std::cerr << "Failed to Create File: " << clerk->getName() + ".txt" << std::endl;
			continue;
		}

		file << "status:" << static_cast<int>(clerk->getStatus()) << std::endl
			 << "name:" << clerk->getName() << std::endl
			 << "password:" << clerk->getPassword() << std::endl;

		file << std::endl;

		file.close();
	}
}

std::vector<std::string> Database::getNames() {
	
	std::vector<std::string> names;

	for (const auto& customer : m_customers)
		names.push_back(customer->getName());

	for (const auto& clerk : m_clerks)
		names.push_back(clerk->getName());

	return names;
}

std::shared_ptr<Customer> Database::getCustomer(const std::string& name) {

	for (const auto& customer : m_customers)
		if (customer->getName() == name)
			return customer;

	return nullptr;
}

std::shared_ptr<Clerk> Database::getClerk(const std::string& name) {

	for (const auto& clerk : m_clerks)
		if (clerk->getName() == name)
			return clerk;

	return nullptr;
}