#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>
uint32_t const emptyID       = 0xffffffff;

enum class IndexType{
  UINT8  = 1, ///< uin8_t type
  UINT16 = 2, ///< uin16_t type
  UINT32 = 4, ///< uint32_t type
};

union Attribute{
	Attribute(){}
	float v1;
	int v2;
	char v3;
};

double     side_length           (double a_x, double a_y, double b_x, double b_y)
{

    // (a_x - b_x) ^ 2
    auto x_d_sqr = pow( (a_x - b_x), 2);
    // (a_y - b_y) ^2
    auto y_d_sqr = pow( (a_y - b_y), 2);

    printf("%f  \n", sqrt(x_d_sqr + y_d_sqr));
    double x = sqrt(x_d_sqr + y_d_sqr);
    printf("%f \n", x);

    return ((sqrt(x_d_sqr + y_d_sqr)));

//    float x = (sqrt( x_d_sqr + y_d_sqr ));

  //  getchar();

    //return x;
}

int main() {

	float a = 0;
	float b = 500;
	float c = 16.5;
	float d = 0.5;

	double y = side_length(a,b,c,d);

	printf("%f\n", y);
	return 0;
}
