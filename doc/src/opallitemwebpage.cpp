#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<vector>
#include<string>

using namespace std;

//#include "visitorcommentitem_is_extuge.h"
#include "visitorcommentitem_webpage_tohtml.h"
#include "opallitemwebpage.h"
//#include "visitorcommentitem_setpath_html.h"
#include "listtarget.h"
#include "util2html.h"
#include "target.h"
//#include "token.h"
//#include "commentitemkeyword.h"
//struct CommentItemKeyword;
#include "pagecomment.h"

/*
 cette fonction a pour objet de créer la page web de chaque item webpage.

*/
void OpAllItemWebPage::operator()( PageComment* page ) {

    // on génère les pages web des commentaitres generaux generic comment de ce PageComment.

    int i,k,n,N;
    VisitorCommentItem_webpage_toHTML w_toHTML( ptr_list_Target,ptr_tree );


    N = page->listComment.size();
    for(k=0;k<N;k++) {
        n = page->listComment[k]->items.size();
        for(i=0;i<n;i++)
            page->listComment[k]->items[i]->execute_function( &w_toHTML );
    }

}













