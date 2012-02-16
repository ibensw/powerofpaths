#include <stdio.h>
#include <stdlib.h>

//Naive way, but no bottleneck
unsigned int bitcount(unsigned int v){
	unsigned int c;
	for (c = 0; v; v >>= 1){
		c += v & 1;
	}
	return c;
}

unsigned int rotateleft(unsigned int v, unsigned int bits){
	v<<=1;
	if (v > (1<<(bits-1))){
		return 1;
	}
	return v;
}

unsigned int rotateright(unsigned int v, unsigned int bits){
	v>>=1;
	if (!v){
		return 1 << (bits-1);
	}
	return v;
}

int main(int argc, char* argv[]){
	if (argc < 3){
		return 1;
	}
	unsigned int size = atoi(argv[1]);
	unsigned int sqrsize = 1 << size;
	unsigned int bitdiff;
	double lambda = atof(argv[2]);
	unsigned int i,j;
	const double mu = 1.0;

	double v;

	printf("Q=matrix(%u,%u,[", sqrsize, sqrsize);

	for (i=0; i < sqrsize; ++i){
		printf("[");
		for (j=0; j < sqrsize; ++j){
			bitdiff = i ^ j;
			if (i == j){
				v=-mu*bitcount(i);
				if (i+1 != sqrsize){
					v-=size*lambda;
				}
				printf("%g", v);
			}else if (bitcount(bitdiff) == 1 && bitdiff & j){ //There is exactly 1 bit extra set in j
				unsigned int b;
				double c = 0.0, p = 0.0, np = 0.0;
				b = rotateleft(bitdiff, size); //1 bit is set
				c=lambda;

				while (b & j && b!=bitdiff){
					p+=lambda;
					b=rotateleft(b, size);
				}
				b = rotateright(bitdiff, size); //1 bit is set
				while (b & j && b!=bitdiff){
					np+=lambda;
					b=rotateright(b, size);
				}

				if (c != 0)
					printf("%+g", c);
				if (p != 0)
					printf("%+g*p", p);
				if (np != 0)
					printf("%+g*(1-p)", np);
			}else if (bitcount(bitdiff) == 1 && bitdiff & i){
				printf("%g", mu);
			}else{
				printf("0");
			}

			if (j != sqrsize-1){
				printf(",");
			}
		}
		printf("]");
		if (i != sqrsize-1){
			printf(",");
		}
	}

	printf("])\n");

	return 0;
}
