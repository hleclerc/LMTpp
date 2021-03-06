#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include<iomanip>
#include<cstdlib>

#include<cmath>
#include"time.h"

using namespace std ;

#include "op.h"
#include "parameter.h"
#include "classe.h"
#include "struct.h"
#include "bloc.h"
#include "visitorbloc.h"
#include "visitorbloc_allclass.h"
#include "visitorbloc_namebaseclass.h"
#include "visitorbloc_getcaracteristicclass.h"
#include "visitorbloc_getcaracteristicstruct.h"
#include "visitorbloc_getcaracteristicfunction.h"
#include "util2html.h"
#include "token.h"
#include "templateparameter.h"
#include "listtarget.h"
//#include "visitorcommentitem_tohtml.h"


VisitorBloc_AllClass :: ~VisitorBloc_AllClass() {
}

void VisitorBloc_AllClass :: generate_stream_HTML_for_typedef( ofstream* f, Bloc* b, bool sommary ) {

    string stmp, stmp2,stmp3 ;
    int i,n,m,j ;

    n = b->listTypedef.size() ;
    if (n>0) {
        if (sommary) {
            *f <<  "<h1> typedef </h1> " << std::endl ;
            *f << "<div class=\"sommaire_typedef\">" << std::endl ;
            *f << "<ul>" << std::endl ;
            for(i=0;i<n;i++) {
                stmp = b->listTypedef[i]->type.name ;
                if ( ptr_list_target->isName( stmp ) != 0 )
                    stmp2 = linkHTML( stmp,"" ) ;
                else
                    stmp2 = french2HTML( stmp ) ;
                stmp = b->listTypedef[i]->nameVariable ;
                if (ptr_list_target->isName( stmp ) != 0 )
                    stmp3 = linkHTML( stmp,"" ) ;
                else
                    stmp3 = french2HTML( stmp ) ;
                *f << "<li> " << stmp2 << "  &#x21D4  " << stmp3 << " </li>"  << std::endl ;
            }
            *f << "</ul>" << std::endl ;
        }
        else {
            *f << "<div class=\"description_typedef\">" << std::endl ;
            *f << "<ul>" << std::endl ;
            for(i=0;i<n;i++) {
                m = b->listTypedef[i]->listTag.size() ;
                if (m>0) {
                    *f <<  "<li> <strong> typedef " ;
                    stmp = b->listTypedef[i]->type.name ;
                    if (ptr_list_target->isName( stmp ) != 0 )
                        stmp2 = linkHTML( stmp,"" ) ;
                    else
                        stmp2 = french2HTML( stmp ) ;
                    stmp = b->listTypedef[i]->nameVariable ;
                    if (ptr_list_target->isName( stmp ) != 0 )
                        stmp3 = linkHTML( stmp,"" ) ;
                    else
                        stmp3 = french2HTML( stmp ) ;
                    *f << stmp2 << " " << stmp3 << " " ;
                    *f << "</strong> </li>" << std::endl ;
                    for(j=0;j<m;j++) 
                        b->listTypedef[i]->listTag[j]->generate_pageHTML(f,ptr_list_target ) ;
                }
            }
            *f << "<ul>" << std::endl ;
            *f << "</div>" << std::endl ;
        }
    }
}

