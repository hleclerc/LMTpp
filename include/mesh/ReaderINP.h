#ifndef READER_INP_H
#define READER_INP_H

#include <map>
#include <limits>

namespace LMT {

/// remplace dans str les caractères c par subs.
void replace_char( std::string& str, char c, char subs) {
    size_t i = 0,i2;
    while ( (i2 = str.find( c, i ) ) != std::string::npos ) {
        str[ i2 ] = subs;
        i = i2;
    }
}

/// retourne le nombre de caractères c à partir de la position start
unsigned compter_caractere( const std::string& s, char c, int start = 0 ) {

    unsigned l,co,p ;

    l = s.size() ;
    co = 0 ;
    for( p = start ; p < l; p++ )
        if (s[ p ] == c ) co++ ;
    return co;
}

/*!
  cette fonction récupère la valeur v d'une expression de la forme param1=v ou param2=v de la chaine str sous forme d'une chaine de caractère.
 */
std::string value( const std::string& str, const char* param1, const char* param2, const char* descripteur = " ,\n" ) {
    std::string stmp;
    size_t pos, pos2;
    char* pchar;

    if ( ( pos = str.find( param1 ) ) != std::string::npos ) {
        pos += strlen( param1 );
        pchar = strpbrk( str.c_str() + pos, descripteur );
        if ( pchar ) pos2 = pchar - str.c_str(); else pos2 = str.size();
        stmp = str.substr( pos, pos2 - pos );
        return stmp;
    } else if ( ( pos = str.find( param2 ) ) != std::string::npos ) {
        pos += strlen( param2 );
        pchar = strpbrk( str.c_str() + pos, descripteur );
        if ( pchar ) pos2 = pchar - str.c_str(); else pos2 = str.size();
        stmp = str.substr( pos, pos2 - pos );
        return stmp;
    }
    return stmp;
}

std::string jump( std::ifstream& is, const char* descripteur) {
    std::string str,res;
    while(true) {
        str.clear();
        getline( is,str );
        if ( !is.good() )
            break;
        if ( str.find( descripteur ) == std::string::npos )
            res += str + "\n" ;
        else
            return res;
    }
    return res;
}

/*!
  cette fonction récupère le texte juqu'à atteindre l'un des descripteurs de la liste descrpteur[] (le dernier de cette liste devant être de longueur nulle i.e. "").
*/
std::string jump( std::ifstream& is, const char* descripteur[], std::string& line ) {
    std::string str,res;
    int c;

    line.clear();
    while( true ) {
        str.clear();
        getline( is , str );
        if ( !is.good() )
            break;
        c = 0;
        while( true ) {
            if ( strlen( descripteur[ c ] ) == 0 )
                break;
            if ( str.find( descripteur[ c ] ) != std::string::npos ) {
                line = str;
                return res;
            }
            c++;
        }
        res += str + "\n" ;
    }
    return res;
}

/*!

    Actuellement le lecteur INP ne connaît que les types : 
        C3D8R   <=> Hexa
        C3D8I   <=> Hexa
        C3D8    <=> Hexa
        C3D4    <=> Tetra
        S3R     <=> Triangle
        S3      <=> Triangle
        S4R     <=> Quad
        R3D4    <=> Quad
        M3D4    <=> Quad
        R3D3    <=> Triangle
        B31     <=> Bar
        SpringA <=> Bar
        SPRING1 <=> Bar
        CONN3D2 <=> Bar
        C3D6    <=> Prism
        ROTARYI <=> NodalElement
        MASS    <=> NodalElement
   Pour en ajouter, il faut le faire dans la méthode MatchElement_INP_LMTpp::add_element_at(), et le constructeur de ElementSet.

    doc interne
    
    ReaderINP contient des structures quasi identiques aux structures de INP, comme par exemple Element, Orientation, SolidSection, etc...
    Parmi ces structures, celles jouant le rôle de conteneur comme par exemple ElementSet contiennent des tableaux d'entiers, ces entiers correspondant à ceux utilisés par INP pour numéroter les objets. 
    Pour ensuite accéder à l'élément ou le noeud d'indice cet entier, on utilise des map du genre map<int, Object > .
    Plus précisément, ReaderINP contient :
    \code C/C++
        map<int, TNode*> map_num_node;
        map<int, MatchElement_INP_LMTpp > map_num_element;
        map<string, NodeSet*> map_NodeSet;
        map<string, ElementSet*> map_ElementSet;
        map<string, Orientation*> map_Orientation;
        map<string, SolidSection*> map_SolidSection;
        map<string, Material*> map_Material;
        map<string, Contact_Pair*> map_Conctact_Pair;
        map<string, Surface*> map_Surface;

*/
template<class TM> 
struct ReaderINP {
    typedef typename TM::Pvec Pvec;
    typedef typename TM::TNode TNode;
    typedef typename TM::TNode::T T;
    typedef typename TM::MA::EA EA;
    static const unsigned dim = TM::dim;
    typedef enum {
        STATUS_IGNORED              = 0,
        STATUS_NODE                 = 1,
        STATUS_ELEMENT              = 2,
        STATUS_NSET                 = 3,
        STATUS_ELSET                = 4,
        STATUS_ORIENTATION          = 5,
        STATUS_SOLID_SECTION        = 6,
        STATUS_MATERIAL             = 7,
        STATUS_STEP                 = 8,
        STATUS_CONTACT_PAIR         = 9,
//         STATUS_SURFACE_INTERACTION  = 10,
        STATUS_SURFACE              = 11
    } Status_ID;
    
    /// double : nécessair et suffisant ; dimension déterminée à l'éxécution
    /// cet objet ne sert qu' à enregistrer la position d'un noeud
    struct NodeInp {
        NodeInp() {}
        NodeInp( const Vec<double> &posi ) : pos( posi ) {}
        
        /// malheureusement le conversion est doublée par un constructeur très générique...
        template< class T, int _s >
        operator Vec<T,_s>() const {
            Vec<T,_s> ret;
            if ( ret.size() != pos.size() )
                std::cerr << "WARNING ReaderINP : error to convert the position of node." << std::endl;
            for( unsigned i = 0; i < ret.size(); ++i ) 
                ret[ i ] = pos[ i ];
        }
        
        template< class T, int _s >
        void copy_to( Vec<T,_s> &v ) const {
            if ( v.size() != pos.size() )
                std::cerr << "WARNING ReaderINP : error to convert the position of node." << std::endl;
            for( unsigned i = 0; i < v.size(); ++i ) 
                v[ i ] = pos[ i ];
        }
        
        Vec<double> pos; 
    };
    
    //typedef map<unsigned, TNode*> Map_num_node;
    typedef std::map<unsigned, NodeInp> Map_num_node;
    
     struct MatchElement_INP_LMTpp {
        MatchElement_INP_LMTpp() : ptrEA( NULL ) { }
        MatchElement_INP_LMTpp( const char* n, EA* p, Vec<unsigned> &lnode ) : name( n ), ptrEA( p ), list_node( lnode ) {}

