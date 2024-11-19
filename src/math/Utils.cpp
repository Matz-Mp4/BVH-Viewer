#include "../include/math/Utils.hpp"

float math_utils::radians(float angle) {
    return  angle *  PI / 180 ;
}


float math_utils::sqrt(float x) {
      asm(
        "fsqrt;"         // root instruction
        : "=t"(x)        // ST(0) is stored in x
        : "0"(x)         // x is passed to ST(0)
    );
    return x;
}
