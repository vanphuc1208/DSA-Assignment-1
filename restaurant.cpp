#include "main.h"
int count=0;// danh dau idx
class custumerInfo{
    public:
    int ID;
    string name;
    int age;
    int idx;
    custumerInfo* next;
    custumerInfo(int ID, string name, int age, custumerInfo* next, int idx=0)
    {
        this->ID = ID;
        this->name = name;
        this->age = age;
        this->idx=idx;
        this->next = next;
    }
};
class queue {
public:
    custumerInfo* head;
    int size;
    queue() {
        head = NULL;
        size = 0;
    }
    ~queue();
    void add(int ID, string name, int age) {// them vao cuoi
        if (size == MAXSIZE) return;
        count++;// tang idx
        custumerInfo* newCustumer = new custumerInfo(ID, name, age, NULL,count);
        if (head ==NULL) {
            head = newCustumer;
            size++;
            return;
        }
        custumerInfo* tmp = head;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = newCustumer;
        size++;
    }
    void remove() {// xoa dau
        if(head==NULL) return;
        custumerInfo *delCustumer=head;
        head=head->next;
        delete delCustumer;
        size--;
    }
    void addps(int ID, string name, int age) {// them vao dau 
        if (size == 2 * MAXSIZE) return;
        custumerInfo* newTable = new custumerInfo(ID, name, age, NULL);
        if (head == NULL) {
            head = newTable;
            size++;
            return;
        }
        newTable->next = head;
        head = newTable;
        size++;
    }// ham add vao dau danh cho pq
    void removeItem(string name, int age) {
        custumerInfo* pCustumer = head;
        custumerInfo* pPrev = NULL;
        while(pCustumer!=NULL) {
            if(pCustumer->name==name && pCustumer->age==age) {
                if(pCustumer->next==NULL) {
                    if(pPrev) pPrev->next=NULL;
                }
                else {
                    if(pPrev) pPrev->next=pCustumer->next;
                    else head=pCustumer->next;
                }
                delete pCustumer;
                size--;
                if(size==0) head=NULL;
                return;
            }
            pPrev=pCustumer;
            pCustumer=pCustumer->next;
        }
    }
    void clear() {
        if (size == 0) return;
        while (head != NULL) {
            custumerInfo* next = head->next;
            delete head;
            head = next;
        }
        size = 0;
    }
};

queue* q = new queue();// danh sach hang doi
queue* qps = new queue();// danh sach khach den nha hang
queue* qpq = new queue();// danh sach hang doi dung de in khach den trc
int numMtable=0;//khoi tao so ban dang dc gop neu bang 0 la chua co ban gop
table* Mtable;// luu ban bat dau merge
table* nextMtable; // luu ban tiep theo cua merge de dung lai trong ham cle

// check da full ban hay chua
bool checkFull(restaurant* r) {
    table* tmp = r->recentTable;
    if (tmp->age == 0) return false;
    tmp = tmp->next;
    while (tmp != r->recentTable) {
        if (tmp->age == 0) return false;
        tmp = tmp->next;
    }
    return true;
}

bool findID(restaurant* r, int ID) {
    table* tmp = r->recentTable;
    if (tmp->ID == ID) return true;
    tmp = tmp->next;
    while (tmp != r->recentTable) {
        if (tmp->ID == ID) return true;
        tmp = tmp->next;
    }
    return false;
}// ham tim kiem theo ID

void reg(restaurant* r, int ID, string name, int age) {
    if (age < 16) return;//khach duoi 16 tuoi se khong phuc vu
    if (!checkFull(r) || q->size!=MAXSIZE)qps->addps(ID, name, age);// add vao hang doi danh sach khach cua nha hang khi ban va hang doi con tron
    if (checkFull(r)) {//neu da full ban
        q->add(ID, name, age);// them vao cuoi hang doi
        qpq->add(ID, name, age);// them vao cuoi hang doi
        return;
    }
    if (ID == 0) {
        table* tmp = r->recentTable;
        table* minID = tmp;// luu vi tri ban trong vs ID nho nhat
        while (minID->age != 0) {
            minID = minID->next;
        } // tim toi vi tri trong gan nhat phong TH chi con ban trong sau recenttable
        while (tmp->next != r->recentTable) {
            if (tmp->age == 0 && tmp->ID < minID->ID) {
                minID = tmp;
            }
            tmp = tmp->next;
        }// roi moi do tiep xem co ban trong co ID nho hon k
        if (tmp->age == 0 && tmp->ID < minID->ID) {
            minID = tmp;
        }// duyet them phan tu cuoi
        minID->name = name;
        minID->age = age;
        r->recentTable=minID;
    }
    else {
        table* tmp = r->recentTable;
        if (!findID(r, ID)) {
            tmp = Mtable->next;
        }// neu ban do o trong nhom ban gop thi phai chi toi ban ngay sau nhom ban gop
        else {
            while (tmp->ID != ID) {
                tmp = tmp->next;
            }// chi toi ban co ID vi khach muon dat
        }
        while (tmp->age != 0) {//kiem tra ban trong ngay sau 
            tmp = tmp->next;
        }
        tmp->age = age;
        tmp->name = name;
         r->recentTable=tmp;
    }
}

