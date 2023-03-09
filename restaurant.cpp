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
void add(int ID,string name,int age) {// them vao cuoi
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
void addps(int ID, string name, int age) {// them vao dau 
  if(size==2*MAXSIZE) return;
  table *newTable= new table (ID, name,age,NULL);
  if(head==NULL) {
        head=newTable;
        size++;
        return;
    }
    newTable->next=head;
    head=newTable;
    size++;
}// ham add vao dau danh cho pq
void removeAt(int index) {
   if (index >= size) return ;

    table* temp = head;
    table* tempPrev = NULL;
    for (int i = 0; i < index; i++)
    {
        tempPrev = temp;
        temp = temp->next;
    }

    if (index == size - 1)
    {
        if (tempPrev) tempPrev->next = NULL;
    }
    else
    {
        if (tempPrev) tempPrev->next = temp->next;
        else head = temp->next;
    }
    delete temp;
    size--;
}
void removeItem(string name, int age) {
   int idx=0;
    table *tmp=head;
    while(tmp!=NULL) {
        if(tmp->name==name && tmp->age==age) {
            removeAt(idx);
            return;
        }
        idx++;
        tmp=tmp->next;
    }
}
void clear() {
   if (size == 0) return;
    while(head!=NULL) {
        table*next=head->next;
        delete head;
        head=next;
    }
    size=0;
}
void print() {
   table *tmp=head;
   while(tmp!=NULL) {
      cout<<tmp->ID <<" "<<tmp->name <<" "<<tmp->age<<endl;
      tmp=tmp->next;
   }
}
};

queue* q= new queue();// danh sach hang doi
queue *qps = new queue();// danh sach khach den nha hang
queue *qpq = new queue();// danh sach hang doi dung de in khach den trc
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
   if(!isdigit(s[s.length()-1])) return false;// ky tu cuoi khac so thi lenh k thoa
   return (s[0]=='R' && s[1]=='E' && s[2]=='G' && s[3]!='M');
}// ham check lenh reg
void reg(restaurant* r, int ID, string name, int age) {
    if(age<16) return;//khach duoi 16 tuoi se khong phuc vu
    qps->addps(ID,name,age);// add vao hang doi danh sach khach cua nha hang
    if(checkFull(r)) {//neu da full ban
     q->add(ID,name,age);// them vao cuoi hang doi
     qpq->add(ID,name,age);// them vao cuoi hang doi
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
      }// roi moi do tiep xem co ban trong co ID nho hon k
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
   if(!isdigit(s[s.length()-1])) return false;// ky tu cuoi khac so thi lenh k thoa
   if (isdigit(s[5])) return false;//tranh truong hop sau regm la so k phai name REGM 3 be 50 
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
      qps->addps(0,name,age);  
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
   if(!isdigit(s[s.length()-1])) return false;// ky tu cuoi khac so thi lenh k thoa
   return (s[0]=='C' && s[1]=='L'&& s[2]=='E');
}

void cle(restaurant *r, int ID) {
   if(!findID(r,ID)) return;
   table *tmp=r->recentTable;
   while(tmp->ID!=ID) {
      tmp=tmp->next;
   }
   if(tmp->age==0) return;
   qps->removeItem(tmp->name,tmp->age);// xoa khoi danh sach hang doi khach khi khach an xong di ve
   if(tmp==Mtable) {
      ismerge=0;
      Mtable->next=nextMtable;
      tmp->name="";
      tmp->age=0;
      // dua khach trong hang doi vao cho den khi het so ban sau khi gop
      while(tmp->age==0 && q->size!=0) {
          tmp->name=q->head->name;
          tmp->age=q->head->age;
          q->remove();// dua vao ban xoa khach khoi hang doi
          qpq->removeItem(tmp->name,tmp->age);// tim dung nguoi dc dua vao o dau hang q xoa trong qpq de k in nua
          tmp=tmp->next;
      }
   }
   else {
      tmp->name="";
      tmp->age=0;
   if(q->size!=0) {
      tmp->name=q->head->name;
      tmp->age=q->head->age;
      q->remove();// dua vao ban xoa khach khoi hang doi
      qpq->removeItem(tmp->name,tmp->age);// tim dung nguoi dc dua vao o dau hang q xoa trong qpq de k in nua
   }// neu co nguoi trong hang doi thi cho vao ban 
   }
}

bool checkps(string s) {
   if(s.length()>2 && !isdigit(s[s.length()-1])) return false; // ky tu cuoi khac so thi lenh k thoa
   return (s[0]=='P' && s[1]=='S');
}

