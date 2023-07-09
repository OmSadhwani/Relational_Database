
#include <bits/stdc++.h>
// #include "rdb.h"
using namespace std;



class Attr { //Base class for attributes
 // Add operators for different attribute type in derived classes
 public:
    virtual bool operator== (const Attr & right) = 0;
    virtual bool operator!= (const Attr & right) = 0;
    virtual bool operator< (const Attr & right) = 0;
    virtual bool operator<= (const Attr & right) = 0;
    virtual bool operator > (const Attr & right) = 0;
    virtual bool operator>= (const Attr & right) = 0;

};


class integerAttribute:public Attr{
    public:
    int val;
    integerAttribute(int v){
        val=v;
    }
    bool operator==(const Attr& right){
        return val==static_cast<const integerAttribute&>(right).val;
    }
    bool operator!=(const Attr& right){
        return val!=static_cast<const integerAttribute&>(right).val;
    }
    bool operator<(const Attr& right){
        return val<static_cast<const integerAttribute&>(right).val;
    }
    bool operator<=(const Attr& right){
        return val<=static_cast<const integerAttribute&>(right).val;
    }
    bool operator>(const Attr& right){
        return val>static_cast<const integerAttribute&>(right).val;
    }
    bool operator>=(const Attr& right){
        return val>=static_cast<const integerAttribute&>(right).val;
    }
    
};

class floatAttribute:public Attr{
    public:
    float val;
    floatAttribute(float v){
        val=v;
    }
    bool operator==(const Attr& right){
        return val==static_cast<const floatAttribute&>(right).val;
    }
    bool operator!=(const Attr& right){
        return val!=static_cast<const floatAttribute&>(right).val;
    }
    bool operator<(const Attr& right){
        return val<static_cast<const floatAttribute&>(right).val;
    }
    bool operator<=(const Attr& right){
        return val<=static_cast<const floatAttribute&>(right).val;
    }
    bool operator>(const Attr& right){
        return val>static_cast<const floatAttribute&>(right).val;
    }
    bool operator>=(const Attr& right){
        return val>=static_cast<const floatAttribute&>(right).val;
    }
    
};

class stringAttribute:public Attr{
    public:
    string val;
    stringAttribute(string v){
        val=v;
    }
    bool operator==(const Attr& right){
        return val==static_cast<const stringAttribute&>(right).val;
    }
    bool operator!=(const Attr& right){
        return val!=static_cast<const stringAttribute&>(right).val;
    }
    bool operator<(const Attr& right){
        return val<static_cast<const stringAttribute&>(right).val;
    }
    bool operator<=(const Attr& right){
        return val<=static_cast<const stringAttribute&>(right).val;
    }
    bool operator>(const Attr& right){
        return val>static_cast<const stringAttribute&>(right).val;
    }
    bool operator>=(const Attr& right){
        return val>=static_cast<const stringAttribute&>(right).val;
    }
};

class Record { 
    public://storing data for each record
    vector <Attr *> attrptr;
    Record(){
        // attrptr.clear();
    }
    Record(const Record &r1){
        for(auto it= r1.attrptr.begin();it!=r1.attrptr.end();it++){
            if((typeid(**it).name())==(typeid(integerAttribute).name())){
                integerAttribute* i= dynamic_cast<integerAttribute*>(*it);
                Attr* at= new integerAttribute(i->val);
                attrptr.push_back(at);
            }
            if((typeid(**it).name())== (typeid(floatAttribute).name())){
                floatAttribute* i= dynamic_cast<floatAttribute*>(*it);
                Attr* at= new floatAttribute(i->val);
                attrptr.push_back(at);

            }
            if((typeid(**it).name())== (typeid(stringAttribute).name())){
                stringAttribute* i= dynamic_cast<stringAttribute*>(*it);
                Attr* at= new stringAttribute(i->val);
                attrptr.push_back(at);

            }
        }
    }
    bool operator==(Record& r1){
        if(attrptr.size()!=r1.attrptr.size())return 0;
        auto it= attrptr.begin();
        for(auto i:r1.attrptr){
            if(**it!=*i){
                return 0;
            }
            it++;
        }
        return 1;
    }
    //methods

};

