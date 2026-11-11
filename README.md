# Reliable Command-Line Expense Tracker (C++)

A beginner-friendly, menu-driven expense tracker built with standard C++17. It lets a user add expenses, list recorded expenses, calculate spending by category, and calculate the overall total.

## Features

- **Add expense:** records a description, category, and positive amount.
- **List expenses:** displays every expense in a readable table.
- **Category total:** totals a category (case-insensitive; for example, `food` matches `Food`).
- **Overall total:** shows the number of entries and total spending.
- **Defensive input handling:** rejects blank text, invalid menu choices, non-numeric amounts, zero/negative amounts, non-finite amounts, and values with extra characters. The program also exits safely if standard input closes.
- **Simple collection and functions:** stores records in a `std::vector<Expense>` and separates menu actions into functions.

> **Storage note:** Expenses are stored in memory while the program is running. They are cleared when the application exits. File/database persistence was not part of this task's stated requirements.

## Expense fields

Each expense contains:

| Field | Type | Purpose |
|---|---|---|
| `id` | `int` | Automatically assigned reference number |
| `description` | `std::string` | What the money was spent on |
| `category` | `std::string` | Group such as Food, Travel, or Bills |
| `amount` | `long double` | Expense amount; must be greater than zero |

## Menu flow

1. Add expense
2. List all expenses
3. Show total by category
4. Show overall total
5. Exit

The menu repeats until the user selects **5. Exit**.

## Requirements

- A C++17-compatible compiler (for example, GCC 8+, Clang 7+, or a recent Microsoft Visual C++ compiler).
- A terminal or command prompt.

## Build and run

### Windows (MinGW-w64 / GCC)

Open PowerShell or Command Prompt in the project folder:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o expense_tracker.exe
.\expense_tracker.exe
```

If `g++` is not recognized, install a C++ compiler such as MinGW-w64 and make sure its `bin` directory is added to the Windows `PATH`. Alternatively, use an online C++17 compiler for a quick test.

### Linux

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o expense_tracker
./expense_tracker
```

### macOS (Clang)

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o expense_tracker
./expense_tracker
```

## Sample execution

The screenshots in [`screenshots/`](screenshots/) show example runs from the supplied program. Text transcripts are also available in [`sample_output.txt`](sample_output.txt) and [`sample_validation_output.txt`](sample_validation_output.txt).

Example session:

```text
Welcome to the Command-Line Expense Tracker!

========== EXPENSE TRACKER ==========
1. Add expense
2. List all expenses
3. Show total by category
4. Show overall total
5. Exit
=====================================
Choose an option (1-5): 1

--- Add an Expense ---
Description: Lunch
Category (e.g. Food, Travel): Food
Amount (Rs.): 120.50
Expense added successfully. Reference ID: 1
```

## Input validation checks

- Menu accepts only whole numbers from 1 to 5.
- Description and category cannot be blank.
- Amount must be numeric, finite, and greater than zero.
- Inputs such as `abc`, `0`, `-25`, `12abc`, or `nan` are rejected as amounts.
- Invalid input displays an explanation and asks again instead of terminating the program.

## Project structure

```text
cpp-expense-tracker/
├── main.cpp
├── README.md
├── sample_output.txt
├── sample_validation_output.txt
└── screenshots/
    ├── sample-run.png
    └── validation-run.png
```

## Testing performed

The supplied source was compiled using GCC in C++17 mode with `-Wall -Wextra -pedantic`. The sample session and invalid-input flow were run to check adding, listing, category totals, overall totals, validation, and clean exit.

## Author

Name: Sk Sahin Arman
