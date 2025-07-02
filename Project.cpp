#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    string issuedTo;

    Book(int id, string title, string author)
        : id(id), title(title), author(author), isIssued(false), issuedTo("") {}
};

class Library {
private:
    vector<Book> books;
public:
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
        cout << "Book successfully.\n";
    }

    void searchBookById(int id) {
        for (auto &book : books) {
            if (book.id == id) {
                displayBook(book);
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void searchBookByTitle(string title) {
        for (auto &book : books) {
            if (book.title == title) {
                displayBook(book);
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void issueBook(int id, string studentName) {
        for (auto &book : books) {
            if (book.id == id) {
                if (!book.isIssued) {
                    book.isIssued = true;
                    book.issuedTo = studentName;
                    cout << "Book issued to " << studentName << ".\n";
                } else {
                    cout << "Book is already issued.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook(int id) {
        for (auto &book : books) {
            if (book.id == id) {
                if (book.isIssued) {
                    book.isIssued = false;
                    book.issuedTo = "";
                    cout << "Book returned successfully.\n";
                } else {
                    cout << "Book was not issued.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void listAllBooks() {
        sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
            return a.title < b.title;
        });

        for (const auto &book : books) {
            displayBook(book);
        }
    }

    void deleteBook(int id) {
        auto it = remove_if(books.begin(), books.end(), [id](const Book &book) {
            return book.id == id;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book deleted successfully.\n";
        } else {
            cout << "Book not found.\n";
        }
    }

private:
    void displayBook(const Book &book) {
        cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author 
             << ", Status: " << (book.isIssued ? "Issued" : "Available") 
             << (book.isIssued ? ", Issued to: " + book.issuedTo : "") << endl;
    }
};

int main() {
    Library library;
    int choice, id;
    string title, author, studentName;

    while (true) {
        cout << "1. Add Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List of All Books\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter book ID: ";
                cin >> id;
                library.searchBookById(id);
                break;
            case 3:
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                library.searchBookByTitle(title);
                break;
            case 4:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, studentName);
                library.issueBook(id, studentName);
                break;
            case 5:
                cout << "Enter book ID: ";
                cin >> id;
                library.returnBook(id);
                break;
            case 6:
                library.listAllBooks();
                break;
            case 7:
                cout << "Enter book ID: ";
                cin >> id;
                library.deleteBook(id);
                break;
            case 8:
                cout << "Exit Successfull.";
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}