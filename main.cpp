#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

struct Expense {
    int id;
    std::string description;
    std::string category;
    long double amount;
};

std::string trim(const std::string& value) {
    const std::string whitespace = " \t\n\r\f\v";
    const std::size_t first = value.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = value.find_last_not_of(whitespace);
    return value.substr(first, last - first + 1);
}

std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return value;
}

std::optional<std::string> readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    if (!std::getline(std::cin, value)) {
        return std::nullopt;
    }
    return trim(value);
}

bool parseInteger(const std::string& text, int& result) {
    std::istringstream input(text);
    input >> result;
    if (input.fail()) {
        return false;
    }
    input >> std::ws;
    return input.eof();
}

bool parseAmount(const std::string& text, long double& result) {
    std::istringstream input(text);
    input >> result;
    if (input.fail()) {
        return false;
    }
    input >> std::ws;
    return input.eof() && std::isfinite(result) && result > 0.0L;
}

std::optional<std::string> readRequiredText(const std::string& prompt) {
    while (true) {
        const auto value = readLine(prompt);
        if (!value.has_value()) {
            return std::nullopt;
        }
        if (!value->empty()) {
            return value;
        }
        std::cout << "Input cannot be empty. Please try again.\n";
    }
}

std::optional<int> readMenuChoice() {
    while (true) {
        const auto line = readLine("Choose an option (1-5): ");
        if (!line.has_value()) {
            return std::nullopt;
        }

        int choice = 0;
        if (parseInteger(*line, choice) && choice >= 1 && choice <= 5) {
            return choice;
        }
        std::cout << "Invalid choice. Enter a whole number from 1 to 5.\n";
    }
}

std::optional<long double> readPositiveAmount() {
    while (true) {
        const auto line = readLine("Amount (Rs.): ");
        if (!line.has_value()) {
            return std::nullopt;
        }

        long double amount = 0.0L;
        if (parseAmount(*line, amount)) {
            return amount;
        }
        std::cout << "Invalid amount. Enter a number greater than 0 (example: 250.50).\n";
    }
}

void printMoney(long double amount) {
    std::cout << "Rs. " << std::fixed << std::setprecision(2) << amount;
}

bool addExpense(std::vector<Expense>& expenses, int& nextId) {
    std::cout << "\n--- Add an Expense ---\n";

    const auto description = readRequiredText("Description: ");
    if (!description.has_value()) {
        return false;
    }

    const auto category = readRequiredText("Category (e.g. Food, Travel): ");
    if (!category.has_value()) {
        return false;
    }

    const auto amount = readPositiveAmount();
    if (!amount.has_value()) {
        return false;
    }

    expenses.push_back({nextId, *description, *category, *amount});
    std::cout << "Expense added successfully. Reference ID: " << nextId << "\n";
    ++nextId;
    return true;
}

void listExpenses(const std::vector<Expense>& expenses) {
    std::cout << "\n--- All Expenses ---\n";
    if (expenses.empty()) {
        std::cout << "No expenses recorded yet.\n";
        return;
    }

    std::cout << std::left << std::setw(6) << "ID"
              << std::setw(26) << "Description"
              << std::setw(18) << "Category"
              << std::right << std::setw(14) << "Amount" << "\n";
    std::cout << std::string(64, '-') << "\n";

    for (const Expense& expense : expenses) {
        std::cout << std::left << std::setw(6) << expense.id
                  << std::setw(26) << expense.description.substr(0, 24)
                  << std::setw(18) << expense.category.substr(0, 16)
                  << std::right << "Rs. " << std::fixed << std::setprecision(2)
                  << expense.amount << "\n";
    }
}

void showCategoryTotal(const std::vector<Expense>& expenses) {
    std::cout << "\n--- Total by Category ---\n";
    const auto category = readRequiredText("Enter category to total: ");
    if (!category.has_value()) {
        return;
    }

    long double total = 0.0L;
    int matches = 0;
    for (const Expense& expense : expenses) {
        if (toLower(expense.category) == toLower(*category)) {
            total += expense.amount;
            ++matches;
        }
    }

    if (matches == 0) {
        std::cout << "No expenses found for category '" << *category << "'.\n";
        return;
    }

    std::cout << "Total for " << *category << " (" << matches << " expense(s)): ";
    printMoney(total);
    std::cout << "\n";
}

void showOverallTotal(const std::vector<Expense>& expenses) {
    long double total = 0.0L;
    for (const Expense& expense : expenses) {
        total += expense.amount;
    }

    std::cout << "\n--- Overall Expense Total ---\n";
    std::cout << "Number of expenses: " << expenses.size() << "\n";
    std::cout << "Total spent: ";
    printMoney(total);
    std::cout << "\n";
}

void displayMenu() {
    std::cout << "\n========== EXPENSE TRACKER ==========\n"
              << "1. Add expense\n"
              << "2. List all expenses\n"
              << "3. Show total by category\n"
              << "4. Show overall total\n"
              << "5. Exit\n"
              << "=====================================\n";
}

int main() {
    std::vector<Expense> expenses;
    int nextId = 1;

    std::cout << "Welcome to the Command-Line Expense Tracker!\n";
    while (true) {
        displayMenu();
        const auto choice = readMenuChoice();
        if (!choice.has_value()) {
            std::cout << "\nInput stream closed. Exiting safely.\n";
            break;
        }

        switch (*choice) {
            case 1:
                if (!addExpense(expenses, nextId)) {
                    std::cout << "\nInput stream closed. Exiting safely.\n";
                    return 0;
                }
                break;
            case 2:
                listExpenses(expenses);
                break;
            case 3:
                showCategoryTotal(expenses);
                if (!std::cin) {
                    std::cout << "\nInput stream closed. Exiting safely.\n";
                    return 0;
                }
                break;
            case 4:
                showOverallTotal(expenses);
                break;
            case 5:
                std::cout << "Thank you for using the Expense Tracker. Goodbye!\n";
                return 0;
            default:
                // readMenuChoice() prevents this case, but keep switch defensive.
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