void VisitorBloc_AllClass :: generate_stream_HTML_for_class_or_struct( ofstream* f, Bloc* b, bool sommary ) {

    VisitorBloc_GetCaracteristicClass    visitor_caract_class ;
    VisitorBloc_GetCaracteristicStruct   visitor_caract_struct ;
    string stmp, stmp2, stmp3 ;
    int i,n,m,j ;

    n = b->list_subType_function.size() ;
    if (n>0) {
        if (sommary) {
            *f <<  "<h1> sous-classe ou sous-struct </h1> " << std::endl ;
            *f << "<div class=\"sommaire_structure\">" << std::endl ;
            *f << "<ul>" << std::endl ;
            for(i=0;i<n;i++) {
                b->list_subType_function[i]->execute_function( &visitor_caract_class ) ;
                b->list_subType_function[i]->execute_function( &visitor_caract_struct ) ;
                if (visitor_caract_class.enphase || visitor_caract_struct.enphase ) {
                    *f << "<li> " << b->list_subType_function[i]->portee + " " ;
                    m = b->list_subType_function[i]->listTemplateParameter.size() ;
                    if (m>0) {
                        *f << " <strong> template </strong> &lt; " ;
                        for(j=0;j<m;j++) {
                            *f << " <strong> " << b->list_subType_function[i]->listTemplateParameter[j]->type << " </strong> " ;
                            stmp = b->list_subType_function[i]->listTemplateParameter[j]->name ;
                            if (ptr_list_target->isName( stmp ) != 0 )
                                stmp2 = linkHTML( stmp,"" ) ;
                            else
                                stmp2 = french2HTML( stmp ) ;
                            if (j != m-1)
                                *f << stmp2 << "," ;
                            else
                                *f << stmp2 << " &gt; " ;
                        }
                    }
                    if (visitor_caract_class.enphase)
                        stmp3 = " class " ;
                    else
                        stmp3 = " struct " ;
                    *f << " <strong>" << stmp3 << "</strong> " << link_fragmentHTML( b->list_subType_function[i]->name.name ) <<  " </li>" << std::endl ;
                }
            }
            *f << "</ul>" << std::endl ;
            *f << "</div>" << std::endl ;
        }
        else {
            *f << "<div class=\"description_typedef\">" << std::endl ;
            *f << "<ul>" << std::endl ;
            for(i=0;i<n;i++) {
                b->list_subType_function[i]->execute_function( &visitor_caract_class ) ;
                b->list_subType_function[i]->execute_function( &visitor_caract_struct ) ;
                if (visitor_caract_class.enphase || visitor_caract_struct.enphase ) {
                    *f << "<li> <strong> " << b->list_subType_function[i]->portee + " " ;
                    m = b->list_subType_function[i]->listTemplateParameter.size() ;
                    if (m>0) {
                        *f << " template &lt; " ;
                        for(j=0;j<m;j++) {
                            *f << " " << b->list_subType_function[i]->listTemplateParameter[j]->type << " " ;
                            stmp = b->list_subType_function[i]->listTemplateParameter[j]->name ;
                            if (ptr_list_target->isName( stmp ) != 0 )
                                stmp2 = linkHTML( stmp,"" ) ;
                            else
                                stmp2 = french2HTML( stmp ) ;
                            if (j != m-1)
                                *f << stmp2 << "," ;
                            else
                                *f << stmp2 << " &gt; " ;
                        }
                    }
                    *f << " class " << ancreHTML( b->list_subType_function[i]->name.name ) <<  " </strong> </li>" << std::endl ;
                    m = b->list_subType_function[i]->listTag.size() ;
                    for(j=0;j<m;j++) 
                        b->list_subType_function[i]->listTag[j]->generate_pageHTML(f,ptr_list_target ) ;
                }
            }
            *f << "</ul>" << std::endl ;
            *f << "</div>" << std::endl ;
        }
    }
}

