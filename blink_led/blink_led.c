#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/timer.h>

#define GPIO_LED_PIN 28 /* Connected to pin 12 on BB P9 */
#define LED_BLINK_RATE 1000 /* Rate in milliseconds */

static int led_current_state = 0;
static struct timer_list timer;

void timer_callback(struct timer_list * this_timer){
    
    int result;

    printk(KERN_INFO "blink_led: Timer callback called.\n");
    printk(KERN_INFO "blink_led: Toggling LED.\n");
    led_current_state = (led_current_state == 0) ? 1 : 0;
    gpio_set_value(GPIO_LED_PIN, led_current_state);

    printk(KERN_INFO "blink_led: Restarting timer.\n");
    if((result = mod_timer(this_timer, jiffies + msecs_to_jiffies(LED_BLINK_RATE))) < 0) {
        printk(KERN_ERR "blink_led: Could not trigger timer. Result is %d\n", result);
    }
}

static int __init init_function(void) {

    int result;

	/* Module entry function */
	printk(KERN_INFO "blink_led: Loading module...\n");
	printk(KERN_INFO "blink_led: Requesting GPIO\n");
    if(!gpio_is_valid(GPIO_LED_PIN)){
        printk(KERN_ERR "blink_led: GPIO pin is not valid\n");
        return -ENODEV;
    }

    /* Request GPIO Pin */
    if((result = gpio_request(GPIO_LED_PIN, "my_led")) < 0) {
        printk(KERN_ERR "blink_led: GPIO pin request failed. Failure code is %d\n", result);
        return -EIO;
    }
    else {
        printk(KERN_INFO "blink_led: GPIO request done. Return value is %d\n", result);
    }

    /* Set direction as output */        
    if((result = gpio_direction_output(GPIO_LED_PIN, 0)) < 0){
        printk(KERN_ERR "blink_led: GPIO pin request failed. Result is %d\n", result);
        return -EIO;
    }
    else {
        printk(KERN_INFO "blink_led: GPIO output direction set done. Setting default value to 0. Result value is %d\n", result);
    }

    /* Configure timer */
    timer_setup(&timer, timer_callback, 0);
    if((result = mod_timer(&timer, jiffies + msecs_to_jiffies(LED_BLINK_RATE))) < 0) {
        printk(KERN_ERR "blink_led: Could not trigger timer. Result is %d\n", result);
    }

	return 0;

}

static void __exit exit_function(void) {

    int result;

	/* Module exit function */
	printk(KERN_INFO "Exiting module...\n");
    result = del_timer_sync(&timer);
    if(result) {
        printk(KERN_INFO "blink_led: Timer is in use\n");
    }

}


module_init(init_function);
module_exit(exit_function);
MODULE_AUTHOR("Sunil Fernandes <sunil.fernandes@gmail.com>");
MODULE_DESCRIPTION("LED Blink Example");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