        /*!
            Cette méthode ajoute à "mesh" l'élément concerné. 
            Pour des raisons de performance on a besoin du conteneur "match_inode_inp_lmtpp" qui fait la correspondance entre l'indice du noeud dans le fichier Inp d'Abaqus et l'indice du noeud de "mesh" dans la liste node_list. Son utilisé est d'éviter les doublons de noeuds dans le maillage LMT++ sans utiliser leurs coordonnées. 
            On a choisi un map et pas un simple vector ou Vec car la méthode find() de map est en complexité O( ln( N ) ) et non O( N ) comme les conteneurs précédents.
        */
        template<class TMESH>
        typename TMESH::MA::EA* add_element_at( TMESH &mesh, std::map< unsigned, unsigned > &match_inode_inp_lmtpp, Map_num_node &mapNode ) const {
            //typedef typename TM::MA::EA EALocal;
            typedef typename TMESH::TNode TNodeLocal;
            typedef typename TMESH::Pvec PvecLocal;
            typedef typename TMESH::TNode::T TLocal;
            
            Vec< TNodeLocal* > vnlocal;
            PvecLocal v;
            typename std::map< unsigned, unsigned >::iterator it;
            
            vnlocal.resize( list_node.size() );

            for( unsigned j = 0; j < list_node.size(); j++ ) {
                
                it = match_inode_inp_lmtpp.find( list_node[ j ] );
                if ( it != match_inode_inp_lmtpp.end() ) {
                    vnlocal[ j ] = &mesh.node_list[ it->second ];    
                } else {
                    mapNode[ list_node[ j ] ].copy_to( v );
                    vnlocal[ j ] = mesh.add_node( v );
                    match_inode_inp_lmtpp[ list_node[ j ] ] = match_inode_inp_lmtpp.size() - 1; 
                }
            }

            if ( name == "Tetra" ) {
                permutation_if_jac_neg ( Tetra(), vnlocal.ptr() );
                return mesh.add_element( Tetra(), DefaultBehavior(), vnlocal.ptr() );
            }
            if ( name == "Hexa") {
                permutation_if_jac_neg ( Hexa(), vnlocal.ptr() );
                return mesh.add_element( Hexa(), DefaultBehavior(), vnlocal.ptr() );
            }
            if ( name == "Triangle") {
                permutation_if_jac_neg ( Triangle(), vnlocal.ptr() );
                return mesh.add_element( Triangle(),DefaultBehavior(), vnlocal.ptr() );
            }
            if ( name == "Quad") {
                permutation_if_jac_neg ( Quad(), vnlocal.ptr() );
                return mesh.add_element( Quad(),DefaultBehavior(), vnlocal.ptr() );
            }
            if ( name == "Bar")
                return mesh.add_element( Bar(),DefaultBehavior(), vnlocal.ptr() );
            if ( name == "NodalElement")
                return mesh.add_element( NodalElement(),DefaultBehavior(), vnlocal.ptr() ); 
            std::cerr << "WARNING ReaderINP : the element " << name << " does not append by MatchElement_INP_LMTpp. TODO" << std::endl; 
            return NULL;
        }
        
        /*!
            cette méthode retourne dans "index" la liste des indices INP des noeuds de la surface d' identifiant idFace de l'élément courant. 
        
        */
        void get_index_node_of_surface( Vec<unsigned> &index, unsigned idFace ) const {
         
            index.resize( 0 );
            if ( name == "Hexa") {
                switch( idFace ) {
                    case 1 : 
                        index.resize( 4 );
                        index[ 0 ] = list_node[ 0 ];
                        index[ 1 ] = list_node[ 1 ];
                        index[ 2 ] = list_node[ 2 ];
                        index[ 3 ] = list_node[ 3 ];
                        return;
                    case 2 : 
                        index.resize( 4 );
                        index[ 0 ] = list_node[ 4 ];
                        index[ 1 ] = list_node[ 5 ];
                        index[ 2 ] = list_node[ 6 ];
                        index[ 3 ] = list_node[ 7 ];
                        return;
                    case 3 : 
                        index.resize( 4 );
                        index[ 0 ] = list_node[ 0 ];
                        index[ 1 ] = list_node[ 1 ];
                        index[ 2 ] = list_node[ 5 ];
                        index[ 3 ] = list_node[ 4 ];
                        return;
                    case 4 :
                        index.resize( 4 );
                        index[ 0 ] = list_node[ 1 ];
                        index[ 1 ] = list_node[ 2 ];
                        index[ 2 ] = list_node[ 6 ];
                        index[ 3 ] = list_node[ 5 ];
                        return;
                    case 5 : 
                        index.resize( 4 );
                        index[ 0 ] = list_node[ 2 ];
                        index[ 1 ] = list_node[ 3 ];
                        index[ 2 ] = list_node[ 7 ];
                        index[ 3 ] = list_node[ 6 ];
                        return;
                    case 6 :
                        index.resize( 4 );
                        index[ 0 ] = list_node[ 0 ];
                        index[ 1 ] = list_node[ 3 ];
                        index[ 2 ] = list_node[ 7 ];
                        index[ 3 ] = list_node[ 4 ]; 
                        return;
                    default : 
                        std::cerr << "WARNING ReaderINP : bad id face of Hexa" << std::endl;
                        return;                        
                }
            }
            std::cerr << "WARNING ReaderINP : the surface element of type " << name << " is not unknown by MatchElement_INP_LMTpp. TODO" << std::endl;
        }
        
        template<class TMESH>
        void add_surface_element_at( TMESH &mesh, std::map< unsigned, unsigned > &match_inode_inp_lmtpp, Map_num_node &mapNode, unsigned idFace ) const {
            typedef typename TMESH::TNode TNodeLocal;
            typedef typename TMESH::Pvec PvecLocal;
            Vec< TNodeLocal* > vnlocal;
            Vec<unsigned> index;
            PvecLocal v;
            typename std::map< unsigned, unsigned >::iterator it;
            
            get_index_node_of_surface( index, idFace );
            
            if ( name == "Hexa") {
                if ( index.size() == 4 ) {
                    
                    vnlocal.resize( 4 );
                    for( unsigned j = 0; j < index.size(); ++j ) {                    
                        it = match_inode_inp_lmtpp.find( index[ j ] );  /// le noeud est-il déjà dans le "mesh" ?
                        if ( it != match_inode_inp_lmtpp.end() ) {
                            vnlocal[ j ] = &mesh.node_list[ it->second ];    
                        } else {
                            mapNode[ index[ j ] ].copy_to( v );
                            vnlocal[ j ] = mesh.add_node( v );
                            match_inode_inp_lmtpp[ index[ j ] ] = match_inode_inp_lmtpp.size() - 1; 
                        }
                    }
//                     for( unsigned i = 0; i < index.size(); ++i ) {
//                         mapNode[ index[ i ] ].copy_to( v );
//                         vnlocal[ i ] = mesh.add_node( v );
//                     }
                    permutation_if_jac_neg ( Quad(), vnlocal.ptr() );
                    mesh.add_element( Quad(), DefaultBehavior(), vnlocal.ptr() );
                    return;
                }
            }
            std::cerr << "WARNING ReaderINP : the surface element of type " << name << " does not append by MatchElement_INP_LMTpp. TODO" << std::endl; 
        }
        
