#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
using namespace std;

// Represents a row in the table
struct Row {
    unordered_map<string, string> data; // Column name to value mapping
};

// Represents a table with dynamic columns
struct Table {
    string name;
    vector<string> columns;      // List of column names
    vector<Row> rows;            // Rows of data

    // Default constructor
    Table() {}

    // Parameterized constructor
    Table(const string& tableName, const vector<string>& cols)
        : name(tableName), columns(cols) {}

    void addRow(const Row& row) {
        rows.push_back(row);
    }

    void display() const {
        // Display column headers
        for (size_t i = 0; i < columns.size(); ++i) {
            cout << columns[i] << "\t";
        }
        cout << endl;

        // Display rows
        for (size_t i = 0; i < rows.size(); ++i) {
            for (size_t j = 0; j < columns.size(); ++j) {
                cout << rows[i].data.at(columns[j]) << "\t";
            }
            cout << endl;
        }
    }
};

// Represents the database with multiple tables
class Database {
    unordered_map<string, Table> tables;

public:
    void createTable(const string& tableName, const vector<string>& columns) {
        if (tables.find(tableName) != tables.end()) {
            cout << "Table with name \"" << tableName << "\" already exists.\n";
            return;
        }
        tables[tableName] = Table(tableName, columns);
        cout << "Table \"" << tableName << "\" created successfully.\n";
    }

    void listTables() const {
        if (tables.empty()) {
            cout << "No tables in the database.\n";
            return;
        }
        cout << "Tables in the database:\n";
        for (unordered_map<string, Table>::const_iterator it = tables.begin(); it != tables.end(); ++it) {
            cout << it->first << endl;
        }
    }

    void addRowToTable(const string& tableName, const Row& row) {
        if (tables.find(tableName) == tables.end()) {
            cout << "Table \"" << tableName << "\" does not exist.\n";
            return;
        }
        tables[tableName].addRow(row);
        cout << "Row added to table \"" << tableName << "\".\n";
    }

    void displayTable(const string& tableName) const {
        if (tables.find(tableName) == tables.end()) {
            cout << "Table \"" << tableName << "\" does not exist.\n";
            return;
        }
        tables.at(tableName).display();
    }

    bool tableExists(const string& tableName) const {
        return tables.find(tableName) != tables.end();
    }

    Table& getTable(const string& tableName) {
        return tables[tableName];
    }
};

int main() {
    Database db;
    int choice;

    do {
        cout << "\n--- Database Management ---\n";
        cout << "1. Create Table\n";
        cout << "2. List Tables\n";
        cout << "3. Add Row to Table\n";
        cout << "4. Display Table\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Check for invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string tableName;
                int columnCount;
                vector<string> columns;

                cout << "Enter table name: ";
                cin >> tableName;
                cout << "Enter number of columns: ";
                cin >> columnCount;

                if (cin.fail() || columnCount <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid column count.\n";
                    continue;
                }

                cout << "Enter column names:\n";
                for (int i = 0; i < columnCount; ++i) {
                    string columnName;
                    cin >> columnName;
                    columns.push_back(columnName);
                }

                db.createTable(tableName, columns);
                break;
            }
            case 2:
                db.listTables();
                break;

            case 3: {
                string tableName;
                cout << "Enter table name to add a row: ";
                cin >> tableName;

                // Check if the table exists
                if (!db.tableExists(tableName)) {
                    cout << "Table \"" << tableName << "\" does not exist.\n";
                    continue;
                }

                Table& table = db.getTable(tableName);
                Row newRow;

                cout << "Enter values for the following columns:\n";
                for (size_t i = 0; i < table.columns.size(); ++i) {
                    string value;
                    cout << table.columns[i] << ": ";
                    cin >> value;
                    newRow.data[table.columns[i]] = value;
                }

                db.addRowToTable(tableName, newRow);
                break;
            }
            case 4: {
                string tableName;
                cout << "Enter table name to display: ";
                cin >> tableName;

                db.displayTable(tableName);
                break;
            }
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
