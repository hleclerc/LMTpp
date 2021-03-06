#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<sstream>

#include<cmath>
#include"time.h"


using namespace std;
#include "op.h"
//#include "visitorbloc_namebaseclass.h"
#include "visitorcommentitem.h"
#include "visitorcommentitem_tohtml.h"
#include "commentitemkeyword.h"
#include "commentitemtxt.h"
#include "commentitemtable.h"
#include "commentitemsection.h"
#include "commentitemcode.h"
#include "commentitemverbatim.h"
#include "commentitemlist.h"
#include "commentitemwebpage.h"
#include "commentitemgenericcomment.h"
#include "commentitemexample.h"
#include "commentitemtutorial.h"
#include "commentitemlatex.h"
#include "commentitem.h"
#include "commentitemverbatim.h"
#include "listtarget.h"
#include "comment.h"
#include "util2html.h"
#include "token.h"

VisitorCommentItem_toHTML :: ~VisitorCommentItem_toHTML() {

}

void VisitorCommentItem_toHTML :: function_at_CommentItem( CommentItem* c ) {

}

void VisitorCommentItem_toHTML :: function_at_CommentItemCode( CommentItemCode* c ) {

    int i,n,m,j;

    n = c->txt.size();
    *web << "<div class=\"code\">" << std::endl;
    *web << "<tt>" << std::endl;
    *web << "<pre> " << std::endl;
    for(i=0;i<n;i++) {
        m = c->tabulation[i];
        for(j=0;j<m;j++)
            *web << '\t';
        *web << french2HTML( c->txt[i] ) << std::endl;
    }
    *web << "</pre>" << std::endl;
    *web << "</tt>" << std::endl;
    *web << "</div>" << std::endl;
}

void VisitorCommentItem_toHTML :: function_at_CommentItemKeyword( CommentItemKeyword* c ) {

    //ListTarget listlocaltarget;
    string mailto;
    string ami;
    int i,n,end,pos,pos2,suiv,suiv2,posaro;
    Target* ptr_t;

    /// consulter le fichier comment.cpp pour avoir la liste des mots clés.

    //cerr << " BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB " << " n = " << n << endl;

    if (c->name.name == "author") {
        end = c->parametres.size();
        suiv = 0;
        *web << "<p class=\"auteur\">" << std::endl;
        *web << "Auteur :" << std::endl;
        while(suiv<end) {
            pos  = extraire_token_delimateur_blanc(&suiv,c->parametres,end,suiv);
            if (pos == -1) break;
            if (chercher_motif(c->parametres,"@",&posaro,suiv,pos)) {
                mailto = c->parametres.substr(pos,suiv-pos);
                *web << " <a href=\"mailto:" << mailto << "\">" << mailto << " </a>" << std::endl;
                continue;
            }
            if (chercher_motif(c->parametres,"www",&posaro,suiv,pos) || chercher_motif(c->parametres,"http",&posaro,suiv,pos) || chercher_motif(c->parametres,"ftp",&posaro,suiv,pos)) {
                mailto = c->parametres.substr(pos,suiv-pos);
                *web << " <a href=\"" << mailto << "\">" << mailto << " </a>" << std::endl;
                continue;
            }
            *web << c->parametres.substr(pos,suiv-pos) << std::endl;
        }
        *web << "</p>" << std::endl;
        return;
    }

    if (c->name.name == "friend") {
        end = c->parametres.size();
        pos  = extraire_token_delimateur_blanc(&suiv,c->parametres,end,0);
        pos2 = extraire_token_delimateur_blanc(&suiv2,c->parametres,end,suiv);
        if (pos == -1)
            return;
        if (chercher_motif(c->parametres,"@",&posaro,suiv,pos))
            mailto = c->parametres.substr(pos,suiv-pos);
        else ami = c->parametres.substr(pos,suiv-pos);
        if (pos2 == -1) {
            if (mailto.size() > 0) {
                *web << "<p class=\"ami\">" << std::endl;
                *web << "friend: <a href=\"mailto:" << mailto << "\">" << mailto << " </a>" << std::endl;
                *web << "</p>" << std::endl;
            }
            else {
                *web << "<p class=\"ami\">" << std::endl;
                *web << "friend: " << ami << std::endl;
                *web << "</p>" << std::endl;
            }
            return;
        }
        if (chercher_motif(c->parametres,"@",&posaro,suiv2,pos2))
            mailto = c->parametres.substr(pos2,suiv2-pos2);
        else ami = c->parametres.substr(pos2,suiv2-pos2);
        *web << "<p class=\"ami\">" << std::endl;
        *web << "friend: <a href=\"mailto:" << mailto << "\">" << ami << " </a>" << std::endl;
        *web << "</p>" << std::endl;
        return;
    }

    if (c->name.name == "relates") {
        //cout << " AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA " << " c->parametres = " << c->parametres << endl;
        /// on regarde si ce relates est un lien vers un document externe à la documentation.
        end = c->parametres.size();
        pos  = extraire_token_delimateur_blanc(&suiv,c->parametres,end,0);
        if (pos == -1 )
            return;
        if (chercher_motif(c->parametres,"@",&posaro,suiv,pos)) {
            mailto = c->parametres.substr(pos,suiv-pos);
            *web << " <a href=\"mailto:" << mailto << "\">" << mailto << " </a>" << std::endl;
            return;
        }

        if (isURL(mailto,c->parametres,suiv,pos)) {
            *web << " <a href=\"" << mailto << "\">" << mailto << " </a>" << std::endl;
            return;
        }
        ami = c->parametres;
        cut_space(ami);
        mailto = suffix(mailto);
        if (mailto.size()>0) {
            *web << linkHTML( ptr_parent->reference(), ami, ami) << std::endl;
        }

        /// A ce niveau, on peut supposer que la chaine parametre correspond à un objet (i.e. classe, struct,fonction,exemple,tutoriel,etc...  du projet.
        //cout << " BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB " << " n = " << n << endl;
        ///ptr_t = ptr_list_target->isPrincipalName( c->parametres );
        ptr_t = ptr_list_target->isName( c->parametres );
        //cerr << " ptr_t = " << ptr_t << endl;
        //cerr << " c->parametres = " << c->parametres << endl;
        if (ptr_t != NULL) {
            //cerr << " ptr_t->name = " << ptr_t->name.name << endl;
            *web << linkHTML( ptr_parent->reference(), ptr_t->reference(), c->parametres ) << std::endl;
        }
        return;
    }
}

