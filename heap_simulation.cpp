#include <iostream>

using namespace std;



typedef struct{
int value;
int size;
}dnode;

class page
{
    public:
        page();
        page(int,int);
        virtual ~page();
        void insertv(int vsize,int val);
        bool searchv(int val);
        int espace;
        int pno;
        page* ls;
        page* rs;
        int counter;


    protected:
        dnode* element;


    private:
};



page::page()
{
    element = nullptr;
    espace =0;
    ls = nullptr;
    rs= nullptr;

    //ctor
}


page::page(int psize,int no)
{
    int k;
     k = (psize-16)/8;
    if(psize>16){
        element = new dnode[k];
        espace = psize -16;
        pno = no;
        counter =0;
        ls = nullptr;
        rs=nullptr;

    }


    //ctor
}


void page::insertv(int vsize,int val)
{
    element[counter].size = vsize;
    element[counter].value = val;
    counter ++;
    espace = espace - vsize;
    espace = espace -4;
    //ctor
}


bool page::searchv(int val)
{
    for(int i=0; i<counter;i++){
        if(element[i].value == val ){
            cout<<pno<<" "<<i<<endl;
            return true;
        }
    }
    return false;

    //ctor
}


page::~page()
{
    //dtor
}


class hfile
{
    public:
        hfile();
        hfile(int);
        virtual ~hfile();
        void insertv(int vsize,int val);
        void searchv(int val);
        void status();
        page* fpage;
        int psize; 
        int pno;


    protected:

    private:
};


hfile::hfile()
{
    fpage  =nullptr;
    pno =0;
    //ctor
}



hfile::hfile(int siz)
{
    fpage  =nullptr;
    pno =0;
    psize = siz;
    //ctor
}

void hfile::insertv(int vsize, int val){
    page* a = fpage;
    page* b = fpage;
    if(pno ==0){
     a= new page(psize,pno);
     fpage = a;
     pno++;
     a->insertv(vsize,val);
     return;

    }else{
    while(a->rs!= nullptr){
     int s = vsize+4;
     if((a->espace)>=s){
        a->insertv(vsize,val);
        return;
     }
   a= a->rs;}
   int s = vsize+4;
     if((a->espace)>=s){
        a->insertv(vsize,val);
        return;
     }
  
   b = new page(psize,pno);
  
   pno++;

   a->rs = b;
   

    b->ls = a;
   

   a->rs->insertv(vsize,val);


     return;
    }
  
}


void hfile::searchv(int val){
  page* a = fpage;
  bool b = false;
  while(a!= nullptr){
      if(b){
          return;
      }
      
      b = a->searchv(val);
    
      a= a->rs;
  }
  if(b){
          return;
      }
   else{
  cout<<"-1 -1"<<endl;
   }
  return;
}

void hfile::status(){
    cout<<pno<<" ";
    page* a = fpage;
    while(a!=nullptr){
        cout<<a->counter<<" ";
        a= a->rs;
    }
    cout<<endl;
   return;
}



hfile::~hfile()
{
    //dtor
}



int main()
{
    int siz;
    cin>>siz;
  
  hfile* h = new hfile(siz);
  int ch;
  while(1){
      cin>>ch;
  switch(ch){
   case 1: int a,b; cin>>a>>b; h->insertv(a,b); break;
   case 2: h->status(); break;
   case 3: int val;cin>>val; h->searchv(val); break;
   case 4: return 0;break;
 
   }
  }
    return 0;
}
