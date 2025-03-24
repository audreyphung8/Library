/*
Programming HW #2, Audrey Phung 
04/30/23
*/

#include "library.h"

//book 
Book::Book(): code(0), title(" "), available(0), rented(0){}
Book::Book(int tcode, string ttitle, int tavailable, int trented): code(tcode), title(ttitle), available(tavailable), rented(trented){}
void Book::setCode(int tcode){code = tcode;}
void Book::setTitle(string ttitle){title = ttitle;}
void Book::setAvailable(int tavailable){available = tavailable;}
void Book::setRented(int trented){rented = trented;}
int Book::getCode(){return code;}
string Book::getTitle(){return title;}
int Book::getAvailable(){return available;}
int Book::getRented(){return rented;}

//children book 
ChildrenBook::ChildrenBook(): age(0){}
ChildrenBook::ChildrenBook(int tcode, string ttitle, int tavailable, int trented, int tage): Book(tcode, ttitle, tavailable, trented), age(tage){}
void ChildrenBook::setAge(int tage){age = tage;}
int ChildrenBook::getAge(){return age;}

void ChildrenBook::setPublisher(string){}
void ChildrenBook::setPublish_date(int){}
string ChildrenBook::getPublisher(){return " ";}
int ChildrenBook::getPublish_date(){return 0;}

//ComputerBook 
ComputerBook::ComputerBook() : publisher(" "){}
ComputerBook::ComputerBook(int tcode, string ttitle, int tavailable, int trented, string tpublisher): Book(tcode, ttitle, tavailable, trented), publisher(tpublisher){}
void ComputerBook::setPublisher(string tpublisher){publisher = tpublisher;}
string ComputerBook::getPublisher(){return publisher;}

void ComputerBook::setAge(int){}
void ComputerBook::setPublish_date(int){}
int ComputerBook::getAge(){return 0;}
int ComputerBook::getPublish_date(){return 0;}

//Novel 
Novel::Novel() : publish_date(0){}
Novel::Novel(int tcode, string ttitle, int tavailable, int trented, int tpublisher_date) : Book(tcode, ttitle, tavailable, trented), publish_date(tpublisher_date){}
void Novel::setPublish_date(int tpublish_date) {publish_date = tpublish_date;}
int Novel::getPublish_date() {return publish_date;}

void Novel::setAge(int){}
void Novel::setPublisher(string){}
int Novel::getAge(){return 0;}
string Novel::getPublisher(){return " ";}

//person
Person::Person(): id(0), name(" "), count(0){}
Person::Person(int tid, string tname, int tcount): id(tid), name(tname), count(tcount){}
void Person:: setID(int tid){id = tid;}
void Person:: setName(string tname){name = tname;}
void Person:: setCount(int tcount){count = tcount;}
int Person::getID(){return id;}
string Person::getName(){return name;}
int Person::getCount(){return count;}


//student
Student::Student()
{
    code[0] = 0;
    code[1] = 0;
}
Student::Student(int tid, string tname, int tcount, int tcode[]): Person(tid, tname, tcount) 
{
    code[0] = tcode[0];
    code[1] = tcode[1];
}

int* Student::getCode()
{
    return code;
}

void Student::print()
{
    cout << code[0] << " " << code [1];
}

//teacher
Teacher::Teacher()
{
    code[0] = 0;
    code[1] = 0;
    code[2] = 0;
}
Teacher::Teacher(int tid, string tname, int tcount, int tcode[]): Person(tid, tname, tcount) 
{
    code[0] = tcode[0];
    code[1] = tcode[1];
    code[2] = tcode[2];
}
int* Teacher::getCode()
{
    return code;
}
void Teacher::print()
{
    cout << code[0] << " " << code[1] << " " << code[2];
}