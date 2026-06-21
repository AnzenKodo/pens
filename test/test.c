#ifndef Mth_Prefix
#define Mth_Prefix(name) MTH_##name
#endif

#define Mth_Prefix(EPSILON_F32)      1.19209290e-7f

#include <stdio.h>

int main(void)
{
    printf("%d", MTH_EPSILON_F32);
    return 0;
}