        std::string name; /// nom LMT++ de l'élément ( e.g. Triangle, Hexa )
        EA* ptrEA; /// pointeur sur l'élément du maillage entier
        //Vec<TNode*> list_node; /// la liste des noeuds de l'élément dans le maillage entier
        Vec<unsigned> list_node; /// la value de l'entier correspond à l'entrée de Map_num_nodeInp de ReaderINP
    };

    typedef std::map<unsigned, MatchElement_INP_LMTpp > Map_num_element;
    //typedef map<int,EA*> Map_num_element;
    //typedef map<int, void*> Map_num_element;
    
    /*!
    Ce code souhaite représenter la méthode de stockage des identifiants entiers des noeuds ou des éléments dans Abaqus.
    Dans le format Inp de Abaqus, un Elset ( ou un NSet ) peut contenir soit :
        * une liste d'indices toute simple soit, 
        * une liste de triplets d'entiers  start, end, step qui signifie que le Elset contient tous les indices de la forme start + i * step où i parcourt les entiers positifs ou nul tout en vérifiant start + i * step <= end ( attention le end est toujours compris pour un step égal à un ).    
    
    
    */
    template<class T = unsigned>
    struct ClusterList {
        struct iterator {
            unsigned i, h;
            const ClusterList *p;
            
            iterator( const ClusterList* pa = NULL ) : i( 0 ), h( 0 ), p( pa ) {}
            
            void operator++() {            
                if ( p->isGenerate ) {
                    unsigned id = p->data[ 3 * i ] + ( h + 1 ) * p->data[ 3 * i + 2 ];
                    if ( id <= p->data[ 3 * i + 1 ] )
                        ++h;
                    else {
                        ++i; h = 0;
                    }
                } else {
                    ++i;
                }
            }
            
            unsigned operator*() const {
                if ( p->isGenerate )
                    return p->data[ 3 * i ] + h * p->data[ 3 * i + 2 ];  
                else
                    return p->data[ i ];            
            }
            
            bool operator!=( const iterator &it ) const {
                return ( it.p != p ) or ( it.i != i ) or ( it.h != h );  
            }
            
            void display() const {
                std::cout << "p = " << p << " i = " << i << " h = " << h << std::endl;
            }
        };
        
        iterator begin() const { 
            iterator iter( this );
            iter.i = 0;
            iter.h = 0; 
            return iter;
        }
    
        iterator end() const {
            iterator iter( this );
            if ( isGenerate )
                iter.i = data.size() / 3;
                
            else
                iter.i = data.size();
            return iter;
        }
        
        unsigned nb_elements() const {
            unsigned sum = 0;
            if ( isGenerate ) {
                for( unsigned i = 0; i < data.size(); i += 3 ) {
                    sum += ( 1 + data[ i + 1 ] - data[ i ]) / data[ i + 2 ];
                }
                return sum ; 
            } else {
                return data.size();
            }
        }
        
        bool isGenerate;
        Vec<T> data;
    };

    struct NodeSet : public ClusterList<> {
        NodeSet() { this->isGenerate = false; withCoordinate = true;}
        NodeSet( const std::string& str ) {
            if ((str.find("GENERATE") != std::string::npos) or (str.find("generate") != std::string::npos))
                this->isGenerate = true;
            else
                this->isGenerate = false;
            withCoordinate = false;
        }
        
        void read( TM &m, std::string& str, Map_num_node &map_num_nodeInp ) {
            double p;
            int number;
            NodeInp node;

            replace_char( str, ',', ' ' );
            std::istringstream iss( str );
            if ( withCoordinate ) {
                iss >> number;
                /// lecture des coordonnées
                while ( true ) {
                    iss >> p;
                    node.pos.push_back( p );
                    if ( iss.eof() )
                        break;
                }
                
                map_num_nodeInp[ number ] = node;
                this->data.push_back( number );
            } else {
                while( true ) {
                    iss >> number;
                    if ( iss.eof() )
                        break;
                    this->data.push_back( number );
                }
            }
        }
        
        void display() const {
            std::cout << " isGenerate = " << this->isGenerate << std::endl;
            std::cout << " withCoordinate = " << withCoordinate << std::endl;
            typename NodeSet::iterator it;
            for( it = this->begin(); it != this->end(); ++it )
                std::cout << *it << " ";
            std::cout << std::endl;
        }
        
        bool withCoordinate;
    };
    
    struct ElementSet : public ClusterList<> {
        ElementSet( const std::string& str ) {
            if ((str.find( "GENERATE" ) != std::string::npos) or (str.find( "generate" ) != std::string::npos))
                this->isGenerate = true;
            else
                this->isGenerate = false;
 
            type = value( str, "TYPE=", "type=" );
            /// ref : liste des éléments Abaqus http://muscadet.lmt.ens-cachan.fr:2080/v6.7/books/usb/default.htm
            /// page : Output Variable and Element Indexes.Abaqus/Standard ElementSet Index
            if ( type.size() ) {
                if ( type == "C3D8R"   ) { type = "Hexa"; nb_nodes = 8; return; }
                if ( type == "C3D8I"   ) { type = "Hexa"; nb_nodes = 8; return; }
                if ( type == "C3D8"    ) { type = "Hexa"; nb_nodes = 8; return; }
                if ( type == "C3D4"    ) { type = "Tetra"; nb_nodes = 4; return; }
                if ( type == "S3R"     ) { type = "Triangle"; nb_nodes = 3; return; }
                if ( type == "S3"      ) { type = "Triangle"; nb_nodes = 3; return; }
                if ( type == "S4R"     ) { type = "Quad"; nb_nodes = 4; return; }
                if ( type == "R3D4"    ) { type = "Quad"; nb_nodes = 4; return; } /// dans R^3
                if ( type == "M3D4"    ) { type = "Quad"; nb_nodes = 4; return; } /// dans R^3
                if ( type == "R3D3"    ) { type = "Triangle"; nb_nodes = 3; return; } /// dans R^3
                if ( type == "B31"     ) { type = "Bar"; nb_nodes = 2; return; } /// dans R^3
                if ( type == "SpringA" ) { type = "Bar"; nb_nodes = 2; return; }
                if ( type == "SPRING1" ) { type = "Bar"; nb_nodes = 2; return; } /// à vérifier sur un exemple  
                if ( type == "CONN3D2" ) { type = "Bar"; nb_nodes = 2; return; } 
                if ( type == "C3D6"    ) { type = "Prism"; nb_nodes = 6; return; }
                if ( type == "ROTARYI" ) { type = "NodalElement"; nb_nodes = 1; return; }
                if ( type == "MASS"    ) { type = "NodalElement"; nb_nodes = 1; return; }
            } else {
                nb_nodes = 0;
//                 if ( not ( isGenerate ) )
//                     std::std::cerr << "Error: the type of element \""<< type << "\" is unknown in \"" << str << "\"."<< std::std::endl;
            }
        }
        
