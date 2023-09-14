#include "Menu.h"

Menu::Menu() : m_customer(nullptr), m_clerk(nullptr) {

	m_database = Database::GetInstance();
	m_bookshop = BookShop::GetInstance();
}

Menu::~Menu() {

	delete m_database;
	delete m_bookshop;
}

void Menu::registerCustomerMenu() {

    std::string name{}, password{};

    std::cout << "\n\n\tEnter Your Name: ";

    std::cin >> name;

    std::cout << "\n\tEnter Your Password: ";

    std::cin >> password;

    if (!m_customer->registerCustomer(name, password)) {

        std::cout << "\n\tYou're Not Succesfully Registred!\n";

        return;
    }

    std::cout << "\n\tYou're Succesfully Registred!\n";
}

void Menu::registerClerkMenu() {

    std::string name{}, password{};

    std::cout << "\n\n\tEnter Your Name: ";

    std::cin >> name;

    std::cout << "\n\tEnter Your Password: ";

    std::cin >> password;

    if (!m_clerk->registerClerk(name, password)) {

        std::cout << "\n\tYou're Not Succesfully Registred!\n";

        return;
    }

    std::cout << "\n\tYou're Succesfully Registred!\n";
}

bool Menu::loginCustomerMenu() {

    std::string name{}, password{};

    std::cout << "\n\n\tEnter Your Name: ";

    std::cin >> name;

    std::cout << "\n\tEnter Your Password: ";

    std::cin >> password;

    if ((m_customer = m_customer->loginCustomer(name, password)) == nullptr) {

        std::cout << "\n\tYou're Not Succesfully Logined!\n";

        return false;
    }

    std::cout << "\n\tYou're Succesfully Logined!\n";

    return true;
}

bool Menu::loginClerkMenu() {

    std::string name{}, password{};

    std::cout << "\n\n\tEnter Your Name: ";

    std::cin >> name;

    std::cout << "\n\tEnter Your Password: ";

    std::cin >> password;

    if ((m_clerk = m_clerk->loginClerk(name, password)) == nullptr) {

        std::cout << "\n\tYou're Not Succesfully Logined!\n";

        return false;
    }

    std::cout << "\n\tYou're Succesfully Logined!\n";

    return true;
}

void Menu::customerMenu() {

    while (true) {

        std::cout << "\n\tWhat Do You Want to Do?"
                  << "\n\t1. Add Book to My Cart"
                  << "\n\t2. Remove Book from My Cart"
                  << "\n\t3. Calculate Cart Price"
                  << "\n\t4. Exit";

        switch (_getch()) {

        case '1': 
            
            m_customer->addBook(); 
            
            m_database->updateDatabase();
            
            break;

        case '2': 
            
            m_customer->removeBook();

            m_database->updateDatabase();

            break;

        case '3':

            m_customer->calculatePrice();

            break;

        case '4': return;
        }
    }
}

void Menu::clerkMenu() {

    while (true) {

        std::cout << "\n\tWhat Do You Want to Do?"
                  << "\n\t1. Add Books to Shop"
                  << "\n\t2. Exit";

        switch (_getch()) {

            case '1': m_bookshop->addBook(); break;

            default: std::cout << "\n\n\tYou're Exit from Your Account!"; return;
        }
    }
}