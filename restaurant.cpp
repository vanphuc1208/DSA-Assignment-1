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
    size--;
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
bool ismerge=0;// khoi tao la chua gop ban
table *Mtable;// luu ban bat dau merge
table *nextMtable; // luu ban tiep theo cua merge de dung lai trong ham cle

// check da full ban hay chua
bool checkFull(restaurant *r) {
table *tmp=r->recentTable;
if (tmp->age==0) return false;
tmp=tmp->next;
while(tmp!=r->recentTable) {
   if(tmp->age==0) return false;
   tmp=tmp->next;
  } 
return true;
}
bool findID(restaurant *r,int ID) {
   table *tmp=r->recentTable;
   if(tmp->ID==ID) return true;
tmp=tmp->next;
while(tmp!=r->recentTable) {
   if(tmp->ID==ID) return true;
   tmp=tmp->next;
  } 
return false;
}// ham tim kiem theo ID
bool checkreg(string s) {
   return (s[0]=='R' && s[1]=='E' && s[2]=='G' && s[3]!='M');
}// ham check lenh reg
void reg(restaurant* r, int ID, string name, int age) {
    if(age<16) return;//khach duoi 16 tuoi se khong phuc vu
    if(checkFull(r)) {//neu da full ban
     q->add(ID,name,age);// them vao cuoi hang doi
     return;
    }
    if(ID==0) {
      table *tmp=r->recentTable;
      table *minID=tmp;// luu vi tri ban trong vs ID nho nhat
      while(minID->age!=0) {
         minID=minID->next;
      } // tim toi vi tri trong gan nhat phong TH chi con ban trong sau recenttable
      while(tmp->next != r->recentTable) {
         if(tmp->age==0 && tmp->ID< minID->ID) {
            minID=tmp;
         }
         tmp=tmp->next;
      }
      if(tmp->age==0 && tmp->ID< minID->ID) {
            minID=tmp;
         }// duyet them phan tu cuoi
      minID->name=name;
      minID->age=age;
    }
    else {
      table*tmp=r->recentTable;
      if(!findID(r,ID)) {
       tmp=Mtable->next;
      }// neu ban do o trong nhom ban gop thi phai chi toi ban ngay sau nhom ban gop
      else {
           while(tmp->ID != ID) {
             tmp=tmp->next;
        }// chi toi ban co ID vi khach muon dat
      }
      while(tmp->age!=0) {//kiem tra ban trong ngay sau 
             tmp=tmp->next;
      }
      tmp->age=age;
      tmp->name=name;
    }
   //  if(ismerge) {
   //    if(ID==0) {
   //       table *tmp=Mtable->next;
   //       while(tmp->ID>)
   //    }
   //  }
   //  else {
   //  if(ID!=0) {// neu khach co ID tuc muon chon ban
   //      table *tmp=r->recentTable;
   //      while(tmp->ID != ID) {
   //           tmp=tmp->next;
   //      }// chi toi ban co ID vi khach muon dat
   //      if(tmp->age==0)  { // neu ban trong
   //         tmp->name=name;
   //         tmp->age=age;
   //      }
   //      else { // neu ban khong trong
   //         while(tmp->age!=0) {//kiem tra ban trong ngay sau 
   //            tmp=tmp->next;
   //         }
   //         tmp->name=name;
   //         tmp->age=age;
   //      }
   //  }
   //  else {// neu khach khong co ID nha hang tu xep vao ban trong co ID nho nhat
   //        table *tmp=r->recentTable;
   //        while(tmp->ID!=1) {
   //          tmp=tmp->next;
   //        }// chi toi ban co ID nho nhat co the khong phai 1 vi da tron
   //        while(tmp->age!=0) {
   //          tmp=tmp->next;
   //        }
   //        tmp->name=name;
   //        tmp->age=age;
   //  }
   //  }
}

bool checkregm(string s) {
   return (s[0]=='R' && s[1]=='E' && s[2]=='G' && s[3]=='M');
}// ham check lenh regm

int maxAdjacentTable(restaurant *r) {// ham tim so ban max canh nhau
int res=0;
int count=1;
table *tmp=r->recentTable;
for(int i=0;i< MAXSIZE-1;i++) {
   if(tmp->age==0 && tmp->next->age==0)  count++;
   if((tmp->age==0&& tmp->age!= tmp->next->age) || i==MAXSIZE-2 ) {
      if(count>res) res=count;
      count=1;
   }  
   tmp=tmp->next;
}
return res;
}

