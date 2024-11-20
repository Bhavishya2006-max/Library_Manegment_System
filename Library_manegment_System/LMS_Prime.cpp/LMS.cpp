#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // For find()

using namespace std;

class Book {
public:
    string title;
    string author;
    bool isBorrowed;

    Book(string t, string a) : title(t), author(a), isBorrowed(false) {}

    void display() const {
        cout << "Title: " << title << ", Author: " << author;
        if (isBorrowed) {
            cout << " (Borrowed)" << endl;
        } else {
            cout << " (Available)" << endl;
        }
    }
};

class User {
public:
    string studentRegNo;  // Student registration number
    string name;
    vector<string> borrowedBooks;

    User(string regNo, string n) : studentRegNo(regNo), name(n) {}

    void display() const {
        cout << "Student Reg No: " << studentRegNo << ", Name: " << name << ", Borrowed Books: ";
        if (borrowedBooks.empty()) {
            cout << "None" << endl;
        } else {
            for (const string& bookTitle : borrowedBooks) {
                cout << bookTitle << " ";
            }
            cout << endl;
        }
    }

    bool hasBorrowed(const string& bookTitle) const {
        return find(borrowedBooks.begin(), borrowedBooks.end(), bookTitle) != borrowedBooks.end();
    }
};

class Library {
    vector<Book> books;
    vector<User> users;

    Book* findBook(const string& title) {
        for (auto &book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;
    }

    User* findUser(const string& studentRegNo) {
        for (auto &user : users) {
            if (user.studentRegNo == studentRegNo) {
                return &user;
            }
        }
        return nullptr;
    }

public:
    void addBook(const string& title, const string& author) {
        if (findBook(title) == nullptr) {
            books.emplace_back(title, author);
            cout << "Book added: " << title << " by " << author << endl;
        } else {
            cout << "Error: A book with title \"" << title << "\" already exists." << endl;
        }
    }

    void addUser(const string& studentRegNo, const string& name) {
        if (findUser(studentRegNo) == nullptr) {
            users.emplace_back(studentRegNo, name);
            cout << "User added: " << name << endl;
        } else {
            cout << "Error: A user with registration number \"" << studentRegNo << "\" already exists." << endl;
        }
    }

    void borrowBook(const string& studentRegNo, const string& title) {
        Book* book = findBook(title);
        User* user = findUser(studentRegNo);

        if (book && user) {
            if (book->isBorrowed) {
                cout << "Sorry, the book \"" << title << "\" is not available. It has already been borrowed." << endl;
            } else if (user->hasBorrowed(title)) {
                cout << "You have already borrowed the book \"" << title << "\"." << endl;
            } else {
                book->isBorrowed = true;
                user->borrowedBooks.push_back(title);
                cout << "Book borrowed: " << title << " by " << user->name << endl;
            }
        } else {
            if (!book) cout << "Error: Book not found." << endl;
            if (!user) cout << "Error: User not found." << endl;
        }
    }

    void returnBook(const string& studentRegNo, const string& title) {
        Book* book = findBook(title);
        User* user = findUser(studentRegNo);

        if (book && user) {
            if (book->isBorrowed) {
                auto it = find(user->borrowedBooks.begin(), user->borrowedBooks.end(), title);
                if (it != user->borrowedBooks.end()) {
                    book->isBorrowed = false;
                    user->borrowedBooks.erase(it);
                    cout << "Book returned: " << title << " by " << user->name << endl;
                } else {
                    cout << "Error: You did not borrow this book." << endl;
                }
            } else {
                cout << "Error: Book was not borrowed." << endl;
            }
        } else {
            if (!book) cout << "Error: Book not found." << endl;
            if (!user) cout << "Error: User not found." << endl;
        }
    }

    void searchBook(const string& title) const {
        bool found = false;
        for (const auto &book : books) {
            if (book.title.find(title) != string::npos) {
                book.display();
                found = true;
            }
        }
        if (!found) {
            cout << "No book found with title containing: " << title << endl;
        }
    }

    void displayAllBooks() const {
        cout << "Books in library:" << endl;
        for (const auto &book : books) {
            book.display();
        }
    }

    void displayAllUsers() const {
        cout << "Registered users:" << endl;
        for (const auto &user : users) {
            user.display();
        }
    }
};

int main() {
    Library library;

    int numBooks, numUsers;

    // Input number of books and users
    cout << "Enter the number of books: ";
    cin >> numBooks;
    cin.ignore();  // To clear the newline after the number input

    // Add books
    for (int i = 0; i < numBooks; ++i) {
        string title, author;

        cout << "Enter details for book " << i + 1 << ":\n";
        cout << "Title: ";
        getline(cin, title);
        cout << "Author: ";
        getline(cin, author);

        library.addBook(title, author);
    }

    // Input number of users
    cout << "Enter the number of users: ";
    cin >> numUsers;
    cin.ignore();  // To clear the newline after the number input

    // Add users
    for (int i = 0; i < numUsers; ++i) {
        string studentRegNo, name;

        cout << "Enter details for user " << i + 1 << ":\n";
        cout << "Student Registration Number: ";
        getline(cin, studentRegNo);
        cout << "Name: ";
        getline(cin, name);

        library.addUser(studentRegNo, name);
    }

    // Display books and users
    library.displayAllBooks();
    library.displayAllUsers();

    // Example of borrowing and returning books
    string title, studentRegNo;
    cout << "Enter student registration number to borrow a book: ";
    getline(cin, studentRegNo);
    cout << "Enter book title to borrow: ";
    getline(cin, title);
    library.borrowBook(studentRegNo, title);

    // Trying to borrow the same book again
    cout << "Enter student registration number to borrow a book again: ";
    getline(cin, studentRegNo);
    cout << "Enter book title to borrow again: ";
    getline(cin, title);
    library.borrowBook(studentRegNo, title);  // This should give feedback that the book is not available

    cout << "Enter student registration number to return a book: ";
    getline(cin, studentRegNo);
    cout << "Enter book title to return: ";
    getline(cin, title);
    library.returnBook(studentRegNo, title);

    // Search for a book by title
    cout << "Enter a title to search for: ";
    getline(cin, title);
    library.searchBook(title);

    return 0;
}