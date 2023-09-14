#include "Customer.h"
#include "Database.h"
#include "BookShop.h"

Customer::Customer(const std::string& name, const std::string& password) : 
	Person(name, password, Status::IsCustomer) {}

Customer::Customer(const std::string& name, const std::string& password, std::vector<std::string> books) :
	Person(name, password, Status::IsCustomer), m_bookCart(books) {}

void Customer::addBook() {

	BookShop* bookShop = BookShop::GetInstance();
	std::shared_ptr<Book> book;
	int choice{};

	bookShop->printBooks();

	choice = _getch() - 48;

	choice = choice > bookShop->getBooks().size() ? bookShop->getBooks().size() : choice;

	book = bookShop->getBook(bookShop->getBooks().size() < choice ? bookShop->getBooks().size() : choice);

	m_bookCart.push_back(book->getTitle());

	std::cout << std::endl;
}

std::vector<std::string> Customer::getBooks() {

	return m_bookCart;
}

void Customer::removeBook() {

	if (m_bookCart.size() == 0) {

		std::cout << "\n\n\tCart is Empty Right Now!\n";

		return;
	}

	std::string book;
	int choice{};

	printBooks();

	choice = _getch() - 48;

	choice = choice > m_bookCart.size() ? m_bookCart.size() : choice;

	m_bookCart.erase(m_bookCart.begin() + choice - 1);

	std::cout << std::endl;
}

void Customer::calculatePrice() {

	int price = 0;

	std::size_t cartSize = m_bookCart.size();

	BookShop* bookShop = BookShop::GetInstance();

	std::for_each(m_bookCart.begin(), m_bookCart.end(), [&] (const std::string& book) {

		price += static_cast<int>(bookShop->getBook(book)->getBinding()) * 100 +
			     static_cast<int>(bookShop->getBook(book)->getEdition()) * 100 +
			     static_cast<int>(bookShop->getBook(book)->getQuality()) * 100;
	});

	std::cout << "\n\n\tPrice of Your Books: " << price << std::endl;
}

void Customer::printBooks() {

	std::size_t cartSize = m_bookCart.size();

	std::cout << std::endl;

	for (std::size_t i = 0; i < cartSize - 1; i++)
		std::cout << "\n\t" << i + 1 << ". " << m_bookCart.at(i);

	std::cout << "\n\tAnother. " << m_bookCart.at(cartSize - 1);
}

bool Customer::registerCustomer(const std::string& name, const std::string& password) {

	Database* database = Database::GetInstance();

	std::vector<std::string> names = database->getNames();

	if (!VerifyName(name, names))
		return false;

	database->addCustomer(name, password);
	database->updateDatabase();

	return true;
}

std::shared_ptr<Customer> Customer::loginCustomer(const std::string& name, const std::string& password) {

	Database* database = Database::GetInstance();

	if (!database->checkCorrectDetails(name, password))
		return nullptr;

	return database->getCustomer(name);
}