#include <bits/stdc++.h>

using namespace std;
typedef struct{
int dir;
int sel;
}sear;

class bucket
{
    public:
        bucket();
        bucket(int,int,int);
        virtual ~bucket();
        int occupancy;
        int local_depth;
        int index;
        int* element;

    protected:

    private:

};


bucket::bucket()
{   occupancy =0;
    element = nullptr;
    //ctor
}
bucket::bucket(int ld, int bucket_size , int i)
{
     local_depth = ld;
     occupancy =0;
     index = i;
     element = new int[bucket_size];
    //ctor
}


bucket::~bucket()
{
    //dtor
}

class hashtable
{
    public:
        int global_depth;
        int bucket_count;
        hashtable();
        hashtable(int gd,int bsize);
        void insertv(int val);
        sear searchv(int val);
        void ldelete(int val);
        void deletev(int val);
        void print_status();

        virtual ~hashtable();

    protected:

    private:
        int initial_global_depth;
        int bucket_size;
        int index_count;
        bucket** directory;

        int hashv(int val){
        return val%(int)pow(2,global_depth);
        }
};

hashtable::hashtable()
{
    directory = nullptr;
    //ctor
}

hashtable::hashtable(int gd,int bsize)
{
    global_depth= gd;
    initial_global_depth = gd;
    index_count = 0;
    bucket_count =0;
    bucket_size = bsize;
    int dir = pow(2,gd);
    directory = new bucket*[dir];
    for(int j=0;j<dir;j++){
       directory[j] = new bucket(gd,bsize,j);
       index_count++;
       bucket_count++;
    }
    //ctor
}

