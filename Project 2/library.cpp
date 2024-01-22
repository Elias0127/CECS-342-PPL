#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Book{
    private:
        string title;
        string author;
        bool isAvailable;
    public:
        Book(string t, string a){
            title = t;
            author = a;
            isAvailable = true;
        }
        void lendBook(){
            isAvailable = false;
        }
        void returnBook()
        {
            isAvailable = true;
        }
        string getTitle(){
            return title;
        }
        string getAuthor()
        {
            return author;
        }
        bool getAvilability(){
            return isAvailable;
        }
};

class Library{
    private:
       vector<Book> books;
    public:
        void addBook(string title, string author)
        {
            books.push_back(Book(title, author));
        }

        void lendBook(string bookTitle)
        {
            bool bookFound = false; // Flag to check if we found the book
            for (Book &b : books)
            {
                if (bookTitle == b.getTitle())
                {
                    bookFound = true; // We found the book
                    if (b.getAvilability())
                    {
                        b.lendBook();
                        cout << bookTitle << " has been lent." << endl;
                        return; // Exit the method
                    }
                    else
                    {
                        cout << "I'm sorry, " << bookTitle << " is currently not available." << endl;
                        return; // Exit the method
                    }
                }
            }
            if (!bookFound)
            {
                cout << "I'm sorry, we don't have the book titled '" << bookTitle << "'." << endl;
            }
        }

        void returnBook(string bookTitle)
        {
            for (Book &b : books)
            {
                if (bookTitle == b.getTitle() && !b.getAvilability())
                {
                    b.returnBook();
                    cout << bookTitle << " has been returned." << endl;
                    return; // Exit the method once the book is returned
                }
            }
        }
};

int main()
{
        Library myLibrary;

        // Add some books to the library
        myLibrary.addBook("The Great Gatsby", "F. Scott Fitzgerald");
        myLibrary.addBook("1984", "George Orwell");
        myLibrary.addBook("The Catcher in the Rye", "J.D. Salinger");

        // Lend a book
        cout << "Lending 'The Great Gatsby'..." << endl;
        myLibrary.lendBook("The Great Gatsby");

        // Try lending the same book again
        cout << "Lending 'The Great Gatsby' again..." << endl;
        myLibrary.lendBook("The Great Gatsby");

        // Return the book
        cout << "Returning 'The Great Gatsby'..." << endl;
        myLibrary.returnBook("The Great Gatsby");

        // Try lending the book again after returning
        cout << "Lending 'The Great Gatsby' again..." << endl;
        myLibrary.lendBook("The Great Gatsby");

        // Try lending a book that isn't in the library
        cout << "Lending 'Moby Dick'..." << endl;
        myLibrary.lendBook("Moby Dick");

        return 0;
}