        void read( TM &m, std::string& str, std::map< unsigned, unsigned > &match_inode_inp_lmtpp, Map_num_node& mapNode, Map_num_element& map_num_element ) {
            unsigned number,number2;
            Vec<unsigned> vninp;

            replace_char( str, ',', ' ' );
            std::istringstream s( str );
            s >> number;
            this->data.push_back( number );
            if ( type.size() ) {
                //vn.resize( nb_nodes );
                vninp.resize( nb_nodes );
                for ( unsigned i = 0; i < nb_nodes; i++ ) {
                    s >> number2;
                    //vn[ i ] = map_num_node[ number2 ];
                    vninp[ i ] = number2;
                }
                map_num_element[ number ] = MatchElement_INP_LMTpp( type.c_str(), NULL, vninp );
                map_num_element[ number ].ptrEA = map_num_element[ number ].add_element_at( m, match_inode_inp_lmtpp, mapNode );
            } else {
                while( true ) {
                    s >> number;
                    this->data.push_back( number );
                    if ( s.eof() )
                        break;
                }
                if ( this->data.back() == this->data[ this->data.size()-2]) /// A REVOIR ...  PROBLEME
                    this->data.pop_back();
            }
        }
        
        void display() const {
            std::cout << " NOMBRE D'ELEMENTS = " << this->nb_elements() << std::endl;
            typename ElementSet::iterator it;
            for( it = this->begin(); it != this->end(); ++it )
                std::cout << *it << " ";
            std::cout << std::endl;
        }
        
        unsigned nb_nodes;
        std::string type;
    };
    
    struct Orientation {
        Orientation( const std::string& str ) {
            std::string s;

            s = value( str, "SYSTEM=", "system=" );
            if ( ( s.size() == 0 ) or ( s == "R" ) )
                rectangular = true;
            else
                rectangular = false;
        }
        
        void read( std::string& str ) { 
            replace_char( str, ',', ' ' );
            std::istringstream iss( str );
            if ( rectangular ) {
                iss >> v1 >> v2;
            } else {
                std::cerr << "WARNING ReaderINP : TODO Orientation::cylindrical " << std::endl;
            }
        }
        
        void setProperty( EA* ptrEA ) const {
            ptrEA->set_field( std::string( "v1" ), v1 );
            ptrEA->set_field( std::string( "v2" ), v2 );
        }
        
        /// A revoir l'utilisation de Pvec ????
        Pvec v1, v2;
        bool rectangular; /// system = rectangular or cylindrical
    };
    
    struct Material_property {
        virtual void display() const {}
        virtual void setData( std::string& str ) {
            std::cerr << "WARNING ReaderINP : hum... you use Material_property::setData() " << std::endl;
        }
        virtual void setProperty( EA* pea ) const { 
            std::cerr << "WARNING ReaderINP : hum... you use Material_property::setProperty() " << std::endl;
        } 
    };
    
    struct Elastic_property : public Material_property {
        Elastic_property( const std::string& s ) { type = s;}
        
        virtual void display() const {
            std::cout << " type = " << type << std::endl;
            std::cout << " data = " ;
            for( unsigned i = 0; i < data.size() ;i++ )
                std::cout << data[ i ] << " ";
            std::cout << std::endl;
        }
        
        virtual void setData( std::string& str ) {
            replace_char( str, ',', ' ' );
            std::istringstream iss( str );
            if (type != "ISO") {
                data.resize( 9 );
                for( unsigned i = 0; i < 9; i++ ) 
                    iss >> data[i];
            } else {
                data.resize( 2 );
                for( unsigned i = 0 ; i < 2 ; i++ ) 
                    iss >> data[i];
            }
        }
        
        virtual void setProperty( EA* pea ) const { 
            if (type == "ISO") {
                pea->set_field( std::string( "elastic_modulus_1" ), data[ 0 ] );
                pea->set_field( std::string( "elastic_modulus_2" ), data[ 0 ] );
                pea->set_field( std::string( "elastic_modulus_3" ), data[ 0 ] );
                pea->set_field( std::string( "poisson_ratio_12" ), data[ 1 ] );
                pea->set_field( std::string( "poisson_ratio_13" ), data[ 1 ] );
                pea->set_field( std::string( "poisson_ratio_23" ), data[ 1 ] );
                double t = data[ 0 ] / ( 2 * ( 1 + data[ 1 ] ) ); 
                pea->set_field( std::string( "shear_modulus_12" ), t );
                pea->set_field( std::string( "shear_modulus_13" ), t );
                pea->set_field( std::string( "shear_modulus_23" ), t );
            } else {
                pea->set_field( std::string( "elastic_modulus_1" ), data[ 0 ] );
                pea->set_field( std::string( "elastic_modulus_2" ), data[ 1 ] );
                pea->set_field( std::string( "elastic_modulus_3" ), data[ 2 ] );
                pea->set_field( std::string( "poisson_ratio_12" ), data[ 3 ] );
                pea->set_field( std::string( "poisson_ratio_13" ), data[ 4 ] );
                pea->set_field( std::string( "poisson_ratio_23" ), data[ 5 ] );
                pea->set_field( std::string( "shear_modulus_12" ), data[ 6 ] );
                pea->set_field( std::string( "shear_modulus_13" ), data[ 7 ] );
                pea->set_field( std::string( "shear_modulus_23" ), data[ 8 ] );
            }
        }
        
        std::string type;
        Vec<double> data;
    };
    
    struct Material {
        typedef enum {
            OPTION_IGNORED       = 0,
            OPTION_DENSITY       = 1,
            OPTION_ELASTIC       = 2,
        } Option_material_ID;
        Material() { material_property = NULL; density = 0.;}
        ~Material() { if ( material_property ) delete material_property ; }
        void display() { 
            std::cout << " density =" << density << std::endl;
            std::cout << " property = " << std::endl;
            if ( material_property )
                material_property->display();
            else
                std::cout << " WARNING ReaderINP : not property..." << std::endl;
        }
        std::string parse( std::ifstream& is ) {
            std::string str,str2;
            unsigned c;
            Option_material_ID ctxte = OPTION_IGNORED;

            while( true ) {
                str.clear();
                getline( is, str );
                if ( !is.good() )
                    break;
                    
                for( c = 0; c < nb_principale_keyword; ++c )
                    if ( str.find( list_principale_keyword[ c ]) != std::string::npos )
                        return str;
                if ( str.size() == 0 )
                    continue;
                    
                if (str[ 0 ] == '*') {
                    if (str[ 1 ] == '*') { ctxte = OPTION_IGNORED; continue; }/// c'est un commentaire
                    if ((str.find ( "DENSITY", 1 ) == 1) or (str.find ( "Density", 1 ) == 1)) { ctxte = OPTION_DENSITY; continue; }
                    if ((str.find ( "ELASTIC", 1 ) == 1) or (str.find ( "Elastic", 1 ) == 1)) { 
                        ctxte = OPTION_ELASTIC; 
                        material_property = new Elastic_property( value( str, "TYPE=", "type=", ",\n" ) );
                        continue; 
                    }
                    ctxte = OPTION_IGNORED; /// na !
                    continue;
                }
                /// utilisation du contexte
                switch( ctxte ) {
                    case OPTION_DENSITY : density = atof( str.c_str() ); break;
                    case OPTION_ELASTIC : 
                        str2.clear();
                        getline( is, str2 );
                        if ( !is.good() )
                            return ""; /// je ne sais pas trop quoi renvoyer...
                        str += str2;
                        material_property->setData( str );
                        break;
                    case OPTION_IGNORED : break;
                }
            }
            return "";
        }
        