void hashtable::insertv(int val){
    sear dc = searchv(val);
     if(directory[dc.dir]->element[dc.sel] == val){
        return;
     }
 int hval = hashv(val);
  if(directory[hval]->occupancy != bucket_size){
    directory[hval]->element[directory[hval]->occupancy] = val;
    directory[hval]->occupancy++;
    return;
  }
  if(directory[hval]->local_depth < global_depth){

   int depth = directory[hval]->local_depth+1;
   int s = pow(2,depth);

    directory[s/2 + hval] = new bucket(depth,bucket_size,bucket_count);
  bucket_count++;
  index_count++;
  int v = s/2,hv = hval;
  int sx =0 ,k = hv%2;
  int asd[s/2 +1];
  asd[0] = val;
  sx++;
  while(v/2 !=1){
    v =v/2;
  if(hv- v >=0){
        int gh = directory[hv]->occupancy;
  for(int j=0;j<gh;j++){
    asd[sx] = directory[hv]->element[j];
    sx++;
  }  delete directory[hv];
   directory[hv] = directory[k];
    directory[hv]->occupancy =0;
    if( directory[hv]->local_depth <= depth)
    directory[hv]->local_depth = depth;
    hv = hv-v;
  }
  }
   int gh = directory[hv]->occupancy;
  for(int j=0;j<gh;j++){
    asd[sx] = directory[hv]->element[j];
    sx++;

  }
    directory[hv]->occupancy =0;
    if( directory[hv]->local_depth <= depth)
    directory[hv]->local_depth = depth;

  for(int j=0;j<sx;j++){
    insertv(asd[j]);
  }
  return;



  return;
  }
  if(global_depth ==20){
    return;
  }
  global_depth++;
  bucket** al;
  int s = pow(2,global_depth);
  al = new bucket*[s];
  for(int j=0;j<s/2;j++){
    al[j] = directory[j];
    al[s/2 +j] = directory[j];
  }
  delete[] directory;
  directory = al;

  directory[s/2 + hval] = new bucket(global_depth,bucket_size,bucket_count);
  bucket_count++;
  index_count++;
  int v = s/2,hv = hval;
  int sx =0 ,k = hv%2;
  int asd[s/2 +1];
  asd[0] = val;
  sx++;
  while(v/2 !=1){
    v =v/2;
  if(hv- v >=0){
        int gh = directory[hv]->occupancy;
  for(int j=0;j<gh;j++){
    asd[sx] = directory[hv]->element[j];
    sx++;
  }  delete directory[hv];
   directory[hv] = directory[k];
    directory[hv]->occupancy =0;
    directory[hv]->local_depth = global_depth;
    hv = hv-v;
  }
  }
   int gh = directory[hv]->occupancy;
  for(int j=0;j<gh;j++){
    asd[sx] = directory[hv]->element[j];
    sx++;

  }
    directory[hv]->occupancy =0;
    directory[hv]->local_depth = global_depth;

  for(int j=0;j<sx;j++){
    insertv(asd[j]);
  }
  return;

}

     sear hashtable::searchv(int val){
         sear k;
       for(int t=2;t<=pow(2,global_depth);t =2*t){
        int r = val%t,f=0;
        for(int j=0;j< directory[r]->occupancy;j++){
       if(directory[r]->element[j]==val){
        f++;
        k.dir=r;
        k.sel =j;
       }

        }
        if(f){
                   return k;

        }
       }
       k.dir =(int)NULL;
       k.sel =(int)NULL;
        return k;

     }

        void hashtable::ldelete(int val){
            sear k = searchv(val);
           if(directory[k.dir]->element[k.sel] == val){
             int g = directory[k.dir]->occupancy;
             for(int f = k.sel;f<g-1;f++){
               directory[k.dir]->element[f] =  directory[k.dir]->element[f+1];
             }
              directory[k.dir]->occupancy--;
           }
            return;


        }

        void hashtable::deletev(int val){
         sear k = searchv(val);
           if(directory[k.dir]->element[k.sel] == val){
             int g = directory[k.dir]->occupancy;
             for(int f = k.sel;f<g-1;f++){
               directory[k.dir]->element[f] =  directory[k.dir]->element[f+1];
             }
              directory[k.dir]->occupancy--;
           }
           else{
            return;
           }

          // int c = k.dir;
           int sx =0;

           int fg = directory[k.dir]->local_depth;
           int a[(int)pow(2,fg)];
           for(int i=1;i<=fg;i++){
                int f =0;
            int dfg= directory[val%(int)pow(2,i)]->occupancy;
            for(int j=0;j<dfg;j++){
                if(a[sx-1] = (directory[val%(int)pow(2,i)]->element[j])){
                        f++;
                    continue;
           }
               a[sx]= directory[val%(int)pow(2,i)]->element[j];
               sx++;
            }
            if(f){
                continue;
            }
            directory[val%(int)pow(2,i)]->occupancy =0;
            directory[val%(int)pow(2,i)]->local_depth--;
           }
           if(val%(int)pow(2,fg) >=(int)pow(2,fg-1))
           delete directory[val%(int)pow(2,fg)];



       //   for(int i=1;i<=fg;i++){




        //  }



           for(int fv=0;fv<sx;fv++){
              insertv(a[sx]);

           }
          return;

        }

        void hashtable::print_status(){
         cout<<global_depth<<endl;
         cout<<bucket_count<<endl;
         for(int j=0;j<index_count;j++){
            for(int i=0; i< pow(2,global_depth);i++){
                if(directory[i]->index ==j){
                    cout<<directory[i]->occupancy<<" "<<directory[i]->local_depth<<endl;
                    break;
                }
            }

         }

        return;

        }



hashtable::~hashtable()
{
    //dtor
}





int main()
{
  int global_depth,bucket_size;
  cin>>global_depth>>bucket_size;
  hashtable hasv(global_depth,bucket_size);

  int c;
  while(1){
        cin>>c;
  switch(c){
   case 2: cin>>c; hasv.insertv(c); break;

   case 3: cin>>c; hasv.searchv(c); break;

   case  4: cin>>c;hasv.deletev(c); break;

   case 5: hasv.print_status();break;

   case 6:  return 0; break;

  }
  }

    return 0;
}
