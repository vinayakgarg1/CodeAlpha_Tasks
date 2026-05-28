#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Function to check if a username already exists in the file
bool isUsernameTaken(const string& username) {
    ifstream file("users.txt");
    string storedUser, storedPass;
    while (file >> storedUser >> storedPass) { // Read file line by line
        if (storedUser == username) {
            file.close();
            return true; // Match found
        }
    }
    file.close();
    return false;
}
// Function to handle user registration
void registerUser() {
    string username, password;
    cout << "\n--- REGISTRATION ---\n";
    cout << "Enter a new username (no spaces): ";
    cin >> username;
    if (isUsernameTaken(username)) { // Check for duplicate username
        cout << "[ERROR] That username is already taken. Please try another one.\n";
        return;
    }
    cout << "Enter a password (no spaces): ";
    cin >> password;
    ofstream file("users.txt", ios::app); // Open file in append mode to add the new user
    if (file.is_open()) {
        file << username << " " << password << "\n";
        file.close();
        cout << "[SUCCESS] Registration successful! You can now login.\n";
    } else {
        cout << "[ERROR] Could not open database file.\n";
    }
}
// Function to handle user login
void loginUser() {
    string username, password;
    string storedUser, storedPass;
    bool isFound = false;
    cout << "\n--- LOGIN ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "[ERROR] Database file not found. Please register a user first.\n";
        return;
    }
    while (file >> storedUser >> storedPass) { // Check credentials against the file
        if (storedUser == username && storedPass == password) {
            isFound = true;
            break;
        }
    }
    file.close();
    if (isFound) { // Provide appropriate messages
        cout << "[SUCCESS] Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "[ERROR] Invalid username or password. Please try again.\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n=======================================\n";
        cout << "      Login & Registration System      \n";
        cout << "=======================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
    
        if (!(cin >> choice)) { // Basic input validation for the menu
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
    return 0;
}