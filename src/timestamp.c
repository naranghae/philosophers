
#include "philo.h"

char	*message(int type)
{
	if (type == PICKFORK)
		return (" has taken a fork");
	else if (type == EATING)
		return (" is eating");
	else if (type == SLEEPING)
		return (" is sleeping");
	else if (type == THINKING)
		return (" is thinking");
	else if (type == DIE)
		return (" died");
	else
		return ("Limited dining finished");
}

void	timestamp(t_philo *philo, int type)
{
	char	*str;

	str = NULL;
	pthread_mutex_lock(&philo->info->message);
	if (!philo->info->quit)
	{
		str = message(type);
		printf("%lldms	", get_time() - philo->info->start_time);
		if (type != EAT_FINISHED)
			printf("%d", philo->pos);
		printf("%s\n", str);
		if (type == DIE || type == EAT_FINISHED)
		{
			philo->info->quit = 1;
			return ;
		}
	}
	pthread_mutex_unlock(&philo->info->message);
}