int maxAdjacentTable(restaurant* r) {// ham tim so ban max canh nhau
int res=0;
int count=1;
table *tmp=r->recentTable;
for(int i=0;i<2*MAXSIZE;i++) {
   if(tmp->age==0 && tmp->next->age==0) {// phai duyet 2 lan
       count++;
       if(count==MAXSIZE) return count;
   } 
   if((tmp->age==0&& tmp->age!= tmp->next->age) || i==2*MAXSIZE-1 ) {
      if(count>res) res=count;
      count=1;
   }
   tmp=tmp->next;
}
return res;
}

// ham tim ban co ID lon nhat de merge
table* mergetable(restaurant* r, int num) {
    table* tmp = r->recentTable;// duyet het cac ban
    while (tmp->ID != 1) { // cai nay khong anh huong boi ham tron vi khi numMtable=0 ms thuc hien
        tmp = tmp->next;
    }// chi toi ban co ID bang 1 roi do ban trong tu day
    table* ptr = tmp;// danh dau vi tri co the la mergetable
    table* mergetable = tmp;
    int count = 0;
    int maxID = 0;
    while (1) {// ham se khong chay qua 2*N
        if (tmp->age == 0) {
            if (count == 0) ptr = tmp;
            count++;
        }
        if (ptr->ID <= maxID && count==num) break;
        if (count == num) {
            mergetable = ptr;
            maxID = mergetable->ID;
            tmp = ptr;// de check xem ban lien ke co the dat du ban de tron k
            count = 0;
        }
        if (tmp->age != 0) {
            count = 0;
        }
        tmp = tmp->next;
    }
    return mergetable;
}

void regm(restaurant* r, string name, int age, int num) {// bien numMtable de check da gop ban nao hay chua khi chua co se thuc hien lenh gop ban va cho numMtable=num
    if (numMtable || checkFull(r) || maxAdjacentTable(r) < num || age < 16) return;
    qps->addps(0, name, age);
    Mtable = mergetable(r, num);
    Mtable->name = name;
    Mtable->age = age;
    nextMtable = Mtable->next;
    table* tmp = Mtable;
    for (int i = 0; i < num; i++) {
        tmp = tmp->next;
    }
    Mtable->next = tmp;
    numMtable = num;
    r->recentTable = Mtable;// de khong bi truong hop recent table nam trong ban da gop anh huong cac ham khac
}


void cle(restaurant* r, int ID) {
    if (!findID(r, ID)) return;
    table* tmp = r->recentTable;
    while (tmp->ID != ID) {
        tmp = tmp->next;
    }
    if (tmp->age == 0) return;
    qps->removeItem(tmp->name, tmp->age);// xoa khoi danh sach hang doi khach khi khach an xong di ve
    r->recentTable=tmp;
    if (tmp == Mtable&&numMtable!=0) {// check do co phai ban gop va dang co ban gop hay k
        int avaiTable=numMtable;
        numMtable = 0;
        Mtable->next = nextMtable;
        tmp->name = "";
        tmp->age = 0;
        while(avaiTable>0 && q->size!=0) {
            int ID=q->head->ID;
            string name=q->head->name;
            int age=q->head->age;
            q->remove();
            qpq->removeItem(name,age);
            if (ID == 0) {
        table* tmp = r->recentTable;
        table* minID = tmp;// luu vi tri ban trong vs ID nho nhat
        while (minID->age != 0) {
            minID = minID->next;
        } // tim toi vi tri trong gan nhat phong TH chi con ban trong sau recenttable
        while (tmp->next != r->recentTable) {
            if (tmp->age == 0 && tmp->ID < minID->ID) {
                minID = tmp;
            }
            tmp = tmp->next;
        }// roi moi do tiep xem co ban trong co ID nho hon k
        if (tmp->age == 0 && tmp->ID < minID->ID) {
            minID = tmp;
        }// duyet them phan tu cuoi
        minID->name = name;
        minID->age = age;
        r->recentTable=minID;
          }
          else {
        table* tmp = r->recentTable;
            while (tmp->ID != ID) {
                tmp = tmp->next;
            }// chi toi ban co ID vi khach muon dat
        while (tmp->age != 0) {//kiem tra ban trong ngay sau 
            tmp = tmp->next;
        }
        tmp->age = age;
        tmp->name = name;
        r->recentTable=tmp;
    }

            avaiTable--;
    }

    }
    else {
        tmp->name = "";
        tmp->age = 0;
        if (q->size != 0) {
            tmp->name = q->head->name;
            tmp->age = q->head->age;
            q->remove();// dua vao ban xoa khach khoi hang doi
            qpq->removeItem(tmp->name, tmp->age);// tim dung nguoi dc dua vao o dau hang q xoa trong qpq de k in nua
            r->recentTable=tmp;
        }// neu co nguoi trong hang doi thi cho vao ban 
    }
}


