#include "classes/Menu.h"

int main() {

    std::shared_ptr<Menu> menu = std::make_shared<Menu>();

    while (true) {

        std::cout << "\n\tWhat Do You Want to Do?"
                  << "\n\t1. Register"
                  << "\n\t2. Login"
                  << "\n\t3. Exit";

        switch (_getch()) {

            case '1':

                std::cout << "\n\n\tHow Do You Want to Register?"
                          << "\n\t1. As Customer"
                          << "\n\t2. As Clerk"
                          << "\n\t3. Cancel";

                switch (_getch()) {

                    case '1': menu->registerCustomerMenu(); break;

                    case '2': menu->registerClerkMenu(); break;

                    default: std::cout << "\n\n\tYou're Cancel Registration!\n"; break;
                }

                break;

            case '2':

                std::cout << "\n\n\tHow Do You Want to Login?"
                          << "\n\t1. As Customer"
                          << "\n\t2. As Clerk"
                          << "\n\t3. Cancel";

                switch (_getch()) {

                    case '1': if (menu->loginCustomerMenu()) { menu->customerMenu(); } break;

                    case '2': if (menu->loginClerkMenu()) { menu->clerkMenu(); } break;

                    default: std::cout << "\n\n\tYou're Cancel Logining!\n"; break;
                }

                break;

            default: std::cout << "\n\n\tGoodbye, Dear User!"; return 0;
        }

        _getch(); system("cls");
    }
}