class Relation {
    public:
    int nattr, nrecs;
    vector<string> attrnames;
    vector<int> attrinds;
    list<Record*> recs;

    Relation() : nattr(0),nrecs(0){}
    Relation(const vector<string> &names){
        nattr= names.size();
        attrnames=names;
        attrinds.resize(nattr);
        for(int i=0;i<nattr;i++){
            attrinds[i]=i;
        }
        nrecs=0;

    }

    void addRecord(Record* r){
        if(r->attrptr.size()!= nattr){
            cout<<"record does not match the relation \n";
            return ;
        }
        Record* newrec= new Record(*r);
        recs.push_back(newrec);
        nrecs++;
    }
    // void deleteRecord(int i){
    //     if(i>= recs.size()){
    //         cout<<"this number is greater than the size of list \n";
    //         return;
    //     }
    //     auto it = recs.begin();
    //     advance(it,i);
    //     recs.erase(it);
    //     nrecs--;

    // }



};

Relation *unionop(Relation * R1, Relation * R2){
    
    Relation* newrel= new Relation(R1->attrnames);
    for(auto it= R1->recs.begin();it!= R1->recs.end();it++){
        // newrel->recs.push_back(*it);
        Record *newrec= new Record(**it);
        newrel->recs.push_back(newrec);
    }
        for(auto iter=R2->recs.begin();iter!=R2->recs.end();iter++){
        int h=0;

    for(auto it= newrel->recs.begin();it!= newrel->recs.end();it++){
            if(**iter== **it){
                h++;
                break;
            }

        }
        if(h)continue;
            Record *newrec= new Record(**iter);
            newrel->recs.push_back(newrec);
            newrel->nrecs++;
    }
    return newrel;
    
}

Relation * difference(Relation * R1,Relation * R2){
   Relation* newrel= new Relation(R1->attrnames);
    for(auto it= R1->recs.begin();it!= R1->recs.end();it++){
        // newrel->recs.push_back(*it);
        Record *newrec= new Record(**it);
        newrel->recs.push_back(newrec);
    }
    int ct=0;
    newrel->nrecs=R1->nrecs;
    for(auto it= R2->recs.begin();it!= R2->recs.end();it++){
        int h=0;

        for(auto iter=newrel->recs.begin();iter!=newrel->recs.end();iter++){
            if(**iter== **it){
            
                auto temp= iter;
                // it++;
                ct++;
                newrel->recs.erase(temp);
                // it--;

                break;
            }

        }
        // if(h==0)continue;
        
    }
    newrel->nrecs-=ct;


    return newrel;
    
}

Relation * cartesianproduct(Relation * R1, Relation * R2){
    // vector<string> names;
    // for(auto r:R1->attrnames){
    //     names.push_back(r)
    // }
    Relation* newrel = new Relation(R1->attrnames);
    newrel->attrnames.insert(newrel->attrnames.end(),R2->attrnames.begin(),R2->attrnames.end());
    for(auto r1 : R1->recs){
        for(auto r2 :R2->recs){
            Record* newrec = new Record(*r1);
            // newrec->attrptr.insert(newrec->attrptr.end(),r1->attrptr.begin(),r1->attrptr.end());
            // newrec->attrptr.insert(newrec->attrptr.end(),r2->attrptr.begin(),r2->attrptr.end());
            for(auto it= r2->attrptr.begin();it!=r2->attrptr.end();it++){
            if((typeid(**it).name())== (typeid(integerAttribute).name())){
                integerAttribute* i= dynamic_cast<integerAttribute*>(*it);
                Attr* at= new integerAttribute(i->val);
                newrec->attrptr.push_back(at);
            }
            if((typeid(**it).name())== (typeid(floatAttribute).name())){
                floatAttribute* i= dynamic_cast<floatAttribute*>(*it);
                Attr* at= new floatAttribute(i->val);
                newrec->attrptr.push_back(at);

            }
            if((typeid(**it).name())== (typeid(stringAttribute).name())){
                stringAttribute* i= dynamic_cast<stringAttribute*>(*it);
                Attr* at= new stringAttribute(i->val);
                newrec->attrptr.push_back(at);

            }
        }

            newrel->recs.push_back(newrec);
        }
    }
    newrel->nrecs= R1->nrecs* R1->nrecs; 
    return newrel;

}

