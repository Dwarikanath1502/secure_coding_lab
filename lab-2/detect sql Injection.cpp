// Implement a program that detects SQL Injection attempts in a login form.


#include <iostream>
#include <string>
#include <regex>

// Function to check for common SQL injection patterns
bool detectSQLInjection(const std::string& input) {
    // Define a refined list of common SQL injection patterns using regular expressions
    std::regex sql_injection_patterns("('|--|;|DROP|SELECT|INSERT|UPDATE|DELETE|UNION|#|OR\\s+1=1|AND\\s+1=1)", std::regex::icase);

    // Search for patterns in the input
    if (std::regex_search(input, sql_injection_patterns)) {
        return true; // Potential SQL injection detected
    }
    return false; // No SQL injection detected
}

int main() {
    std::string username, password;

    // Simulating a simple login form
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    // Check for SQL injection in username or password
    bool is_injection_detected = detectSQLInjection(username) || detectSQLInjection(password);

    if (is_injection_detected) {
        std::cout << "Warning: SQL Injection attempt detected!" << std::endl;
    } else {
        std::cout << "Input seems safe. Proceeding with login..." << std::endl;
    }

    return 0;
}
