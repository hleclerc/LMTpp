#include <iostream>
#include <string>
#include <vector>


using namespace std;

#include "opdebug.h"
#include "pagecomment.h"
#include "opallclass.h"
#include "visitorbloc_allclass_tohtml.h"
#include "listtarget.h"


// cette fonction a pour objet de générer une page web à partir de la page "page" dans un futur proche
void OpAllClass :: operator()( PageComment* page ) {

    VisitorBloc_AllClass_toHTML v_all_class( ptr_list_target,ptr_tree );
    int i,n;

    // on génère toutes les pages web, une par classe ou struct.
    n = page->code.list_subType_function.size();
    for(i=0;i<n;i++) {
        v_all_class.setParent( page->code.list_subType_function[i] );
        page->code.list_subType_function[i]->exec( &v_all_class );
    }

}













