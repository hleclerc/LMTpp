#include <iostream>
#include <string>
#include <vector>


using namespace std ;
#include "opgetbrief_for_principalname.h" // pour le type List_Target_brief
#include "visitorcommentitem_getbrief.h"
#include "commentitemkeyword.h"
#include "commentitemtutorial.h"
#include "commentitemgenericcomment.h"
#include "comment.h"
#include "listtarget.h"


void VisitorCommentItem_getBrief :: function_at_CommentItemKeyword( CommentItemKeyword* c ) {

    if (c->name.name == "brief")
        list_commentItemKeyword.push_back( c) ;
}

void VisitorCommentItem_getBrief :: clear() {

    list_commentItemKeyword.clear() ;
}

