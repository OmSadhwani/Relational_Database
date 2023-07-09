#include "rdb.h"



    integerAttribute :: integerAttribute(int val){
        this->val=val;
    }

    int integerAttribute :: get(){
        return this->val;
    }
    
    
    bool integerAttribute:: operator==(const Attr& right){
        return val==static_cast<const integerAttribute&>(right).val;
    }
    bool integerAttribute :: operator!=(const Attr& right){
        return val!=static_cast<const integerAttribute&>(right).val;
    }
    bool integerAttribute :: operator<(const Attr& right){
        return val<static_cast<const integerAttribute&>(right).val;
    }
    bool integerAttribute :: operator<=(const Attr& right){
        return val<=static_cast<const integerAttribute&>(right).val;
    }
    bool integerAttribute :: operator>(const Attr& right){
        return val>static_cast<const integerAttribute&>(right).val;
    }
    bool integerAttribute :: operator>=(const Attr& right){
        return val>=static_cast<const integerAttribute&>(right).val;
    }
    

    floatAttribute :: floatAttribute(float val){
        this->val=val;
    }
    float floatAttribute :: get(){
        return this->val;
    }

    bool floatAttribute :: operator==(const Attr& right){
        return val==static_cast<const floatAttribute&>(right).val;
    }
    bool floatAttribute :: operator!=(const Attr& right){
        return val!=static_cast<const floatAttribute&>(right).val;
    }
    bool floatAttribute :: operator<(const Attr& right){
        return val<static_cast<const floatAttribute&>(right).val;
    }
    bool floatAttribute :: operator<=(const Attr& right){
        return val<=static_cast<const floatAttribute&>(right).val;
    }
    bool floatAttribute :: operator>(const Attr& right){
        return val>static_cast<const floatAttribute&>(right).val;
    }
    bool floatAttribute :: operator>=(const Attr& right){
        return val>=static_cast<const floatAttribute&>(right).val;
    }
    


    stringAttribute :: stringAttribute(string val){
        this->val=val;
    }
    string stringAttribute :: get(){
        return this->val;
    }
    bool stringAttribute :: operator==(const Attr& right){
        return val==static_cast<const stringAttribute&>(right).val;
    }
    bool stringAttribute :: operator!=(const Attr& right){
        return val!=static_cast<const stringAttribute&>(right).val;
    }
    bool stringAttribute :: operator<(const Attr& right){
        return val<static_cast<const stringAttribute&>(right).val;
    }
    bool stringAttribute :: operator<=(const Attr& right){
        return val<=static_cast<const stringAttribute&>(right).val;
    }
    bool stringAttribute :: operator>(const Attr& right){
        return val>static_cast<const stringAttribute&>(right).val;
    }
    bool stringAttribute :: operator>=(const Attr& right){
        return val>=static_cast<const stringAttribute&>(right).val;
    }
