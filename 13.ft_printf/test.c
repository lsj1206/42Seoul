#include <stdio.h>
int main (void)
{
	char	*str = "abcdefg";
	int	i = 2147483647;
	int	j = -2147483648;

	ft_printf("[%%c = %c || ", 'c');
	printf("%c]\n", 'c');
	ft_printf("[%%s = %s || ", str);
	printf("%s]\n", str);
	ft_printf("[%%p = %p || ", str);
	printf("%p]\n", str);
	ft_printf("[%%d = %d || ", i);
	printf("%d]\n", i);
	ft_printf("[%%d = %d || ", j);
	printf("%d]\n", j);
	ft_printf("[%%i = %i || ", i);
	printf("%i]\n", i);
	ft_printf("[%%i = %i || ", j);
	printf("%i]\n", j);
	ft_printf("[%%u = %u || ", i);
	printf("%u]\n", i);
	ft_printf("[%%u = %u || ", j);
	printf("%u]\n", j);
	ft_printf("[%%x = %x || ", i);
	printf("%x]\n", i);
	ft_printf("[%%x = %x || ", j);
	printf("%x]\n", j);
	ft_printf("[%%X = %X || ", i);
	printf("%X]\n", i);
	ft_printf("[%%X = %X || ", j);
	printf("%X]\n", j);
	return (0);
}
