#include "main.h"
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
void simulate(string filename, restaurant* r)
{
    return;
}

