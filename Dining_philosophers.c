#include <rtthread.h>

#define THREAD_PRIORITY       6
#define THREAD_STACK_SIZE     512
#define THREAD_TIMESLICE      5

static rt_mutex_t mutex_fork1 = RT_NULL;
static rt_mutex_t mutex_fork2 = RT_NULL;
static rt_mutex_t mutex_fork3 = RT_NULL;
static rt_mutex_t mutex_fork4 = RT_NULL;
static rt_mutex_t mutex_fork5 = RT_NULL;

static rt_sem_t sem_fork1 = RT_NULL;
static rt_sem_t sem_fork2 = RT_NULL;
static rt_sem_t sem_fork3 = RT_NULL;
static rt_sem_t sem_fork4 = RT_NULL;
static rt_sem_t sem_fork5 = RT_NULL;

static rt_thread_t philosopher1 = RT_NULL;
static rt_thread_t philosopher2 = RT_NULL;
static rt_thread_t philosopher3 = RT_NULL;
static rt_thread_t philosopher4 = RT_NULL;
static rt_thread_t philosopher5 = RT_NULL;

void philosopher1_entry(void *parameter)
{
	while(1)
      {
          rt_mutex_take(mutex_fork1, RT_WAITING_FOREVER);
					rt_sem_take(sem_fork1, RT_WAITING_FOREVER);
					rt_kprintf("philosopher1 take fork1.\n" );
          rt_mutex_take(mutex_fork5, RT_WAITING_FOREVER);      
					rt_sem_take(sem_fork5, RT_WAITING_FOREVER);				
          rt_kprintf("philosopher1 take fork5.\n" ); 
					rt_kprintf("==============================>philosopher1 is eating.\n" ); 
          rt_sem_release(sem_fork5);
					rt_mutex_release(mutex_fork5);
					rt_kprintf("philosopher1 put down fork5.\n" );
          rt_sem_release(sem_fork1);
					rt_mutex_release(mutex_fork1);
					rt_kprintf("philosopher1 put down fork1.\n" );
					rt_thread_mdelay(50);
       }
}

void philosopher2_entry(void *parameter)
{
	while(1)
      {
          rt_mutex_take(mutex_fork2, RT_WAITING_FOREVER);  
					rt_sem_take(sem_fork2, RT_WAITING_FOREVER);
					rt_kprintf("philosopher2 take fork2.\n" );        
          rt_mutex_take(mutex_fork1, RT_WAITING_FOREVER);   
					rt_sem_take(sem_fork1, RT_WAITING_FOREVER);
          rt_kprintf("philosopher2 take fork1.\n" ); 
					rt_kprintf("==============================>philosopher2 is eating.\n" ); 
					rt_sem_release(sem_fork1);
          rt_mutex_release(mutex_fork1);
					rt_kprintf("philosopher2 put down fork1.\n" );
					rt_sem_release(sem_fork2);
          rt_mutex_release(mutex_fork2);
					rt_kprintf("philosopher2 put down fork2.\n" );
					rt_thread_mdelay(50);
       }
}

void philosopher3_entry(void *parameter)
{
	while(1)
      {
          rt_mutex_take(mutex_fork3, RT_WAITING_FOREVER);  
					rt_sem_take(sem_fork3, RT_WAITING_FOREVER);
					rt_kprintf("philosopher3 take fork3.\n" );  
          rt_mutex_take(mutex_fork2, RT_WAITING_FOREVER);    
					rt_sem_take(sem_fork2, RT_WAITING_FOREVER);
          rt_kprintf("philosopher3 take fork2.\n" ); 
					rt_kprintf("==============================>philosopher3 is eating.\n" );  
					rt_sem_release(sem_fork2);
          rt_mutex_release(mutex_fork2);
					rt_kprintf("philosopher3 put down fork2.\n" );
					rt_sem_release(sem_fork3);
          rt_mutex_release(mutex_fork3);
					rt_kprintf("philosopher3 put down fork3.\n" );
					rt_thread_mdelay(50);
       }
}

