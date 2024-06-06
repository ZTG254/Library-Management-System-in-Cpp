#include <iostream>
#include <string>
using namespace std;

// Book class definition
class Book {
private:
    string title;
    string author;
    int publicationYear;
    bool isBorrowed;

public:
    Book() : title(""), author(""), publicationYear(0), isBorrowed(false) {}
    Book(string t, string a, int py) : title(t), author(a), publicationYear(py), isBorrowed(false) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getPublicationYear() const { return publicationYear; }
    bool getIsBorrowed() const { return isBorrowed; }

    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }
};

// Library class definition
class Library {
private:
    Book books[100];
    int bookCount;

public:
    Library() : bookCount(0) {}

    void addBook(const Book& book) {
        if (bookCount < 100) {
            books[bookCount++] = book;
        } else {
            cout << "Library is full, cannot add more books" << endl;
        }
    }

    void removeBook(const string& title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle() == title) {
                for (int j = i; j < bookCount - 1; ++j) {
                    books[j] = books[j + 1];
                }
                --bookCount;
                return;
            }
        }
    }

    Book* getAvailableBooks(int& availableCount) const {
        static Book availableBooks[100];
        availableCount = 0;
        for (int i = 0; i < bookCount; ++i) {
            if (!books[i].getIsBorrowed()) {
                availableBooks[availableCount++] = books[i];
            }
        }
        return availableBooks;
    }

    Book* searchBookByTitle(const string& title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle() == title) {
                return &books[i];
            }
        }
        return nullptr; // Return nullptr if not found
    }

    Book* searchBookByAuthor(const string& author, int& authorCount) const {
        static Book result[100];
        authorCount = 0;
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getAuthor() == author) {
                result[authorCount++] = books[i];
            }
        }
        return result;
    }

    Book* searchBookByPublicationYear(int year, int& yearCount) const {
        static Book result[100];
        yearCount = 0;
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getPublicationYear() == year) {
                result[yearCount++] = books[i];
            }
        }
        return result;
    }
};

// User class definition
class User {
private:
    string name;
    Book borrowedBooks[10];
    int borrowedCount;

public:
    User(string n) : name(n), borrowedCount(0) {}

    void borrowBook(Library& library, const string& title) {
        Book* book = library.searchBookByTitle(title);
        if (book != nullptr && !book->getIsBorrowed() && borrowedCount < 10) {
            book->borrowBook();
            borrowedBooks[borrowedCount++] = *book;
            cout << "Book borrowed successfully!" << endl;
        } else {
            cout << "Book not available for borrowing" << endl;
        }
    }

    void returnBook(Library& library, const string& title) {
        for (int i = 0; i < borrowedCount; ++i) {
            if (borrowedBooks[i].getTitle() == title) {
                Book* book = library.searchBookByTitle(title);
                if (book != nullptr) {
                    book->returnBook();
                    for (int j = i; j < borrowedCount - 1; ++j) {
                        borrowedBooks[j] = borrowedBooks[j + 1];
                    }
                    --borrowedCount;
                    cout << "Book returned successfully!" << endl;
                    return;
                }
            }
        }
        cout << "You have not borrowed this book" << endl;
    }
};

void displayMenu() {
    cout << "Library Menu:\n1. Add book\n2. View available books\n3. Search books by title\n4. Search books by author\n5. Search books by publication year\n6. Borrow book\n7. Return book\n8. Exit\nEnter your choice: ";
}

int main() {
    Library library;
    User user("Alice");

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        cin.ignore();  // To ignore the newline character left by cin

        if (choice == 8) break;

        switch (choice) {
            case 1: {
                string title, author;
                int year;
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter publication year: ";
                cin >> year;
                library.addBook(Book(title, author, year));
                cout << "Book added successfully!" << endl;
                break;
            }
            case 2: {
                int availableCount;
                Book* availableBooks = library.getAvailableBooks(availableCount);
                cout << "Available books:" << endl;
                for (int i = 0; i < availableCount; ++i) {
                    cout << availableBooks[i].getTitle() << " by " << availableBooks[i].getAuthor() << " (" << availableBooks[i].getPublicationYear() << ")" << endl;
                }
                break;
            }
            case 3: {
                string title;
                cout << "Enter title: ";
                getline(cin, title);
                Book* book = library.searchBookByTitle(title);
                if (book != nullptr) {
                    cout << "Found book: " << book->getTitle() << " by " << book->getAuthor() << " (" << book->getPublicationYear() << ")" << endl;
                } else {
                    cout << "Book not found" << endl;
                }
                break;
            }
            case 4: {
                string author;
                cout << "Enter author: ";
                getline(cin, author);
                int authorCount;
                Book* books = library.searchBookByAuthor(author, authorCount);
                if (authorCount > 0) {
                    cout << "Books by " << author << ":" << endl;
                    for (int i = 0; i < authorCount; ++i) {
                        cout << books[i].getTitle() << " (" << books[i].getPublicationYear() << ")" << endl;
                    }
                } else {
                    cout << "No books found by this author" << endl;
                }
                break;
            }
            case 5: {
                int year;
                cout << "Enter publication year: ";
                cin >> year;
                cin.ignore();  // To ignore the newline character left by cin
                int yearCount;
                Book* books = library.searchBookByPublicationYear(year, yearCount);
                if (yearCount > 0) {
                    cout << "Books published in " << year << ":" << endl;
                    for (int i = 0; i < yearCount; ++i) {
                        cout << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
                    }
                } else {
                    cout << "No books found from this year" << endl;
                }
                break;
            }
            case 6: {
                string title;
                cout << "Enter title of the book to borrow: ";
                getline(cin, title);
                user.borrowBook(library, title);
                break;
            }
            case 7: {
                string title;
                cout << "Enter title of the book to return: ";
                getline(cin, title);
                user.returnBook(library, title);
                break;
            }
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }

    return 0;
}
