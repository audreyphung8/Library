/*
Programming HW #2, Audrey Phung 
04/30/23
*/

#include <iostream>
using namespace std;

class Book 
{
private:
   int code;
   string title;
   int available;
   int rented;
public:
//declarations
   Book();
   Book(int, string, int, int);
//setters
   void setCode(int);
   void setTitle(string);
   void setAvailable(int);
   void setRented(int);
//getters
   int getCode();
   string getTitle();
   int getAvailable();
   int getRented();
//virtual
   virtual void setAge(int) = 0;
   virtual void setPublisher(string) = 0;
   virtual void setPublish_date(int) = 0;
   virtual int getAge() = 0;
   virtual string getPublisher() = 0;
   virtual int getPublish_date() = 0;
};

class ChildrenBook: public Book 
{
private:
   int age;
public:
   ChildrenBook();
   ChildrenBook(int, string, int, int, int);
   void setAge(int);
   int getAge();
//virtual
   void setPublisher(string);
   void setPublish_date(int);
   string getPublisher();
   int getPublish_date();
};

class ComputerBook: public Book 
{
private:
   string publisher;
public:
   ComputerBook();
   ComputerBook(int, string, int, int, string);
   void setPublisher(string);
   string getPublisher();
//virtual
   void setAge(int);
   void setPublish_date(int);
   int getAge();
   int getPublish_date();
};

class Novel : public Book
{
private:
   int publish_date;
public:
   Novel();
   Novel(int, string, int, int, int);
   void setPublish_date(int);
   int getPublish_date();
//virtual
   void setAge(int);
   void setPublisher(string);
   int getAge();
   string getPublisher();
};

class Person
{
private:
   int id;
   string name;
   int count;
public:
//declarations
   Person();
   Person(int, string, int);
//setters
   void setID(int);
   void setName(string);
   void setCount(int);
//getters
   int getID();
   string getName();
   int getCount();
//virtual
   virtual int* getCode() = 0;
};

class Student: public Person
{
private:
   int code[2];
public:
   Student();
   Student(int, string, int, int[]);
   //Pointer array, PCC tutor suggested this method where we can access and set by calling this
   int* getCode();
   void print();
};

class Teacher: public Person
{
private:
   int code[3];
public:
   Teacher();
   Teacher(int, string, int, int[]);
   int* getCode();
   void print();
};
