
#include "rdb.h"



//addrecord 

void Relation:: add_name(string name){
    this->attrnames.push_back(name);
}
void Relation::set_name(int idx,string name){
    this->attrnames[idx]=name;
}
vector<string> &Relation :: get_attrnames(){
    return this->attrnames;
}

list<Record*>& Relation :: get_rec(){
    return this->recs;
}





Record:: Record(){

}
Record:: ~Record(){
    for(auto i: attrptr){
        delete(i);
    }
}
Record:: Record(const Record &r1){
    for(auto it= r1.attrptr.begin();it!=r1.attrptr.end();it++){
            if((typeid(**it).name())==(typeid(integerAttribute).name())){
                integerAttribute* i= dynamic_cast<integerAttribute*>(*it);
                Attr* at= new integerAttribute(i->get());
                attrptr.push_back(at);
            }
            if((typeid(**it).name())== (typeid(floatAttribute).name())){
                floatAttribute* i= dynamic_cast<floatAttribute*>(*it);
                Attr* at= new floatAttribute(i->get());
                attrptr.push_back(at);

            }
            if((typeid(**it).name())== (typeid(stringAttribute).name())){
                stringAttribute* i= dynamic_cast<stringAttribute*>(*it);
                Attr* at= new stringAttribute(i->get());
                attrptr.push_back(at);

            }
        }
}
bool Record::operator==(Record& r1){
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





Relation:: Relation(){
    nattr=0;
    nrecs=0;
}
Relation:: Relation(const vector<string> &names){
    nattr= names.size();
        attrnames=names;
        attrinds.resize(nattr);
        for(int i=0;i<nattr;i++){
            attrinds[i]=i;
        }
        nrecs=0;

}

Relation :: ~Relation(){
    for(auto i:recs){
        delete(i);
    }
}

void Relation :: del_rec(list<Record*>:: iterator  temp){
        this->recs.erase(temp);
}

void Record::addAttr(Attr* attr){
    if(dynamic_cast<integerAttribute*>(attr)){
        attrptr.push_back(new integerAttribute(dynamic_cast<integerAttribute*>(attr)->get()));
    }
    else if(dynamic_cast<stringAttribute*>(attr)){
        attrptr.push_back(new stringAttribute(dynamic_cast<stringAttribute*>(attr)->get()));
    }
    else if(dynamic_cast<floatAttribute*>(attr)){
        attrptr.push_back(new floatAttribute(dynamic_cast<floatAttribute*>(attr)->get()));
    }   
}

Attr* Record::getAttr(int index) const{
    return attrptr[index];
}
vector<Attr*> Record::getAttrv() {
    return attrptr;
}

int Relation ::get_nrecs(){
    return this->nrecs;
}
void Relation::  set_nrecs(int i){
    this->nrecs=i;
}
void Relation::addRecord_interactive(){
    string attr_types[]={"integer","floating-point","string"};
    Record *new_rec = new Record;
    int int_temp;
    float float_temp;
    string str_temp;
    for(int i=0; i<nattr; i++){
        cout<<"Enter the value for the column '"<<attrnames[i]<<"' (of "<<attr_types[attrinds[i]]<<" data type): ";
        if(attrinds[i]==0){
            cin>>int_temp;
            Attr* newat= new integerAttribute(int_temp);
            new_rec->addAttr(newat);

        }
        else if(attrinds[i]==1){
            cin>>float_temp;
            Attr* newat= new floatAttribute(float_temp);
            new_rec->addAttr(newat);
        }
        else if(attrinds[i]==2){
            cin>>str_temp;
            Attr* newat= new stringAttribute(str_temp);
            new_rec->addAttr(newat);
        }
    }
    nrecs++;
    recs.push_back(new_rec);
}





void Relation::addRecord(Record* r){

    if(r->getAttrv().size()!= nattr){
            cout<<"record does not match the relation \n";
            return ;
        }
        Record* newrec= new Record(*r);
        recs.push_back(newrec);
        nrecs++;
}

void Relation:: add_rec(Record* rec) {
    this->recs.push_back(rec);
}
// void Relation :: del_rec(list<Record*>:: iterator  temp){

// }


Relation *unionop(Relation * R1, Relation * R2){
    
    Relation* newrel= new Relation(R1->get_attrnames());
    for(int i=0;i<R1->attrinds.size();i++){
        newrel->attrinds[i]=R1->attrinds[i];
    }
    for(auto it= R1->get_rec().begin();it!= R1->get_rec().end();it++){
        // newrel->recs.push_back(*it);
        Record *newrec= new Record(**it);
        // newrel->recs.push_back(newrec);
        newrel->add_rec(newrec);
    }
        for(auto iter=R2->get_rec().begin();iter!=R2->get_rec().end();iter++){
        int h=0;

    for(auto it= newrel->get_rec().begin();it!= newrel->get_rec().end();it++){
            if(**iter== **it){
                h++;
                break;
            }

        }
        if(h)continue;
            Record *newrec= new Record(**iter);
            // newrel->recs.push_back(newrec);
            newrel->addRecord(newrec);
            // newrel->nrecs++;
            newrel->set_nrecs(newrel->get_nrecs()+1);
    }
    return newrel;
    
}


Relation * difference(Relation * R1,Relation * R2){
   Relation* newrel= new Relation(R1->get_attrnames());
   for(int i=0;i<R1->attrinds.size();i++){
        newrel->attrinds[i]=R1->attrinds[i];
    }
    for(auto it= R1->get_rec().begin();it!= R1->get_rec().end();it++){
        // newrel->recs.push_back(*it);
        Record *newrec= new Record(**it);
        newrel->add_rec(newrec);
    }
    int ct=0;
    newrel->set_nrecs(R1->get_nrecs());
    for(auto it= R2->get_rec().begin();it!= R2->get_rec().end();it++){
        int h=0;

        for(auto iter=newrel->get_rec().begin();iter!=newrel->get_rec().end();iter++){
            if(**iter== **it){
            
                auto temp= iter;
                // it++;
                ct++;
                // newrel->recs.erase(temp);
                newrel->del_rec(temp);
                // it--;

                break;
            }

        }
       
        
    }
    // newrel->nrecs-=ct;
    newrel->set_nrecs(newrel->get_nrecs()-ct);


    return newrel;
    
}
Relation * cartesianproduct(Relation * R1, Relation * R2){
    
    Relation* newrel = new Relation(R1->get_attrnames());
    
    // newrel->attrnames.insert(newrel->attrnames.end(),R2->attrnames.begin(),R2->attrnames.end());
    for(int i=0;i<R2->get_attrnames().size();i++){
        newrel->add_name(R2->get_attrnames()[i]);
    }
    for(int i=0;i<R1->attrinds.size();i++){
        newrel->attrinds[i]=R1->attrinds[i];
    }
    for(int i=R1->attrinds.size();i<R1->attrinds.size()+R2->attrinds.size();i++){
        newrel->attrinds[i]=R1->attrinds[i];
    }
    for(auto r1 : R1->get_rec()){
        for(auto r2 :R2->get_rec()){
            Record* newrec = new Record(*r1);
            
            for(auto it= r2->getAttrv().begin();it!=r2->getAttrv().end();it++){
           
            newrec->addAttr(r2->getAttr(it-r2->getAttrv().begin()));
        }

            newrel->add_rec(newrec);
        }
    }
    newrel->set_nrecs(R1->get_nrecs()* R2->get_nrecs()); 

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
            int it = find(R1->get_attrnames().begin(),R1->get_attrnames().end(),pr)-R1->get_attrnames().begin();
            
            idx.push_back(it);
        }

        for(auto it:idx)
        cout<<it<<" ";
        cout<<endl;
    for(auto it:R1->get_rec()){
        Record* newrec= new Record();
        for(int i=0;i<idx.size();i++){
            if(dynamic_cast<integerAttribute*>(*(it->getAttrv().begin()+idx[i]))){
                integerAttribute* ii= dynamic_cast<integerAttribute*>(*(it->getAttrv().begin()+idx[i]));
                Attr* at= new integerAttribute(ii->get());
                // newrec->attrptr.push_back(at);
                newrec->addAttr(at);
            }
            if(dynamic_cast<floatAttribute*>(*(it->getAttrv().begin()+idx[i]))){
                floatAttribute* ii= dynamic_cast<floatAttribute*>(*(it->getAttrv().begin()+idx[i]));
                Attr* at= new floatAttribute(ii->get());
                // newrec->attrptr.push_back(at);
                newrec->addAttr(at);

            }
            if(dynamic_cast<stringAttribute*>(*(it->getAttrv().begin()+idx[i]))){
                stringAttribute* ii= dynamic_cast<stringAttribute*>(*(it->getAttrv().begin()+idx[i]));
                Attr* at= new stringAttribute(ii->get());
                // newrec->attrptr.push_back(at);
                newrec->addAttr(at);

            }
        }
        newrel->add_rec(newrec);
        
    }
    newrel->set_nrecs(R1->get_nrecs());
    for(int i=0;i<newrel->get_attrnames().size();i++){
        auto ind=find(R1->get_attrnames().begin(),R1->get_attrnames().end(),newrel->get_attrnames()[i])-R1->get_attrnames().begin();
        newrel->attrinds[i]=R1->attrinds[ind];
    }
    return newrel;

    

}