        double density;
        Material_property* material_property;
    };
    
    struct ContactPair {
        void display() const {
            std::cout << " name 1 is \"" << s_surface_1 << "\"" << std::endl;
            std::cout << " name 2 is \"" << s_surface_2 << "\"" << std::endl;
            std::cout << " data   is  |" << s_data << "|" << std::endl;
        }
        
        std::string parse( std::ifstream& is ) {
            std::string str;
            unsigned c;
            
            getline( is, str ); /// lecture des deux surfaces écrits sous la forme nom1, nom2
            char *pchar = strpbrk( str.c_str(), "," );
            int i;
            if ( pchar ) i = pchar - str.c_str(); else i = str.size();
            s_surface_1 = str.substr( 0, i );
            s_surface_2 = str.substr( i + 2 ); /// + 2 pour sauter le , et l'espace
            if ( !is.good() )
                    return "";
            while( true ) {
                str.clear();
                getline( is, str );
                if ( !is.good() )
                    break;
                for( c = 0; c < nb_keyword; ++c )
                    if ( str.find( list_keyword[ c ] ) != std::string::npos ) {
                        s_data += str + "\n"; /// pas super comme traitement ;-)
                        break;
                    }
                if ( c < nb_keyword ) 
                    continue;   
                for( c = 0; c < nb_principale_keyword; ++c )
                    if ( str.find( list_principale_keyword[ c ] ) != std::string::npos ) {
                        return str;
                    }
                s_data += str + "\n";
            }
            return "";
        }            
    
        std::string s_surface_1, s_surface_2, s_data;
        
        static const unsigned nb_keyword = 4;
        static const char* list_keyword[ nb_keyword ];
    };
    
    struct Surface {
        Surface( const std::string &str ) {
            std::string s_type = value( str, "TYPE=", "Type=" ); 
            if ( ( s_type == "ELEMENT" ) or ( s_type == "Element" ) )
                type = 0;
            else 
                type = 1; /// Node
        }
        void display() const {
            if ( type == 0 ) { 
                std::cout << "this type is ELEMENT" << std::endl; 
                for( unsigned i = 0; i < indice.size() ; ++i )
                    std::cout << " element " << indice[ i ] << " and id face = " << id_face[ i ] << std::endl;
            } else {
                std::cout << "this type is NODE" << std::endl;
                for( unsigned i = 0; i < indice.size() ; ++i )
                    std::cout << " node " << indice[ i ] << std::endl;
            }         
        }
        
        void read( std::string& str ) {
            unsigned number;
            unsigned p;
            
            replace_char( str, ',', ' ' );
            std::istringstream iss( str );
            iss >> number;
            indice.push_back( number );
            
            if ( type == 0 ) {
                p = str.find( 'S' );
                if ( p != std::string::npos ) 
                    id_face.push_back( str[ p + 1 ] - '0' );
                else {
                    std::cerr << "WARNING ReaderINP : ID face of Surface is unknown" << std::endl;
                    id_face.push_back( 0 );        
                }
            }
        }

        Vec<unsigned> indice; /// la value correspond à l'entrée dans la Map_num_node ou Map_num_nodeInp ou encore Map_num_element.
        Vec<unsigned> id_face; /// la valeur correspond à l'identifiant de face de Abaqus
        unsigned type; /// 0 <=> ELEMENT, 1 <=> NODE
    };
    
    struct SolidSection {
        SolidSection( const std::string& str ) { 
            s_material = value( str, "MATERIAL=", "material=" ); 
            s_orientation = value( str, "ORIENTATION=", "orientation=" ); 
            material = NULL;
            orientation = NULL;
        }
        void setData( Material* pma, Orientation* por ) { material = pma; orientation = por; }
        void display() {
            std::cout << " s_material    = ||" << s_material << "||" << std::endl;
            std::cout << " s_orientation = ||" << s_orientation << "||" << std::endl;
            if ( material )
                material->display();
            if ( orientation )
                orientation->display();
        }
        std::string s_material;
        std::string s_orientation;
        Material* material;
        Orientation* orientation;
    };
    
    void update_solidSection() {
        Material* pmat;
        Orientation* por;
        typename std::map< std::string, SolidSection* >::iterator it4;
        for( it4 = map_SolidSection.begin(); it4 != map_SolidSection.end(); it4++ )
            if ( it4->second ) {
                if ( it4->second->s_material.size() )
                    pmat = map_Material[ it4->second->s_material ];
                else
                    pmat = NULL;
                if (it4->second->s_orientation.size())
                    por = map_Orientation[ it4->second->s_orientation ];
                else
                    por = NULL;
                it4->second->setData( pmat, por ) ;
            }
    }
    
    ReaderINP() {}
    
    ReaderINP( TM &m, const char* filename) { parse( m, filename ); }
    
    ~ReaderINP() {
        typename std::map< std::string, ElementSet*>::iterator it;
        for( it = map_ElementSet.begin(); it != map_ElementSet.end(); it++) delete it->second;
        
        typename std::map< std::string, NodeSet*>::iterator it2;
        for( it2 = map_NodeSet.begin(); it2 != map_NodeSet.end(); it2++) delete it2->second;
        
        typename std::map< std::string, Orientation*>::iterator it3;
        for( it3 = map_Orientation.begin(); it3 != map_Orientation.end(); it3++) delete it3->second;
        
        typename std::map< std::string, SolidSection*>::iterator it4;
        for( it4 = map_SolidSection.begin(); it4 != map_SolidSection.end(); it4++) delete it4->second;
        
        typename std::map< std::string, Material*>::iterator it5;
        for( it5 = map_Material.begin(); it5 != map_Material.end(); it5++) delete it5->second;
        
        typename std::map< std::string, ContactPair*>::iterator it6;
        for( it6 = map_ConctactPair.begin(); it6 != map_ConctactPair.end(); it6++) delete it6->second;
        
        typename std::map< std::string, Surface*>::iterator it7;
        for( it7 = map_Surface.begin(); it7 != map_Surface.end(); it7++) delete it7->second;
    }
    
