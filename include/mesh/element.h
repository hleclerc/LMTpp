//
// C++ Interface: element
//
// Description:
//
//
// Author: Hugo LECLERC <leclerc@lmt.ens-cachan.fr>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LMTELEMENT_H
#define LMTELEMENT_H

#include "meshdata.h"
#include "nbchildrenelement.h"

namespace LMT {

///
template<class TNode_>
class ElementAncestor {
public:
    typedef TNode_ TNode;
    typedef typename TNode_::T T;
    static const unsigned dim = TNode::dim;

    virtual unsigned nb_nodes_virtual() const = 0;
    virtual unsigned nb_var_inter_virtual() const = 0;
    virtual TNode *node_virtual(unsigned i) = 0;
    virtual const TNode *node_virtual(unsigned i) const = 0;
    virtual void set_node_virtual(unsigned i,TNode *n) = 0;
    virtual const char *name_virtual() const = 0;
    virtual const char *can_directly_be_represented_by_virtual() = 0;
    virtual unsigned num_in_elem_list_virtual() const = 0;
    virtual T measure_virtual() const = 0;

    virtual typename TNode::Pvec sample_normal_virtual() const = 0;
    virtual typename TNode::Pvec sample_tangent_virtual() const = 0;

    virtual void set_field( const std::string field_name, T value ) = 0;
    virtual void set_field( const std::string field_name, Vec<T,1> value ) = 0;
    virtual void set_field( const std::string field_name, Vec<T,2> value ) = 0;
    virtual void set_field( const std::string field_name, Vec<T,3> value ) = 0;
    virtual void set_field( const std::string field_name, Vec<T,4> value ) = 0;
    virtual void set_field( const std::string field_name, Vec<T,5> value ) = 0;
    virtual void set_field( const std::string field_name, Vec<T,6> value ) = 0;
    virtual void set_field( const std::string field_name, Mat<T,Gen<1, 1> > value ) = 0;
    virtual void set_field( const std::string field_name, Mat<T,Gen<2, 2> > value ) = 0;
    virtual void set_field( const std::string field_name, Mat<T,Gen<3, 3> > value ) = 0;
    virtual void set_field( const std::string field_name, Mat<T,Gen<4, 4> > value ) = 0;
    virtual void set_field( const std::string field_name, Mat<T,Gen<5, 5> > value ) = 0;
    virtual void set_field( const std::string field_name, Mat<T,Gen<6, 6> > value ) = 0;

    virtual T        get_field( const std::string field_name, StructForType<T        > ) const = 0;
    virtual Vec<T,1> get_field( const std::string field_name, StructForType<Vec<T,1> > ) const = 0;
    virtual Vec<T,2> get_field( const std::string field_name, StructForType<Vec<T,2> > ) const = 0;
    virtual Vec<T,3> get_field( const std::string field_name, StructForType<Vec<T,3> > ) const = 0;
    virtual Vec<T,4> get_field( const std::string field_name, StructForType<Vec<T,4> > ) const = 0;
    virtual Vec<T,5> get_field( const std::string field_name, StructForType<Vec<T,5> > ) const = 0;
    virtual Vec<T,6> get_field( const std::string field_name, StructForType<Vec<T,6> > ) const = 0;
    virtual Mat<T,Gen<1, 1> > get_field( const std::string field_name, StructForType<Mat<T,Gen<1, 1> > > ) const = 0;
    virtual Mat<T,Gen<2, 2> > get_field( const std::string field_name, StructForType<Mat<T,Gen<2, 2> > > ) const = 0;
    virtual Mat<T,Gen<3, 3> > get_field( const std::string field_name, StructForType<Mat<T,Gen<3, 3> > > ) const = 0;
    virtual Mat<T,Gen<4, 4> > get_field( const std::string field_name, StructForType<Mat<T,Gen<4, 4> > > ) const = 0;
    virtual Mat<T,Gen<5, 5> > get_field( const std::string field_name, StructForType<Mat<T,Gen<5, 5> > > ) const = 0;
    virtual Mat<T,Gen<6, 6> > get_field( const std::string field_name, StructForType<Mat<T,Gen<6, 6> > > ) const = 0;
    virtual Mat<T,Sym<1> > get_field( const std::string field_name, StructForType<Mat<T,Sym<1> > > ) const = 0;
    virtual Mat<T,Sym<2> > get_field( const std::string field_name, StructForType<Mat<T,Sym<2> > > ) const = 0;
    virtual Mat<T,Sym<3> > get_field( const std::string field_name, StructForType<Mat<T,Sym<3> > > ) const = 0;

    unsigned number;
    unsigned absolute_number;
    unsigned group;

