#ifndef MAIN_H
#define MAIN_H
#include<iostream>
#include<cmath>
#include<fstream>
#include<string>

using namespace std;
#define MAXSIZE 15

class table
{
public:
    int ID;
    string name;
    int age;
    table* next;
    table(int ID, string name, int age, table* next)
    {
        this->ID = ID;
        this->name = name;
        this->age = age;
        this->next = next;
    }
};

class restaurant
{
public:
    table *recentTable;
    restaurant()
    {
        recentTable = nullptr;
    }
    ~restaurant()
    {
        delete recentTable;
    }
    table* finsert(table *last, int ID, string name, int age)
    {
        if (last != nullptr)
            return last;
        table *temp = new table(ID, "", age, last);

        last = temp;
        last->next = last;
        return last;
    }
    table *insert(table *last, int ID, string name, int age)
    {
        if (last == NULL)
            return finsert(last, ID, name, age);
        table *temp = new table (ID, name, age, last->next);
        last -> next = temp;
        last = temp;
        return last;
    }
};
class queue {
public:
table *head;
int size;
queue() {
    head=NULL;
    size=0;
}
~queue();
void add(int ID,string name,int age) {
    if(size== MAXSIZE) return;
    table *newTable= new table (ID, name,age,NULL);
    if(head==NULL) {
        head=newTable;
        size++;
        return;
    }
    table *tmp=head;
    while(tmp->next!=NULL) {
        tmp=tmp->next;
    }
    tmp->next=newTable;
    size++;
}
void remove() {
    if(head==NULL) return;
    table *delTable=head;
    head=head->next;
    delete delTable;
}

};
#endif
