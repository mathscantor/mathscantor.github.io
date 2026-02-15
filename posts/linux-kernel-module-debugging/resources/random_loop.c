#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/random.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mathscantor");
MODULE_DESCRIPTION("LKM that generates a random number every second");
MODULE_VERSION("0.1");

static struct task_struct *thread;

// Thread function: generates random number every second
static int random_thread_fn(void *data)
{
    while (!kthread_should_stop()) {
        u32 rand;
        get_random_bytes(&rand, sizeof(rand));
        pr_info("random_loop_module: random number = %u\n", rand);
        msleep(1000);
    }
    return 0;
}

static int __init random_loop_init(void)
{
    pr_info("random_loop_module: loaded\n");
    thread = kthread_run(random_thread_fn, NULL, "random_loop_thread");
    if (IS_ERR(thread)) {
        pr_err("random_loop_module: failed to create thread\n");
        return PTR_ERR(thread);
    }

    return 0;
}

static void __exit random_loop_exit(void)
{
    if (thread)
        kthread_stop(thread);

    pr_info("random_loop_module: unloaded\n");
}

module_init(random_loop_init);
module_exit(random_loop_exit);