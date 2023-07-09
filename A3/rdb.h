#include <bits/stdc++.h>
using namespace std;
class Attr{
    public:
    virtual bool operator== (const Attr & right) = 0;
    virtual bool operator!= (const Attr & right) = 0;
    virtual bool operator< (const Attr & right) = 0;
    virtual bool operator<= (const Attr & right) = 0;
    virtual bool operator> (const Attr & right) = 0;
    virtual bool operator>= (const Attr & right) = 0;
};
class Record{
    vector<Attr*> attrptr;
    public:
    Record();
    Record(const Record&rec);
    void addAttr(Attr* attr);
    vector<Attr*> getAttrv() ;
    Attr* getAttr(int index)const;

    bool operator==(Record&r1);
    ~Record();
};
class Relation{
    int nattr, nrecs;
    vector<string> attrnames;
    list<Record*> recs;
    public:
    int getAttrInd(string s) ;
    void add_rec(Record* rec);
    list<Record*> &get_rec();
    void del_rec(list<Record*>:: iterator  temp);
    vector<int> attrinds;
    int get_nrecs();
    void add_name(string name);
    void addRecord_interactive();
    void set_name(int idx,string name);
    vector<string> &get_attrnames();
    

    void set_nrecs(int i);
    Relation(const vector<string> &names);
    Relation();
    void addRecord(Record* r);
    
    ~Relation();
};

class integerAttribute:public Attr{
    int val;
    public:
    int get();
    integerAttribute(int v=0);
    bool operator==(const Attr& right);
    bool operator!=(const Attr& right);
    bool operator<(const Attr& right);
    bool operator<=(const Attr& right);
    bool operator>(const Attr& right);
    bool operator>=(const Attr& right);
};

class floatAttribute:public Attr{
    float val;
    public:
    floatAttribute(float v=0.0);
    float get();
    bool operator==(const Attr& right);
    bool operator!=(const Attr& right);
    bool operator<(const Attr& right);
    bool operator<=(const Attr& right);
    bool operator>(const Attr& right);
    bool operator>=(const Attr& right);
};

class stringAttribute:public Attr{
    string val;
    public:
    stringAttribute(string v="");
    string get();
    bool operator==(const Attr& right);
    bool operator!=(const Attr& right);
    bool operator<(const Attr& right);
    bool operator<=(const Attr& right);
    bool operator>(const Attr& right);
    bool operator>=(const Attr& right);
};
typedef struct DNFformula{
    list<list<tuple<string,char,Attr*>>> ops;
}DNFformula;


Relation *unionop(Relation * R1, Relation * R2);
Relation * difference(Relation * R1,Relation * R2);
Relation * cartesianproduct(Relation * R1, Relation * R2);
Relation * projection(Relation * R1, list<string> projectattrs);
Relation* selection(Relation* r, DNFformula * f);
Relation* rename(Relation* r,string s1,string s2);
void display_at(Attr* a);
void display(Relation* r);
Relation* naturaljoin(Relation* r1,Relation* r2,list<string> joinattr);
void display_all(vector<Relation*>&Relations);
Relation * createTable(vector<Relation *> &Relations);
