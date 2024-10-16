#include <iostream>
#include <limits>
#include <climits>
using namespace std;


int main(){

  //know the range of data types 
  cout << "short: sizeof(short) is " << sizeof(short) << " bytes" << endl;
  cout << "\tmax is " << SHRT_MAX << ", min is " <<SHRT_MIN << endl;
  cout << "int: sizeof(int) is " << sizeof(int) << " bytes" << endl;
  cout << "\tmax is " << INT_MAX << ", min is " <<INT_MIN << endl;
  cout << "int: sizeof(long) is " << sizeof(long int) << " bytes" << endl;
  cout << "\tmax is " << LONG_MAX << ", min is " <<LONG_MIN << endl;
  cout << "int: sizeof(long long int) is " << sizeof(long long int) << " bytes" << endl;
  cout << "\tmax is " << LLONG_MAX << ", min is " <<LLONG_MIN << endl;

  cout << "---------- Task 1-------------" <<endl;
  /* Task 1: explain why you got correct or overflowed value in the following 10 examples.
     Note: Your answer should focus on what type conversions happened.
  */
  
  //for example
  //1a, x and y are first integer promoted to be int before the addition. Then the result of x+y (int) is stored in a register, I am using a 64bit system, so my registers are 8 bytes. 8-byte register is big enough to hold the result of 20000+20000, so output value is the correct value.
  short x = 20000;
  short y = 20000;
  cout << "x + y = " << x+y << endl;

  //1b, x and y are promoted to int prior to the addition. The result of the addition is accurate, but is truncated to fit into z, which is a signed short (maxes out at ~32000), The output will be inaccurate, printing roughly -24000

    x = 20000; 
    y = 20000; 
    short z = x + y; //z is out of range now 
    cout << "z = " << z << endl; 

    //1c, once again, x and y are promoted. The result can now be stored in the integer z1, which caps out at ~2 billion, so the output value should be accurate
    x = 20000; 
    y = 20000; 
    int z1 = x + y; 
    cout << "int z1 = " << z1 << endl; 

    //1d, this is essentially the same as 1c, except x and y are promoted manually. The output value will once again be accurate.
    x = 20000; 
    y = 20000;
    int z2 = (int)x + (int)y; 
    cout << "int z2 = " << z2 << endl;
  

    //example 2.2a, both integers are left as is, meaning the addition result will be an integer. Signed integers max at ~2 billion, so the result will overflow and be inaccurate
    int x_int = 2000000000; 
    int y_int = 2000000000; 
    cout << "x_int + y_int = " << x_int + y_int << endl;

    //new example, the long long integers behave similar to 2.2a, but this time, the addition result will be a matching long long, which will be more than enough to hold our correct answer of 4 billion
    long long  x_int_ll = 2000000000; 
    long long  y_int_ll = 2000000000; 
    cout << "x_int_ll + y_int_ll = " << x_int_ll + y_int_ll << endl;

    //example 2.2b, z_int is too small to hold 4 billion, since it is an int, so our output will once again be wrong.
    x_int = 2000000000; 
    y_int = 2000000000; 
    int z_int = x_int + y_int; //z is out of range now 
    cout << "z_int = " << z_int << endl; 
    
    //example 2.2c, once again, we are adding 2 ints, so the result will be an int, which is too small for our data. Out output will be wrong
    x_int = 2000000000; 
    y_int = 2000000000; 
    long long z1_ll = x_int + y_int; 
    cout << "long z1_ll = " << z1_ll << endl;

    //new example, since one of our numbers is a long long, our integer will be promoted, resulting in a long long that is large enough to store our correct answer of 4 billion
    x_int = 2000000000; 
    long long y_ll = 2000000000;
    long long z2_ll = x_int + y_ll; 
    cout << "long long z2_ll = " << z2_ll << endl;

    //example 2.2d, since we are casting both integers, the result of our addition will be a long long, which is large enough for our answer
    x_int = 2000000000; 
    y_int = 2000000000;
    long long z2_llong = (long long)x_int + (long long)y_int; 
    cout << "long long z2_llong = " << z2_llong << endl;


  

  cout << "---------------Task 2-------------" <<endl;
  //-----task2: add in checks---------
  //for addition, subtruction, and division operations
  //for example, for addition operation
  
  int num1, num2, result_add, result_sub, result_div;
  cout << "For addition operation: " <<endl;
  cout << "    Enter integer1: ";
  cin >> num1;
  cout << "    Enter integer2: ";
  cin >> num2;

  //checks for addition operation
  if (((num1 > 0) && (num2 >0) && (num1 > (INT_MAX - num2)))||
      ((num1 < 0) && (num2 <0) && (num1 < (INT_MIN - num2))))
      {cout << "Integer overflow!" <<endl;
	exit(1);
      }
  else {
    result_add = num1+num2;
    cout << "sum of integer1 and integer2 is: " << result_add <<endl;
  }

  //Your turn, for subtraction operation, add checks

  cout << "For subtraction operation: " <<endl;
  cout << "Enter integer1: ";
  cin >> num1;
  cout << "Enter integer2: ";
  cin >> num2;

  //your code here
  if((num1 > 0 && num2 < 0 && num1 > INT_MAX + num2) ||
     (num1 < 0 && num2 > 0 && num1 < INT_MAX + num2)) {
	  cout << "Integer Overflow" << endl;
	  exit(1);
  }

  result_sub = num1-num2;




  //for division operation, add checks
  //HINTS:(1) we talked about when integer overflow could happen in division :)
  //          you need to check for that specific condition
  //      (2) your code should also check for the divide by 0 problem!
   cout << "For division operation: " <<endl;
  cout << "Enter integer1: ";
  cin >> num1;
  cout << "Enter integer2: ";
  cin >> num2;

  //your code here
  if(num2 == 0) {
  	cout << "Division by 0 Error" << endl;
	exit(1);
  }
  if(num1 == INT_MIN && num2 == -1) {
  	cout << "Integer overflow" << endl;
	exit(1);
  }


  result_div = num1/num2; 





  //Don't forget to run your program to test whether your checks can catch the integer overflows
  
  //For lab 4, you only need to turn in this .cpp file.
  //your explanations should be written as comments in this .cpp file
}