void VisitorBloc_AllClass :: generate_stream_HTML_for_method( ofstream* f, Bloc* b, bool sommary ) {

    VisitorBloc_GetCaracteristicFunction visitor_caract_function ;
    int n,i,m,j ;
    string stmp ;
    string stmp2 ;
    string stmp3 ;
    ListParameter* ptr_listParameter ;


    n = b->list_subType_function.size() ;
    if (n>0) {
        if (sommary) {
            *f <<  "<h1> m&eacutethodes </h1> " << std::endl ;
            *f << "<div class=\"sommaire_method\">" << std::endl ;
            *f << "<ul>" << std::endl ;
            for(i=0;i<n;i++) {
                b->list_subType_function[i]->execute_function( &visitor_caract_function ) ;
                if (visitor_caract_function.enphase) {
                    *f << "<li> " << b->list_subType_function[i]->portee + " " ;
                    m = b->list_subType_function[i]->listTemplateParameter.size() ;
                    if (m>0) {
                        *f << " <strong> template </strong> &lt; " ;
                        for(j=0;j<m;j++) {
                            *f << " <strong> " << b->list_subType_function[i]->listTemplateParameter[j]->type << " </strong> " ;
                            stmp = b->list_subType_function[i]->listTemplateParameter[j]->name ;
                            //if (ptr_VisitorBloc_NameBaseClass->isNameBaseClass( stmp ))
                            if (ptr_list_target->isName( stmp ) != 0 )
                                stmp2 = linkHTML( stmp,"" ) ;
                            else
                                stmp2 = french2HTML( stmp ) ;
                            if (j != m-1)
                                *f << stmp2 << "," ;
                            else
                                *f << stmp2 << " &gt; " ;
                        }
                    }
                    stmp = (*visitor_caract_function.ptr_returnType).name ;
                    if (ptr_list_target->isName( stmp ) != 0 )
                        stmp2 = linkHTML( stmp,"" ) ;
                    else
                        stmp2 = french2HTML( stmp ) ;
                    *f << stmp2 << "   " ;
                    stmp = b->list_subType_function[i]->name.name ;
                    *f << link_fragmentHTML( stmp ) << " ( " ;
                    ptr_listParameter = visitor_caract_function.ptr_listParameter ;
                    m = (*ptr_listParameter).size() ;
                    for(j=0;j<m;j++) {
                        stmp = (*ptr_listParameter)[j]->type.name ;
                        if (ptr_list_target->isName( stmp ) != 0 )
                            stmp2 = linkHTML( stmp,"" ) ;
                        else
                            stmp2 = french2HTML( stmp ) ;
                        *f << " <strong> " <<  (*ptr_listParameter)[j]->listAttribut << " " << stmp2 << " </strong> " ;
                        *f << (*ptr_listParameter)[j]->nameVariable ;
                        stmp = (*ptr_listParameter)[j]->defaultType ;
                        if (stmp.size() > 0 ) {
                            *f << " = " << french2HTML( stmp ) << " " ;
                        }
                        if (j != m-1)
                            *f << ", " ;
                        else
                            *f << " ) " ;
                    }
                    if (m == 0)
                        *f << " ) " ;
                    stmp = *visitor_caract_function.ptr_listAttribut ;
                    *f << " <strong> " << stmp << " </strong> ; </li>" << std::endl ;
                }
            }
            *f << "</ul>" << std::endl ;
            *f << "</div>" << std::endl ;
        }
        else {
            *f << "<div class=\"description_method\">" << std::endl ;
            *f << "<ul>" << std::endl ;
            for(i=0;i<n;i++) {
                b->list_subType_function[i]->execute_function( &visitor_caract_function ) ;
                if (visitor_caract_function.enphase) {
                    *f << "<li> <strong> " << b->list_subType_function[i]->portee + " " ;
                    m = b->list_subType_function[i]->listTemplateParameter.size() ;
                    if (m>0) {
                        *f << " template  &lt; " ;
                        for(j=0;j<m;j++) {
                            *f << " " << b->list_subType_function[i]->listTemplateParameter[j]->type << " " ;
                            stmp = b->list_subType_function[i]->listTemplateParameter[j]->name ;
                            //if (ptr_VisitorBloc_NameBaseClass->isNameBaseClass( stmp ))
                            if (ptr_list_target->isName( stmp ) != 0 )
                                stmp2 = linkHTML( stmp,"" ) ;
                            else
                                stmp2 = french2HTML( stmp ) ;
                            if (j != m-1)
                                *f << stmp2 << "," ;
                            else
                                *f << stmp2 << " &gt; " ;
                        }
                    }
                    stmp = (*visitor_caract_function.ptr_returnType).name ;
                    if (ptr_list_target->isName( stmp ) != 0 )
                        stmp2 = linkHTML( stmp,"" ) ;
                    else
                        stmp2 = french2HTML( stmp ) ;
                    *f << stmp2 << "   " ;
                    stmp = b->list_subType_function[i]->name.name ;
                    *f << ancreHTML( stmp ) << " ( " ;
                    ptr_listParameter = visitor_caract_function.ptr_listParameter ;
                    m = (*ptr_listParameter).size() ;
                    for(j=0;j<m;j++) {
                        stmp = (*ptr_listParameter)[j]->type.name ;
                        if (ptr_list_target->isName( stmp ) != 0 )
                            stmp2 = linkHTML( stmp,"" ) ;
                        else
                            stmp2 = french2HTML( stmp ) ;
                        *f << " " <<  (*ptr_listParameter)[j]->listAttribut << " " << stmp2 << " " ;
                        *f << (*ptr_listParameter)[j]->nameVariable ;
                        stmp = (*ptr_listParameter)[j]->defaultType ;
                        if (stmp.size() > 0 ) {
                            *f << " = " << french2HTML( stmp ) << " " ;
                        }
                        if (j != m-1)
                            *f << ", " ;
                        else
                            *f << " ) " ;
                    }
                    if (m == 0)
                        *f << " ) " ;
                    stmp = *visitor_caract_function.ptr_listAttribut ;
                    *f << " " << stmp << " ; </strong> </li>" << std::endl ;
                    m = b->list_subType_function[i]->listTag.size() ;
                    for(j=0;j<m;j++) 
                        b->list_subType_function[i]->listTag[j]->generate_pageHTML(f,ptr_list_target ) ;
                }
            }
            *f << "</ul>" << std::endl ;
            *f << "</div>" << std::endl ;
        }
    }
}

