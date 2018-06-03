#include <stdio.h>
#include <math.h>

#include "rational.h"

int main()
{
	int p, q;
	Rational a, b, sum, sub, mul, div;
	printf("Enter two ratio: \n");
	printf("First one: ");
	scanf("%d/%d", &p, &q);
	a = ratiolize(p, q);
	
	printf("Ratiolized: %d/%d = %.2lf\n", a.p, a.q, a.value);
	
	printf("Second one: ");
	scanf("%d/%d", &p, &q);
	b = ratiolize(p, q);
	
	printf("Ratiolized: %d/%d = %.2lf\n",  b.p, b.q, b.value);
	
	puts("");
	if(equal(a,b)==TRUE) printf("::equal\n");
	else printf("::not equal\n");
	
	sum = add(a, b);
	printf("::Add operation: (%d/%d) + (%d/%d) = %d/%d\n", a.p, a.q, b.p, b.q, sum.p, sum.q);
	
	sub = substract(a, b);
	printf("::Substraction operation: (%d/%d) - (%d/%d) = %d/%d\n", a.p, a.q, b.p, b.q, sub.p, sub.q);
	
	mul = multipicate(a, b);
	printf("::Multipication operation: (%d/%d) * (%d/%d) = %d/%d\n", a.p, a.q, b.p, b.q, mul.p, mul.q);
	
	div = divide(a, b);
	printf("::Dividing operation: (%d/%d) / (%d/%d) = %d/%d, mean value = %.2lf\n", a.p, a.q, b.p, b.q, div.p, div.q, div.value);

	puts("");
	puts("");
	main();
	
	return 0;
}