Relation * projection(Relation * R1, list<string> projectattrs){
    vector<string> names;
    for(auto it= projectattrs.begin();it!=projectattrs.end();it++){
        names.push_back(*it);
    }
    Relation* newrel= new Relation(names);
    vector<int> idx;
    
        
        for(auto pr:names){
            int it = find(R1->attrnames.begin(),R1->attrnames.end(),pr)-R1->attrnames.begin();
            // if(it==R1->nattr){
            //     cout<<"the"<<pr<<" is not present in R1 \n";
            //     break;
            // }
            idx.push_back(it);
        }

        for(auto it:idx)
        cout<<it<<" ";
        cout<<endl;
    for(auto it:R1->recs){
        Record* newrec= new Record();
        for(int i=0;i<idx.size();i++){
            if((typeid(*(it->attrptr[idx[i]])).name())== (typeid(integerAttribute).name())){
                integerAttribute* ii= dynamic_cast<integerAttribute*>(*(it->attrptr.begin()+idx[i]));
                Attr* at= new integerAttribute(ii->val);
                newrec->attrptr.push_back(at);
            }
            if((typeid(*(it->attrptr[idx[i]])).name())== (typeid(floatAttribute).name())){
                floatAttribute* ii= dynamic_cast<floatAttribute*>(*(it->attrptr.begin()+idx[i]));
                Attr* at= new floatAttribute(ii->val);
                newrec->attrptr.push_back(at);

            }
            if((typeid(*(it->attrptr[idx[i]])).name())== (typeid(stringAttribute).name())){
                stringAttribute* ii= dynamic_cast<stringAttribute*>(*(it->attrptr.begin()+idx[i]));
                Attr* at= new stringAttribute(ii->val);
                newrec->attrptr.push_back(at);

            }
        }
        newrel->recs.push_back(newrec);
        
    }
    newrel->nrecs=R1->nrecs;
    return newrel;

    

}

Relation* rename(Relation* r,string s1,string s2){
    auto it=find(r->attrnames.begin(),r->attrnames.end(),s1);
    *it=s2;
    return r;
}

typedef struct DNFformula{
    list<list<tuple<string,char,Attr*>>> ops;
}DNFformula;

Relation* selection(Relation* r, DNFformula * f){
    int i=0;
    Relation* newrel= new Relation (r->attrnames);
    for(auto it:f->ops){
        auto it3= r->recs.begin();
        advance(it3,i);
        i++;
        bool flag=true;
        for(auto it1:it){
            auto it2= find(r->attrnames.begin(),r->attrnames.end(),get<0>(it1));
            int idx= it2-r->attrnames.begin();
            if(get<1>(it1)=='>'){
                if(*((*it3)->attrptr[idx])<=*get<2>(it1)){
                    flag=false;
                    break;
                }
                
            }
            else if(get<1>(it1)=='='){
                if(*((*it3)->attrptr[idx])!=*get<2>(it1)){
                    flag=false;
                    break;
                }
                

            }
            else if(get<1>(it1)=='<'){
                if(*((*it3)->attrptr[idx])>=*get<2>(it1)){
                    flag=false;
                    break;
                }
                
            }
        }
            if(flag){
                newrel->addRecord(*it3);
            }
        

    }

    return newrel;
}
























































