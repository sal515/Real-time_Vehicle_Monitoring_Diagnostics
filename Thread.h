/*
 * Thread.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Salman
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

namespace realtime_vehicle_monitoring_diagnostics
{
	// typedef void *(*start_routine_t)(void *);

	/* allocate multiple thread ids */
	// thread_ids = malloc (sizeof (pthread_t) * num_cpus);

	/* Before using attr structure - needs to be initialized */
	// pthread_attr_t attr;
	// … pthread_attr_init(&attr);

	/* 
	typedef struct {
    int                 __flags;
    size_t              __stacksize;
    void                *__stackaddr;
    void                (*__exitfunc)(void *status);
    int                 __policy;
    struct sched_param  __param;
    unsigned            __guardsize;
	} pthread_attr_t;
 	*/

	/* 
	 
	 To create a “joinable” thread (meaning that another thread can synchronize to its termination via pthread_join()), you'd use:

	(default)
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
	To create one that can't be joined (called a “detached” thread), you'd use:

	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
	 
	  */

	/* 
	 
	int
	pthread_attr_setschedparam (pthread_attr_t *attr,
								const struct sched_param *param);

	int
	pthread_attr_setschedpolicy (pthread_attr_t *attr,
								int policy);
	 
	  */

	/* Example with custon attr */
	/* 
	 pthread_attr_t attr;

	// initialize the attribute structure
	pthread_attr_init (&attr);

	// set the detach state to "detached"
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

	// override the default of INHERIT_SCHED
	pthread_attr_setinheritsched (&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy (&attr, SCHED_RR);
	attr.param.sched_priority = 15;

	// finally, create the thread
	pthread_create (NULL, &attr, new_thread, NULL);

	 
	  */

	/* consumer and producer tasks */
	/* 
	 
	#include <stdio.h>
	#include <pthread.h>

	int data_ready = 0;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t  condvar = PTHREAD_COND_INITIALIZER;

	void *
	consumer (void *notused)
	{
		printf ("In consumer thread...\n");
		while (1) {
			pthread_mutex_lock (&mutex);
			while (!data_ready) {
				pthread_cond_wait (&condvar, &mutex);
			}
			// process data
			printf ("consumer:  got data from producer\n");
			data_ready = 0;
			pthread_cond_signal (&condvar);
			pthread_mutex_unlock (&mutex);
		}
	}

	void *
	producer (void *notused)
	{
		printf ("In producer thread...\n");
		while (1) {
			// get data from hardware
			// we'll simulate this with a sleep (1)
			sleep (1);
			printf ("producer:  got data from h/w\n");
			pthread_mutex_lock (&mutex);
			while (data_ready) {
				pthread_cond_wait (&condvar, &mutex);
			}
			data_ready = 1;
			pthread_cond_signal (&condvar);
			pthread_mutex_unlock (&mutex);
		}
	}

	main ()
	{
		printf ("Starting consumer/producer example...\n");

		// create the producer and consumer threads
		pthread_create (NULL, NULL, producer, NULL);
		pthread_create (NULL, NULL, consumer, NULL);

		// let the threads run for a bit
		sleep (20);
	}
	 
	  */

#define THREAD_IDLE_PRIORITY (1)
#define THREAD_IDLE_PRIORITY (60)

	struct Thread_Control
	{
		// int data_ready = 0;
		pthread_mutex_t mutex;
		pthread_cond_t condvar;
	};

	typedef void *(*start_routine_t)(void *);

	class Thread
	{
	public:
		Thread();
		Thread(start_routine_t start_routine,
			   int sched_priority,
			   char *thread_name);
		// Thread(pthread_t thread,
		// 	   pthread_attr_t attr,
		// 	   start_routine_t start_routine,
		// 	   void *args);

		virtual ~Thread();

		char *thread_name;
		pthread_t thread;

		// int pthread_setschedprio( pthread_t thread, int prio );

		pthread_attr_t attr;
		struct sched_param params;
		start_routine_t start_routine;
		void *args;

		struct Thread_Control thread_control;

		void block();
		void signal();

		int destroy_thread(pthread_t thread);
		int change_priority_of_thread();
		// private:
	};

} // namespace realtime_vehicle_monitoring_diagnostics

#endif /* THREAD_H_ */
