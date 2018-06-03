#include <stdbool.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct
{
	int p;
	int q;
	double value;

} Rational;

//returns smaller value from two variables.    minimum value of two variable.
int mainor(int a, int b)
{
	return ((a+b)-abs(a-b))/2;
}

//Greatest Common Divisor of two.
int gcd(int a, int b)
{
	int temp;
	while(b!=0)
	{
		temp = b;
		b = a%b;
		a = temp;
	}
	return a;
}

//Lowest Common Multipication of two.
int lcm(int a, int b)
{
	return (a*b)/gcd(a,b);
}

//Returns a Rational structure where two number a and b, can be represented as p/q rational number.
//This function makes the rational version of two number a and b.
//The result kept in a Rational structure.  //  recursive.
//Then returns the final Rational structure.
Rational ratiolize(int a, int b)
{
	
	int lim;
	Rational result;
	result.p = a;
	result.q = b;
	if(b==0)							// b is the divisor of that a/b, so b=0 means Infinity.
	{
		result.p = a;
		result.q = 0;
		result.value = NFDBITS;
	}
	else if(a==0)						// a is the numerator of a/b, so a=0 means the whole representation is 0. though the b is assigned to q.	
	{
		result.p = 0;
		result.q = b;
		result.value = 0.0;
	}
	else if(a%b==0)						//  a modulus b = 0 means the numberator is divided by divisor without any remain value. remain value is 0.
	{
		result.p = result.value = (a*1.0/b);
		result.q = 1;
	}
	else if(b%a==0)						// if b modulus a = 0 means the divisor is divided by numerator easily without any remain value. remain value is 0.
	{
		result.p = 1;
		result.q = b/a;
		result.value = 1.0/result.q;
	}
	
	//It is a recursive method to produce the rational form of any a and b if above condition fails.
	//
	//Don't tempt it.
	//Just try once.
	//
	//A cool approach to produce rational. Atleast to me.
	else
	{
		lim = mainor(a,b)/2;			// take a = 4 and b = 6. So 4/6, as it is rational will be 2/3. 
										// This operations does that.
										// lim is minium/2 because if any number has to divided fully both a and b,
										// it should be under the minium/2.		Natural method.
		result.value = (a*1.0)/b;

		for(int i=2; i<=lim; i++)
		{
			if(a%i==0 && b%i==0)
			{
				result.p = a/i;
				result.q = b/i;
				
				result = ratiolize(result.p, result.q);			//Recursive approach.
				
				result.value = (result.p*1.0)/result.q;
			}
		}
	}
	
	
	//One last two operations to turn -p/-q to p/q and p/-q to -p/q.
	if(result.value < 0.0)
	{
		if(result.q < 0 ) result.q *= -1;
		if(result.p > 0 ) result.p *= -1;
	}
	else 
	{
		if(result.q < 0) result.q *= -1;
		if(result.p < 0) result.p *= -1;
	}
	
	return(result);
}

//Ratiolize a Rational structure. Self changer.
void rationize(Rational * a)
{
	*a = ratiolize(a->p, a->q);
}

//Is equal
bool equal(Rational a, Rational b)
{
	rationize(&a);
	rationize(&b);
	
	if(a.value == b.value) return TRUE;
	return FALSE;
}

//Rational Addition.
Rational add(Rational a, Rational b)
{
	Rational sum;
	
	rationize(&a);
	rationize(&b);
	
	if(a.q==b.q)
	{
		sum.p = a.p+b.p;
		sum.q = (a.q+b.q)/2;
		sum = ratiolize(sum.p, sum.q);
	}
	else
	{
		int l = lcm(a.q, b.q);
		int for_a = l/a.q;
		int for_b = l/b.q;
		
		sum = ratiolize((for_a*a.p)+(for_b*b.p), l);
	}
	return sum;
}
//Rational Substraction.
Rational substract(Rational a, Rational b)
{
	Rational sub;
	
	rationize(&a);
	rationize(&b);
	
	if(a.q==b.q)
	{
		sub.p = a.p - b.p;
		sub.q = (a.q+b.q)/2;
		sub = ratiolize(sub.p, sub.q);
	}
	else
	{
		int l = lcm(a.q, b.q);
		int for_a = l/a.q;
		int for_b = l/b.q;
		
		sub = ratiolize((for_a*a.p)-(for_b*b.p), l);
	}
	
	return sub;
}

//Rational Multipication.
Rational multipicate(Rational a, Rational b)
{
	Rational mul;
	
	rationize(&a);
	rationize(&b);
	
	mul = ratiolize(a.p*b.p, a.q*b.q);
	
	return mul;
}
//Rational Division.
Rational divide(Rational a, Rational b)
{
	Rational div;
	
	rationize(&a);
	rationize(&b);
	
	div = ratiolize(a.p*b.q, a.q*b.p);
	
	return div;
}
