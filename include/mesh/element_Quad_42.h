#ifndef LMT_QUAD_42
#define LMT_QUAD_42
namespace LMT {
inline const double *gauss_point_for_order(unsigned order, const Quad_42 &elem) { /// order -> degre du polynome a integrer exactement
    static const unsigned offset[] = { 0, 28, 56, 84, 112, 140, 168, 196, 224, 252, }; // fonction de lordre du poly
    static const double values[] = {
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
        0.197530864198,0.5,0.5,
        0.123456790123,0.5,0.112701665379,
        0.123456790123,0.5,0.887298334621,
        0.123456790123,0.112701665379,0.5,
        0.0771604938272,0.112701665379,0.112701665379,
        0.0771604938272,0.112701665379,0.887298334621,
        0.123456790123,0.887298334621,0.5,
        0.0771604938272,0.887298334621,0.112701665379,
        0.0771604938272,0.887298334621,0.887298334621,
        0.0,
    };
    return values + offset[order];
}
template<class TNode> void permutation_if_jac_neg(const Quad_42 &elem,TNode **nodes) {
    typedef typename TNode::T T;
    T reg0=0.5624999999999998751*nodes[4]->pos[0]; T reg1=0.062499999999999993061*nodes[0]->pos[0]; T reg2=0.062499999999999993061*nodes[0]->pos[1]; T reg3=0.5624999999999998751*nodes[4]->pos[1]; T reg4=1.6875*nodes[4]->pos[0];
    T reg5=1.6875*nodes[4]->pos[1]; T reg6=0.062500000000000055511*nodes[0]->pos[0]; T reg7=0.062500000000000055511*nodes[0]->pos[1]; T reg8=reg7-reg5; reg3=reg3-reg2;
    T reg9=0.56250000000000006245*nodes[5]->pos[1]; T reg10=1.6875*nodes[5]->pos[1]; T reg11=1.6875*nodes[5]->pos[0]; T reg12=reg6-reg4; T reg13=0.56250000000000006245*nodes[5]->pos[0];
    reg0=reg0-reg1; T reg14=0.062499999999999993061*nodes[1]->pos[1]; reg3=reg9+reg3; reg8=reg8+reg10; T reg15=0.062499999999999930604*nodes[1]->pos[1];
    T reg16=0.062499999999999993061*nodes[1]->pos[0]; reg0=reg13+reg0; reg12=reg12+reg11; T reg17=0.062499999999999930604*nodes[1]->pos[0]; T reg18=0.062500000000000055511*nodes[3]->pos[1];
    reg8=reg8-reg15; T reg19=0.062499999999999993061*nodes[3]->pos[0]; T reg20=reg16-reg0; T reg21=reg14-reg3; T reg22=0.062499999999999993061*nodes[3]->pos[1];
    reg12=reg12-reg17; T reg23=0.062500000000000055511*nodes[3]->pos[0]; reg8=reg8+reg18; T reg24=1.6875*nodes[7]->pos[1]; T reg25=0.5624999999999998751*nodes[7]->pos[1];
    reg21=reg21-reg22; reg12=reg12+reg23; T reg26=1.6875*nodes[7]->pos[0]; reg20=reg20-reg19; T reg27=0.5624999999999998751*nodes[7]->pos[0];
    T reg28=0.56250000000000006245*nodes[6]->pos[0]; reg27=reg20+reg27; reg20=1.6875*nodes[6]->pos[1]; reg8=reg8-reg24; T reg29=0.56250000000000006245*nodes[6]->pos[1];
    reg25=reg21+reg25; reg12=reg12-reg26; reg21=1.6875*nodes[6]->pos[0]; reg8=reg8+reg20; T reg30=0.062499999999999930604*nodes[2]->pos[1];
    reg27=reg27+reg28; T reg31=0.062499999999999993061*nodes[2]->pos[0]; T reg32=0.062499999999999993061*nodes[2]->pos[1]; reg25=reg25+reg29; reg12=reg12+reg21;
    T reg33=0.062499999999999930604*nodes[2]->pos[0]; reg27=reg27-reg31; reg8=reg8-reg30; reg25=reg25-reg32; reg12=reg12-reg33;
    reg25=reg12*reg25; reg27=reg8*reg27; T det_jac=reg25-reg27;

    if ( det_jac < 0 ) {
        TNode *tmp[] = {nodes[3],nodes[2],nodes[1],nodes[0],nodes[7],nodes[6],nodes[5],nodes[4]};
        for(unsigned i=0;i<8;++i) nodes[i] = tmp[i];
    }
}
template<class PosNodes,class Pvec,class TVI> void get_var_inter_linear(const Quad_42 &elem,const PosNodes &pos_nodes,const Pvec &pos,TVI &var_inter) {
typedef typename Pvec::template SubType<0>::T T;
    T reg0=0.66666666666666662966-var_inter[0]; T reg1=0.33333333333333331483-var_inter[0]; T reg2=reg0-var_inter[0]; T reg3=reg1+reg0; T reg4=1-var_inter[0];
    reg2=reg4*reg2; T reg5=reg4*reg3; T reg6=var_inter[0]*reg0; T reg7=reg1*reg0; T reg8=reg1-var_inter[0];
    reg2=reg2-reg6; T reg9=reg4*reg8; reg1=var_inter[0]*reg1; reg5=reg7+reg5; reg2=13.5*reg2;
    T reg10=1-var_inter[1]; reg6=reg4*reg6; reg8=reg0*reg8; reg9=reg9-reg1; reg7=reg4*reg7;
    T reg11=4.5*reg5; reg6=13.5*reg6; reg4=reg4*reg1; T reg12=reg10*reg11; reg7=4.5*reg7;
    reg9=13.5*reg9; T reg13=reg10*reg2; reg8=reg8-reg1; T reg14=pos_nodes[0][1]*reg7; T reg15=reg6*pos_nodes[4][1];
    T reg16=pos_nodes[0][1]*reg12; T reg17=pos_nodes[4][1]*reg13; T reg18=pos_nodes[0][0]*reg7; T reg19=reg10*reg9; reg8=4.5*reg8;
    T reg20=pos_nodes[4][0]*reg13; T reg21=pos_nodes[0][0]*reg12; T reg22=pos_nodes[4][0]*reg6; reg1=reg0*reg1; reg4=13.5*reg4;
    reg0=reg4*pos_nodes[5][0]; T reg23=pos_nodes[5][0]*reg19; reg21=reg20-reg21; reg18=reg22+reg18; reg20=reg4*pos_nodes[5][1];
    reg22=reg10*reg8; reg1=4.5*reg1; T reg24=reg6*reg10; T reg25=reg7*reg10; reg16=reg17-reg16;
    reg17=pos_nodes[5][1]*reg19; reg14=reg15+reg14; reg15=reg1*pos_nodes[1][1]; T reg26=pos_nodes[0][0]*reg25; T reg27=reg24*pos_nodes[4][0];
    T reg28=reg24*pos_nodes[4][1]; T reg29=pos_nodes[0][1]*reg25; T reg30=reg1*pos_nodes[1][0]; reg18=reg0-reg18; reg17=reg16-reg17;
    reg0=pos_nodes[1][1]*reg22; reg14=reg20-reg14; reg16=reg4*reg10; reg20=var_inter[1]*reg11; T reg31=pos_nodes[1][0]*reg22;
    reg23=reg21-reg23; reg10=reg1*reg10; reg21=reg16*pos_nodes[5][0]; reg26=reg27+reg26; reg2=var_inter[1]*reg2;
    reg27=pos_nodes[3][1]*reg7; reg15=reg14-reg15; reg14=pos_nodes[3][0]*reg7; reg30=reg18-reg30; reg31=reg23+reg31;
    reg29=reg28+reg29; reg18=reg16*pos_nodes[5][1]; reg0=reg17+reg0; reg17=pos_nodes[3][1]*reg20; reg23=pos_nodes[3][0]*reg20;
    reg28=pos_nodes[1][1]*reg10; T reg32=var_inter[1]*reg7; reg27=reg15+reg27; reg17=reg0-reg17; reg0=pos_nodes[7][1]*reg2;
    reg15=reg6*pos_nodes[7][1]; reg23=reg31-reg23; reg31=pos_nodes[1][0]*reg10; reg21=reg26-reg21; reg9=var_inter[1]*reg9;
    reg26=pos_nodes[7][0]*reg2; T reg33=reg6*pos_nodes[7][0]; reg14=reg30+reg14; reg18=reg29-reg18; reg29=pos_nodes[3][1]*reg32;
    reg30=pos_nodes[6][1]*reg9; reg0=reg17+reg0; reg26=reg23+reg26; reg17=pos_nodes[6][0]*reg9; reg8=var_inter[1]*reg8;
    reg28=reg18+reg28; reg18=var_inter[1]*reg6; reg33=reg14+reg33; reg14=reg4*pos_nodes[6][0]; reg15=reg27+reg15;
    reg23=reg4*pos_nodes[6][1]; reg27=pos_nodes[3][0]*reg32; reg31=reg21+reg31; reg21=reg18*pos_nodes[7][1]; reg23=reg15-reg23;
    reg15=reg1*pos_nodes[2][1]; reg29=reg28+reg29; reg28=var_inter[1]*reg4; reg17=reg26-reg17; reg26=pos_nodes[2][0]*reg8;
    T reg34=pos_nodes[2][1]*reg8; reg30=reg0-reg30; reg14=reg33-reg14; reg0=reg1*pos_nodes[2][0]; reg27=reg31+reg27;
    reg31=reg18*pos_nodes[7][0]; reg33=var_inter[1]*reg1; reg26=reg17+reg26; reg15=reg23+reg15; reg0=reg14+reg0;
    reg31=reg27+reg31; reg14=reg28*pos_nodes[6][0]; reg17=reg28*pos_nodes[6][1]; reg34=reg30+reg34; reg21=reg29+reg21;
    reg14=reg31-reg14; reg23=pos_nodes[2][0]*reg33; reg17=reg21-reg17; reg21=reg26*reg15; reg27=reg0*reg34;
    reg29=pos_nodes[2][1]*reg33; reg29=reg17+reg29; reg27=reg21-reg27; reg23=reg14+reg23; reg14=reg15/reg27;
    reg23=pos[0]-reg23; reg29=pos[1]-reg29; reg17=reg34/reg27; reg30=reg0/reg27; reg27=reg26/reg27;
    reg14=reg23*reg14; reg30=reg29*reg30; reg17=reg23*reg17; reg27=reg29*reg27; var_inter[0]=reg14-reg30;
    var_inter[1]=reg27-reg17;

}
template<class PosNodes,class Pvec,class TVI> void get_var_inter(const Quad_42 &elem,const PosNodes &pos_nodes,const Pvec &pos,TVI &var_inter) {
typedef typename Pvec::template SubType<0>::T T;
    T reg0=0.66666666666666662966-var_inter[0]; T reg1=0.33333333333333331483-var_inter[0]; T reg2=reg0-var_inter[0]; T reg3=reg1+reg0; T reg4=1-var_inter[0];
    reg2=reg4*reg2; T reg5=reg4*reg3; T reg6=reg0*var_inter[0]; T reg7=reg1*reg0; T reg8=reg1-var_inter[0];
    reg2=reg2-reg6; reg5=reg7+reg5; T reg9=reg4*reg8; reg1=reg1*var_inter[0]; reg2=13.5*reg2;
    reg7=reg4*reg7; T reg10=4.5*reg5; reg8=reg0*reg8; reg6=reg4*reg6; T reg11=1-var_inter[1];
    reg9=reg9-reg1; reg4=reg4*reg1; T reg12=reg11*reg2; T reg13=reg11*reg10; reg9=13.5*reg9;
    reg8=reg8-reg1; reg6=13.5*reg6; reg7=4.5*reg7; T reg14=reg11*reg9; T reg15=pos_nodes[0][1]*reg13;
    T reg16=pos_nodes[4][1]*reg12; T reg17=reg6*pos_nodes[4][1]; T reg18=reg7*pos_nodes[0][1]; T reg19=reg7*pos_nodes[0][0]; reg8=4.5*reg8;
    T reg20=pos_nodes[4][0]*reg6; T reg21=pos_nodes[0][0]*reg13; T reg22=pos_nodes[4][0]*reg12; reg1=reg0*reg1; reg4=13.5*reg4;
    reg1=4.5*reg1; reg15=reg16-reg15; reg0=pos_nodes[5][1]*reg14; reg19=reg20+reg19; reg16=reg4*pos_nodes[5][0];
    reg20=reg4*pos_nodes[5][1]; reg18=reg17+reg18; reg17=pos_nodes[5][0]*reg14; reg21=reg22-reg21; reg22=reg11*reg8;
    T reg23=reg6*reg11; T reg24=reg7*reg11; reg0=reg15-reg0; reg15=pos_nodes[1][1]*reg22; T reg25=reg1*pos_nodes[1][0];
    reg19=reg16-reg19; reg16=pos_nodes[0][1]*reg24; T reg26=pos_nodes[4][0]*reg23; T reg27=pos_nodes[0][0]*reg24; T reg28=reg23*pos_nodes[4][1];
    T reg29=pos_nodes[1][0]*reg22; reg17=reg21-reg17; reg21=reg4*reg11; reg18=reg20-reg18; reg20=reg1*pos_nodes[1][1];
    T reg30=var_inter[1]*reg10; T reg31=reg21*pos_nodes[5][1]; T reg32=pos_nodes[3][0]*reg7; reg25=reg19-reg25; reg2=var_inter[1]*reg2;
    reg16=reg28+reg16; reg20=reg18-reg20; reg15=reg0+reg15; reg0=pos_nodes[3][1]*reg30; reg11=reg1*reg11;
    reg18=pos_nodes[3][1]*reg7; reg19=reg21*pos_nodes[5][0]; reg27=reg26+reg27; reg26=pos_nodes[3][0]*reg30; reg29=reg17+reg29;
    reg17=pos_nodes[1][0]*reg11; reg28=pos_nodes[1][1]*reg11; reg0=reg15-reg0; reg15=pos_nodes[7][1]*reg2; reg18=reg20+reg18;
    reg20=reg6*pos_nodes[7][1]; reg31=reg16-reg31; reg32=reg25+reg32; reg16=reg6*pos_nodes[7][0]; reg25=pos_nodes[7][0]*reg2;
    reg26=reg29-reg26; reg9=var_inter[1]*reg9; reg29=reg7*var_inter[1]; reg19=reg27-reg19; reg15=reg0+reg15;
    reg0=pos_nodes[6][1]*reg9; reg17=reg19+reg17; reg16=reg32+reg16; reg19=reg4*pos_nodes[6][0]; reg27=pos_nodes[6][0]*reg9;
    reg25=reg26+reg25; reg26=pos_nodes[3][0]*reg29; reg28=reg31+reg28; reg31=pos_nodes[3][1]*reg29; reg8=var_inter[1]*reg8;
    reg32=reg6*var_inter[1]; reg20=reg18+reg20; reg18=reg4*pos_nodes[6][1]; T reg33=reg1*pos_nodes[2][1]; T reg34=reg4*var_inter[1];
    T reg35=pos_nodes[2][1]*reg8; reg0=reg15-reg0; reg18=reg20-reg18; reg27=reg25-reg27; reg15=pos_nodes[2][0]*reg8;
    reg19=reg16-reg19; reg16=reg1*pos_nodes[2][0]; reg31=reg28+reg31; reg20=reg32*pos_nodes[7][1]; reg25=reg32*pos_nodes[7][0];
    reg26=reg17+reg26; reg25=reg26+reg25; reg17=reg34*pos_nodes[6][0]; reg33=reg18+reg33; reg18=reg1*var_inter[1];
    reg26=reg34*pos_nodes[6][1]; reg20=reg31+reg20; reg16=reg19+reg16; reg35=reg0+reg35; reg15=reg27+reg15;
    reg0=reg15*reg33; reg17=reg25-reg17; reg19=pos_nodes[2][0]*reg18; reg25=pos_nodes[2][1]*reg18; reg26=reg20-reg26;
    reg20=reg16*reg35; reg25=reg26+reg25; reg20=reg0-reg20; reg19=reg17+reg19; reg17=reg15/reg20;
    reg26=reg16/reg20; reg27=reg35/reg20; reg20=reg33/reg20; reg19=pos[0]-reg19; reg25=pos[1]-reg25;
    reg26=reg26*reg25; reg20=reg19*reg20; reg27=reg19*reg27; reg17=reg17*reg25; var_inter[0]+=reg20-reg26;
    var_inter[1]+=reg17-reg27;

}
template<> struct ElemVarInterFromPosNonLinear<Quad_42> { static const bool res = 2; };
#ifndef STRUCT_Elementary_mul_nb_nodes_of_each_children_elem
#define STRUCT_Elementary_mul_nb_nodes_of_each_children_elem
struct Elementary_mul_nb_nodes_of_each_children_elem {};
#endif // STRUCT_Elementary_mul_nb_nodes_of_each_children_elem
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Elementary_mul_nb_nodes_of_each_children_elem &n,const TVI &var_inter,const TVAL &val,T &res) {
    res=val[0];

}
#ifndef STRUCT_Elementary_mul_nb_nodes
#define STRUCT_Elementary_mul_nb_nodes
struct Elementary_mul_nb_nodes {};
#endif // STRUCT_Elementary_mul_nb_nodes
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Elementary_mul_nb_nodes &n,const TVI &var_inter,const TVAL &val,T &res) {
    res=val[0];

}
#ifndef STRUCT_Nodal
#define STRUCT_Nodal
struct Nodal {};
#endif // STRUCT_Nodal
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Nodal &n,const TVI &var_inter,const TVAL &val,T &res) {
    T reg0=0.33333333333333331483-var_inter[0]; T reg1=0.66666666666666662966-var_inter[0]; T reg2=1-var_inter[0]; T reg3=reg0*reg1; T reg4=var_inter[0]*reg1;
    reg3=reg2*reg3; reg4=reg2*reg4; reg0=var_inter[0]*reg0; reg3=4.5*reg3; reg4=13.5*reg4;
    reg2=reg2*reg0; T reg5=1-var_inter[1]; T reg6=reg5*reg4; T reg7=reg5*reg3; reg2=13.5*reg2;
    reg0=reg1*reg0; reg0=4.5*reg0; reg6=val[4]*reg6; reg1=reg5*reg2; reg7=val[0]*reg7;
    reg6=reg7+reg6; reg1=val[5]*reg1; reg5=reg5*reg0; reg1=reg6-reg1; reg5=val[1]*reg5;
    reg3=var_inter[1]*reg3; reg5=reg1+reg5; reg3=val[3]*reg3; reg4=var_inter[1]*reg4; reg1=var_inter[1]*reg2;
    reg4=val[7]*reg4; reg3=reg5+reg3; reg1=val[6]*reg1; reg0=var_inter[1]*reg0; reg4=reg3+reg4;
    reg1=reg4-reg1; reg0=val[2]*reg0; res=reg1+reg0;

}
#ifndef STRUCT_Global
#define STRUCT_Global
struct Global {};
#endif // STRUCT_Global
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Global &n,const TVI &var_inter,const TVAL &val,T &res) {
    res=val[0];

}
#ifndef STRUCT_Gauss
#define STRUCT_Gauss
struct Gauss {};
#endif // STRUCT_Gauss
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Gauss &n,const TVI &var_inter,const TVAL &val,T &res) {
    res=val[0];

}
#ifndef STRUCT_Flat_interpolation
#define STRUCT_Flat_interpolation
struct Flat_interpolation {};
#endif // STRUCT_Flat_interpolation
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Flat_interpolation &n,const TVI &var_inter,const TVAL &val,T &res) {
    res=val[0];

}
#ifndef STRUCT_Der_nodal
#define STRUCT_Der_nodal
struct Der_nodal {};
#endif // STRUCT_Der_nodal
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Der_nodal &n,const TVI &var_inter,const TVAL &val,T &res) {
    res=val[0];

}
#ifndef STRUCT_Elementary
#define STRUCT_Elementary
struct Elementary {};
#endif // STRUCT_Elementary
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Elementary &n,const TVI &var_inter,const TVAL &val,T &res) {
    res=val[0];

}
#ifndef STRUCT_Skin_elementary
#define STRUCT_Skin_elementary
struct Skin_elementary {};
#endif // STRUCT_Skin_elementary
template<class TVI,class TVAL,class T> void get_interp(const Quad_42 &ne,const Skin_elementary &n,const TVI &var_inter,const TVAL &val,T &res) {
    res=val[0];

}
template<class TVI,class TVAL> void get_shape_functions(const Quad_42 &ne,const TVI &var_inter,TVAL &res) {
    typedef typename TVAL::template SubType<0>::T T;
    T reg0=0.33333333333333331483-var_inter[0]; T reg1=1-var_inter[0]; T reg2=0.66666666666666662966-var_inter[0]; T reg3=var_inter[0]*reg0; T reg4=reg1*reg3;
    reg0=reg0*reg2; T reg5=var_inter[0]*reg2; reg3=reg2*reg3; reg4=13.5*reg4; reg5=reg1*reg5;
    reg0=reg1*reg0; reg1=1-var_inter[1]; reg0=4.5*reg0; reg5=13.5*reg5; reg3=4.5*reg3;
    reg2=reg1*reg4; T reg6=var_inter[1]*reg4; T reg7=reg1*reg5; res[4]=reg7; T reg8=reg1*reg0;
    res[0]=reg8; reg1=reg1*reg3; res[1]=reg1; reg0=var_inter[1]*reg0; res[3]=reg0;
    reg5=var_inter[1]*reg5; res[7]=reg5; reg3=var_inter[1]*reg3; res[2]=reg3; res[5]=-reg2;
    res[6]=-reg6;

}
#ifndef AUTORIZEDPERM
#define AUTORIZEDPERM
template<class T> struct AuthorizedPerm;
#endif // AUTORIZEDPERM
template<> struct AuthorizedPerm<Quad_42> {
    static const unsigned nb_permutations = 0;
    template<class TE> static void make_permutation( TE &e, unsigned nb_perm ) {
    }
    template<class TE> static void unmake_permutation( TE &e, unsigned nb_perm ) {
    }
};

}
#endif // LMT_QUAD_42