#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "test_printf.h"


void test_printf_string(){
	printf("%s\n", "Just the string flag and no extra text"); // test 1

	printf("%s\n","Print just this","Shouldn't print");

	printf("%s\n","Print just this","Shouldn't print1",
		   "Shouldn't prin2", "Shouldn't print3", "Shouldn't print4",
	   	   "Shouldn't print5");

	printf("%s%s\n","Print this"," (and this)");

	printf("%s-%s\n","Print this","(and this)");

	printf("Undefined result: %s\n", 3.2); // Shouldn't print float

	printf("Undefined result: %s\n", 150); // Shouldn't print int

	printf("Undefined result: %s\n", -124); // Shouldn't print int


	printf("%s\n",
	"This is a long string that should wrap over to the next line to test how the terminal	will behave");


	printf("%s%s\n","Print this once");

	printf("%s%s\n\n"); // Erroneous behavior, va_arg will pull last argument
					   // in memory, which, in this case, is the last string
					   // passed in by the previous printf call. This happens
					   // due to string interning/pooling and va_list holding
					   // the same memory location of the past call to va_arg.

}


void test_printf_char(){

	printf("48 ('0') == %c\n",48);

	printf("-1 == %c\n",-1);

	printf("4.4 == %c\n",4.4);

	printf("-20202 == %c\n",-20202);

	printf("-20202 == %c%c\n",-20202); //undefined

	printf("64 (@) == %c%c\n",64); //undefined

}


void test_printf_int(){
	printf("%d\n",-1);

	printf("%d\n",INT_MAX);

	printf("%d\n",INT_MIN);

	printf("%d\n",LONG_MAX); // prints INT_MAX (32 bit system)

	printf("%d\n",LONG_MIN); // prints INT_MIN (32 bit system)


}

void test_printf_mixed(){
	// TODO fill
}

void test_scroll() {
	// Rows should display letters from B-Y with a blank line at the end
	// which is then filled by the last two printf's in this function.
	// The second last printf statement should expand across the second and
	// third last lines (23rd and 24th). The last printf statement should print
	// on the last line.
	for(int i = 0; i < 25; i++){
		for(int j=0; j < 80; j++){
			printf("%c", 65+i);
		}
	}
	printf(" Print on last line and print a really long string that exceeds the width of the last line\n");
	printf("Last words");
}

void test_scroll2(){

	for(int i=0; i < 25; i++){
		for(int j=0; j<1000000; j++) printf("");

		if (i%3==0){
			printf("/home/User: $ ls");
			if(i!=24)printf("\n");
		}
		else if (i%3==1){
			printf("/home/User: $ cat\n");
		}
		else{
			printf("/home/User: $ tr\n");
		}
	}
}
