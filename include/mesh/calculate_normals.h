//
// C++ Interface: calculate_normals
//
// Description: 
//
//
// Author: Hugo LECLERC <hugo.leclerc@lmt.ens-cachan.fr>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LMT_calculate_normals_HEADER
#define LMT_calculate_normals_HEADER

namespace LMT {

struct CalculateNormals {
    template<class TE>
    void operator()(TE &e) const {
        typename TE::Pvec n = sample_normal( e );
        for(unsigned i=0;i<TE::nb_nodes;++i)
            e.node(i)->normal += n;
    }
};

template<class TM>
void calculate_normals(TM &m) {
    apply( m.elem_list, CalculateNormals() );
    for(unsigned i=0;i<m.node_list.size();++i)
        m.node_list[i].normal /= length( m.node_list[i].normal, 1e-40 );
}


};

#endif // LMT_calculate_normals_HEADER