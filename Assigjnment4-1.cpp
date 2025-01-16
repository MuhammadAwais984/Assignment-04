#include <iostream>
#include <fstream>
using namespace std;

struct book{
    int bookID;
    string title;
    string author;
    int quantity;
};

const int MAX_BOOKS=50;

void SaveInventoryFile(book newBook)
{
    ofstream outFile("library_inventory.txt", ios::app);
    if(outFile.is_open())
    {
        outFile << newBook.bookID << "\n";
        outFile << newBook.title << "\n";
        outFile << newBook.author << "\n";
        outFile << newBook.quantity << "\n";

        outFile.close();
        cout << "\nInventory Saved Successfully!" << endl;
    }
    else
    {
        cout << "\nError Opening File!" << endl;
    }
}

void addBook(book inventory[], int &count, int maxBooks)
{
    if(count>=maxBooks)
    {
        cout<<"\n Inventory is full.";
        return;
    }
    
    book newBook;
    cout<<"\nEnter the Book ID: ";
    cin>>newBook.bookID;

    for (int i = 0; i < count; i++)
    {
        if (inventory[i].bookID == newBook.bookID)
        {
            cout << "Book ID already exists. Try Different." << endl;
            return;
        }
    }

    cin.ignore();
    cout<<"Enter the Book Title: ";
    getline(cin, newBook.title);
    cout<<"Enter the Name of Author: ";
    getline(cin, newBook.author);
    cout<<"Enter Quantity of Book: ";
    cin>>newBook.quantity;

    while(newBook.quantity<0)
    {
        cout<<"Invalid Quantity."<<endl;
        cin>>newBook.quantity;
    }

    inventory[count]=newBook;
    SaveInventoryFile(newBook);
    count++;
    cout<<"\t Book added successfully!"<<endl;
}

void searchBook(book inventory[], int count)
{
    int choice;
    cout<<"Search Book by:\n1.Book ID\t2.Book Title"<<endl;
    cin>>choice;

    if(choice==1)
    {
        int ID;
        cout<<"Enter the Book ID: ";
        cin>>ID;
        for(int i=0; i<count; i++)
        {
            if(inventory[i].bookID==ID)
            {
                cout<<"\nBook Found!"<<endl;
                cout<<"ID: "<<inventory[i].bookID<<"\nTitle: "<<inventory[i].title<<"\nAuthor: "<<inventory[i].author<<"\nAvailable Copies: "<<inventory[i].quantity<<endl;
                return;
            }
        }
        cout<<"\nBook not Found!"<<endl;
        return;
    }
    else if(choice==2)
    {
        string title;
        cin.ignore();
        cout<<"Enter the Book Title: ";
        getline(cin, title);
        for(int i=0; i<count; i++)
        {
            if(inventory[i].title==title)
            {
                cout<<"\nBook Found!"<<endl;
                cout<<"ID: "<<inventory[i].bookID<<"\nTitle: "<<inventory[i].title<<"\nAuthor: "<<inventory[i].author<<"\nAvailable Copies: "<<inventory[i].quantity<<endl;
                return;
            }
        }
        cout<<"\nBook not Found!"<<endl;
        return;
    }
    else
    {
        cout<<"\nInvalid Choice."<<endl;
    }
}

void displayBooks(book inventory[], int count)
{
    if(count==0)
    {
        cout<<"\nNo Books available."<<endl;
        return;
    }
    cout<<"\nAvailable Books:"<<endl;
    for(int i=0; i<count; i++)
    {
        cout<<i+1<<". ID: "<<inventory[i].bookID<<", Title: "<<inventory[i].title<<", Author: "<<inventory[i].author<<", Available Copies: "<<inventory[i].quantity<<"\n"<<endl;
    }
}

void LoadInventoryFile(book inventory[], int &count)
{
    ifstream inFile("library_inventory.txt");
    if(inFile.is_open())
    {
        count = 0;
        while(count < MAX_BOOKS && inFile >> inventory[count].bookID)
        {
            inFile.ignore(); 
            getline(inFile, inventory[count].title);
            getline(inFile, inventory[count].author);
            inFile >> inventory[count].quantity;
            inFile.ignore(); 
            count++;
        }
        inFile.close();
        cout << "\nFile Loaded Successfully!" << endl;
    }
    else
    {
        cout << "\nError Opening File!" << endl;
    }
}

int main() {

    book inventory[MAX_BOOKS];
    int bookCount=0;
    LoadInventoryFile(inventory, bookCount);

    int choice;
    do
    {
        cout<<"\n\tLibrary Management System"<<endl;
        cout<<"1. Add New Book"<<endl;
        cout<<"2. Search for a Book"<<endl;
        cout<<"3. Display all Books"<<endl;
        cout<<"4. Exit "<<endl;
        cout<<"Please choose an option from 1-4"<<endl;
        cin>>choice;

        switch (choice)
        {
            case 1:
            addBook(inventory, bookCount, MAX_BOOKS);
            break;

            case 2:
            searchBook(inventory, bookCount);
            break;

            case 3:
            displayBooks(inventory, bookCount);
            break;
            
            case 4:
            cout<<"Thank You for your service";
            break;

            default:
            cout<<"Error. Please try again."<<endl;
        }
    }
    while (choice!=6);

    return 0;
}