#include<iostream>

using namespace std;

int callA=0;
int callB=0;
int callC=0;
class A
{
protected:
   
   void func(int  & a)
   {
      a=a*2;
      callA++;
   }
};

class B
{
protected:
   void func(int & a)
   {
      a=a*3;
      callB++;
   }
};

class C
{
protected:
   void func(int & a)
   {
      a=a*5;
      callC++;
   }
};

class D : A, B, C
{

	int val;
	public:
		//Initially val is 1
		 D()
		 {
		 	val=1;
		 }


		 //Implement this function
		 void update_val(int new_val)
		 {
             int tmp = new_val;
             while (tmp >= 5 && tmp%5 == 0) {
                 C::func(val);
                 tmp = tmp/5;
             }

             tmp = new_val;
             while (tmp >= 3 && tmp%3 == 0) {
                 B::func(val);
                 tmp = tmp/3;
             }

             tmp = new_val;
             while (tmp >= 2 && tmp%2 == 0) {
                 A::func(val);
                 tmp = tmp/2;
             }
		 }
		 //For Checking Purpose
		 void check(int); //Do not delete this line.
};