void VisitorCommentItem_toHTML :: function_at_CommentItemList( CommentItemList* c ) {

    int i,j,n,m,nb_ref;

    *web << "<div class=\"liste\">" << std::endl;
    *web << "<ul> " << std::endl;
    n = c->txt.size();
    if (n>0) nb_ref = c->nb_espace[0];
    for(i=0;i<n;i++) {
        if (c->nb_espace[i] > nb_ref ) {
            nb_ref = c->nb_espace[i];
            *web << "<ul>" << std::endl;
        }
        if (c->nb_espace[i] < nb_ref ) {
            nb_ref = c->nb_espace[i];
            *web << "</ul>" << std::endl;
        }
        *web << "<li>" << text2HTML( c->txt[i],ptr_parent,ptr_list_target ) << "</li>" << std::endl;
    }
    *web << "</ul>" << std::endl;
    *web << "</div>" << std::endl;
}

void VisitorCommentItem_toHTML :: function_at_CommentItemSection( CommentItemSection* c ) {

    string stmp;
    stringstream ss;

    ss << c->order+1;
    stmp = "h" + ss.str() + ">";
    *web << "<" + stmp << text2HTML( c->titre,ptr_parent,ptr_list_target ) << "</" << stmp  << std::endl;
}

void VisitorCommentItem_toHTML :: function_at_CommentItemTable( CommentItemTable* c ) {

    int i,j,n,m;

    n = c->tableau.size();
    if (n>0)
        m = c->tableau[0].size();
    else
        m = 0;
    *web << "<div class=\"tableau\">" << std::endl;
    *web << "<table>" << std::endl;
    *web << "<caption>" << std::endl;
    *web << text2HTML( c->titre,ptr_parent,ptr_list_target ) << std::endl;
    *web << "</caption>" << std::endl;

    for(i=0;i<n;i++) {
        *web << "    <tr>" << std::endl;
        for(j=0;j<m;j++) {
            *web << "        <td>" << std::endl;
            *web << text2HTML( c->tableau[i][j],ptr_parent,ptr_list_target ) << std::endl;
            *web << "        </td>" << std::endl;
        }
        *web << "    </tr>" << std::endl;
    }
    *web << "</table>" << std::endl;
    *web << "</div>" << std::endl;
}

void VisitorCommentItem_toHTML :: function_at_CommentItemTxt( CommentItemTxt* c ) {

    int i,n;

    *web << "<p class=\"texte_documentation\">" << std::endl;
    n = c->txt.size();
    if ( not( n ) ) {
        *web << "</p>" << std::endl;
        return;
    }
    if ( c->txt[0].size() )
        *web << text2HTML( c->txt[0],ptr_parent,ptr_list_target );
    
    for( i = 1; i < n; i++ ) {
        if ( c->txt[i].size() )
            *web << "<br /> " <<  text2HTML( c->txt[i],ptr_parent,ptr_list_target ); //<< std::endl ;
    }
    *web << "</p>" << std::endl;

}


/*
void VisitorCommentItem_toHTML :: function_at_CommentItemExample( CommentItemExample* c ) {


    VisitorCommentItem_toHTML vivi( web,ptr_list_target );
    int i,n;

    *web << "<p class=\"example\">" << std::endl;
    n = c->items.size();
    for(i=0;i<n;i++) {
        c->items[i]->execute_function( &vivi );
    }
    *web << "</p>" << std::endl;

}
*/