int Relation::getAttrInd(string s) {
    int i=0;
    for(auto str:attrnames){
        if(s == str) return i;
        i++;
    }
    return -1;
}

 Relation* selection(Relation* r1,DNFformula* f){
        
    Relation* r3 = new Relation(r1->get_attrnames());

    for(auto rec: r1->get_rec()){
        bool flag = true;
        for(auto clause: f->ops){
            bool flag2 = true;
            for(auto tup:clause){
                if(get<1>(tup)=='='){
                    if(*rec->getAttr(r1->getAttrInd(get<0>(tup))) != *get<2>(tup)){
                        flag2 = false;
                        break;
                    }
                }
                else if(get<1>(tup)=='<'){
                    if(*rec->getAttr(r1->getAttrInd(get<0>(tup))) >= *get<2>(tup)){
                        flag2 = false;
                        break;
                    }
                }
                else if(get<1>(tup)=='>'){
                    if(*rec->getAttr(r1->getAttrInd(get<0>(tup))) <= *get<2>(tup)){
                        flag2 = false;
                        break;
                    }
                }
                
            }

            if(flag2){
                flag = true;
                break;
            }
            else{
                flag = false;
            }
        }

        if(flag){
            Record* temp = new Record(*rec);
            r3->addRecord(temp);
            r3->set_nrecs(r3->get_nrecs()+1);
        }
    }

    return r3;
        
}