    static Status_ID setStatus( const std::string& str ) {
        if (str[1] == '*')                                                              { return STATUS_IGNORED; }/// c'est un commentaire
        if ((str.find ("Node",1) == 1) or (str.find ("NODE",1 ) == 1) )                 { return STATUS_NODE; }
        if ((str.find ("Element",1) == 1) or (str.find ("ELEMENT",1) == 1))             { return STATUS_ELEMENT; }
        if ((str.find ("NSET",1) == 1) or (str.find ("Nset",1) == 1))                   { return STATUS_NSET; }
        if ((str.find ("ELSET",1) == 1)  or (str.find ("Elset",1) == 1))                { return STATUS_ELSET; }
        if ((str.find ("ORIENTATION",1) == 1) or (str.find ("Orientation",1) == 1))     { return STATUS_ORIENTATION; }
        if ((str.find ("SOLID SECTION",1) == 1) or (str.find ("Solid Section",1) == 1)) { return STATUS_SOLID_SECTION; }
        if ((str.find ("MATERIAL",1) == 1) or (str.find ("Material",1) == 1))           { return STATUS_MATERIAL; }
        if ((str.find ("STEP",1) == 1) or (str.find ("Step",1) == 1))                   { return STATUS_STEP; }
        if ((str.find ("CONTACT PAIR",1) == 1) or (str.find ("Contact Pair",1) == 1))   { return STATUS_CONTACT_PAIR; }
        if ((str.find ("SURFACE",1) == 1) or (str.find ("Surface",1) == 1))             { return STATUS_SURFACE; }
        std::cerr << "WARNING ReaderINP : ignored option = " << value( str, "*", "*", ",\n") << std::endl;
        return STATUS_IGNORED; /// option non traitée
    }
    
    void parse( TM &m, const char* filename ) {
        std::string str, str2, name;
        std::map< unsigned, unsigned > match_inode_inp_lmtpp;
        unsigned n;
        Status_ID ctxte = STATUS_IGNORED;
        NodeSet* pns = NULL;
        ElementSet* pes = NULL;
        Orientation* por = NULL;
        SolidSection* pss = NULL;
        Material* pma = NULL;
        ContactPair* pcp = NULL;
        Surface* ps = NULL;

        str.reserve( 2048 );
        str2.reserve( 2048 );
        // ouverture du fichier
        std::ifstream is( filename );
        if ( ! is.is_open() )
            throw std::runtime_error( "opening of file INP has failed." );
        // état de l'automate
        while ( true ) {
            if ( ( ctxte != STATUS_MATERIAL ) and ( ctxte != STATUS_CONTACT_PAIR ) ) { /// Material et Contact Pair sont vus comme des conteneurs donc ils parsent eux-même le fichier et leur parseur rend la prochaine ligne à lire 
                str.clear();
                getline( is, str );
                if ( !is.good() )
                    break;
            }
            /// évaluation du contexte
            if ( str.size() == 0 )
                continue;
            if ( str[ 0 ] == '*' ) {
                ctxte = setStatus( str );
                switch( ctxte ) {
                    case STATUS_NODE          : pns  = map_NodeSet[ internal_name[ 0 ] ] = new NodeSet(); break;
                    case STATUS_ELEMENT       : pes  = map_ElementSet[ value( str, "ELSET=","elset=" ) ] = new ElementSet( str ); break;
                    case STATUS_NSET          : pns  = map_NodeSet[ value( str, "NSET=","nset=" ) ] = new NodeSet( str ); break;
                    case STATUS_ELSET         : pes  = map_ElementSet[ value( str, "ELSET=", "elset=" ) ] = new ElementSet( str ); break;
                    case STATUS_ORIENTATION   : por  = map_Orientation[ value( str, "NAME=", "name=" ) ] = new Orientation( str ); break;
                    case STATUS_SOLID_SECTION : pss  = map_SolidSection[ value( str, "ELSET=", "elset=" ) ] = new SolidSection( str ); break;
                    case STATUS_STEP          : str2 = jump( is, "*END STEP" ); break; /// STEP est aussi un "conteneur".
                    case STATUS_MATERIAL      : pma  = map_Material[ value( str, "NAME=", "name=" ) ] = new Material() ; 
                                                str  = pma->parse( is );
                                                //pma->display();
                                                break;
                    case STATUS_CONTACT_PAIR  : pcp  = map_ConctactPair[ value( str, "INTERACTION=", "Interaction=" ) ] = new ContactPair();
                                                str  = pcp->parse( is );
                                                //pcp->display();
                                                break;
                    case STATUS_SURFACE       : ps = map_Surface[ value( str, "NAME=", "Name=" ) ] = new Surface( str ); break;
                    case STATUS_IGNORED       : ; //std::cerr << "WARNING ReaderINP : STATUS_IGNORED line " << str << std::endl;  
                }
                continue;
            }
            /// utilisation du contexte
            switch( ctxte ) {
                case STATUS_NODE : case STATUS_NSET : 
                    pns->read( m, str, map_num_node );
                    continue;
                case STATUS_ELEMENT : case STATUS_ELSET :
                    /// malheureusement l'info de *ELEMENT est parfois mise sur deux lignes...
                    n = pes->nb_nodes;
                    if ( ( n > 0 ) and ( compter_caractere( str, ',' ) < n ) ) {
                        str2.clear();
                        getline ( is,str2 );
                        if ( !is.good() )
                            break;
                        str += str2;
                    }
                    pes->read( m, str, match_inode_inp_lmtpp, map_num_node, map_num_element );
                    continue;
                case STATUS_ORIENTATION :
                    /// malheureusement l'info est parfois mise sur deux lignes...
                    if (compter_caractere(str,',') == 5) {
                        str2.clear();
                        getline ( is, str2 );
                        if ( !is.good() )
                            break;
                        str += str2;
                    }
                    por->read( str );
                    continue;
                case STATUS_SURFACE :
                    ps->read( str );
                    continue;
                case STATUS_IGNORED : case STATUS_SOLID_SECTION : case STATUS_MATERIAL : case STATUS_STEP : case STATUS_CONTACT_PAIR : break;
            }
        }
        is.close();
        update_solidSection();
    }
    
    template<class _TNODE> 
    struct EgalityPos {
        bool operator()( _TNODE& n1, _TNODE& n2) const {return n1.pos == n2.pos; }
        
    };
     
    template<class TMESH>
    void create_mesh_by_elset( TMESH &mesh, const std::string &nameElSet ) {
        std::map< unsigned, unsigned > match_inode_inp_lmtpp;
        typename std::map< std::string, ElementSet*>::iterator it;

        it = map_ElementSet.find( nameElSet );
        if ( it != map_ElementSet.end() ) {
            ElementSet* elset = it->second;
            typename ElementSet::iterator itel;
            for( itel = elset->begin(); itel != elset->end(); ++itel ) {
                map_num_element[ *itel ].add_element_at( mesh, match_inode_inp_lmtpp, map_num_node );
            }
        } else 
            std::cerr << "WARNING ReaderINP : you wish to create a mesh by unknown ElSet " << nameElSet << " ." << std::endl; 
    }
    