void VisitorBloc_AllClass :: generate_stream_HTML_for_attribut( ofstream* f, Bloc* b, bool sommary ) {

    int i,n,j,m ;
    string stmp ;
    string stmp2 ;


    n = b->listMember.size() ;
    if (n>0) {
        if (sommary) {
            *f <<  "<h1> attributs </h1> " << std::endl ;
            *f << "<div class=\"sommaire_attribut\">" << std::endl ;
            *f << "<ul>" << std::endl ;
                for(i=0;i<n;i++) {
                    stmp = b->listMember[i]->listAttribut ;
                    *f << "<li> " << " <strong> " << stmp << " </strong> " ;
                    stmp = b->listMember[i]->type.name ;
                    if (ptr_list_target->isName( stmp ) != 0 )
                        stmp2 = linkHTML( stmp,"" ) ;
                    else
                        stmp2 = french2HTML( stmp ) ;
                    *f << stmp2 << "  " ;
                    stmp = b->listMember[i]->nameVariable ;
                    *f << link_fragmentHTML( stmp ) << " " ;
                    if ( b->listMember[i]->defaultType.size() >0 ) {
                        stmp = b->listMember[i]->defaultType ;
                        *f << " = " <<french2HTML( stmp ) << " ; </li> " << std::endl ;
                    } else
                        *f << " ; </li> " << std::endl ;

                }
            *f << "</ul>" << std::endl ;
            *f << "</div>" << std::endl ;
        }
        else {
            *f << "<div class=\"description_attribut\">" << std::endl ;
            *f << "<ul>" << std::endl ;
                for(i=0;i<n;i++) {
                    stmp = b->listMember[i]->listAttribut ;
                    *f << "<li> <strong> " << stmp << " " ;
                    stmp = b->listMember[i]->type.name ;
                    if (ptr_list_target->isName( stmp ) != 0 )
                        stmp2 = linkHTML( stmp,"" ) ;
                    else
                        stmp2 = french2HTML( stmp ) ;
                    *f << stmp2 << "  " ;
                    stmp = b->listMember[i]->nameVariable ;
                    *f << ancreHTML( stmp ) << " " ;
                    if ( b->listMember[i]->defaultType.size() >0 ) {
                        stmp = b->listMember[i]->defaultType ;
                        *f << " = " << french2HTML( stmp ) << " ; </strong> </li> " << std::endl ;
                    } else
                        *f << " ; </strong> </li> " << std::endl ;
                    m = b->listMember[i]->listTag.size() ;
                    for(j=0;j<m;j++) 
                        b->listMember[i]->listTag[j]->generate_pageHTML(f,ptr_list_target ) ;
                }
            *f << "</ul>" << std::endl ;
            *f << "</div>" << std::endl ;
        }
    }
}