    ElementAncestor()
    {
        group = 0;
    }
    virtual ~ElementAncestor() {}
};

template<class TNode>
std::ostream &operator<<(std::ostream &os,const ElementAncestor<TNode> &ea) {
    os << ea.name_virtual();
    for(unsigned i=0;i<ea.nb_nodes_virtual();++i)
        os << " " << ea.node_virtual(i)->number_in_original_mesh();
    return os;
}

/*!
\generic_comment Element

    C'est la classe parent de tous les éléments géométriques (Triangle, Tetra, ...) servant à construire les maillages. Elle hérite de la classe "générique" TData qui contient les informations et surtout de \a ElementAncestor qui permet le polymorphisme dynamique sur des méthodes générales et lestockage de l'attribut number (pour l'indexation dans le maillage original).

    \a Element et ses spécialisations ont cinq paramètres template :
        * NameElem est la classe du type d'élément (e.g. Triangle_6,...)
        * NameBehavior est la classe contenant les informations sur le comportement de l'élément.
        * TNode est le type de noeud (rappelons que TNode contient au moins sa position et d'autres données si nécessaires).
        * TData est la classe stockant les données propres à un élément. Pour simplifier leur accès, element hérite aussi de TData.
        * num_in_elem_list est le numéro de la sous liste du vecteur hétérogène qui contient l'élément.

    \keyword Maillage/Elément
    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/

template<class NameElem_,class NameBehavior,class TNode_,class TData,unsigned num_in_elem_list_>
class Element : public TData, public ElementAncestor<TNode_> {
public:
    typedef NameElem_ NameElem;
    typedef TNode_ TNode;
    typedef typename TNode::T T;
    typedef typename TNode::Pvec Pvec;
    typedef ElementAncestor<TNode> EA;
    typedef Element TClass;
    typedef Element* TClassPtr;
    static const unsigned nb_nodes = NameElem::nb_nodes;
    static const unsigned nb_var_inter = NameElem::nb_var_inter;
    static const char *name() {
        return NameElem::name();
    }
    static const char *can_directly_be_represented_by() {
        return NameElem::can_directly_be_represented_by();
    }
    typedef NameElem NE;
    typedef NameBehavior BE;
    typedef TData TD;
    static const unsigned num_in_elem_list = num_in_elem_list_;

    TNode *node(unsigned i) {
        return nodes[i];
    }
    const TNode *node(unsigned i) const {
        return nodes[i];
    }
    virtual void set_node_virtual(unsigned i,TNode *n) {
        nodes[i] = n;
    }

    Pvec pos(unsigned i) const { return nodes[i]->pos; }

    // virtual
    virtual unsigned nb_nodes_virtual() const {
        return nb_nodes;
    }
    virtual unsigned nb_var_inter_virtual() const {
        return nb_var_inter;
    }
    virtual TNode *node_virtual(unsigned i) {
        return node(i);
    }
    virtual const TNode *node_virtual(unsigned i) const {
        return node(i);
    }
    virtual const char *name_virtual() const {
        return name();
    }
    virtual const char *can_directly_be_represented_by_virtual() {
        return can_directly_be_represented_by();
    }
    virtual unsigned num_in_elem_list_virtual() const {
        return num_in_elem_list;
    }

    virtual typename TNode::Pvec sample_normal_virtual() const {
        return sample_normal(*this);
    }
    virtual typename TNode::Pvec sample_tangent_virtual() const {
        return sample_tangent(*this);
    }
    virtual T measure_virtual() const { return measure( *this ); }

    virtual ~Element() {}

    virtual void set_field( const std::string field_name, T value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Vec<T,1> value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Vec<T,2> value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Vec<T,3> value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Vec<T,4> value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Vec<T,5> value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Vec<T,6> value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Mat<T,Gen<1, 1> > value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Mat<T,Gen<2, 2> > value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Mat<T,Gen<3, 3> > value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Mat<T,Gen<4, 4> > value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Mat<T,Gen<5, 5> > value ) { TData::dm_data_set_field( field_name, value ); }
    virtual void set_field( const std::string field_name, Mat<T,Gen<6, 6> > value ) { TData::dm_data_set_field( field_name, value ); }

    virtual T        get_field( const std::string field_name, StructForType<T        > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Vec<T,1> get_field( const std::string field_name, StructForType<Vec<T,1> > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Vec<T,2> get_field( const std::string field_name, StructForType<Vec<T,2> > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Vec<T,3> get_field( const std::string field_name, StructForType<Vec<T,3> > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Vec<T,4> get_field( const std::string field_name, StructForType<Vec<T,4> > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Vec<T,5> get_field( const std::string field_name, StructForType<Vec<T,5> > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Vec<T,6> get_field( const std::string field_name, StructForType<Vec<T,6> > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Gen<1, 1> > get_field( const std::string field_name, StructForType<Mat<T,Gen<1, 1> > > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Gen<2, 2> > get_field( const std::string field_name, StructForType<Mat<T,Gen<2, 2> > > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Gen<3, 3> > get_field( const std::string field_name, StructForType<Mat<T,Gen<3, 3> > > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Gen<4, 4> > get_field( const std::string field_name, StructForType<Mat<T,Gen<4, 4> > > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Gen<5, 5> > get_field( const std::string field_name, StructForType<Mat<T,Gen<5, 5> > > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Gen<6, 6> > get_field( const std::string field_name, StructForType<Mat<T,Gen<6, 6> > > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Sym<1> > get_field( const std::string field_name, StructForType<Mat<T,Sym<1> > > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Sym<2> > get_field( const std::string field_name, StructForType<Mat<T,Sym<2> > > e ) const { return TData::dm_data_get_field( field_name, e ); }
    virtual Mat<T,Sym<3> > get_field( const std::string field_name, StructForType<Mat<T,Sym<3> > > e ) const { return TData::dm_data_get_field( field_name, e ); }

    ///
    TNode *nodes[nb_nodes];
    /// nb fields
    static const unsigned nb_params = DM::NbFields<TData>::res;
};

///
template<class NameBehavior,class TN,class TData,unsigned num_in_elem_list>
class Element<void,NameBehavior,TN,TData,num_in_elem_list> {
public:
    typedef void TClass;
    typedef void TClassPtr;
    typedef void NE;
};

/// to be specialized for each geometric element
template<class T1,class T2,class T3,unsigned nvi_to_subs>
void append_skin_elements(const T1 &,const T2 &,const T3 &,const Number<nvi_to_subs> &n) {}

/*!
    Cette fonction retourne l'isobarycentre des noeuds de l'élément.

    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/
template<class NameElem,class NameBehavior,class TNode,class TData,unsigned num_in_elem_list>
typename TNode::Pvec center(const Element<NameElem,NameBehavior,TNode,TData,num_in_elem_list> &e) {
    typename TNode::Pvec res = 0.0;
    for(unsigned i=0;i<NameElem::nb_nodes;++i)
        res += e.node(i)->pos;
    return res / NameElem::nb_nodes;
}

/*!
\generic_comment center
    Cette fonction retourne l'isobarycentre des noeuds de l'élément.

    \keyword Maillage/Elément/Opération
    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/

/*!
    Cette fonction retourne l'isobarycentre des noeuds de l'élément.

    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/
template<class TNode>
typename TNode::Pvec center(const ElementAncestor<TNode> &e) {
    typename TNode::Pvec res = 0.0;
    for(unsigned i=0;i<e.nb_nodes_virtual();++i)
        res += e.node_virtual(i)->pos;
    return res / e.nb_nodes_virtual();
}

/*!
    A faire
    A finir de programmer

    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/
template<class TE>
typename TE::Pvec sample_normal(const TE &e) {
    assert(0); // not implemented
}

/*!
    A faire


    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/
struct EquElem {
    template<class TE1,class TE2>
    bool operator()(const TE1 &e1,const TE2 &e2) const {
        if ( AreSameType<typename TE1::NE,typename TE2::NE>::res == false )
            return false;
        unsigned nb_eq = 0;
        for(unsigned i=0;i<TE1::nb_nodes;++i)
            for(unsigned j=0;j<TE2::nb_nodes;++j)
                nb_eq += ( length( e1.node(i)->pos - e2.node(j)->pos ) < 1e-6 );
        return ( nb_eq==TE1::nb_nodes );
    }
};

/*!
    A faire


    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/
struct DistBetweenElemCenter {
    template<class P1,class P2,class T3=void,class T4=void> struct ReturnType { typedef typename TypePromote<Plus,typename P1::T,typename P2::T>::T T; };
    template<class P1,class P2> typename TypePromote<Plus,typename P1::T,typename P2::T>::T operator()(const P1 &n1,const P2 &n2) const {
        return length(center(n2)-center(n1));
    }
};

/*!
    Trouve les variables d'interpolation correspondant à la position pos.
    On suppose que var_inter n'est pas initialisé.

    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
  */
template<class TE,class Pvec,class TVI> void get_var_inter(const TE &elem,const Pvec &pos,TVI &var_inter,typename TE::T criterium) {
    Vec<Vec<typename TE::T,TE::dim>,TE::nb_nodes> pos_nodes;
    for(unsigned i=0;i<TE::nb_nodes;++i)
        pos_nodes[i] = elem.pos(i);

    get_var_inter_linear( typename TE::NE(), pos_nodes, pos, var_inter );
    Vec<typename TE::T,TE::nb_var_inter> old_var_inter = var_inter;
    while ( true ) {
        get_var_inter( typename TE::NE(), pos_nodes, pos, var_inter );
        if ( length( old_var_inter - var_inter ) < criterium )
            break;
        old_var_inter = var_inter;
    }
}

/** contains res -> true if eq to find var!inter from pos is non linear (recquires iterations) */
template<class NE> struct ElemVarInterFromPosNonLinear { };

/*!
    La fonction renvoie vrai si pos est à l'intérieur de l'élément avec une tolérance tol.


    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/
template<class TE,class Pvec> bool pos_is_inside( const TE &elem,const Pvec &pos,typename TE::T criterium=1e-4,typename TE::T tol=1e-4) {
    Vec<typename TE::T,TE::nb_var_inter> var_inter;
    get_var_inter(elem,pos,var_inter,criterium);
    return var_inter_is_inside( typename TE::NE(), var_inter, tol );
}


/*!
    A faire


    \friend raphael.pasquier@lmt.ens-cachan.fr
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/
template<class TE> typename TE::Pvec sample_tangent( const TE &e ) {
    assert( 0 ); // non défini
    return typename TE::Pvec(typename TE::T(0));
}

};

#endif