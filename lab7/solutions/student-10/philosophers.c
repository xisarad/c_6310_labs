/*
 * Лабораторная работа №7
 * Студент: номер 10
 * Задача: Обедающие философы
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* ========== ENUMS ========== */

/* Состояние философа */
typedef enum e_state
{
	THINKING,
	HUNGRY,
	EATING
}	t_state;

/* Флаги для отслеживания вилок в руках (флаговый enum) */
typedef enum e_philo_flags
{
	PHILO_NONE		= 0,
	PHILO_HAS_LEFT	= 1 << 0,
	PHILO_HAS_RIGHT	= 1 << 1
}	t_philo_flags;

/* ========== STRUCTURES ========== */

typedef struct s_philosopher
{
	int				id;
	t_state			state;
	t_philo_flags	flags;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

/* Глобальный мьютекс для синхронизации вывода в консоль */
pthread_mutex_t	g_print_mutex = PTHREAD_MUTEX_INITIALIZER;

/* ========== SAFE PRINT FUNCTION ========== */

/**
 * Безопасный вывод сообщений в консоль.
 * Использует мьютекс для предотвращения race condition при печати.
 */
void	safe_print(t_philosopher *philo, const char *action)
{
	pthread_mutex_lock(&g_print_mutex);
	printf("Philosopher %d is %s\n", philo->id, action);
	pthread_mutex_unlock(&g_print_mutex);
}

/* ========== PHILOSOPHER ACTIONS ========== */

/**
 * Философ думает.
 */
void	think(t_philosopher *philo)
{
	philo->state = THINKING;
	safe_print(philo, "THINKING");
	usleep(500000); /* 0.5 seconds */
}

/**
 * Философ берёт вилки.
 * Для предотвращения deadlock философы с чётным номером сначала берут левую вилку,
 * а с нечётным — правую.
 */
void	take_forks(t_philosopher *philo)
{
	philo->state = HUNGRY;
	safe_print(philo, "HUNGRY");

	if (philo->id % 2 == 0)
	{
		/* Чётный: сначала левая, потом правая */
		pthread_mutex_lock(philo->left_fork);
		philo->flags |= PHILO_HAS_LEFT;
		safe_print(philo, "took left fork");
		
		pthread_mutex_lock(philo->right_fork);
		philo->flags |= PHILO_HAS_RIGHT;
		safe_print(philo, "took right fork");
	}
	else
	{
		/* Нечётный: сначала правая, потом левая */
		pthread_mutex_lock(philo->right_fork);
		philo->flags |= PHILO_HAS_RIGHT;
		safe_print(philo, "took right fork");
		
		pthread_mutex_lock(philo->left_fork);
		philo->flags |= PHILO_HAS_LEFT;
		safe_print(philo, "took left fork");
	}
}

/**
 * Философ ест.
 */
void	eat(t_philosopher *philo)
{
	philo->state = EATING;
	safe_print(philo, "EATING");
	usleep(500000); /* 0.5 seconds */
}

/**
 * Философ кладёт вилки.
 */
void	put_forks(t_philosopher *philo)
{
	if (philo->flags & PHILO_HAS_LEFT)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->flags &= ~PHILO_HAS_LEFT;
		safe_print(philo, "put left fork");
	}
	if (philo->flags & PHILO_HAS_RIGHT)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->flags &= ~PHILO_HAS_RIGHT;
		safe_print(philo, "put right fork");
	}
	safe_print(philo, "put forks");
}

/* ========== PHILOSOPHER ROUTINE ========== */

/**
 * Основной цикл философа.
 * Каждый философ выполняет 5 циклов: думает -> голодает -> ест -> думает...
 */
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

/* ========== MAIN ========== */

int	main(void)
{
	t_philosopher		philosophers[5];
	pthread_mutex_t		forks[5];
	int					i;

	/* Инициализация мьютексов для вилок */
	i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

	/* Инициализация философов */
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

	/* Создание потоков философов */
	i = 0;
	while (i < 5)
	{
		pthread_create(&philosophers[i].thread, NULL, philosopher_routine,
			&philosophers[i]);
		i++;
	}

	/* Ожидание завершения всех потоков */
	i = 0;
	while (i < 5)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}

	/* Уничтожение мьютексов вилок */
	i = 0;
	while (i < 5)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}

	/* Уничтожение мьютекса вывода (опционально, main завершается) */
	pthread_mutex_destroy(&g_print_mutex);

	printf("\nAll philosophers finished dining!\n");
	return (0);
}