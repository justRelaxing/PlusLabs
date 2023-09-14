#include "BookShop.h"

BookShop* BookShop::m_instance{ nullptr };

BookShop* BookShop::GetInstance() {

	if (m_instance == nullptr)
		m_instance = new BookShop();

	return m_instance;
}

BookShop::~BookShop() {}

BookShop::BookShop() {

	std::string folderPath = "books";

	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {

		if (entry.is_regular_file()) {

			std::ifstream book(entry.path());

			if (!book.is_open()) {

				std::cerr << "Wrong Account Path!";
				continue;
			}

			std::string line;
			std::string currentSection;

			std::string title;
			Binding binding;
			Edition edition;
			Quality quality;

			while (std::getline(book, line)) {

				if (line.empty())
					continue;

				std::istringstream data(line);
				std::string key, value;

				std::getline(data, key, ':');
				std::getline(data, value);

				if (key == "title")
					title = value;

				else if (key == "binding")
					binding = static_cast<Binding>(std::stoi(value));

				else if (key == "edition")
					edition = static_cast<Edition>(std::stoi(value));

				else if (key == "quality") {

					quality = static_cast<Quality>(std::stoi(value));

					m_books.emplace_back(std::make_shared<Book>(title, binding, edition, quality));
				}
			}

			book.close();
		}
	}
}

std::shared_ptr<Book> BookShop::getBook(std::string name) {

	for (const auto& book : m_books)
		if (book->getTitle() == name)
			return book;

	return nullptr;
}

std::shared_ptr<Book> BookShop::getBook(int index) {

	return m_books.at(index - 1);
}

std::vector<std::shared_ptr<Book>> BookShop::getBooks() {

	return m_books;
}

void BookShop::addBook() {

	std::string title;
	Binding binding;
	Edition edition;
	Quality quality;

	std::cout << "\n\n\tInput Title of Book: ";

	std::cin >> title;

	std::cout << "\n\tSelect Binding of Book: "
		<< "\n\t1. Stapling"
		<< "\n\t2. Spring"
		<< "\n\t3. French"
		<< "\n\t4. Typographic"
		<< "\n\t5. Office"
		<< "\n\t6. Diploma"
		<< "\n\tAnother. Integral";

	switch (_getch()) {

		case '1':	binding = Binding::Stapling;	break;
		case '2':	binding = Binding::Spring;		break;
		case '3':	binding = Binding::French;		break;
		case '4':	binding = Binding::Typographic;	break;
		case '5':	binding = Binding::Office;		break;
		case '6':	binding = Binding::Diploma;		break;
		default:	binding = Binding::Integral;	break;
	}

	std::cout << "\n\n\tSelect Edition of Book: "
		      << "\n\t1. Trade"
		      << "\n\t2. Science"
		      << "\n\t3. Children"
		      << "\n\t4. Academic"
		      << "\n\tAnother. Art";

	switch (_getch()) {

		case '1':	edition = Edition::Trade;		break;
		case '2':	edition = Edition::Science;		break;
		case '3':	edition = Edition::Children;	break;
		case '4':	edition = Edition::Academic;	break;
		default:	edition = Edition::Art;			break;
	}

	std::cout << "\n\n\tSelect Quality of Book: "
			  << "\n\t1. Bad"
			  << "\n\t2. Good"
			  << "\n\tAnother. Excellent";

	switch (_getch()) {

		case '1':	quality = Quality::Bad;			break;
		case '2':	quality = Quality::Good;		break;
		default:	quality = Quality::Excellent;	break;
	}

	std::cout << std::endl;

	m_books.emplace_back(std::make_shared<Book>(title, binding, edition, quality));

	updateBookShop();
}

void BookShop::updateBookShop() {

	for (const auto& book : m_books) {

		std::ofstream file("books\\" + book->getTitle() + ".txt");

		if (!file.is_open()) {

			std::cerr << "Failed to Create File: " << book->getTitle() + ".txt" << std::endl;
			continue;
		}

		file << "title:" << book->getTitle() << std::endl
			 << "binding:" << static_cast<int>(book->getBinding()) << std::endl
			 << "edition:" << static_cast<int>(book->getEdition()) << std::endl
			 << "quality:" << static_cast<int>(book->getQuality()) << std::endl;

		file.close();
	}
}

void BookShop::printBooks() {

	std::size_t cartSize = m_books.size();

	std::cout << std::endl;

	for (std::size_t i = 0; i < cartSize - 1; i++)
		std::cout << "\n\t" << i + 1 << ". " << m_books.at(i)->getTitle();

	std::cout << "\n\tAnother. " << m_books.at(cartSize - 1)->getTitle();
}