void philosopher4_entry(void *parameter)
{
	while(1)
      {
          rt_mutex_take(mutex_fork4, RT_WAITING_FOREVER);  
					rt_sem_take(sem_fork4, RT_WAITING_FOREVER);
					rt_kprintf("philosopher4 take fork4.\n" );  
          rt_mutex_take(mutex_fork3, RT_WAITING_FOREVER);  
					rt_sem_take(sem_fork3, RT_WAITING_FOREVER);        
          rt_kprintf("philosopher4 take fork3.\n" );  
					rt_kprintf("==============================>philosopher4 is eating.\n" ); 
					rt_sem_release(sem_fork3);
          rt_mutex_release(mutex_fork3);
					rt_kprintf("philosopher4 put down fork3.\n" );
					rt_sem_release(sem_fork4);
          rt_mutex_release(mutex_fork4);
					rt_kprintf("philosopher4 put down fork4.\n" );
					rt_thread_mdelay(50);
       }
}

void philosopher5_entry(void *parameter)
{
	while(1)
      {
          rt_mutex_take(mutex_fork5, RT_WAITING_FOREVER);  
					rt_sem_take(sem_fork5, RT_WAITING_FOREVER);
					rt_kprintf("philosopher5 take fork5.\n" );  
          rt_mutex_take(mutex_fork4, RT_WAITING_FOREVER);    
					rt_sem_take(sem_fork4, RT_WAITING_FOREVER);
          rt_kprintf("philosopher5 take fork4.\n" );  
					rt_kprintf("==============================>philosopher5 is eating.\n" );     
					rt_sem_release(sem_fork4);
          rt_mutex_release(mutex_fork4);
					rt_kprintf("philosopher5 put down fork4.\n" );
					rt_sem_release(sem_fork5);
          rt_mutex_release(mutex_fork5);
					rt_kprintf("philosopher5 put down fork5.\n" );
					rt_thread_mdelay(50);
       }
}

