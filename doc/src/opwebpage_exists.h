#ifndef OP_WEBPAGE_EXISTS_H
#define OP_WEBPAGE_EXISTS_H

#include <map>
#include <string>

//#include "pagecomment.h"
#include "op.h"

struct PageComment ;
struct VisitorBloc_NameBaseClass ;
struct ListTarget ;



struct OpWebPage_exists : Op {
    OpWebPage_exists() { exists = false ; }
    virtual ~OpWebPage_exists() {}
    virtual void operator()( PageComment* page ) ;
    void init(const string n) { exists = false ; name = n ; }

    bool exists ;
    string name ;
};

#endif

