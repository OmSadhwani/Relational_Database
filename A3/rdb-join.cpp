#include "rdb.h"

Relation* selection1(Relation* r, DNFformula * f){
    int i=0;
    Relation* newrel= new Relation (r->get_attrnames());
    for(auto it:f->ops){
        auto it3= r->get_rec().begin();
        advance(it3,i);
        i++;
        bool flag=true;
        for(auto it1:it){
            auto it2= find(r->get_attrnames().begin(),r->get_attrnames().end(),get<0>(it1));
            int idx= it2-r->get_attrnames().begin();
            if(get<1>(it1)=='>'){
                if(*((*it3)->getAttr(idx))<=*get<2>(it1)){
                    flag=false;
                    break;
                }
                
            }
            else if(get<1>(it1)=='<'){
                if(*((*it3)->getAttr(idx))>=*get<2>(it1)){
                    flag=false;
                    break;
                }
                
            }
            else if(get<1>(it1)=='='){
                if(*((*it3)->getAttr(idx))!=*get<2>(it1)){
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
Relation* naturaljoin(Relation* r1,Relation* r2,list<string> joinattr){
    Relation* newt=new Relation(r2->get_attrnames());
    for(auto it:r2->get_rec()){
        Record* newrec=new Record(*it);
        newt->add_rec(newrec);
    }



    int cnt=1;
    for(auto it:joinattr){
        Relation* newrel= rename(newt,it,to_string(cnt));
        cnt++;
    }
    cnt=1;
    Relation* cartesian=cartesianproduct(r1,newt);
    cout<<"Table after taking the cartesian product"<<endl;
    display(cartesian);
    cout<<endl;
    map<int,int> mp;
    for(auto it:joinattr){
        auto it1=find(cartesian->get_attrnames().begin(),cartesian->get_attrnames().end(),it);
        auto it2=find(cartesian->get_attrnames().begin(),cartesian->get_attrnames().end(),to_string(cnt));
        cnt++;
        mp[it1-cartesian->get_attrnames().begin()]=it2-cartesian->get_attrnames().begin();
    }

    for(auto it:mp){
        cout<<it.first<<" "<<it.second<<endl;
    }

    

    DNFformula f;

    for(auto it1:cartesian->get_rec()){
        list<tuple<string,char,Attr*>> l;
        for(auto it:mp){

            if((dynamic_cast<integerAttribute*>((it1->getAttr(it.second))))){
                integerAttribute* pt=dynamic_cast<integerAttribute*>((it1->getAttr(it.second)));
                l.push_back(make_tuple(cartesian->get_attrnames()[it.first],'=',new integerAttribute(pt->get())));
            }
            else if(dynamic_cast<stringAttribute*>((it1->getAttr(it.second)))){
                stringAttribute* ptr2=dynamic_cast<stringAttribute*>((it1->getAttr(it.second)));
                l.push_back(make_tuple(cartesian->get_attrnames()[it.first],'=',new stringAttribute(ptr2->get())));
            }

            else if(dynamic_cast<floatAttribute*>((it1->getAttr(it.second)))){
                floatAttribute* ptr2=dynamic_cast<floatAttribute*>((it1->getAttr(it.second)));
                l.push_back(make_tuple(cartesian->get_attrnames()[it.first],'=',new floatAttribute(ptr2->get())));
            }


        }
        f.ops.push_back(l);
    }


    
    Relation* select=selection1(cartesian,&f);
    cout<<"Table obtained after choosing the desired records"<<endl;
    display(select);
    cout<<endl;
    list<string> lis;
    
    for(auto it:select->get_attrnames()){
        int h=0;
        for(int i=0;i<it.length();i++){
            if(!isdigit(it[i])){
                h++;
                break;
            }
        }
        if(h>0){
            lis.push_back(it);
        }
    
    }

    Relation* final_table=projection(select,lis);

    return final_table;

}