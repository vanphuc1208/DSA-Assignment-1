#include "main.h"
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
void print() {
   table *tmp=head;
   while(tmp!=NULL) {
      cout<<tmp->ID <<" "<<tmp->name <<" "<<tmp->age<<endl;
      tmp=tmp->next;
   }
}
};
queue* q= new queue();
// check da full ban hay chua
bool checkFull(restaurant *r) {
table *tmp=r->recentTable;
if(tmp->age ==0) return false;
while(tmp!= r->recentTable) {
   if(tmp->age==0) return false;
   tmp=tmp->next;
  } 
return true;
}
bool checkreg(string s) {
   return (s[0]=='R' && s[1]=='E' && s[2]=='G' && s[3]!='M');
}
void reg(restaurant* r, int ID, string name, int age) {
    if(age<16) return;//khach duoi 16 tuoi se khong phuc vu
    if(checkFull(r)) {//neu da full ban
     q->add(ID,name,age);// them vao cuoi hang doi
    }
    else {
    if(ID!=0) {// neu khach co ID tuc muon chon ban
        table *tmp=r->recentTable;
        while(tmp->ID != ID) {
             tmp=tmp->next;
        }// chi toi ban co ID vi khach muon dat
        if(tmp->age==0)  { // neu ban trong
           tmp->name=name;
           tmp->age=age;
        }
        else { // neu ban khong trong
           while(tmp->age!=0) {//kiem tra ban trong ngay sau 
              tmp=tmp->next;
           }
           tmp->name=name;
           tmp->age=age;
        }
    }
    else {// neu khach khong co ID nha hang tu xep vao ban trong co ID nho nhat
          table *tmp=r->recentTable;
          while(tmp->ID!=1) {
            tmp=tmp->next;
          }// chi toi ban co ID bang 1 roi do ban trong tu day
          while(tmp->age!=0) {
            tmp=tmp->next;
          }
          tmp->name=name;
          tmp->age=age;
    }
    }
}
void test(restaurant *r) {
   table*tmp = r->recentTable;
   while(tmp->next != r->recentTable) {
      cout<<tmp->ID <<" "<<tmp->name <<" "<<tmp->age<<endl;
      tmp=tmp->next;
   }
   cout<<tmp->ID <<" "<<tmp->name <<" "<<tmp->age<<endl;// in ra thong tin ban truoc currentTable
}
void simulate(string filename, restaurant* r)
{
   ifstream filein; // ifstream ofstream 
   filein.open(filename);
   string s;
   while(getline(filein,s)) {
     if(checkreg(s)) {
      int ID,age;
      string name="";
      string Sage="";
      if (isdigit(s[4])) {
         int i=4;
         string tmp="";
         while(s[i]!=' ') {
              tmp+=s[i];
              i++;
         }
         while(i<s.length()) {
            if(isdigit(s[i])) Sage+=s[i];
         
            if(islower(s[i]) || isupper(s[i])) name+=s[i];
            i++;
         }
         ID=stoi(tmp);
         age=stoi(Sage);
      }
      else {
         int i=4;
         while(i<s.length()) {
            if(isdigit(s[i])) Sage+=s[i];
         
            if(islower(s[i]) || isupper(s[i])) name+=s[i];
            i++;
         }
         ID=0;
         age=stoi(Sage);
      }
      reg(r,ID,name,age);
     }
   }
    test(r);
    cout<<"Print queue:"<<endl;
    q->print();
}

