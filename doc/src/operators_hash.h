#ifndef OPERATORHASH_H
#define OPERATORHASH_H
#include "hashstring.h"
#include "usual_strings.h"
#include <string.h>
inline int num_operator_op(const char *s,unsigned si) {
    static const int tab[] = {-1,105,64,73,-1,-1,98,60,-1,-1,75,54,-1,50,43,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,91,-1,-1,62,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,56,-1,-1,-1,-1,-1,-1,85,-1,74,65,-1,-1,57,-1,-1,76,-1,-1,55,84,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,63,83,-1,-1,-1,-1,79,-1,-1,-1,-1,-1,-1,-1,-1,-1,58,51,-1,42,-1,-1,-1,82,89,45,-1,-1,-1,-1,-1,-1,97,-1,-1,-1,-1,-1,94,-1,-1,-1,92,-1,-1,-1,-1,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,72,-1,-1,-1,59,103,-1,44,-1,-1,-1,81,87,-1,-1,-1,-1,52,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,93,-1,71,-1,102,-1,-1,-1,-1,-1,-1,-1,-1,-1,96,-1,80,46,104,-1,-1,47,-1,78,90,-1,-1,22,-1,-1,-1,-1,88,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,101,-1,-1,-1,-1,-1,86,-1,};
    int n = tab[ hashstring(s,si) % 214 ];
    if ( n>=0 and name_size_of_operator(n)==si and strncmp(s,name_of_operator(n),si)==0 )
        return n;
    return -1;
}
inline int num_operator_le(const char *s,unsigned si) {
    static const int tab[] = {-1,-1,-1,69,-1,-1,38,-1,-1,-1,-1,-1,-1,-1,-1,29,-1,16,-1,-1,-1,-1,-1,30,-1,-1,8,-1,-1,68,12,-1,-1,-1,-1,31,-1,-1,66,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,32,-1,25,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,40,4,27,-1,-1,-1,41,100,-1,-1,23,-1,-1,-1,-1,-1,67,-1,-1,-1,-1,-1,-1,-1,-1,19,-1,-1,70,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1,26,-1,-1,33,-1,-1,-1,-1,-1,-1,-1,-1,-1,35,-1,-1,-1,-1,24,-1,-1,-1,-1,-1,28,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,17,-1,2,-1,-1,-1,-1,18,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,77,-1,99,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,36,-1,-1,37,-1,6,-1,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,-1,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,-1,-1,-1,39,-1,-1,-1,-1,-1,-1,48,-1,-1,-1,5,-1,-1,-1,-1,};
    int n = tab[ hashstring(s,si) % 308 ];
    if ( n>=0 and name_size_of_operator(n)==si and strncmp(s,name_of_operator(n),si)==0 )
        return n;
    return -1;
}
#endif // OPERATORHASH_H