void VisitorCommentItem_toHTML :: function_at_CommentItemLaTex( CommentItemLaTex* c ) {

    string stmp;
    string stmp2;
    stringstream ss;
    // code pour créer l'image du source LaTex
    //cout << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << c->reference() << endl;
    ofstream texfile( c->reference().c_str() );
    texfile << "\\documentclass[11pt,a4paper]{article}" << std::endl;
    texfile << "%***mise en page***" << std::endl;
    texfile << "\\setlength{\\textwidth}{17cm} \\setlength{\\textheight}{25cm}" << std::endl;
    texfile << "\\setlength{\\oddsidemargin}{-5.5mm}" << std::endl;
    texfile << "\\setlength{\\evensidemargin}{0pt} \\setlength{\\marginparwidth}{1cm}" << std::endl;
    texfile << "\\setlength{\\headheight}{13pt} \\setlength{\\topmargin}{-30pt}" << std::endl;
    texfile << "\\setlength{\\footskip}{26pt} \\setlength{\\headsep}{13pt}" << std::endl;
    texfile << std::endl;
    texfile << "%***package***" << std::endl;
    texfile << "\\usepackage{amsmath,amscd,amssymb}" << std::endl;
    texfile << "\\pagestyle{empty}" << std::endl;
    texfile << "\\usepackage[T1]{fontenc}" << std::endl;
    texfile << "\\usepackage{graphics}" << std::endl;
    texfile << "\\usepackage{epic}" << std::endl;
    texfile << std::endl;
    texfile << "\\usepackage[french]{babel}" << std::endl;
    texfile << "\\usepackage[utf8]{inputenc}" << std::endl;
    texfile << std::endl;
    texfile << "%*** Environnement ***" << std::endl;
    texfile << "\\newtheorem{myth}{Théorème}" << std::endl;
    texfile << "\\newtheorem{myprop}{Proposition}" << std::endl;
    texfile << "\\newtheorem{mylem}{Lemme}" << std::endl;
    texfile << "\\newtheorem{mycoro}{Corollaire}" << std::endl;
    texfile << std::endl;
    texfile << "%*** Macros ***" << std::endl;
    texfile << "\\newcommand{\\ineg}{\\leqslant}" << std::endl;
    texfile << "\\newcommand{\\sueg}{\\geqslant}" << std::endl;
    texfile << "\\newcommand{\\cqfd}{\\begin{flushright} $\\blacksquare$ \\end{flushright} }" << std::endl;
    texfile << "\\newcommand{\\Rp}{ [ \\, 0 \\, ; \\, +\\infty \\, [}" << std::endl;
    texfile << "\\newcommand{\\Rpe}{ ] \\, 0 \\, ; \\, +\\infty \\, [}" << std::endl;
    texfile << "\\newcommand{\\R}{ \\mathbb{R}  }" << std::endl;
    texfile << std::endl;
    texfile << "\\begin{document}" << std::endl;
    texfile << "\\pagestyle{empty}" << std::endl;
    
    /// ancien en-tête
//     texfile << "\\documentclass{article}\n";
//     texfile << "\\usepackage[latin1]{inputenc}\n";
//     texfile << "\\usepackage{graphicx}\n";
//     texfile << "\\usepackage{amsmath}\n";
//     texfile << "\\begin{document}\n";
//     texfile << "\\pagestyle{empty}\n";
    texfile << c->txt << std::endl;
    texfile << "\\end{document}" << std::endl;
    texfile.close();
    ostringstream command;
    stmp = c->reference();
    stmp2 = enleve_suffix( stmp );
    //ss.str("");
    //ss << c->id;
    //stmp = c->name.name + "_" + ss.str();
    stmp = directory( stmp );
    if ( c->multipage == "multipage" )
        command  << "latex -output-directory " << stmp << " -interaction=batchmode " << c->reference() <<  " && dvips -o ";
    else
        command  << "latex -output-directory " << stmp << " -interaction=batchmode " << c->reference() <<  " && dvips -O0in,11in -E -o ";
    
    //command  << "latex -output-directory " << stmp << " -interaction=batchmode " << c->reference() <<  " && dvips -O0in,11in -o ";
    command << stmp2 << ".eps " << stmp2 << ".dvi && convert -antialias -append -density 128 " << stmp2 << ".eps " 
            << stmp2 << ".png && rm ";
    const char *ext[] = {".tex",".dvi",".eps",".aux",".log"};
    for(unsigned i = 1; i < 5; ++i ) command << " " << stmp2 << ext[i];
    //cout << " IIIIIIIIIIIIIIIIIIIIIIIIII command =|" << command.str() << "|===" << endl;
    system( command.str().c_str() );
    c->suffix_reference = "png";
    ///stmp = "mv " + 
    *web << "<div class=\"texte_latex\">" << std::endl;
    *web << linkImage(ptr_parent->reference(),c->reference(),"LaTeX") << std::endl;
    *web << "</div>" << std::endl;
}

void VisitorCommentItem_toHTML :: function_at_CommentItemVerbatim( CommentItemVerbatim* c ) {

    int i,n,m,j;

    n = c->txt.size();
    *web << "<div class=\"verbatim\">" << std::endl;
    *web << "<pre> " << std::endl;
    for(i=0;i<n;i++) {
        m = c->tabulation[i];
        for(j=0;j<m;j++)
            *web << '\t';
        *web << french2HTML( c->txt[i] ) << std::endl;
    }
    *web << "</pre>" << std::endl;
    *web << "</div>" << std::endl;
}