// ham tim ban co ID lon nhat de merge
table *mergetable(restaurant *r, int num) {
   table*tmp=r->recentTable;// duyet het cac ban
      while(tmp->ID!=1) { // cai nay khong anh huong boi ham tron vi khi ismerge=0 ms thuc hien
            tmp=tmp->next;
         }// chi toi ban co ID bang 1 roi do ban trong tu day
      table *ptr=tmp;// danh dau vi tri co the la mergetable
      table *mergetable=tmp;
      int count=0;
      int maxID=0;
      while(1) {// ham se khong chay qua 2*N
         if(tmp->age==0) {
            if(count ==0) ptr=tmp;
             count++;
         }
         if(ptr->ID <= maxID) break;
         if (count==num) {
             mergetable=ptr;
             maxID=mergetable->ID;
             tmp=ptr;
             count=0;
         }
         if(tmp->age!=0) {
            count=0;
         }
         tmp=tmp->next;
      }
      return mergetable;
}
void regm(restaurant *r,string name, int age, int num) {// bien ismerge de check da gop ban nao hay chua khi chua co se thuc hien lenh gop ban va cho ismerge=1
      if(ismerge|| checkFull(r) || maxAdjacentTable(r)<num||age<16) return;  
      Mtable=mergetable(r,num);
      Mtable->name=name;
      Mtable->age=age;
      nextMtable=Mtable->next;
      table* tmp=Mtable;
      for(int i=0;i<num;i++) {
         tmp=tmp->next;
      }
      Mtable->next=tmp;
      ismerge=1;
      r->recentTable=Mtable;// de khong bi truong hop recent table nam trong ban da gop anh huong cac ham khac
}
bool checkcle(string s) {
   return (s[0]=='C' && s[1]=='L'&& s[2]=='E');
}
void cle(restaurant *r, int ID) {
   if(!findID(r,ID)) return;
   table *tmp=r->recentTable;
   while(tmp->ID!=ID) {
      tmp=tmp->next;
   }
   if(tmp->age==0) return;
   if(tmp==Mtable) {
      ismerge=0;
      Mtable->next=nextMtable;
      tmp->name="";
      tmp->age=0;
      while(tmp->age==0 && q->size!=0) {
          tmp->name=q->head->name;
          tmp->age=q->head->age;
          q->remove();
          tmp=tmp->next;
      }
   }
   else {
      tmp->name="";
      tmp->age=0;
   if(q->size!=0) {
      tmp->name=q->head->name;
      tmp->age=q->head->age;
      q->remove();
   }// neu co nguoi trong hang doi thi cho vao ban 
   }
}

bool checkps(string s) {
   return (s[0]=='P' && s[1]=='S');
}
void ps(restaurant *r, int num) {

}
void test(restaurant *r) {
   table*tmp = r->recentTable;
  while(tmp->next!=r->recentTable) {
   cout<<tmp->ID <<" "<<tmp->name <<" "<<tmp->age<<endl;
   tmp=tmp->next;
  }
   cout<<tmp->ID <<" "<<tmp->name <<" "<<tmp->age<<endl;// in ra thong tin ban  co ID cao nhat
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
     }// xu ly xong lenh reg

     else if(checkregm(s)){
      int i=5;
      string name="";
      string Sage="";
      string Snum="";
      while(s[i]!=' ') {
       name+=s[i];
       i++;
      }
      i++;
      while(s[i]!=' ') {
       Sage+=s[i];
       i++;
      }
      i++;
      while(i<s.length()) {
         Snum+=s[i];
         i++;
      }
      int age=stoi(Sage);
      int num=stoi(Snum);
      regm(r,name,age,num);
     }// xu ly xong lenh regm
     
     else if(checkcle(s)) {
      string SID="";
      for(int i=4;i<s.length();i++) {
         SID+=s[i];
      }
      int ID=stoi(SID);
      cle(r,ID);
     }// xu ly xong lenh cle

     else if(checkps(s)) {
      string Snum="";
      for(int i=3;i<s.length();i++) {
         Snum+=s[i];
      }
      int num=stoi(Snum);
     }

   }

    test(r);
    cout<<"Print queue:"<<endl;
    q->print();
    //table *tmp=mergetable(r,4);
    //cout<<tmp->ID;
}