    template<class TMESH>
    void create_mesh_by_surface( TMESH &mesh, const std::string &nameSurface ) {
        typename std::map< std::string, Surface* >::iterator it;
        std::map< unsigned, unsigned > match_inode_inp_lmtpp;
        
        it = map_Surface.find( nameSurface );
        if ( it != map_Surface.end() ) {
            Surface* surf = it->second;
            if ( surf->type == 0 ) { /// ELEMENTS
                for( unsigned i = 0; i < surf->indice.size(); ++i )
                    map_num_element[ surf->indice[ i ] ].add_surface_element_at( mesh, match_inode_inp_lmtpp, map_num_node, surf->id_face[ i ] );
            } else
                std::cerr << "WARNING ReaderINP : does not create surface defined by node : TODO" << std::endl;
        } else {
            std::cerr << "WARNING ReaderINP : you use create_mesh_by_surface() with un unknown name " << nameSurface << std::endl;
        }
    }
    
    void tag_mesh_by_surface( const std::string &nameSurface, const std::string& nameTag, T valueTag = (T) 1. ) {
        typename std::map< std::string, Surface* >::iterator it;
        
        it = map_Surface.find( nameSurface );
        if ( it != map_Surface.end() ) {
            Surface* surf = it->second;
            if ( surf->type == 0 ) { /// ELEMENTS-SURFACE
                typename Map_num_element::iterator it2;
                
                for( it2 = map_num_element.begin(); it2 != map_num_element.end(); ++it2 )
                    if ( it2->second.ptrEA )
                        it2->second.ptrEA->set_field( nameTag, 0. );
                    else
                        std::cerr << "WARNING ReaderINP : buzzzzzzzzzzz "  << std::endl;
               
                for( unsigned i = 0; i < surf->indice.size(); ++i )
                    if ( map_num_element[ surf->indice[ i ] ].ptrEA )
                        map_num_element[ surf->indice[ i ] ].ptrEA->set_field( nameTag, valueTag );
                    else
                        std::cerr << "WARNING ReaderINP : problem to tag the element " << surf->indice[ i ] << std::endl;
            } else
                std::cerr << "WARNING ReaderINP : does not tag mesh by surface defined by node : TODO" << std::endl;
        } else {
            std::cerr << "WARNING ReaderINP : you use tag_mesh_by_surface() with un unknown name " << nameSurface << std::endl;
        }
    }
    
    /*!
    Cette méthode place dans index les indices des noeuds du maillage "mesh" qui appartiennent à la surface nommé "nameSurface".
    Elle retourne le nombre de ces indices.
    Deux points sont considérés comme confondus si leur distance euclidienne est inféieure à "tol".
    Par défaut la tolérance "tol" est à 10^-4.
    */
    template<class TMESH >
    unsigned get_index_node_of_surface( Vec<unsigned> &index, TMESH &mesh, const std::string& nameSurface, typename TMESH::TNode::T tol = 1e-4 ) {
        typedef typename TMESH::Pvec PvecLocal;
        PvecLocal po;
        typename std::map< std::string, Surface* >::iterator it;
        
        it = map_Surface.find( nameSurface );
        index.resize( 0 );
        
        if ( it != map_Surface.end() ) {
            Surface* surf = it->second;
            if ( surf->type == 0 ) { /// ELEMENT-SURFACE
                Vec<unsigned> lindex, bigindex;
                for( unsigned i = 0; i < surf->indice.size(); ++i ) {
                    /// on cherche à obtenir les indices des noeuds de la surface de l'élément "i" concerné .
                    map_num_element[ surf->indice[ i ] ].get_index_node_of_surface( lindex, surf->id_face[ i ] );

                    for( unsigned j = 0; j < lindex.size(); ++j )
                        if ( not( bigindex.contains( lindex[ j ] ) ) ) 
                                    bigindex.push_back( lindex[ j ] );
                }

                for( unsigned i = 0; i < bigindex.size(); ++i ) {
                    map_num_node[ bigindex[ i ] ].copy_to( po ); /// pas optimisé
                    for( unsigned j = 0; j < mesh.node_list.size(); ++j )
                        if ( LMT::distance( po, mesh.node_list[ j ].pos ) < tol ) {
                            index.push_back( j );
                            ///break; on retire le "break" à cause d'éventuelles doublons
                        }
                }
                return index.size();
                
            } else { /// NODAL-SURFACE
                for( unsigned i = 0; i < surf->indice.size(); ++i ) {
                    //po = (PvecLocal) map_num_node[ surf->indice[ i ] ];
                    map_num_node[ surf->indice[ i ] ].copy_to( po ); /// pas optimisé
                    for( unsigned j = 0; j < mesh.node_list.size(); ++j )
                        if ( LMT::distance( po, mesh.node_list[ j ].pos ) < tol ) {
                            index.push_back( j );
                            ///break; on retire le "break" à cause d'éventuelles doublons
                        }
                }
                return index.size();
            }
        } else {
            std::cerr << "WARNING ReaderINP : you use get_index_node_of_surface() with un unknown name " << nameSurface << std::endl;
            return 0;
        }
    }
    
    template<class TMESH>
    void create_mesh_by_material( TMESH &mesh, const std::string &nameMaterial ) {
        std::map< unsigned, unsigned > match_inode_inp_lmtpp;
        typename std::map< std::string, SolidSection* >::iterator it;
        typename TMESH::MA::EA *ptrEA;
        ElementSet* elset;
        Orientation *ori;
        Material* material;
        //MatchElement_INP_LMTpp mel;

        for( it = map_SolidSection.begin(); it != map_SolidSection.end(); it++ ) {
            //PRINT(it->first);
            if ( it->second ) {
                if ( it->second->s_material == nameMaterial ) {
                    ori = it->second->orientation;
                    material = it->second->material;
                    typename std::map< std::string, ElementSet*>::iterator itelset = map_ElementSet.find( it->first );
                    
                    if ( itelset != map_ElementSet.end() ) {
                        elset = itelset->second;
                        typename ElementSet::iterator itel;
                        for( itel = elset->begin(); itel != elset->end(); ++itel ) {
                            ptrEA = map_num_element[ *itel ].add_element_at( mesh, match_inode_inp_lmtpp, map_num_node );
                            if ( ptrEA ) {
                                if ( ori )
                                    ori->setProperty( ptrEA );
                                //else
                                    //std::cerr << "WARNING ReaderINP : ori == NULL  material = " << nameMaterial << std::endl;
                                if ( material ) {
                                    if ( material->material_property ) 
                                        material->material_property->setProperty( ptrEA );
                                    //else
                                        //std::cerr << "WARNING ReaderINP : material->material_property == NULL" << std::endl;
                                } else
                                    std::cerr << "WARNING ReaderINP : material == NULL" << std::endl;
                            } else
                                std::cerr << "WARNING ReaderINP : ptrEA == NULL" << std::endl;
                        }
                    }
                }
            } else
                std::cerr << ">> it->second == NULL ..." << std::endl;
        }

        /// remove_doubles(mesh.node_list,egalityPos);/// problème avec remove_double
    }
    