void VisitorBloc_AllClass :: generate_page_HTML_for_class_or_struct( const string& type_block, Bloc* b,const string& path, const string& name_file ) {

    int n,i,m,j ;
    string stmp ;
    string stmp2 ;
    string stmp3 ;
    VisitorBloc_GetCaracteristicClass    visitor_caract_class ;
    VisitorBloc_GetCaracteristicStruct   visitor_caract_struct ;
    ListParameter* ptr_listParameter ;

    stmp = path + name_file ;
    ofstream pageWeb( stmp.c_str() ,ios::out);

    stmp = type_block + ' ' + b->name.name ;

    generate_header(pageWeb, stmp ) ;

    pageWeb << "<hr />" << std::endl ;
    
    pageWeb << "<div class=\"table_des_matieres_structure\">" << std::endl ;
    
    /// namespace
    if (b->_namespace.size() > 0) {
        pageWeb << "<h1>  namespace is </h1> " << b->_namespace << std::endl ;
    }

    /// les héritages
    b->execute_function( &visitor_caract_class ) ;
    b->execute_function( &visitor_caract_struct ) ;
    if (visitor_caract_class.enphase) {
        ptr_listParameter = visitor_caract_class.ptr_listHerited ;
        n = (*ptr_listParameter).size() ;
    } else {
        if (visitor_caract_struct.enphase) {
            ptr_listParameter = visitor_caract_struct.ptr_listHerited ;
            n = (*ptr_listParameter).size() ;
        } else
            n = 0 ;
    }

    if (n>0) {
        pageWeb <<  "<h1> H&eacuterite de </h1> " << std::endl ;
        pageWeb << "<ul>" << std::endl ;
        for(i=0;i<n;i++) {
            stmp = (*ptr_listParameter)[i]->type.name ;
            //if (ptr_VisitorBloc_NameBaseClass->isNameBaseClass( stmp ))
            if (ptr_list_target->isName( stmp ) != 0 )
                stmp2 = linkHTML( stmp, "" ) ;
            else
                stmp2 = french2HTML( stmp ) ;
            pageWeb << "<li> <strong>" << (*ptr_listParameter)[i]->listAttribut << " </strong>" << "   " <<  stmp2 << " </li>" << std::endl ;
        }
        pageWeb << "</ul>" << std::endl ;
    }

    /// les paramètres template

    n = b->listTemplateParameter.size() ;
    if (n>0) {
        pageWeb <<  "<h1> Param&egravetre template </h1> " << std::endl ;
        pageWeb << "<ul>" << std::endl ;
        for(i=0;i<n;i++) {
            pageWeb << "<li> <strong> " << b->listTemplateParameter[i]->type << " </strong>" << " " ;
            stmp = b->listTemplateParameter[i]->name ;
            //if (ptr_VisitorBloc_NameBaseClass->isNameBaseClass( stmp ))
            if (ptr_list_target->isName( stmp ) != 0 )
                stmp2 = linkHTML( stmp,"" ) ;
            else
                stmp2 = french2HTML( stmp ) ;
            pageWeb << stmp2 << " " ;
            stmp = b->listTemplateParameter[i]->defaultType ;
            if (stmp.size() >0) {
                //if (ptr_VisitorBloc_NameBaseClass->isNameBaseClass( stmp ))
                if (ptr_list_target->isName( stmp ) != 0 )
                    stmp3 = linkHTML( stmp,"" ) ;
                else
                    stmp3 = french2HTML( stmp ) ;
                 pageWeb << " = " << stmp3 << " </li>"  << std::endl ;
            }
            else {
                pageWeb << " </li>"  << std::endl ;
            }
        }
        pageWeb << "</ul>" << std::endl ;
    }

    /// typedef de la classe
    generate_stream_HTML_for_typedef( &pageWeb,b,true ) ;

    /// sous-type classe de la classe
    generate_stream_HTML_for_class_or_struct( &pageWeb,b,true ) ;

    /// sous-type function de la classe
    generate_stream_HTML_for_method( &pageWeb,b,true ) ;

    /// membre de la classe
    generate_stream_HTML_for_attribut( &pageWeb,b,true) ;


    pageWeb << "<br>" << std::endl ;
    pageWeb << "<hr />" << std::endl ;
    pageWeb <<  "<h1> Description </h1> " << std::endl ;
    pageWeb << "<div class=\"description_structure\">" << std::endl ;

    n = b->listTag.size() ;
    if (n>0) {
        for(i=0;i<n;i++) {
            b->listTag[i]->generate_pageHTML(&pageWeb,ptr_list_target ) ;
        }
    }
    pageWeb << "</div>" ;
    /// typedef de la classe
    generate_stream_HTML_for_typedef( &pageWeb,b,false ) ;

    /// sous-classe ou sous-struct de la classe
    generate_stream_HTML_for_class_or_struct( &pageWeb,b,false ) ;

    /// methodes de la classe
    generate_stream_HTML_for_method( &pageWeb,b,false ) ;

    /// membre de la classe
    generate_stream_HTML_for_attribut( &pageWeb,b,false) ;

    pageWeb << "<hr />" << std::endl ;
    for(i=0;i<7;i++)
        pageWeb << "<br>" << std::endl ;
    pageWeb << "</body>" << std::endl ;
    pageWeb << "</html>" << std::endl ;
    pageWeb <<std::endl;
}