void ps(int num) {
    if (qps->size == 0) {
        cout << "Empty" << endl;
        return;
    }
    if (num > qps->size || num == 0) num = qps->size;
    custumerInfo* tmp = qps->head;
    for (int i = 0; i < num; i++) {
        cout << tmp->name << endl;
        tmp = tmp->next;
    }
}


void pq(int num) {// TH num=0 la se k co tham so num tu dong in het
    if (qpq->size == 0) {
        cout << "Empty" << endl;
        return;
    }
    if (num > qpq->size || num == 0) num = qpq->size;
    custumerInfo* tmp = qpq->head;
    for (int i = 0; i < num; i++) {
        cout << tmp->name << endl;
        tmp = tmp->next;
    }
}
// danh dau cac idx trung nhau 
void sq(int num) {
    if (q->size == 0) {
        cout << "Empty" << endl;
        return;
    }
    if (num > q->size) num = q->size;
    custumerInfo* tmp = q->head;
    int i = 0;
    while (i < num && tmp->next != NULL) {
        custumerInfo* maxPos = tmp;
        custumerInfo* ptr = tmp->next;
        while (ptr != NULL) {
            if (ptr->age > maxPos->age) maxPos = ptr;// neu lon tuoi hon chi xet tuoi
            else if(ptr->age==maxPos->age && ptr->idx < maxPos->idx) maxPos=ptr;// neu cung tuoi xet idx
            ptr = ptr->next;
        }
        string saveName; saveName = tmp->name; tmp->name = maxPos->name; maxPos->name = saveName;// swap name
        int saveAge; saveAge = tmp->age; tmp->age = maxPos->age; maxPos->age = saveAge;//swap age
        int saveID; saveID = tmp->ID; tmp->ID = maxPos->ID; maxPos->ID = saveID;//swap age
        int saveidx; saveidx = tmp->idx; tmp->idx = maxPos->idx; maxPos->idx = saveidx;//swap age
        i++;
        tmp = tmp->next;
    }
    tmp = q->head;
    while (tmp != NULL) {
        cout << tmp->name << endl;
        tmp = tmp->next;
    }
}

void pt(restaurant* r) {
    table* tmp = r->recentTable;
    while (tmp->next != r->recentTable) {
        if(tmp->age!=0) cout << tmp->ID << "-" << tmp->name <<endl;
        tmp = tmp->next;
    }
    if(tmp->age!=0) cout << tmp->ID << "-" << tmp->name <<endl;
}

void simulate(string filename, restaurant* r)
{
    ifstream filein; // ifstream ofstream 
    filein.open(filename);
    string s;
    // quy doi string::npos=-1 de chay dc tren bkel
    while (getline(filein,s))
    {
        if(s.substr(0,4)=="REGM") {// tranh TH ham REG trc thi REGM cx substr(0,3) la REG
            int fSpace = s.find(" ", 5);
            int sSpace = s.find(" ", fSpace+1);
            string name,sage,snum;
            name=s.substr(5,fSpace-5);
            sage=s.substr(fSpace+1,sSpace-fSpace-1);
            snum=s.substr(sSpace+1);
            regm(r,name,stoi(sage),stoi(snum));
        }

        else if(s.substr(0,3)=="REG") {
            string sID,name,sage;
            int fSpace = s.find(" ", 4);
            int sSpace = s.find(" ", fSpace+1);
            if(s.find(" ", fSpace+1) !=string::npos) //co ID{
            {
                 sID=s.substr(4,fSpace-4);
                 name=s.substr(fSpace+1,sSpace-fSpace-1);
                 sage=s.substr(sSpace+1);
            }
            else {// k co ID
                 sID="0";
                 name=s.substr(4,fSpace-4);
                 sage=s.substr(fSpace+1);
            }
            reg(r,stoi(sID),name,stoi(sage));
        }

        else if(s.substr(0,3)=="CLE") {
            string sID=s.substr(4);
            cle(r,stoi(sID));
        }

        else if(s.substr(0,2)=="PS") {
            if(s.find(" ",2) !=string::npos) {//co tham so num
              string snum=s.substr(3);
              ps(stoi(snum));
            }
            else ps(0);
        }

        else if(s.substr(0,2)=="PQ") {
            if(s.find(" ",2) !=string::npos) {//co tham so num
              string snum=s.substr(3);
              pq(stoi(snum));
            }
            else pq(0);
        }

        else if(s.substr(0,2)=="SQ") {
            string snum=s.substr(3);
            sq(stoi(snum));
        }
        else if(s.substr(0,2)=="PT") 
        {
            pt(r);
        }
        

    }
    
filein.close();
     q->clear(); qps->clear(); qpq->clear();
}