    void display_map_element_set( bool withElement = false) {

        typename std::map< std::string, ElementSet* >::iterator it;

        std::cout << "****************************************************" << std::endl;
        std::cout << "*                Element Set                       *" << std::endl;
        std::cout << "****************************************************" << std::endl;
        
        for( it = map_ElementSet.begin(); it != map_ElementSet.end(); it++) {
            std::cout << "name is " <<  it->first << std::endl;
            if ( withElement ) {
                if ( it->second )
                    it->second->display();
                else
                    std::cout << ">> it->second == NULL ..." << std::endl;
            }
        }
    }
    
    void display_map_node_set(bool withNode = false) {

        typename std::map< std::string, NodeSet* >::iterator it;

        std::cout << "****************************************************" << std::endl;
        std::cout << "*                   Node Set                       *" << std::endl;
        std::cout << "****************************************************" << std::endl;
        
        for( it = map_NodeSet.begin(); it != map_NodeSet.end(); it++) {
            std::cout << "name is " <<  it->first << std::endl;
            if ( withNode ) {
                if (it->second)
                    it->second->display();
                else
                    std::cout << ">> it->second == NULL ..." << std::endl;
            }
        }
    }
    
    void display_map_orientation() {

        typename std::map< std::string, Orientation* >::iterator it;

        std::cout << "****************************************************" << std::endl;
        std::cout << "*                 Orientation                      *" << std::endl;
        std::cout << "****************************************************" << std::endl;

        for( it = map_Orientation.begin(); it != map_Orientation.end(); it++) {
            //PRINT(it->first);
            std::cout << "Orientation named " << it->first << std::endl;
            if (it->second) {
                //std::cout << " DATA = " << it->second->data << std::endl;
                std::cout << " v1 = " << it->second->v1 << std::endl;
                std::cout << " v2 = " << it->second->v2 << std::endl;
            } else
                std::cout << ">> it->second == NULL ..." << std::endl;
        }
    }
    
    void display_node() {

        //typename map< unsigned,TNode*>::iterator it;
        typename Map_num_node::iterator it;

        std::cout << "****************************************************" << std::endl;
        std::cout << "*                       Node                       *" << std::endl;
        std::cout << "****************************************************" << std::endl;

        for( it = map_num_node.begin(); it != map_num_node.end(); it++ )
            std::cout << "name is " <<  it->first << " at position " << it->second.pos << std::endl;
    }
    
    void display_element() {

        typename Map_num_element::iterator it;
        
        std::cout << "****************************************************" << std::endl;
        std::cout << "*                   Element                        *" << std::endl;
        std::cout << "****************************************************" << std::endl;
        PRINT( map_num_element.size() );
        for( it = map_num_element.begin(); it != map_num_element.end(); it++)
            std::cout << "name is " <<  it->first << " of type " << it->second.name << std::endl; //PRINT( *( it->second.ptr ) );
    }
    
    void display_map_material() {

        typename std::map< std::string, Material* >::iterator it;

        std::cout << "****************************************************" << std::endl;
        std::cout << "*                   Material                       *" << std::endl;
        std::cout << "****************************************************" << std::endl;

        for( it = map_Material.begin(); it != map_Material.end(); it++) {
            std::cout << "name is " <<  it->first << std::endl;
            if ( it->second ) {
                    it->second->display();
            } else
                std::cout << ">> it->second == NULL ..." << std::endl;
        }
    }
    
    void display_map_solid_section() {

        typename std::map< std::string, SolidSection* >::iterator it;

        std::cout << "****************************************************" << std::endl;
        std::cout << "*                Solid Section                     *" << std::endl;
        std::cout << "****************************************************" << std::endl;
        
        for( it = map_SolidSection.begin(); it != map_SolidSection.end(); it++) {
            std::cout << "name is " <<  it->first << std::endl;
            if ( it->second ) {
                if ( it->second->material )
                    it->second->material->display();
                else
                    std::cout << ">> it->second->material == NULL ..." << std::endl;
                if ( it->second->orientation ) {
                    std::cout << " orientation::v1 = " << it->second->orientation->v1 << std::endl;
                    std::cout << " orientation::v2 = " << it->second->orientation->v2 << std::endl;
                } else
                    std::cout << ">> it->second->orientation == NULL ..." << std::endl;
            } else
                std::cout << ">> it->second == NULL ..." << std::endl;
        }
    }
    
    void display_map_Surface( bool withIndice = false ) {

        typename std::map< std::string, Surface* >::iterator it;

        std::cout << "****************************************************" << std::endl;
        std::cout << "*                   Surface                        *" << std::endl;
        std::cout << "****************************************************" << std::endl;
        
        for( it = map_Surface.begin(); it != map_Surface.end(); it++) {
            std::cout << "name is " <<  it->first << std::endl;
            if ( withIndice ) {
                if ( it->second )
                    it->second->display();
                else
                    std::cout << ">> it->second == NULL ..." << std::endl;
            }
        }
    }
    
    /// attributs :
    std::map< std::string, NodeSet*> map_NodeSet;
    std::map< std::string, ElementSet*> map_ElementSet;
    std::map< std::string, Orientation*> map_Orientation;
    std::map< std::string, SolidSection*> map_SolidSection;
    std::map< std::string, Material*> map_Material;
    std::map< std::string, ContactPair*> map_ConctactPair;
    std::map< std::string, Surface*> map_Surface;
    // correspondance between number in file -> ref in mesh
    //Map_num_node    map_num_node;
    Map_num_node map_num_node;
    Map_num_element map_num_element;

    static const char* internal_name[ 2 ];
    static const unsigned nb_principale_keyword = 26;
    static const char* list_principale_keyword[ nb_principale_keyword ];
};

template<class TM> 
const char* ReaderINP<TM>::internal_name[2] = {
    "__READERINP__ALL_NODES__",
    "__READERINP__ALL_ELEMENTS__"
};

template<class TM> 
const char* ReaderINP<TM>::list_principale_keyword[ ReaderINP<TM>::nb_principale_keyword ] = {
    "MATERIAL",
    "NODE",
    "ELEMENT",
    "NSET",
    "ELSET",
    "ORIENTATION",
    "SOLID SECTION",
    "BOUNDARY",
    "AMPLITUDE",
    "SURFACE",   /// 10
    "CONTACT PAIR",
    "STEP",
    "END STEP",
    "Material",
    "Node",
    "Element",
    "Nset",
    "Elset",
    "Orientation",
    "Solid Section",   /// 20
    "Boundary",
    "Amplitude",
    "Surface",
    "Contact Pair",
    "Step",
    "End Step"
    //"" /// pour indiquer la fin
};

template<class TM> 
const char* ReaderINP<TM>::ContactPair::list_keyword[ ReaderINP<TM>::ContactPair::nb_keyword ] = {
    "FRICTION",
    "Friction",
    "SURFACE INTERACTION",
    "Surface Interaction"
    //""
};    

};


#endif  /// READER_INP_H

