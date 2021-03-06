#ifndef COND_H
#define COND_H

namespace LMT {

/**
    helper function
*/
template<class TM,class TV,class T>
typename TM::T _cond( const TM &m, TV &vp, T crit, T offset ) {
    vp /= norm_2( vp );
    //
    T lambda = 0;
    while ( true ) {
        Vec<T> new_vp = m * vp + offset * vp;
        T new_lambda = norm_2( new_vp ); // * ( dot( vp, new_vp ) < 0 ? -1 : 1 );
        if ( new_lambda == T( 0 ) )
            return 0;
        if ( abs_indication( new_lambda - lambda ) < abs_indication( crit * new_lambda ) )
            break;
        vp = new_vp / new_lambda;
        lambda = new_lambda;
    }
    return lambda - offset;
}

/**
    conditionnement d'un opérateur ou d'une matrice carré.
*/
template<class TM>
typename TM::T cond( const TM &m, typename TM::T prec = 1e-6 ) {
    typedef typename TM::T T;

    unsigned s = m.nb_rows();
    Vec<T> vp; vp.resize( s );
    for(unsigned i=0;i<s;++i)
        vp[i] = T( rand() ) / T( RAND_MAX );
    Vec<T> gvp = vp, lvp = vp;

    //
    T greatest_lambda = _cond( m, gvp, T( prec ), T( 0 ) );

    //
    T lowest_lambda, crit_lowest_lambda = 1e-6;
    while ( true ) {
        lowest_lambda = _cond( m, lvp, crit_lowest_lambda, - greatest_lambda );
        if ( abs_indication( greatest_lambda * crit_lowest_lambda ) <= abs_indication( prec ) )
            break;
        crit_lowest_lambda = prec / greatest_lambda / T( 10 );
    }

    //
    return greatest_lambda / lowest_lambda;
}

}

#endif // COND_H
