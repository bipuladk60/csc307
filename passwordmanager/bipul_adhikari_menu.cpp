#include "bipul_adhikari_HashTable.h"
#include <iostream>
#include <string>

void DisplayMenu() {
    std::cout << "1. Add Platform\n"
              << "2. Add New Username/Password\n"
              << "3. Update Existing Password\n"
              << "4. Remove Platform\n"
              << "5. Remove Username/Password\n"
              << "6. Exit\n";
}

int main() {
    HashTable<HashTable<std::string>> platform_table;

    int choice;
    do {
        DisplayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string platform;
            std::cout << "Enter platform name: ";
            std::cin >> platform;
            HashTable<std::string> username_table;
            platform_table.InsertItem(platform, username_table);
            std::cout << "Platform added successfully.\n";
            break;
        }
        case 2: {
            std::string platform, username, password;
            std::cout << "Enter platform name: ";
            std::cin >> platform;
            auto [username_table, found] = platform_table.LookupItem(platform);
            if (!found) {
                std::cout << "Platform not found.\n";
                break;
            }
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;
            username_table.InsertItem(username, password);
            platform_table.UpdateItem(platform, username_table);
            std::cout << "Username and password added successfully.\n";
            break;
        }
        case 3: {
            std::string platform, username, password;
            std::cout << "Enter platform name: ";
            std::cin >> platform;
            auto [username_table, found] = platform_table.LookupItem(platform);
            if (!found) {
                std::cout << "Platform not found.\n";
                break;
            }
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter new password: ";
            std::cin >> password;
            if (!username_table.UpdateItem(username, password)) {
                std::cout << "Username not found.\n";
                break;
            }
            platform_table.UpdateItem(platform, username_table);
            std::cout << "Password updated successfully.\n";
            break;
        }
        case 4: {
            std::string platform;
            std::cout << "Enter platform name: ";
            std::cin >> platform;
            if (!platform_table.RemoveItem(platform)) {
                std::cout << "Platform not found.\n";
                break;
            }
            std::cout << "Platform removed successfully.\n";
            break;
        }
        case 5: {
            std::string platform, username;
            std::cout << "Enter platform name: ";
            std::cin >> platform;
            auto [username_table, found] = platform_table.LookupItem(platform);
            if (!found) {
                std::cout << "Platform not found.\n";
                break;
            }
            std::cout << "Enter username: ";
            std::cin >> username;
            if (!username_table.RemoveItem(username)) {
                std::cout << "Username not found.\n";
                break;
            }
            platform_table.UpdateItem(platform, username_table);
            std::cout << "Username removed successfully.\n";
            break;
        }
        case 6:
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
