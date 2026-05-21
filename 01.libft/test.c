#include <stdio.h>
#include "libft.h"

void del(void *c)
{
	int *p;
	p = (int *)c;
	*p = 0;
}

int main(void)
{
	int	a = 10;
	int	b = 20;
	int	c = 30;
	t_list	*test_lst;
	t_list	*test_new;
	t_list	*test_xxx;

	test_lst = ft_lstnew((void *)&a);
	printf("lst = %d\n", *(int *)test_lst->content);

	test_new = ft_lstnew((void *)&b);
	printf("new = %d\n", *(int *)test_new->content);

	ft_lstadd_front(&test_lst, test_new);

	printf("len = %d\n", ft_lstsize(test_lst));
	printf("last = %d\n", *(int *)ft_lstlast(test_lst)->content);

	test_xxx = ft_lstnew((void *)&c);
	ft_lstadd_back(&test_lst, test_xxx);
	printf("len = %d\n", ft_lstsize(test_lst));
	printf("last = %d\n", *(int *)ft_lstlast(test_lst)->content);

	ft_lstclear(&test_lst, del);
	printf("len = %d\n", ft_lstsize(test_lst));
	//printf("last = %d", *(int *)ft_lstlast(test_lst)->content);
	return (0);
}