int phiosophers(void)
{
    /* 创建一个动态互斥量 */
    mutex_fork1 = rt_mutex_create("mutex_fork1", RT_IPC_FLAG_FIFO);
    if (mutex_fork1 == RT_NULL)
    {
        rt_kprintf("create fork1 mutex failed.\n");
        return -1;
    }
		
		/* 创建一个动态互斥量 */
    mutex_fork2 = rt_mutex_create("mutex_fork2", RT_IPC_FLAG_FIFO);
    if (mutex_fork2 == RT_NULL)
    {
        rt_kprintf("create fork2 mutex failed.\n");
        return -1;
    }
		
		/* 创建一个动态互斥量 */
    mutex_fork3 = rt_mutex_create("mutex_fork3", RT_IPC_FLAG_FIFO);
    if (mutex_fork3 == RT_NULL)
    {
        rt_kprintf("create fork3 mutex failed.\n");
        return -1;
    }
		
		/* 创建一个动态互斥量 */
    mutex_fork4 = rt_mutex_create("mutex_fork4", RT_IPC_FLAG_FIFO);
    if (mutex_fork4 == RT_NULL)
    {
        rt_kprintf("create fork4 mutex failed.\n");
        return -1;
    }
		
		/* 创建一个动态互斥量 */
    mutex_fork5 = rt_mutex_create("mutex_fork5", RT_IPC_FLAG_FIFO);
    if (mutex_fork5 == RT_NULL)
    {
        rt_kprintf("create fork5 mutex failed.\n");
        return -1;
    }
		
		/* 创建一个动态信号量，初始值是1 */
    sem_fork1 = rt_sem_create("sem_fork1", 1, RT_IPC_FLAG_FIFO);
    if (sem_fork1 == RT_NULL)
    {
        rt_kprintf("create fork1 semaphore failed.\n");
        return -1;
    }
    else
    {
        rt_kprintf("create done. fork1 semaphore value = 0.\n");
    }
		
		/* 创建一个动态信号量，初始值是1 */
    sem_fork2 = rt_sem_create("sem_fork2", 1, RT_IPC_FLAG_FIFO);
    if (sem_fork2 == RT_NULL)
    {
        rt_kprintf("create fork2 semaphore failed.\n");
        return -1;
    }
    else
    {
        rt_kprintf("create done. fork2 semaphore value = 0.\n");
    }
		
		/* 创建一个动态信号量，初始值是1 */
    sem_fork3 = rt_sem_create("sem_fork3", 1, RT_IPC_FLAG_FIFO);
    if (sem_fork3 == RT_NULL)
    {
        rt_kprintf("create fork3 semaphore failed.\n");
        return -1;
    }
    else
    {
        rt_kprintf("create done. fork3 semaphore value = 0.\n");
    }
		
		/* 创建一个动态信号量，初始值是1 */
    sem_fork4 = rt_sem_create("sem_fork4", 1, RT_IPC_FLAG_FIFO);
    if (sem_fork4 == RT_NULL)
    {
        rt_kprintf("create fork4 semaphore failed.\n");
        return -1;
    }
    else
    {
        rt_kprintf("create done. fork4 semaphore value = 0.\n");
    }
		
		/* 创建一个动态信号量，初始值是1 */
    sem_fork5 = rt_sem_create("sem_fork5", 1, RT_IPC_FLAG_FIFO);
    if (sem_fork5 == RT_NULL)
    {
        rt_kprintf("create fork5 semaphore failed.\n");
        return -1;
    }
    else
    {
        rt_kprintf("create done. fork5 semaphore value = 0.\n");
    }

		//哲学家1
		philosopher1 = rt_thread_create("philosopher1",
                                    philosopher1_entry, RT_NULL,
                                    THREAD_STACK_SIZE,
                                    THREAD_PRIORITY, THREAD_TIMESLICE);
    if (philosopher1 != RT_NULL)
    {
        rt_thread_startup(philosopher1);
    }
    else
    {
        rt_kprintf("create thread philosopher1 failed");
        return -1;
    }
		
		//哲学家2
		philosopher2 = rt_thread_create("philosopher2",
                                    philosopher2_entry, RT_NULL,
                                    THREAD_STACK_SIZE,
                                    THREAD_PRIORITY, THREAD_TIMESLICE);
    if (philosopher2 != RT_NULL)
    {
        rt_thread_startup(philosopher2);
    }
    else
    {
        rt_kprintf("create thread philosopher2 failed");
        return -1;
    }
		
		//哲学家3
		philosopher3 = rt_thread_create("philosopher3",
                                    philosopher3_entry, RT_NULL,
                                    THREAD_STACK_SIZE,
                                    THREAD_PRIORITY, THREAD_TIMESLICE);
    if (philosopher3 != RT_NULL)
    {
        rt_thread_startup(philosopher3);
    }
    else
    {
        rt_kprintf("create thread philosopher3 failed");
        return -1;
    }
		
		//哲学家4
		philosopher4 = rt_thread_create("philosopher4",
                                    philosopher4_entry, RT_NULL,
                                    THREAD_STACK_SIZE,
                                    THREAD_PRIORITY, THREAD_TIMESLICE);
    if (philosopher4 != RT_NULL)
    {
        rt_thread_startup(philosopher4);
    }
    else
    {
        rt_kprintf("create thread philosopher4 failed");
        return -1;
    }
		
		//哲学家5
		philosopher5 = rt_thread_create("philosopher5",
                                    philosopher5_entry, RT_NULL,
                                    THREAD_STACK_SIZE,
                                    THREAD_PRIORITY, THREAD_TIMESLICE);
    if (philosopher5 != RT_NULL)
    {
        rt_thread_startup(philosopher5);
    }
    else
    {
        rt_kprintf("create thread philosopher5 failed");
        return -1;
    }
		
		return 0;
}


/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(phiosophers, phiosophers sample);
