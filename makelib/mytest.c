#include <stdio.h>
#include "mylib.h"
#include "foo.h"
#include "bar.h"
#include "baz.h"

int main(void)
{
	printf("I am main()\n");
	foo();
	bar();
	baz();
	printf("FOO is %d\n", FOO);
	printf("BAR is %d\n", BAR);
	printf("BAZ is %d\n", BAZ);
	return 0;
}