// Relation* selection(Relation* r, DNFformula * f){
//     Relation* table = new Relation(r->attrnames);
//     int ab=0;
//     for(auto it1:f->ops){
//         auto it=r->recs.begin();
//         advance(it,ab);
//         bool flag=true;
//         for(auto it2:it1){
//             auto it3=find(r->attrnames.begin(),r->attrnames.end(),get<0>(it2));
//             auto i=it3-r->attrnames.begin();
//             if(get<1>(it2) == '>'){
//                 if(*((*it)->attrptr[i]) <= *get<2>(it2)){
//                     flag=false;
//                     break;
//                 }    
//             }
//             else if(get<1>(it2) == '<'){
//                 if(*((*it)->attrptr[i]) >= *get<2>(it2)){
//                     flag=false;
//                     break;
//                 }
//             }

//             else if(get<1>(it2) == '='){
//                 if(*((*it)->attrptr[i]) != *get<2>(it2)){
//                     flag=false;
//                     break;
//                 }
//             }
//         }
//         if(flag){
//             Record* abcd=new Record(**it);
//             table->recs.push_back(abcd);
//             table->nrecs++;
//         }
//         ab++;
//     }

//     return table;
// }


void display_at(Attr* a){
    // cout<<"hi 1"<<endl;
    // cout<<(typeid(*a).name())<<endl;

            if((typeid(*a).name())== (typeid(stringAttribute).name())){
            // cout<<"hi 4"<<endl;
                stringAttribute* i= dynamic_cast<stringAttribute*>(a);
                // Attr* at= new stringAttribute(i->val);
                // attrptr.push_back(at);
                cout<<i->val<<" ";

            }
    if((typeid(*a).name())== (typeid(integerAttribute).name())){
            // cout<<"hi 2"<<endl;
            
                integerAttribute* i= dynamic_cast<integerAttribute*>(a);
                // Attr* at= new integerAttribute(i->val);
                // attrptr.push_back(at);
                cout<<i->val<<" ";
            }
            if((typeid(*a).name())== (typeid(floatAttribute).name())){
            // cout<<"hi 3"<<endl;
                floatAttribute* i= dynamic_cast<floatAttribute*>(a);
                // Attr* at= new floatAttribute(i->val);
                // attrptr.push_back(at);
                cout<<i->val<<" ";

            }
}

void display(Relation* r){
    cout<<"idx"<<" ";
    for(int i=0;i<r->attrnames.size();i++){
        cout<<r->attrnames[i]<<" ";
    }

    cout<<endl;

    int ct=0;

    for(auto it: r->recs){

            cout<<ct<<" ";
            ct++;
        for(auto i: it->attrptr){
            
            display_at(i);

        }
        cout<<endl;


        
    }
}

