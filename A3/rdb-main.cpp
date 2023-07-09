#include "rdb.h"

int main(){
vector<Relation *> Relations;
int t=1;
while(t){


    int x;
    display_all(Relations);
    cout<<endl;
    cout<<"Enter 1 to create a new table\nEnter 2 to take union of 2 tables\nEnter 3 to take difference of 2 tables\nEnter 4 to take cartesian product of 2 tables\nEnter 5 to take projection of a table\nEnter 6 to perform rename operation on a table\nEnter 7 to perform natural join\nEnter 8 to perform selection on a particular table\nEnter 9 to delete a table\nEnter 0 to exit\nEnter 10 to add a record to a particular table\n";
    cin>>x;
    if(x==0){
        break;
    }
    
    switch(x){

        case 1:{
            createTable(Relations);
            break;
        }

        case 2:{
            cout<<"Enter the indexes of the table of which union is to be found \n";
            int x,y;
            cin>>x>>y;
            vector<string> r1= Relations[x-1]->get_attrnames();
            vector<string> r2= Relations[y-1]->get_attrnames();
            bool flag = true;
            if(r1.size()!=r2.size())flag = false;
            if(flag){
                for(int i=0;i<r1.size();i++){
                    if(r1[i]!=r2[i]){
                        flag = false;
                        break;

                    }
                }
            }
            if(!flag){
                cout<<"union of these two tables is not possible \n";
                break;
            }



            Relation* uni= unionop(Relations[x-1],Relations[y-1]);
            Relations.push_back(uni);
            break;
        }
        case 3:{
            cout<<"Enter the indexes of the table of which difference is to be found \n";
            int x,y;
            cin>>x>>y;

            vector<string> r1= Relations[x-1]->get_attrnames();
            vector<string> r2= Relations[y-1]->get_attrnames();
            bool flag = true;
            if(r1.size()!=r2.size())flag = false;
            if(flag){
                for(int i=0;i<r1.size();i++){
                    if(r1[i]!=r2[i]){
                        flag = false;
                        break;

                    }
                }
            }
            if(!flag){
                cout<<"difference of these two tables is not possible \n";
                break;
            }

            Relation* diff= difference(Relations[x-1],Relations[y-1]);
            Relations.push_back(diff);
            break;
        }
        case 4:{
            cout<<"Enter the indexes of the table of which cartesian product is to be found \n";
            int x,y;
            cin>>x>>y;
            cout<<"hi\n";
            Relation* cartesian= cartesianproduct(Relations[x-1],Relations[y-1]);
            Relations.push_back(cartesian);
            break;
        }
        case 5:{
            cout<<"Enter the index of the table on which projection operation is to be applied \n";
            list<string> l;

            int x;
            cin>>x;
            cout<<"Enter how many attibute names you want to keep in this table \n";
            int n;
            cin>>n;
            for(int i=0;i<n;i++){
                cout<<"Enter the name of the attribute "<<i+1<<endl;
                string s;
                cin>>s;
                l.push_back(s);
            }
            Relation* r= projection(Relations[x-1],l);
            Relations.push_back(r);
            break;
        }
        case 6:{
            cout<<"Enter the index of the table on which rename operation is to be performed \n";
            int x;
            cin>>x;
            string old,ne;
            cout<<"Enter the column name that you want to change \n";
            cin>>old;
            cout<<"Enter the new column name \n";
            cin>>ne;
            Relation* ren= rename(Relations[x-1],old,ne);
            // Relations.push_back(ren);
            break;
        }
        case 7:{
            cout<<"Enter the indexes of the table that you want to join \n";
            int x,y;
            cin>>x>>y;
            vector<string> v1=Relations[x-1]->get_attrnames(),v2=Relations[y-1]->get_attrnames();
            list<string> joinattr;
            for(int i=0;i<v1.size();i++){
                if(find(v2.begin(),v2.end(),v1[i])!=v2.end()){
                    joinattr.push_back(v1[i]);

                }

            }
            Relation* join= naturaljoin(Relations[x-1],Relations[y-1],joinattr);
            Relations.push_back(join);
            break;


        }
        case 8:{
            
                cout<<"Choose table to perform selection operation on:"<<endl;
                int a;
                cin>>a;
                DNFformula f;
                cout<<"Enter the number of disjunctions"<<endl;
                int n;cin>>n;
                for(int i=0;i<n;i++){
                    list<tuple<string,char,Attr*>> l;
                    cout<<"Enter the number of conjunctions in disjunction "<<i+1<<endl;
                    int k;cin>>k;
                    for(int j=0;j<k;j++){
                        string s;char ch;
                        cout<<"Enter the comparison in the form of (string,char,value to be compared to)"<<endl;
                        cin>>s;cin>>ch;
                        auto m=find(Relations[a-1]->get_attrnames().begin(),Relations[a-1]->get_attrnames().end(),s)-Relations[a-1]->get_attrnames().begin();
                        if(Relations[a-1]->attrinds[m]==0){
                            int val;cin>>val;
                            l.push_back(make_tuple(s,ch,new integerAttribute(val)));
                        }
                        else if(Relations[a-1]->attrinds[m]==1){
                            float val;cin>>val;
                            l.push_back(make_tuple(s,ch,new floatAttribute(val)));
                        }
                        else if(Relations[a-1]->attrinds[m]==2){
                            string val;cin>>val;
                            l.push_back(make_tuple(s,ch,new stringAttribute(val)));
                        }
                    }
                    f.ops.push_back(l);
                }

                Relation* table=selection(Relations[a-1],&f);
                cout<<"Table after the selection operation"<<endl;
                display(table);
                Relations.push_back(table);
                break;
        }
        case 9:{
            cout<<"Enter the index of the table that you want to delete \n";
            int x;
            cin>>x;
            Relations.erase(Relations.begin()+x-1);
            break;
        }
        case 10:{
            
                
                int add_rec;
                cout<<"Enter the table no. to which a record is to be added: ";
                cin>>add_rec;
                if(add_rec>Relations.size()){
                    cout<<"Please enter a valid table number."<<endl;
                    break;
                }
                Relations[add_rec-1]->addRecord_interactive();
                cout<<"The record has been added to the table."<<endl;
                break;
        }

    // cout<<"Enter 1 to create a new table\nEnter 2 to take union of 2 tables\nEnter 3 to take difference of 2 tables\nEnter 4 to take cartesian product of 2 tables\nEnter 5 to take projection of a table\nEnter 6 to perform rename operation on a table\nEnter 7 to perform natural join\nEnter 8 to perform selection on a particular table\nEnter 9 to delete a table\nEnter 0 to exit\n";

    }
}
}
