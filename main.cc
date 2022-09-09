#include <iostream>
#include <math.h>
#include <chrono>

#include "im2col.h"

int main()
{
    float *in = new float[1 * 3 * 48 *120];
    float *out = new float[1 * 3 * 48 *120];

    im2col_gpu<float>(in, 3, 48, 120, 5, 2, 2, 2, 2, 2, 2, 2, out);
	im2col_gpu<float>(in, 3, 48, 120, 5, 2, 2, 2, 2, 2, 2, 2, out);

    free(in);
    free(out);
}