vector<Relation *> Relations;
Relation * createTable(){
    vector<string> v;
    cout<<"enter the number of columns in the table \n";
    int n;
    cin>>n;
    int hsh[n];
    for(int i=0;i<n;i++){
        cout<<"enter the name of the header of the  column "<<i<<"\n";
        string name;
        cin>>name;
        v.push_back(name);
        cout<<"Enter 0 if this column contains int, Enter 1 if this column contains float, Enter 2 if this column contains strings \n";
        int x;
        cin>>x;
        hsh[i]=x;

    }



    Relation* r=new Relation(v);
    int j;
    cout<<"Enter the number of records you need to input \n";
    cin>>j;
    for(int k=0;k<j;k++){
        Record* newrec = new Record();
        for(int i=0;i<n;i++){
            cout<<"Enter the value in the column of "<<v[i]<<endl;
            if(hsh[i]==0){
                int value;
                cin>>value;
                integerAttribute * newat= new integerAttribute(value);
                newrec->attrptr.push_back(newat);                
            }
            if(hsh[i]==1){
                float value;
                cin>>value;
                floatAttribute * newat= new floatAttribute(value);
                newrec->attrptr.push_back(newat);                
            }
            if(hsh[i]==2){
                string value;
                cin>>value;
                stringAttribute * newat= new stringAttribute(value);
                newrec->attrptr.push_back(newat);                
            }
        }
        r->recs.push_back(newrec);
    }
    int jj=0;
    for(int i=0;i<r->attrinds.size();i++){
        r->attrinds[i]=hsh[jj];
        jj++;
    }
    Relations.push_back(r);
    return r;

}
Relation* naturaljoin(Relation* r1,Relation* r2,list<string> joinattr){
    Relation* table1=new Relation(r2->attrnames);
    for(auto it:r2->recs){
        Record* abc=new Record(*it);
        table1->recs.push_back(abc);
    }

    cout<<"Table 1"<<endl;
    display(table1);
    cout<<endl;

    int cnt=1;
    for(auto it:joinattr){
        rename(table1,it,to_string(cnt));
        cnt++;
    }
    cnt=1;
    Relation* table2=cartesianproduct(r1,table1);
    cout<<"Table 2"<<endl;
    display(table2);
    cout<<endl;
    unordered_map<int,int> mp;
    for(auto it:joinattr){
        auto it1=find(table2->attrnames.begin(),table2->attrnames.end(),it);
        auto it2=find(table2->attrnames.begin(),table2->attrnames.end(),to_string(cnt));
        cnt++;
        mp[it1-table2->attrnames.begin()]=it2-table2->attrnames.begin();
    }

    for(auto it:mp){
        cout<<it.first<<" "<<it.second<<endl;
    }

    list<tuple<string,char,Attr*>> l;
    DNFformula f;

    for(auto it1:table2->recs){
        for(auto it:mp){

            if((typeid(*(it1->attrptr[it.second])).name())==(typeid(integerAttribute)).name()){
                integerAttribute* ptr2=dynamic_cast<integerAttribute*>((it1->attrptr[it.second]));
                l.push_back(make_tuple(table2->attrnames[it.first],'=',new integerAttribute(ptr2->val)));
            }

            else if((typeid(*(it1->attrptr[it.second])).name())==(typeid(floatAttribute)).name()){
                floatAttribute* ptr2=dynamic_cast<floatAttribute*>((it1->attrptr[it.second]));
                l.push_back(make_tuple(table2->attrnames[it.first],'=',new floatAttribute(ptr2->val)));
            }

            else if((typeid(*(it1->attrptr[it.second])).name())==(typeid(stringAttribute)).name()){
                stringAttribute* ptr2=dynamic_cast<stringAttribute*>((it1->attrptr[it.second]));
                l.push_back(make_tuple(table2->attrnames[it.first],'=',new stringAttribute(ptr2->val)));
            }

        }
        f.ops.push_back(l);
    }

    for(auto it: l){
        cout<<get<0>(it)<<" "<<get<1>(it)<<" "<<get<2>(it)<<endl;

    }




    // for(int i=0;i<table2->nrecs;i++){
    //     f.ops.push_back(l);
    // }

    Relation* table3=selection(table2,&f);
    cout<<"Table 3"<<endl;
    display(table3);
    cout<<endl;
    list<string> proattrs;
    
    for(auto it:table3->attrnames){
        int h=0;
        for(int i=0;i<it.length();i++){
            if(!isdigit(it[i])){
                h++;
                break;
            }
        }
        if(h>0){
            proattrs.push_back(it);
        }
    
    }

    Relation* table4=projection(table3,proattrs);

    return table4;

}






int main(){

  createTable();
  createTable();

  list<string> l;
  l.push_back("name");
  l.push_back("age");

  Relation* table = naturaljoin(Relations[0],Relations[1],l);
  display(table);
  
    


}