void VisitorBloc_AllClass :: function_at_Bloc( Bloc* b ) {
}

void VisitorBloc_AllClass :: function_at_Classe( Classe* c ) {

    string stmp ;
    Target* pt ;

    pt = ptr_list_target->isName( c->name.name ) ;
    if (pt != 0 ) {
        stmp = "html/" + pt->path ;
        generate_page_HTML_for_class_or_struct( "class",c,stmp,pt->reference() ) ;
    }
}

void VisitorBloc_AllClass :: function_at_Struct( Struct* s ) {

    string stmp ;
    Target* pt ;

    pt = ptr_list_target->isName( s->name.name ) ;
    if (pt != 0 ) {
        stmp = "html/" + pt->path ;
        generate_page_HTML_for_class_or_struct( "struct",s,stmp,pt->reference() ) ;
    }
}

void VisitorBloc_AllClass :: function_at_Function( Function* f ) {

    int j,m ;
    Target* pl ;
    string stmp ;
    string stmp2 ;
    string stmp3 ;
    string path ;

    pl = ptr_list_target->isName( f->name.name ) ;
    if (pl != 0 ) {
        path = "html/" + pl->path + pl->reference() ;
        ofstream pageWeb( path.c_str() ,ios::out);
        stmp = "fonction " + french2HTML( f->name.name ) ;

        generate_header(pageWeb, stmp ) ;

        pageWeb << "<div class=\"fonction\">" << std::endl ;
        pageWeb << f->portee << " " ;
        m = f->listTemplateParameter.size() ;
        if (m>0) {
            pageWeb << " <strong> template </strong> &lt; " ;
            for(j=0;j<m;j++) {
                pageWeb << " <strong> " << f->listTemplateParameter[j]->type << " </strong> " ;
                stmp = f->listTemplateParameter[j]->name ;
                if ( (pl = ptr_list_target->isName( stmp )) != 0 ) {
                    stmp3 = "../" + pl->path ;
                    stmp2 = linkHTML( stmp,stmp3 ) ;
                }
                else
                    stmp2 = french2HTML( stmp ) ;
                if (j != m-1)
                    pageWeb << stmp2 << "," ;
                else
                    pageWeb << stmp2 << " &gt; " ;
            }
        }
        stmp = f->returnType.name ;
        if ((pl = ptr_list_target->isName( stmp )) != 0 ) {
            stmp3 = "../" + pl->path ;
            stmp2 = linkHTML( stmp,stmp3 ) ;
        }
        else
            stmp2 = french2HTML( stmp ) ;
        pageWeb << stmp2 << "   " ;
        pageWeb << french2HTML( f->name.name ) << " ( " ;
        m = f->listParameter.size() ;
        for(j=0;j<m;j++) {
            stmp = f->listParameter[j]->type.name ;
            if ( (pl = ptr_list_target->isName( stmp )) != 0 ) {
                stmp3 = "../" + pl->path ;
                stmp2 = linkHTML( stmp,stmp3 ) ;
            }
            else
                stmp2 = french2HTML( stmp ) ;
            pageWeb << " <strong> " <<  f->listParameter[j]->listAttribut << " " << stmp2 << " </strong> " ;
            pageWeb << f->listParameter[j]->nameVariable ;
            stmp = f->listParameter[j]->defaultType ;
            if (stmp.size() > 0 )
                pageWeb << " = " << french2HTML( stmp ) << " " ;
            if (j != m-1)
                pageWeb << ", " ;
            else
                pageWeb << " ) " ;
            }
        if (m == 0)
            pageWeb << " ) " ;
        pageWeb << " <strong> " << f->listAttribut << " </strong> ; </li>" << std::endl ;
        pageWeb << "</div>" << std::endl ;
        
        m = f->listTag.size() ;
        for(j=0;j<m;j++) {
            f->listTag[j]->generate_pageHTML(&pageWeb,ptr_list_target ) ;
        }
    }
}











