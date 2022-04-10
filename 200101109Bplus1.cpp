#include <iostream>

using namespace std;




class bnode
{
    public:

         typedef struct{
 int value;
 bnode* lc;
 bnode* rc;

}bpn;
        bnode();
        bnode(int,int);
        virtual ~bnode();
        int occupancy;

       // bpnode* lpc;

       // bpnode* rpc;
        bnode* parent;
        int index;
        int siz;
        bpn* element;
        int ind;

    protected:

    private:
};

bnode::bnode()
{ // lc= nullptr;
 //  lpc = nullptr;
  // rc= nullptr;
  // rpc = nullptr;
   occupancy=0;
   parent = nullptr;
   element = nullptr;
    //ctor
}

bnode::bnode(int in,int t)
{


     //lc= nullptr;
  // lpc = nullptr;
  // rc= nullptr;
  // rpc = nullptr;
   occupancy=0;
   index = in;
   parent = nullptr;
   element = new bpn[2*t +1];
   for(int i=0;i<2*t+1;i++){
    element[i].lc =nullptr;
    element[i].rc = nullptr;
   }
   siz = 2*t+1;
   ind=0;
    //ctor
}

bnode::~bnode()
{
    //dtor
}






class bpnode
{
    public:
        bpnode();
        bpnode(int,int);
        virtual ~bpnode();
        int index;
        int occupancy;
        int* element;
        bpnode* ls;
        bpnode* rs;
        bnode* parent;
        int siz;

    protected:

    private:
};


bpnode::bpnode()
{
    occupancy =0;
    element = nullptr;
    ls = nullptr;
    rs = nullptr;
    parent = nullptr;
    //ctor
}

bpnode::bpnode(int i,int d)
{
    occupancy =0;
    index = i;
    element = new int[2*d];
    ls = nullptr;
    rs = nullptr;
    parent = nullptr;
    siz = 2*d;
    //ctor
}

bpnode::~bpnode()
{
    //dtor
}



class bptree
{
    public:
        bptree();
        bptree(int,int);
        void insertv(int v);
        void print_status();
        bnode* root;
        int index_node;
        int data_node;
        virtual ~bptree();

    protected:

    private:
        int t;
        int d;


};


bptree::bptree()
{  root = nullptr;
    //ctor
}



bptree::bptree(int bt,int bd)
{  t= bt;
 d =bd;
 index_node =0;


    root =(bnode*) new bpnode(data_node,d);

    data_node=1;
    //ctor
}

