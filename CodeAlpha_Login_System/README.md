# CodeAlpha Login and Registration System

A C++ console application that allows users to register an account and securely log in. User credentials are saved to a local text file (`users.txt`) acting as a simple database.

## Features
* **Registration:** Validates inputs and prevents duplicate usernames.
* **Login:** Verifies credentials against the stored database file.
* **File Handling:** Uses `ifstream` and `ofstream` to read and write user data persistently.