/*
Programming HW #2, Audrey Phung
04/30/23
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "library.cpp"
using namespace std;

//Struct to create node
struct Node
{
   int code;
   string title;
   int available;
   int rented;
   int age;
   string publisher;
   int publish_date;
   Node* link;
};

//Function Declarations
typedef Node* NodePtr; //Declares node for linked lists
Book** readFromFile1(string file, int &count);
Person** readFromFile2(string file, int &count);
void searchABook(Book *library[], int count);
void rentABook(Book *library[], Person *profile[], int bCount, int pCount);
void returnABook(Book *library[], Person *profile[], int bCount, int pCount);
void showMyInfo(Book *library[], Person *profile[], int bCount, int pCount);
void showAllBooks(Book *library[], int bCount);
void printList(NodePtr head);
void menu();

int main()
{
   //Variable declarations
   int bookCount = 0, peopleCount = 0, response; 
   string filename1 = "Book.txt";
   string filename2 = "person.txt";
   //Reads in files
   Book** libraryBooks = readFromFile1(filename1, bookCount);
   Person** people = readFromFile2(filename2, peopleCount);

   do
   {
      menu();
      cin >> response;

      //Calls a function corresponded to the user's choice
      if (response == 1)
      {
         searchABook(libraryBooks, bookCount);
      }
      else if (response == 2)
      {
         rentABook(libraryBooks, people, bookCount, peopleCount);
      }
      else if (response == 3)
      {
         returnABook(libraryBooks, people, bookCount, peopleCount);
         cout << endl;
      }
      else if (response == 4)
      {
         showMyInfo(libraryBooks, people, bookCount, peopleCount);
      }
      else if (response == 5)
      {
         showAllBooks(libraryBooks, bookCount);
      }
      //If user enters 6 then program will end
   } while (response != 6);
}

void menu()
{
   //Prints the menu options
   cout << "------------------------" << endl;
   cout << setw(13) << "Menu" << endl;
   cout << "------------------------" << endl;
   cout << "1. Search a book" << endl;
   cout << "2. Rent a book" << endl;
   cout << "3. Return a book" << endl;
   cout << "4. Show my information" << endl;
   cout << "5. Show all books" << endl;
   cout << "6. Exit" << endl;
   cout << endl;
   cout << "Select (1~6) : ";
}

void showAllBooks(Book *library[], int bCount)
{
   //Declared NodePtrs
   NodePtr head = NULL;
   NodePtr ptr = NULL;
   NodePtr prev = NULL;

   //Assign everything in array to a node
   for (int i = 0; i < bCount; i++)
   {
      ptr = new Node;
      ptr -> code = library[i]->getCode();
      ptr -> title = library[i]->getTitle();
      ptr -> available = library[i]->getAvailable();
      ptr -> rented = library[i]->getRented();
      ptr -> age = library[i]->getAge();
      ptr -> publisher = library[i]->getPublisher();
      ptr -> publish_date = library[i]->getPublish_date();
      ptr -> link = NULL;

      //If head is empty, then assign it to ptr
      if (head == NULL)
      {
         head = ptr;
      }
      else
      {
         //If code in head is greater than code in ptr, than head is moved to the link
         if (head -> code > ptr -> code)
         {
            ptr -> link = head;
            head = ptr;
         }
         else
         {
            //Otherwise it moves onto the next node by using previous to keep track of the current one
            prev = head;
            while (prev -> link != NULL && prev -> link -> code < ptr -> code)
            {
               prev = prev -> link;
            }
            
            //Moves to the next node
            ptr -> link = prev -> link;
            prev -> link = ptr;
         }
      }
   }

   //Calls function to print all the books
   printList(head);
}


void printList(NodePtr head)
{
   cout << "===============================================================" << endl;
   cout << setw(35) << "Children Books" << endl;
   cout << "===============================================================" << endl;
   cout << " code" << setw(20) << "title" << setw(35) << "age  available  rented" << endl;
   cout << "---------------------------------------------------------------" << endl;
   
   //Begins with ptr, if it is not null then for loop will continue to execute, lastly ptr moves through the link which has another node
   for (NodePtr ptr = head; ptr != NULL; ptr = ptr->link)
   {
      //Prints children books first by using ptr
      if (ptr->code >= 1001 && ptr->code <= 2000)
      {
         cout << " " << ptr->code << setw(30) << ptr->title << setw(6) << ptr->age << setw(9) << ptr->available << setw(8) << ptr->rented << endl;
      }
   }

   cout << endl;
   cout << "============================================================================" << endl;
   cout << setw(35) << "Computer Books" << endl;
   cout << "============================================================================" << endl;
   cout << " code" << setw(25) << "title" << setw(45) << "publisher     available  rented" << endl;
   cout << "----------------------------------------------------------------------------" << endl;
   //Begins with ptr, if it is not null then for loop will continue to execute, lastly ptr moves through the link which has another node
   for (NodePtr ptr = head; ptr != NULL; ptr = ptr->link)
   {
      //Prints computer books first by using ptr
      if (ptr->code >= 2001 && ptr->code <= 3000)
      {
         cout << " " << ptr->code << setw(30) << ptr->title << setw(21) << ptr->publisher << setw(8) << ptr->available << setw(8) << ptr->rented << endl;
      }
   }

   cout << endl;
   cout << "============================================================================" << endl;
   cout << setw(35) << "Novel Books" << endl;
   cout << "============================================================================" << endl;
   cout << " code" << setw(25) << "title" << setw(45) << "published date  available  rented" << endl;
   cout << "----------------------------------------------------------------------------" << endl;
   //Begins with ptr, if it is not null then for loop will continue to execute, lastly ptr moves through the link which has another node
   for (NodePtr ptr = head; ptr != NULL; ptr = ptr->link)
   {
      //Prints novel books first by using ptr
      if (ptr->code >= 3000)
      {
         cout << " " << ptr->code << setw(30) << ptr->title << setw(15) << ptr->publish_date << setw(14) << ptr->available << setw(8) << ptr->rented << endl;
      }
   }
}

void showMyInfo(Book *library[], Person *profile[], int bCount, int pCount)
{
   //Variable declarations
   int id, amountOfBooks;
   string name;

   //User input
   cout << "Enter your id   : ";
   cin >> id;
   cout << "Enter your name : ";
   cin >> name;

   for (int i = 0; i < pCount; i++)
   {
      //This searches the ID in the file to access other information 
      if (id == profile[i]->getID())
      {
         cout << "You rented " << profile[i]->getCount() << " book(s)." << endl;
         //Stores the id's amount of books they rented out for easier access 
         amountOfBooks = profile[i]->getCount();

         //Searches the book codes in the person's array with the library to find and print the corresponding information
         for (int k = 0; k < amountOfBooks; k++)
         {
            for (int j = 0; j < bCount; j++)
            {
               //If the person's book code matches with the library then it will search which category it's in (children/computer/novel)
               if (profile[i]->getCode()[k] == library[j]->getCode())
               {
                  //Prints children
                  if (library[j]->getCode() >= 1001 && library[j]->getCode() <= 2000)
                  {
                     cout << "* " << library[j]->getTitle() << " (" << library[j]->getCode() << ") - age " << library[j]->getAge() << endl;
                  }
                  //Prints computer
                  else if (library[j]->getCode() >= 2001 && library[j]->getCode() <= 3000)
                  {
                     cout << "* " << library[j]->getTitle() << " (" << library[j]->getCode() << ") - publisher " << library[j]->getPublisher() << endl;
                  }
                  //Prints novels
                  else
                  {
                     cout << "* " << library[j]->getTitle() << " (" << library[j]->getCode() << ") - published date " << library[j]->getPublish_date() << endl;
                  }
               }
            }
            
         }
      }
     
   }
}

void returnABook(Book *library[], Person *profile[], int bCount, int pCount)
{
   //Variable Declarations
   int id, bookCode, indexOfBook, amountOfBooks, temp = 0;
   char response;

   //User-input
   cout << "Enter your id" << setw(6) << ": ";
   cin >> id;
   cout << "Enter the book code to return : ";
   cin >> bookCode;

   cout << endl;
   //This searches through library to find the index of the book
   for (int i = 0; i < bCount; i++)
   {
      if (library[i]->getCode() == bookCode)
      {
         indexOfBook = i;
      }
   }
   
   try
   {
      for (int i = 0; i < pCount; i++)
      {
         //This searches the ID in the file to access other information 
         if (profile[i]->getID() == id)
         {
            //Stores the id's amount of books they rented out for easier access 
            amountOfBooks = profile[i]->getCount();

            //If the user didn't rent any books, then they can't return anything so it throws an error.
            if (amountOfBooks == 0)
            {
               throw (profile[i]->getCount());
            }

            for (int k = 0; k < profile[i]->getCount(); k++)
            {
               //If the code matches the file, it shows that they did rent it out & can return it
               if (profile[i]->getCode()[k] == bookCode)
               {
                  cout << endl << "Do you want to return '" << library[indexOfBook]->getTitle() << "' (y/n)? ";
                  cin >> response;
                  if (response == 'n')
                  {
                     break;
                  }
                  else
                  {
                     profile[i]->setCount(amountOfBooks - 1); //Decreases the amount of books they rented
                     library[indexOfBook]->setAvailable(library[indexOfBook]->getAvailable() + 1); //Increases availability
                     library[indexOfBook]->setRented(library[indexOfBook]->getRented() - 1); //Decreases the amount that is rented

                     //Stores 3 book codes that the user can possibly have to 3 temp variables to move the code
                     //If the user has 3 or less, it will have default value of 0
                     int temp1 = profile[i]->getCode()[0];
                     int temp2 = profile[i]->getCode()[1];
                     int temp3 = profile[i]->getCode()[2];

                     //This moves the book codes down the array
                     if (temp1 == bookCode)
                     {
                        profile[i]->getCode()[0] = temp2;
                        profile[i]->getCode()[1] = temp3;
                        profile[i]->getCode()[2] = 0;
                     }
                     //Second code will be replaced with the third 
                     else if (temp2 == bookCode)
                     {
                        profile[i]->getCode()[1] = temp3;
                        profile[i]->getCode()[2] = 0;
                     }
                     //If third book is removed it will be replaced with 0
                     else if (temp3 == bookCode)
                     {
                        profile[i]->getCode()[2] = 0;
                     }
                     
                     cout << "***** Return succeed. Check your info!" << endl;
                     break;
                  }
               }
               else
               {
               //If both book codes don't match, then temp variable will increment
                  temp++;
               }
               //If temp is equal to the person's total books rented out, then it shows that they did not rent it & it throws an error
               if (temp == profile[i]->getCount())
               {
                  throw (profile[i]->getCount());
               }
            }
         }
      }
   }
   catch (int falseCode)
   {
      cout << "The 'id' did not rent the book.";
   }
   
}

void rentABook(Book *library[], Person *profile[], int bCount, int pCount)
{
   //Variable Declarations
   int id, amountOfBooks, indexOfBook;
   string title;
   char response;

   //User-input
   cout << "Enter your id" << setw(5) << ": ";
   cin >> id;
   cout << "Enter book title" << ": ";
   cin >> title;

   cout << endl;
   //This searches through library to find the index of the book and saves it to a variable
   for (int i = 0; i < bCount; i++)
   {
      if (library[i]->getTitle() == title)
      {
         indexOfBook = i;
      }
   }

   //For-loop searches the ID in the file to access other information 
   for (int i = 0; i < pCount; i++)
   {
      if (profile[i]->getID() == id)
      {
         //Stores the id's amount of books they rented out for easier access to the index
         amountOfBooks = profile[i]->getCount();
         cout << "You are " << profile[i]->getName() << ". You rented " << amountOfBooks << " book." << endl;

         try
         {
            //Ensures the user is a teacher
            if (id >= 1 && id <= 100)
            {
               if (profile[i]->getCount() < 3)
               {
                  //If there are no books are available, it will throw an "unavailable" error
                  if (library[indexOfBook]->getAvailable() == 0)
                  {
                     throw (library[indexOfBook]->getTitle());
                  }
                  //Otherwise, it would be available to the user to rent
                  else
                  {
                     cout << "Do you want to rent '" << title << "' (y/n)? ";
                     cin >> response;
                     if (response == 'n')
                     {
                        //If user doesn't want to rent it, then function will break.
                        break;
                     }
                     else
                     {
                        profile[i]->setCount(amountOfBooks + 1); //Increases the amount of books they rented
                        library[indexOfBook]->setAvailable(library[indexOfBook]->getAvailable() - 1); //Decreases availability
                        library[indexOfBook]->setRented(library[indexOfBook]->getRented() + 1); //Increases the amount that is rented
                        //The user's quantity of rented items is used as index to insert new book code
                        profile[i]->getCode()[amountOfBooks] = library[indexOfBook]->getCode(); 
                        cout << "***** Rent succeed. Check your info!" << endl;
                     }
                  }
               }
               //If the user exceeds 3 books, it throws an error.
               else
               {
                  throw (profile[i]->getCount());
               }
            }
            //Ensures user is a student
            else
            {
               if (profile[i]->getCount() < 2)
               {
                  //If there are no books are available, it will throw an "unavailable" error
                  if (library[indexOfBook]->getAvailable() == 0)
                  {
                     throw (library[indexOfBook]->getTitle());
                  }
                  //Otherwise, it would be available to the user to rent
                  else
                  {
                     cout << "Do you want to rent '" << title << "' (y/n)? ";
                     cin >> response;
                     if (response == 'n')
                     {
                        break;
                     }
                     else
                     {
                        profile[i]->setCount(amountOfBooks + 1); //Increases the amount of books they rented
                        library[indexOfBook]->setAvailable(library[indexOfBook]->getAvailable() - 1); //Decreases Availability
                        library[indexOfBook]->setRented(library[indexOfBook]->getRented() + 1); //Increases the amount that is rented
                        //The user's quantity of rented items is used as index to insert new book code
                        profile[i]->getCode()[amountOfBooks] = library[indexOfBook]->getCode();
                        cout << "***** Rent succeed. Check your info!" << endl;
                     }
                  }
               }
               //If the user exceeds 2 books, it throws an error.
               else
               {
                  throw (profile[i]->getCount());
               }
            }
         }
         //Exception handlings
         catch (int rent)
         {
            cout << "You already rented 2 (or 3) books." << endl;
         }
         catch (string unavailable)
         {
            cout << "The book is not available (all rented out)." << endl;
         }
      }
   }
}

void searchABook(Book *library[], int count)
{
   //Variable declarations
   int code, temp = 0;
   string title;

   //User-input
   cout << endl << "Enter code: ";
   cin >> code;
   cout << "Enter title: ";
   cin >> title;

   try
   {
      //For-loop will search the code & title in the library array
      for (int i = 0; i < count; i++)
      {
         //If user inputs code and title that are present in the file, then it will output that it exists
         if (library[i]->getCode() == code && library[i]->getTitle() == title)
         {
            cout << endl << title << "(" << code << ") exists." << endl;
            //Then, it searches the file to find which category the code is in and print information from that category
            if (code >= 1001 && code <= 2000)
            {
               cout << "category : children\nage : " << library[i]->getAge() << endl;
               cout << library[i]->getAvailable() << " available, " << library[i]->getRented() << " rented" << endl;
            }
            else if (code >= 2001 && code <= 3000)
            {
               cout << "category : computer\npublisher : " << library[i]->getPublisher() << endl;
               cout << library[i]->getAvailable() << " available, " << library[i]->getRented() << " rented" << endl;
            }
            else
            {
               cout << "category : novel\npublished date : " << library[i]->getPublish_date() << endl;
               cout << library[i]->getAvailable() << " available, " << library[i]->getRented() << " rented" << endl;
            }
            //Once information is found, then it can stop executing
            break;
         }
         //However, if code and title are not found in the file, then temp variable will increment
         else
         {
            temp++;
         }
      }
      //If temp is equal to the amount of books, then it shows that the book does not exist & it throws an error
      if (temp == count)
      {
         throw(code);
      }
   }
   //exception handling
   catch (int falseCode)
   {
      cout << "No match (code and title do not match)" << endl;
   }
}

Person** readFromFile2(string file, int &count)
{
   ifstream infile;
   infile.open(file);
   if (infile.fail()) 
   {
      cout << "Input file opening failed." << endl;
      exit(1);
   }
   
   //Variables representing every characteristic in person class
   int id, number_of_rented, bookID;
   string name;

   while (getline(infile, name))
   {
      if (!name.empty())
      {
         count++;
      }
   }
   infile.close();
   infile.open(file);

   //Creates a dynamic array of Person class
   Person** makeArray = new Person*[count];
   for (int i = 0; i < count; i++)
   {  
      infile >> id >> name >> number_of_rented;
      //Since the first three information is the same, we characterizied it by id
      if (id >= 1 && id <= 100)
      {
         //Creates a "Teacher" space
         Teacher* t = new Teacher;
         for (int i = 0; i < number_of_rented; i++)
         {
            //Depending on the number of rented books (2-3), it assigns the book code to the getCode() array
            infile >> bookID;
            t->getCode()[i] = bookID;
         }
         
         //Sets information from the file to the class
         t->setID(id);
         t->setName(name);
         t->setCount(number_of_rented);

         //Teacher object is stored into Person array
         makeArray[i] = t;
      } 
      else
      {
         //Creates a "Student" space
         Student* s = new Student;
         for (int i = 0; i < number_of_rented; i++)
         {
            //Depending on the number of rented books (2-3), it assigns the book code to the getCode() array
            infile >> bookID;
            s->getCode()[i] = bookID;
         }
         s->setID(id);
         s->setName(name);
         s->setCount(number_of_rented);

         //Student object is stored into Person array
         makeArray[i] = s;
      }
   }
   infile.close();
   return makeArray;
}

Book** readFromFile1(string file, int &count)
{
   ifstream infile;
   infile.open(file);
   if (infile.fail()) 
   {
      cout << "Input file opening failed." << endl;
      exit(1);
   }
   
   //Variables representing every characteristic in book class
   int code, age, available, rent, published_date;
   string title, publisher;

   //Counts how many books are in the file
   while (getline(infile, title))
   {
      if (!title.empty())
      {
         count++;
      }
   }

   infile.close();
   infile.open(file);
   //Create dynamic array for book
   Book** makeArray = new Book*[count];
   for (int i = 0; i < count; i++)
   {
      //first reads in the code to know which category it belongs 
      infile >> code;
      if (code >= 1001 && code <= 2000)
      {
         infile >> title >> age >> available >> rent;
         //Creates a children space for book array
         makeArray[i] = new ChildrenBook;
         makeArray[i] -> setCode(code);
         makeArray[i] -> setTitle(title);
         makeArray[i] -> setAge(age);
         makeArray[i] -> setAvailable(available);
         makeArray[i] -> setRented(rent);
      }
      else if (code >= 2001 && code <= 3000)
      {
         infile >> title >> publisher >> available >> rent;
         //Creates a computer space for book array
         makeArray[i] = new ComputerBook;
         makeArray[i] -> setCode(code);
         makeArray[i] -> setTitle(title);
         makeArray[i] -> setPublisher(publisher);
         makeArray[i] -> setAvailable(available);
         makeArray[i] -> setRented(rent);
      }
      else
      {
         infile >> title >> published_date >> available >> rent;
         //Creates a novel space for book array
         makeArray[i] = new Novel;
         makeArray[i] -> setCode(code);
         makeArray[i] -> setTitle(title);
         makeArray[i] -> setPublish_date(published_date);
         makeArray[i] -> setAvailable(available);
         makeArray[i] -> setRented(rent);
      }
   }
   return makeArray;
}