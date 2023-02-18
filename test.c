#include <stdio.h>

int main()
{
	char	x;
	char	*str;

	str = "test";
	x = 33;
	while (x < 127)
		printf("%c", x++);
}