void bptree::insertv(int val){

    if(index_node==0){
       bpnode* r = (bpnode*)root;
       if(r->occupancy < 2*d){
        r->element[r->occupancy] = val;
        r->occupancy++;

       }
       else{
        int temp[2*d +1];
        for(int i=0;i<2*d;i++){
            temp[i] = r->element[i];
        }
        temp[2*d] = val;
        for(int i=0;i<2*d;i++){
            for(int j=0;j<2*d-i;j++){
                if(temp[j]>temp[j+1]){
                    int tp = temp[j];
                    temp[j] = temp[j+1];
                    temp[j+1] = tp;
                }
            }
        }
        r->occupancy =0;
        for(int i=0;i<d;i++){
            r->element[r->occupancy] = temp[i];
            r->occupancy++;
        }
        bpnode* f = new bpnode(data_node,d);
        data_node++;
        root = new bnode(index_node,t);
        index_node++;
        r->parent = root;
        r->rs = f;
        for(int i =d;i<2*d+1;i++){
             f->element[f->occupancy] = temp[i];
            f->occupancy++;
        }
        f->ls = r;
        f->parent =root;
        root->element[root->occupancy].value = f->element[0];
        root->element[root->occupancy].lc =(bnode*) r;
        root->element[root->occupancy].rc = (bnode*)f;
        root->occupancy++;
        root->ind =1;
       }
       return;
    }

    bnode* xp = root;

    while(xp->ind !=1){
        if(xp->element[0].value >val){
            xp = xp->element[0].lc;
            continue;
        }
        for(int i=0; i< xp->occupancy; i++){
            if(val> xp->element[i].value){
                xp = xp->element[i].rc;
            }
            else{
                break;
            }
        }

    }
    bpnode* r;
     if(xp->element[0].value >val){
            r =(bpnode*) xp->element[0].lc;

        }
        else{
        for(int i=0; i< xp->occupancy; i++){
            if(val>= xp->element[i].value){
                r =(bpnode*) xp->element[i].rc;
            }
            else{
                break;
            }
        }
        }

        
        if(r->occupancy < 2*d){
        r->element[r->occupancy] = val;
        r->occupancy++;
          return;
       }
       else{ 
        int temp[2*d +1];
        for(int i=0;i<2*d;i++){
            temp[i] = r->element[i];
        }
        int tk = r->element[0];
        temp[2*d] = val;
        for(int i=0;i<2*d;i++){
            for(int j=0;j<2*d-i;j++){
                if(temp[j]>temp[j+1]){
                    int tp = temp[j];
                    temp[j] = temp[j+1];
                    temp[j+1] = tp;
                }
            }
        } 
        r->occupancy =0;
        for(int i=0;i<d;i++){
            r->element[r->occupancy] = temp[i];
            r->occupancy++;
        }
        bpnode* f = new bpnode(data_node,d);
        data_node++;
         for(int i =d;i<2*d+1;i++){
             f->element[f->occupancy] = temp[i];
            f->occupancy++;
        }
        bpnode* right = r->rs;
        if(right==nullptr){
            f->rs = nullptr;
        }
        else{
            right->ls = f;
            f->rs = right;
        }
        r->rs = f;
        f->ls = r;
        bnode* pj = r->parent; 
        
        if(pj->occupancy <2*t+1){ 
            int bh; if(pj->element[0].value >tk){
            bh =-1;
        }else{
           for( int gh=0;gh<pj->occupancy;gh++){
                f->parent  = pj;
            if(pj->element[gh].value== tk){
                bh = gh;
                break;
            }
           }
        }
           for(int gh= pj->occupancy;gh>bh+1;gh--){
            pj->element[gh].value = pj->element[gh-1].value;
            pj->element[gh].lc = pj->element[gh-1].lc;
            pj->element[gh].rc = pj->element[gh-1].rc;
           }
           pj->occupancy++;
           pj->element[bh+1].lc =(bnode*) r;
           pj->element[bh+1].rc =(bnode*) f;
           pj->element[bh+2].lc =(bnode*)f;
           pj->element[bh+1].value = f->element[0];
           return;
        }
        cout<<"ghdgh"<<endl;
        
       
        struct{
            int value;
            bnode* lc;
            bnode* rc;
        }s[2*t+2];
       for(int v =0;v<2*t+1;v++){
        s[v].value = pj->element[v].value;
        s[v].lc = pj->element[v].lc;
        s[v].rc = pj->element[v].rc;
       }
        int bh; if(pj->element[0].value >tk){
            bh =-1;
        }else{
           for( int gh=0;gh<pj->occupancy;gh++){
               
            if(pj->element[gh].value== tk){
                bh = gh;
                break;
            }
           }
        }
        
             for(int gh= 2*t+1;gh>bh+1;gh--){
           s[gh].value = s[gh-1].value;
            s[gh].lc =s[gh-1].lc;
            s[gh].rc = s[gh-1].rc;
           }

          s[bh+1].lc =(bnode*) r;
          s[bh+1].rc =(bnode*) f;
          s[bh+2].lc =(bnode*)f;
          s[bh+1].value = f->element[0];

          bnode* dc = new bnode(index_node,t);
          dc->ind =1;
          index_node++;
          pj->occupancy =0;
             for(int gh= 0;gh<t;gh++){
             pj->element[gh].value = s[gh].value;
             pj->element[gh].lc = s[gh].lc;
             pj->element[gh].rc = s[gh].rc;
             pj->occupancy++;
           }
           for(int gh=t+1;gh<2*t+2;gh++){
             dc->element[dc->occupancy].value = s[gh].value;
             dc->element[dc->occupancy].lc = s[gh].lc;
             bpnode* bv = (bpnode*) s[gh].lc;
              bv->parent = dc;
              bv = (bpnode*) s[gh].rc;
               bv->parent = dc;
             dc->element[dc->occupancy].rc = s[gh].rc;
             dc->occupancy++;
           }



          if(bh<t){
            f->parent = pj;
          }
          else{
            f->parent = dc;
          }

          

          tk = dc->element[0].value;
          bnode* cx = pj;

          bnode* cv = dc;
          pj = pj->parent;
          while(pj->occupancy==2*t+1){
            if(pj->parent ==nullptr){
                break;
            }

             struct{
            int value;
            bnode* lc;
            bnode* rc;
        }s[2*t+2];

       for(int v =0;v<2*t+1;v++){
        s[v].value = pj->element[v].value;
        s[v].lc = pj->element[v].lc;
        s[v].rc = pj->element[v].rc;
       }
        int bh;
        if(pj->element[0].value >tk){
            bh =-1;
        }
           for( int gh=0;gh<2*t+1;gh++){
            if(s[gh].value < tk){
                bh = gh;
           }
           else{
            break;
           }
           }
             for(int gh= 2*t+1;gh>bh+1;gh--){
           s[gh].value = s[gh-1].value;
            s[gh].lc =s[gh-1].lc;
            s[gh].rc = s[gh-1].rc;
           }

          s[bh+1].lc =cx;
          s[bh+1].rc =dc;
          s[bh+2].lc =dc;
          s[bh+1].value = tk;


           dc = new bnode(index_node,t);

          index_node++;
          pj->occupancy =0;
             for(int gh= 0;gh<t;gh++){
             pj->element[gh].value = s[gh].value;
             pj->element[gh].lc = s[gh].lc;
             pj->element[gh].rc = s[gh].rc;
             pj->occupancy++;
           }
           for(int gh=t+1;gh<2*t+2;gh++){
             dc->element[dc->occupancy].value = s[gh].value;
             dc->element[dc->occupancy].lc = s[gh].lc;
             bnode* bv =  s[gh].lc;
              bv->parent = dc;
              bv =  s[gh].rc;
               bv->parent = dc;
             dc->element[dc->occupancy].rc = s[gh].rc;
             dc->occupancy++;
           }



          if(bh<t){
            cv->parent = pj;
          }
          else{
            cv->parent = dc;
          }

           cv =dc;
           cx =pj;
           pj = pj->parent;

          }

          if(pj->parent ==nullptr && pj->occupancy == 2*t+1){
              struct{
            int value;
            bnode* lc;
            bnode* rc;
        }s[2*t+2];

       for(int v =0;v<2*t+1;v++){
        s[v].value = pj->element[v].value;
        s[v].lc = pj->element[v].lc;
        s[v].rc = pj->element[v].rc;
       }
        int bh;
        if(pj->element[0].value >tk){
            bh =-1;
        }
           for( int gh=0;gh<2*t+1;gh++){
            if(s[gh].value < tk){
                bh = gh;
           }
           else{
            break;
           }
           }
             for(int gh= 2*t+1;gh>bh+1;gh--){
           s[gh].value = s[gh-1].value;
            s[gh].lc =s[gh-1].lc;
            s[gh].rc = s[gh-1].rc;
           }

          s[bh+1].lc =cx;
          s[bh+1].rc =dc;
          s[bh+2].lc =dc;
          s[bh+1].value = tk;


           dc = new bnode(index_node,t);

          index_node++;
          pj->occupancy =0;
             for(int gh= 0;gh<t;gh++){
             pj->element[gh].value = s[gh].value;
             pj->element[gh].lc = s[gh].lc;
             pj->element[gh].rc = s[gh].rc;
             pj->occupancy++;
           }
           for(int gh=t+1;gh<2*t+2;gh++){
             dc->element[dc->occupancy].value = s[gh].value;
             dc->element[dc->occupancy].lc = s[gh].lc;
             bnode* bv =  s[gh].lc;
              bv->parent = dc;
              bv =  s[gh].rc;
               bv->parent = dc;
             dc->element[dc->occupancy].rc = s[gh].rc;
             dc->occupancy++;
           }



          if(bh<t){
            cv->parent = pj;
          }
          else{
            cv->parent = dc;
          }
          return;
          }


             if(pj->element[0].value >tk){
            bh =-1;
        }else{
           for( int gh=0;gh<pj->occupancy;gh++){
               cv->parent  = pj;
                if(pj->element[gh].value < tk){
                bh = gh;
           }
           else{
            break;
           }

           }
        }


           for(int gh= pj->occupancy;gh>bh+1;gh--){
            pj->element[gh].value = pj->element[gh-1].value;
            pj->element[gh].lc = pj->element[gh-1].lc;
            pj->element[gh].rc = pj->element[gh-1].rc;
           }
           pj->occupancy++;
           pj->element[bh+1].lc =cx;
           pj->element[bh+1].rc =cv;
           pj->element[bh+2].lc =cv;
           pj->element[bh+1].value = cv->element[0].value;
           return;










       }


}

void bptree::print_status(){
  cout<<index_node<<" "<<data_node;
  if(index_node==0){
        bpnode* r = (bpnode*)root;
  for(int i=0;i<r->occupancy;i++){
    cout<<" "<<r->element[i];
  }
  cout<<endl;
  return;

}
else{for(int i=0;i<root->occupancy;i++){
    cout<<" "<<root->element[i].value;
  }
  cout<<endl;
  return;

}
}

bptree::~bptree()
{
    //dtor
}




int main()
{
   int d,t;
   cin>>d>>t;
   bptree b(t,d);
   while(1){
        int ch;
        cin>>ch;
    switch(ch){
case 1: int val; cin>>val; b.insertv(val); break;
case 2: b.print_status();break;
case 3: return 0;break;

    }

   }

    return 0;
}
