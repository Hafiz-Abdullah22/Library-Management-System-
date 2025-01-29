#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <stdexcept> // For exception handling

using namespace std;

class Library {
    int BookId;
    char Title[20];
    char Author[20];
    char Category[20];
    int Pages;
    float Edition;

public:
    // Accessor Functions
    int getID() { return BookId; }
    char* getTitle() { return Title; }
    char* getAuthor() { return Author; }
    char* getCategory() { return Category; }
    float getEdition() { return Edition; }

    // Default Constructor
    Library() {
        BookId = 0;
        strcpy(Title, "");
        strcpy(Author, "");
        strcpy(Category, "");
        Pages = 0;
        Edition = 0;
    }

    void getBook();
    void listView();
    void showBook();
    void header();
} l;

void Library::getBook() {
    cout << "\tEnter Book Id: ";
    cin >> BookId;
    cout << "\tEnter Book Title: ";
    cin.ignore();
    cin.getline(Title, 20);
    cout << "\tEnter Book Author: ";
    cin.getline(Author, 20);
    cout << "\tEnter Book Category: ";
    cin.getline(Category, 20);
    cout << "\tEnter No of Pages: ";
    cin >> Pages;
    cout << "\tEnter date of Edition of Book: ";
    cin >> Edition;
    cout << endl;
}

void Library::showBook() {
    cout << endl;
    cout << "Book Id: " << BookId << endl;
    cout << "Book Title: " << Title << endl;
    cout << "Author Name: " << Author << endl;
    cout << "Category: " << Category << endl;
    cout << "No of Pages: " << Pages << endl;
    cout << "Edition: " << Edition << endl;
}

void Library::header() {
    cout.setf(ios::left);
    cout << setw(5) << "I.D."
         << setw(20) << "Book Title"
         << setw(20) << "Book Author"
         << setw(15) << "Category"
         << setw(6) << "Pages"
         << setw(6) << "Edition" << endl;

    for (int i = 1; i <= 72; i++)
        cout << "=";
    cout << endl;
}

void Library::listView() {
    cout.setf(ios::left);
    cout << setw(5) << BookId
         << setw(20) << Title
         << setw(20) << Author
         << setw(15) << Category
         << setw(6) << Pages
         << setw(6) << Edition << endl;
}

void drawLine(char);
void heading();
void searchMenu();
void addBook();
void displayBooks();
void searchByID();
void searchByTitle();
void searchByCategory();
void searchByEdition();
void searchByAuthor();
void dispose();
void modify();
void displayDisposed();
void deleteBook();
void deleteAllBooks();

void drawLine(char ch) {
    for (int i = 1; i < 88; i++)
        cout << ch;
    cout << endl;
}

void heading() {
    drawLine('+');
    cout << "\t\tLIBRARY MANAGEMENT SYSTEM\n";
    drawLine('+');
}

