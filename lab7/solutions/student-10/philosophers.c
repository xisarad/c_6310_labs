#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef enum e_state
{
	THINKING,
	HUNGRY,
	EATING
}	t_state;

typedef enum e_philo_flags
{
	PHILO_NONE		= 0,
	PHILO_HAS_LEFT	= 1 << 0,
	PHILO_HAS_RIGHT	= 1 << 1
}	t_philo_flags;

typedef struct s_philosopher
{
	int				id;
	t_state			state;
	t_philo_flags	flags;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

static void	print_state(t_philosopher *philo, const char *action)
{
	printf("Philosopher %d is %s\n", philo->id, action);
}

static void	think(t_philosopher *philo)
{
	philo->state = THINKING;
	print_state(philo, "THINKING");
	usleep(500000);
}

static void	take_forks(t_philosopher *philo)
{
	philo->state = HUNGRY;
	print_state(philo, "HUNGRY");

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->flags |= PHILO_HAS_LEFT;
		print_state(philo, "took left fork");
		pthread_mutex_lock(philo->right_fork);
		philo->flags |= PHILO_HAS_RIGHT;
		print_state(philo, "took right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo->flags |= PHILO_HAS_RIGHT;
		print_state(philo, "took right fork");
		pthread_mutex_lock(philo->left_fork);
		philo->flags |= PHILO_HAS_LEFT;
		print_state(philo, "took left fork");
	}
}

static void	eat(t_philosopher *philo)
{
	philo->state = EATING;
	print_state(philo, "EATING");
	usleep(500000);
}

static void	put_forks(t_philosopher *philo)
{
	if (philo->flags & PHILO_HAS_LEFT)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->flags &= ~PHILO_HAS_LEFT;
		print_state(philo, "put left fork");
	}
	if (philo->flags & PHILO_HAS_RIGHT)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->flags &= ~PHILO_HAS_RIGHT;
		print_state(philo, "put right fork");
	}
	print_state(philo, "put forks");
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	int				cycles;

	philo = (t_philosopher *)arg;
	cycles = 0;
	while (cycles < 5)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		cycles++;
	}
	return (NULL);
}

int	main(void)
{
	t_philosopher		philosophers[5];
	pthread_mutex_t		forks[5];
	int					i;

	i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		philosophers[i].id = i + 1;
		philosophers[i].state = THINKING;
		philosophers[i].flags = PHILO_NONE;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % 5];
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	printf("All philosophers finished dining!\n");
	return (0);
}
