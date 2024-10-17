#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>

class Book {
public:
    Book(const std::string &title, const std::string &author)
        : title(title), author(author), is_available(true) {}

    std::string get_title() const { return title; }
    std::string get_author() const { return author; }
    bool isAvailable() const { return is_available; }
    void setAvailability(bool availability) { is_available = availability; }

private:
    std::string title;
    std::string author;
    bool is_available;
};

class User {
public:
    User(const std::string &name) : name(name) {}

    std::string get_name() const { return name; }
    void borrow_book(const Book &book) {
        borrowed_books.push_back(book);
    }
    
    void return_book(const std::string &book_title) {
        auto it = std::remove_if(borrowed_books.begin(), borrowed_books.end(),
                                 [&book_title](const Book &book) { return book.get_title() == book_title; });
        if (it != borrowed_books.end()) {
            borrowed_books.erase(it, borrowed_books.end());
        }
    }

    void list_borrowed_books() const {
        std::cout << name << "'s borrowed books:\n";
        for (const auto &book : borrowed_books) {
            std::cout << "- " << book.get_title() << " by " << book.get_author() << '\n';
        }
    }

private:
    std::string name;
    std::vector<Book> borrowed_books;
};

class Library {
public:
    void add_book(const Book &book) {
        books.push_back(book);
    }

    void register_user(const User &user) {
        users.push_back(user);
    }

    void borrow_book(const std::string &book_title, const std::string &user_name) {
        for (auto &book : books) {
            if (book.get_title() == book_title && book.isAvailable()) {
                book.setAvailability(false);
                for (auto &user : users) {
                    if (user.get_name() == user_name) {
                        user.borrow_book(book);
                        std::cout << user_name << " borrowed " << book_title << ".\n";
                        return;
                    }
                }
            }
        }
        std::cout << "Book not available or user not found.\n";
    }

    void return_book(const std::string &book_title, const std::string &user_name) {
        for (auto &book : books) {
            if (book.get_title() == book_title) {
                book.setAvailability(true);
                for (auto &user : users) {
                    if (user.get_name() == user_name) {
                        user.return_book(book_title);
                        std::cout << user_name << " returned " << book_title << ".\n";
                        return;
                    }
                }
            }
        }
        std::cout << "Book or user not found.\n";
    }

    void list_books() const {
        std::cout << "Available books in the library:\n";
        for (const auto &book : books) {
            if (book.isAvailable()) {
                std::cout << "- " << book.get_title() << " by " << book.get_author() << '\n';
            }
        }
    }

private:
    std::vector<Book> books;
    std::vector<User> users;
};

int main() {
    Library library;

    // Adding books to the library
    library.add_book(Book("1984", "George Orwell"));
    library.add_book(Book("To Kill a Mockingbird", "Harper Lee"));
    library.add_book(Book("The Great Gatsby", "F. Scott Fitzgerald"));

    // Registering users
    library.register_user(User("Alice"));
    library.register_user(User("Bob"));

    // Listing available books
    library.list_books();

    // Borrowing and returning books
    library.borrow_book("1984", "Alice");
    library.borrow_book("The Great Gatsby", "Bob");
    library.borrow_book("To Kill a Mockingbird", "Alice");

    // Listing borrowed books
    library.list_books();
    library.borrow_book("The Great Gatsby", "Alice"); // should show book not available

    // Returning books
    library.return_book("1984", "Alice");
    library.return_book("The Great Gatsby", "Bob");

    // Listing available books after return
    library.list_books();

    return 0;
}
