/*
 * Util.h
 *
 *  Created on: Jul 8, 2017
 *      Author: kladspear
 */

#ifndef SOURCE_HEADERS_UTIL_H_
#define SOURCE_HEADERS_UTIL_H_

/*
volatile double asmSqrt(double a){
	double b = 0;
	for(int i=0;i<2;i++){
		asm volatile(
				"movq %1, %%xmm0 \n"
				"sqrtsd %%xmm0, %%xmm1 \n"
				"movq %%xmm1, %0 \n"
				: "=r"(b)
				: "g"(a)
				: "xmm0", "xmm1", "memory"
		);
	}
	return b;
}
*/

float sqrt7(float x){
	unsigned int i = *(unsigned int*) &x;
	i += 127<<23;
	i >>= 1;
	return *(float*) &i;
}

float getMagnitude(const sf::Vector2f &vec){
	return sqrt7(vec.x*vec.x+vec.y*vec.y);
}

void normalize(sf::Vector2f &vec){
	vec /= getMagnitude(vec);
}


#endif /* SOURCE_HEADERS_UTIL_H_ */