void ps(int num) {
if(qps->size==0) {
   cout<<"Empty"<<endl;
   return;
}
if (num>qps->size || num==0) num=qps->size;
  table *tmp=qps->head;
  for(int i=0;i<num;i++) {
    cout<<tmp->name<<endl;
    tmp=tmp->next;
  }
}

bool checkpq(string s) {
   if(s.length()>2 && !isdigit(s[s.length()-1])) return false; // ky tu cuoi khac so thi lenh k thoa
   return(s[0]=='P' && s[1]=='Q');
}

void pq(int num) {// TH num=0 la se k co tham so num tu dong in het
  if(qpq->size==0) {
   cout<<"Empty"<<endl;
   return;
  }
  if (num>qpq->size || num==0) num=qpq->size;
  table *tmp=qpq->head;
  for(int i=0;i<num;i++) {
    cout<<tmp->name<<endl;
    tmp=tmp->next;
  }
}

bool checksq(string s) {
  if(!isdigit(s[s.length()-1])) return false;// ky tu cuoi khac so thi lenh k thoa
  return (s[0]=='S' && s[1]=='Q');
}

void sq(int num) {
   if(q->size==0) {
      cout<<"Empty"<<endl;
      return;
   } 
   if (num>q->size) num=q->size;
   table*tmp=q->head;
   int i=0;
   while(i<num && tmp->next!=NULL) {
      table *maxPos=tmp;
      table *ptr=tmp->next;
      while(ptr!=NULL) {
         if(ptr->age> maxPos->age) maxPos=ptr;// chi dung lon hon k >= vi ai toi trc se dc uu tien len trc
         ptr=ptr->next;
      }
      string saveName; saveName=tmp->name; tmp->name=maxPos->name; maxPos->name=saveName;// swap name
      int saveAge; saveAge=tmp->age; tmp->age=maxPos->age; maxPos->age=saveAge;//swap age
      i++;
      tmp=tmp->next;
   }
   tmp=q->head;
   while(tmp!=NULL) {
      cout<<tmp->name<<endl;
      tmp=tmp->next;
   }
}

void test(restaurant *r) {
   table*tmp = r->recentTable;
  while(tmp->next!=r->recentTable) {
   cout<<tmp->ID <<" "<<tmp->name <<" "<<tmp->age<<endl;
   tmp=tmp->next;
  }
   cout<<tmp->ID <<" "<<tmp->name <<" "<<tmp->age<<endl;// in ra thong tin ban  co ID cao nhat
}

bool checkDuplicateSpace(string s) {
   for(int i=0;i<s.length()-1;i++) {
      if(s[i]==' '&& s[i+1]==' ') return true;
   }
   return false;
}

void simulate(string filename, restaurant* r)
{
   ifstream filein; // ifstream ofstream 
   filein.open(filename);
   string s;
   while(getline(filein,s)) {
     if(s[0]==' ' || s[s.length()-1] ==' '|| checkDuplicateSpace(s)) continue; // check khoang trang dau cuoi neu co thi lenh do bi bo qua
     if(checkreg(s)) {
      int ID,age;
      string name="";
      string Sage="";
      if (isdigit(s[4])) {// TH khach co yeu cau ID
         int i=4;
         string tmp="";
         while(s[i]!=' ') {
              tmp+=s[i];
              i++;
         }
         i++;
         while(s[i]!=' ') {
              name+=s[i];
              i++;
         }
         i++;
         while(i<s.length()) {
             Sage+=s[i];
             i++;
         }
         ID=stoi(tmp);
         age=stoi(Sage);
      }
      else {
         int i=4;
         while(s[i]!=' ') {
              name+=s[i];
              i++;
         }
         i++;
         while(i<s.length()) {
             Sage+=s[i];
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
      if (s.length()==2) {//TH k co num
         ps(0);
         continue;
      }
      string Snum="";
      for(int i=3;i<s.length();i++) {
         Snum+=s[i];
      }
      int num=stoi(Snum);
      ps(num);
     }// xu ly xong lenh ps

     else if(checkpq(s)) {
      if (s.length()==2) {// TH k co num
         pq(0);
         continue;
      }
      string Snum="";
      for(int i=3;i<s.length();i++) {
         Snum+=s[i];
      }
      int num=stoi(Snum);
      pq(num);
     }// xu ly xong lenh pq

     else if(checksq(s)) {
      string Snum="";
      for(int i=3;i<s.length();i++) {
         Snum+=s[i];
      }
      int num=stoi(Snum);
      sq(num);
     }// xu ly xong lenh sq

   }
   
   // xoa rac trong bo nho sau khi xu ly xong
   q->clear(); qps->clear();qpq->clear();
   
   //  test(r);
   //  cout<<"Print queue:"<<endl;
   //  q->print();
    //table *tmp=mergetable(r,4);
    //cout<<tmp->ID;
}