Relation * createTable(vector<Relation *> &Relations){
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
                Attr * newat= new integerAttribute(value);
                // newrec->attrptr.push_back(newat);  
                newrec->addAttr(newat);              
            }
            if(hsh[i]==1){
                float value;
                cin>>value;
                Attr * newat= new floatAttribute(value);
                // newrec->attrptr.push_back(newat);       
                newrec->addAttr(newat);         
            }
            if(hsh[i]==2){
                string value;
                cin>>value;
                Attr * newat= new stringAttribute(value);
                // newrec->attrptr.push_back(newat);       
                newrec->addAttr(newat);         
            }
        }
        r->add_rec(newrec);
    }
    int jj=0;
    for(int i=0;i<r->attrinds.size();i++){
        r->attrinds[i]=hsh[jj];
        jj++;
    }
    Relations.push_back(r);
    return r;

}
Relation* rename(Relation* r,string s1,string s2){
    auto it=find(r->get_attrnames().begin(),r->get_attrnames().end(),s1);
    // cout<<it<<endl;
    // r->set_name(it,s2);
    *it=s2;
    return r;
}


void display_at(Attr* a){
    

            if(dynamic_cast<stringAttribute*>(a)){
            
                stringAttribute* i= dynamic_cast<stringAttribute*>(a);
                
                cout<<i->get()<<" ";

            }
            if(dynamic_cast<integerAttribute*>(a)){
            
                integerAttribute* i= dynamic_cast<integerAttribute*>(a);
                
                cout<<i->get()<<" ";
            }
            if(dynamic_cast<floatAttribute*>(a)){
            
                floatAttribute* i= dynamic_cast<floatAttribute*>(a);
                
                cout<<i->get()<<" ";

            }
}
void display(Relation* r){
    cout<<"idx"<<" ";
    for(int i=0;i<r->get_attrnames().size();i++){
        cout<<r->get_attrnames()[i]<<" ";
    }
    cout<<endl;
    int ct=0;
    for(auto it: r->get_rec()){
            cout<<ct<<" ";
            ct++;
        for(auto i: it->getAttrv()){
            display_at(i);

        }
        cout<<endl;


        
    }
}

void display_all(vector<Relation*>&Relations){
    for(int i=0;i<(int)Relations.size();i++){
        cout<<"Table "<<i+1<<endl;
        display(Relations[i]);
        cout<<endl;

    }
}







