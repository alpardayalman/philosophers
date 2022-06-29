#include "../inc/philosophers.h"

bool	checker(int ac, char **av)
{
	int	i;

	if (ac > 6 || ac < 5)
	{
		ft_printf("yeterince veyahutta cok fazla arguman girdiniz\n");
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (i < ac)
	{
		if (!ft_str_isnum(av[i]) || ft_atoi(av[i]) <= 0)
			exit(EXIT_FAILURE);
		i++;
	}
	if (ac == 5)
		return (0);
	return (1);
}