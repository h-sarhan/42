
// 	unsigned int	left;
// 	unsigned int	right;
// 	bool			success;
// 	t_phil			*phil;
// 	bool			left_held;
// 	bool			right_held;
// 	t_time_ms		time;

// 	phil = (t_phil *) phil_ptr;
// 	get_start_time(phil->phil_eat_time);
// 	if (phil->sim->num_phils == 1)
// 	{
// 		left = 0;
// 		right = 0;
// 	}
// 	else
// 	{
// 		left = phil->num - 1;
// 		right = phil->num;
// 	}
// 	if (phil->num == phil->sim->num_phils)
// 		right = 0;
// 	left_held = true;
// 	// if (left == right)
// 	// 	right_held = true;
// 	// else
// 		right_held = true;
// 	while (1)
// 	{
// 		if (phil->state == THINKING)
// 		{
// 			success = true;
// 			while ((left_held == true || right_held == true))	
// 			{
// 				left_held = read_fork_status(phil->sim, left, &success);
// 				if (left == right)
// 					right_held = true;
// 				else
// 					right_held = read_fork_status(phil->sim, right, &success);
// 				if (get_micro_time(phil->phil_eat_time, &success) >= phil->sim->time_to_die * 1000)
// 				{
// 					// printf("%d DIED WHILE WATING FOR FORK\n", phil->num);
// 					phil->state = DEAD;
// 					lock_mutex(&phil->sim->status_mutex, &success);
// 					if (phil->sim->status == true)
// 					{
// 						phil->sim->status = false;
// 						unlock_mutex(&phil->sim->status_mutex, &success);
// 						log_action(phil->sim, phil->num, &success, log_death);
// 					}
// 					else
// 						unlock_mutex(&phil->sim->status_mutex, &success);
// 					return (NULL);
// 				}
// 			}
// 			// lock_mutex(&phil->sim->logging_mutex, &success);
// 			// printf("fork %d and fork %d have been taken by philosopher %d\n", left, right, phil->num);
// 			// unlock_mutex(&phil->sim->logging_mutex, &success);
// 			// f | f | f
// 			set_fork_status(phil->sim, left, true, &success);
// 			set_fork_status(phil->sim, right, true, &success);
// 			// if (read_sim_status(phil->sim, &success) == false)
// 			// 	return (NULL);
// 			time = get_time(phil->sim->start_time, &success);
// 			lock_mutex(&phil->sim->logging_mutex, &success);
// 			log_fork(&time, phil->num, &success);
// 			log_fork(&time, phil->num, &success);
// 			log_eat(&time, phil->num, &success);
// 			unlock_mutex(&phil->sim->logging_mutex, &success);
// 			get_start_time(phil->phil_eat_time);
// 			sleepsleep(phil->sim->time_to_eat * 1000);
// 			set_fork_status(phil->sim, left, false, &success);
// 			set_fork_status(phil->sim, right, false, &success);
// 			if (read_sim_status(phil->sim, &success) == true)
// 				log_action(phil->sim, phil->num, &success, log_sleep);
// 			else
// 				return (NULL);
// 			phil->state = EATING;
// 		}
// 		if (phil->state == EATING)
// 		{
// 			phil->state = SLEEPING;
// 			if (get_micro_time(phil->phil_eat_time, &success) >= phil->sim->time_to_die * 1000)
// 			{
// 				// printf("%d DIED AFTER EATING\n", phil->num);

// 				phil->state = DEAD;
// 				lock_mutex(&phil->sim->status_mutex, &success);
// 				if (phil->sim->status == true)
// 				{
// 					phil->sim->status = false;
// 					unlock_mutex(&phil->sim->status_mutex, &success);
// 					// set_sim_status(phil->sim, false, &success);
// 					log_action(phil->sim, phil->num, &success, log_death);
// 				}
// 				else
// 					unlock_mutex(&phil->sim->status_mutex, &success);
// 				return (NULL);
// 			}
// 			time = phil->sim->time_to_sleep * 1000 + get_micro_time(phil->phil_eat_time, &success);
// 			if (time >= phil->sim->time_to_die * 1000)
// 			{
// 				phil->state = DEAD;
// 				// printf("%d GO HERE AND SLEEP %lums\n", phil->num, (phil->sim->time_to_die - phil->sim->time_to_sleep));
// 				sleepsleep((phil->sim->time_to_die * 1000 - get_micro_time(phil->phil_eat_time, &success)));
				
// 				lock_mutex(&phil->sim->status_mutex, &success);
// 				if (phil->sim->status == true)
// 				{
// 					phil->sim->status = false;
// 					unlock_mutex(&phil->sim->status_mutex, &success);
// 					lock_mutex(&phil->sim->logging_mutex, &success);
// 					printf("%-4lu %-3u has died\n", get_time(phil->phil_eat_time, &success), phil->num);
// 					unlock_mutex(&phil->sim->logging_mutex, &success);
// 				}
// 				else
// 					unlock_mutex(&phil->sim->status_mutex, &success);
// 				return (NULL);
// 			}
// 			else
// 				sleepsleep(phil->sim->time_to_sleep * 1000);
// 			if (read_sim_status(phil->sim, &success) == true)
// 				log_action(phil->sim, phil->num, &success, log_think);
// 			else
// 				return (NULL);
// 		}
// 		if (phil->state == SLEEPING)
// 		{
// 			phil->state = THINKING;
// 			if (get_micro_time(phil->phil_eat_time, &success) >= phil->sim->time_to_die * 1000)
// 			{
// 				phil->state = DEAD;
// 				printf("%d DIED AFTER SLEEPING\n", phil->num);
				
// 				lock_mutex(&phil->sim->status_mutex, &success);
// 				if (phil->sim->status == true)
// 				{
// 					phil->sim->status = false;
// 					unlock_mutex(&phil->sim->status_mutex, &success);
// 					log_action(phil->sim, phil->num, &success, log_death);
// 				}
// 				else
// 					unlock_mutex(&phil->sim->status_mutex, &success);
// 				return (NULL);
// 			}
// 		}
// 		if (phil->state == DEAD)
// 			return (NULL);
// 	}
// 	return (NULL);
// }
