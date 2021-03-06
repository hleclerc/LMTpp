#ifndef VISITOR_COMMENT_ITEM_TO_HTML_H
#define VISITOR_COMMENT_ITEM_TO_HTML_H

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>

using namespace std ;

//struct CommentItem ;
//struct LangRef ;

#include "visitorcommentitem.h"
//#include "visitorbloc_namebaseclass.h"
//struct VisitorCommentItem ;
struct CommentItem ;
struct CommentItemCode ;
struct CommentItemVerbatim ;
struct CommentItemKeyword ;
struct CommentItemList ;
struct CommentItemSection ;
struct CommentItemTable ;
struct CommentItemTxt ;
struct CommentItemWebPage ;
struct CommentItemGenericComment ;
struct CommentItemTutorial ;
struct CommentItemExample ;
struct CommentItemLaTex ;
struct CommentItemVerbatim ;
struct ListTarget ;
struct Target ;

/*!
cette classe va générer un flux au format HTML des items **sauf** :
    * les pages webs définis dans les sources du projet
    * les items example
    * les items tutorial
    * les items génériques
*/

struct VisitorCommentItem_toHTML : public VisitorCommentItem  {
    VisitorCommentItem_toHTML( ofstream* ptr_ofstream, ListTarget* plt, Target* parent  ) { ptr_list_target = plt ; web = ptr_ofstream ; ptr_parent = parent ; }
    virtual ~VisitorCommentItem_toHTML() ;
    virtual void function_at_CommentItem( CommentItem* c ) ;
    virtual void function_at_CommentItemCode( CommentItemCode* c ) ;
    virtual void function_at_CommentItemKeyword( CommentItemKeyword* c ) ;
    virtual void function_at_CommentItemList( CommentItemList* c ) ;
    virtual void function_at_CommentItemSection( CommentItemSection* c ) ;
    virtual void function_at_CommentItemTable( CommentItemTable* c ) ;
    virtual void function_at_CommentItemTxt( CommentItemTxt* c ) ;
    virtual void function_at_CommentItemWebPage( CommentItemWebPage* c ) {}
    virtual void function_at_CommentItemGenericComment( CommentItemGenericComment* c ) {}
    virtual void function_at_CommentItemExample( CommentItemExample* c ) {}
    virtual void function_at_CommentItemTutorial( CommentItemTutorial* c ) {}
    virtual void function_at_CommentItemLaTex( CommentItemLaTex* c ) ;
    virtual void function_at_CommentItemVerbatim( CommentItemVerbatim* c ) ;
    //void apply_on_related_to( const std::string &s, Op *op ) ;
    //friend std::ostream &operator<<( std::ostream &os, const Comment &c ) ;

    ListTarget* ptr_list_target ;
    ofstream* web ;
    Target* ptr_parent ;
} ;


#endif