void addBook() {
    try {
        ofstream fout("books.dat", ios::app | ios::binary);
        fout.exceptions(ofstream::failbit | ofstream::badbit); // Set exceptions
        l.getBook();
        fout.write((char*)&l, sizeof(l));
        cout << "Book data saved in file...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void displayBooks() {
    try {
        ifstream fin("books.dat", ios::binary);
        fin.exceptions(ifstream::failbit | ifstream::badbit); // Set exceptions
        int rec = 0;
        while (fin.read((char*)&l, sizeof(l))) {
            if (rec < 1)
                l.header();
            l.listView();
            rec++;
        }
        cout << "\nTotal " << rec << " Records in file...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void searchByID() {
    int n, flag = 0;
    try {
        ifstream fin("books.dat", ios::binary);
        fin.exceptions(ifstream::failbit | ifstream::badbit); // Set exceptions
        cout << "Enter book ID: ";
        cin >> n;
        while (fin.read((char*)&l, sizeof(l))) {
            if (n == l.getID()) {
                l.showBook();
                flag++;
            }
        }
        if (flag == 0)
            cout << "Book Number with ID: " << n << " not available...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void searchByTitle() {
    int flag = 0;
    char title[20];
    try {
        ifstream fin("books.dat", ios::binary);
        fin.exceptions(ifstream::failbit | ifstream::badbit); // Set exceptions
        cout << "Enter Book Title: ";
        cin.ignore();
        cin.getline(title, 20);
        while (fin.read((char*)&l, sizeof(l))) {
            if (strcmp(title, l.getTitle()) == 0) {
                l.showBook();
                flag++;
            }
        }
        if (flag == 0)
            cout << "Book with Title: " << title << " not available...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void searchByCategory() {
    int flag = 0, rec = 0;
    char cat[20];
    try {
        ifstream fin("books.dat", ios::binary);
        fin.exceptions(ifstream::failbit | ifstream::badbit); // Set exceptions
        cout << "Enter Book Category: ";
        cin.ignore();
        cin.getline(cat, 20);
        while (fin.read((char*)&l, sizeof(l))) {
            if (strcmp(cat, l.getCategory()) == 0) {
                if (rec < 1)
                    l.header();
                l.listView();
                flag++;
                rec++;
            }
        }
        if (flag == 0)
            cout << "Book with Category: " << cat << " not available...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void searchByAuthor() {
    int flag = 0, rec = 0;
    char aut[20];
    try {
        ifstream fin("books.dat", ios::binary);
        fin.exceptions(ifstream::failbit | ifstream::badbit); // Set exceptions
        cout << "Enter Book Author: ";
        cin.ignore();
        cin.getline(aut, 20);
        while (fin.read((char*)&l, sizeof(l))) {
            if (strcmp(aut, l.getAuthor()) == 0) {
                if (rec < 1)
                    l.header();
                l.listView();
                flag++;
                rec++;
            }
        }
        if (flag == 0)
            cout << "Book with Author name: " << aut << " not available...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void dispose() {
    int n, flag = 0;
    try {
        ifstream fin("books.dat", ios::binary);
        fin.exceptions(ifstream::failbit | ifstream::badbit); // Set exceptions
        ofstream fout("dispose.dat", ios::binary);
        fout.exceptions(ofstream::failbit | ofstream::badbit); // Set exceptions
        cout << "Enter Book ID: ";
        cin >> n;
        while (fin.read((char*)&l, sizeof(l))) {
            if (n == l.getID()) {
                l.showBook();
                flag++;
            } else {
                fout.write((char*)&l, sizeof(l));
            }
        }
        fin.close();
        fout.close();
        if (flag == 0)
            cout << "Book Number with ID: " << n << " not available...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void modify() {
    int n, flag = 0, pos;
    try {
        fstream fin("books.dat", ios::in | ios::out | ios::binary);
        fin.exceptions(fstream::failbit | fstream::badbit); // Set exceptions
        cout << "Enter Book ID: ";
        cin >> n;
        while (fin.read((char*)&l, sizeof(l))) {
            if (n == l.getID()) {
                pos = fin.tellg();
                cout << "Following data will be edited...\n";
                l.showBook();
                flag++;
                fin.seekg(pos - sizeof(l));
                l.getBook();
                fin.write((char*)&l, sizeof(l));
                cout << "\nData Modified successfully...\n";
            }
        }
        fin.close();
        if (flag == 0)
            cout << "Book Number with ID: " << n << " not available...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void displayDisposed() {
    try {
        ifstream fin("dispose.dat", ios::binary);
        fin.exceptions(ifstream::failbit | ifstream::badbit); // Set exceptions
        int rec = 0;
        while (fin.read((char*)&l, sizeof(l))) {
            if (rec < 1)
                l.header();
            l.listView();
            rec++;
        }
        fin.close();
        cout << "\nTotal " << rec << " Records in disposed off file...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << " File operation failed: " << e.what() << endl;
    }
}

void deleteBook() {
    int n, flag = 0;
    try {
        ifstream fin("books.dat", ios::binary);
        fin.exceptions(ifstream::failbit | ifstream::badbit); // Set exceptions
        ofstream fout("temp.dat", ios::binary);
        fout.exceptions(ofstream::failbit | ofstream::badbit); // Set exceptions
        cout << "Enter Book ID to delete: ";
        cin >> n;
        while (fin.read((char*)&l, sizeof(l))) {
            if (n == l.getID()) {
                flag++;
                cout << "Book with ID: " << n << " deleted successfully.\n";
            } else {
                fout.write((char*)&l, sizeof(l));
            }
        }
        fin.close();
        fout.close();
        remove("books.dat");
        rename("temp.dat", "books.dat");
        if (flag == 0)
            cout << "Book Number with ID: " << n << " not available...\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

void deleteAllBooks() {
    try {
        remove("books.dat");
        cout << "All books deleted successfully.\n";
    } catch (const std::ios_base::failure& e) {
        cerr << "File operation failed: " << e.what() << endl;
    }
}

int main() {
    int choice;
    do {
        heading();
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search by ID\n";
        cout << "4. Search by Title\n";
        cout << "5. Search by Author\n";
        cout << "6. Search by Category\n";
        cout << "7. Modify Book\n";
        cout << "8. Delete Book\n";
        cout << "9. Delete All Books\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchByID(); break;
            case 4: searchByTitle(); break;
            case 5: searchByAuthor(); break;
            case 6: searchByCategory(); break;
            case 7: modify(); break;
            case 8: deleteBook(); break;
            case 9: deleteAllBooks(); break;
            case 0: cout << "Exiting the program...\n"; break;
            default: cout << "Invalid choice! Please try again.\n"; break;
        }
    } while (choice != 0);
    return 0;
}
