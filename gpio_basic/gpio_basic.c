#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define GPIO_LED_PIN 28 /* Connected to pin 12 on BB P9 */

static int __init init_function(void) {

    int result;

	/* Module entry function */
	printk(KERN_INFO "gpio_basic: Loading module...\n");
	printk(KERN_INFO "gpio_basic: Requesting GPIO\n");
    if(!gpio_is_valid(GPIO_LED_PIN)){
        printk(KERN_ERR "gpio_basic: GPIO pin is not valid\n");
        return -ENODEV;
    }

    if((result = gpio_request(GPIO_LED_PIN, "my_led")) < 0) {
        printk(KERN_ERR "gpio_basic: GPIO pin request failed. Failure code is %d\n", result);
        return -EIO;
    }
    else {
        printk(KERN_INFO "gpio_basic: GPIO request done. Return value is %d\n", result);
    }

        
    if((result = gpio_direction_output(GPIO_LED_PIN, 0)) < 0){
        printk(KERN_ERR "gpio_basic: GPIO pin request failed. Result is %d\n", result);
        return -EIO;
    }
    else {
        printk(KERN_INFO "gpio_basic: GPIO output direction set done. Setting default value to 0. Result value is %d\n", result);
    }


    printk(KERN_INFO "gpio_basic: Set GPIO pin value to 1\n");
    gpio_set_value(GPIO_LED_PIN, 1);

	return 0;

}

static void __exit exit_function(void) {

	/* Module exit function */
    printk(KERN_INFO "gpio_basic: Set GPIO pin value to 0\n");
    gpio_set_value(GPIO_LED_PIN, 0);
    printk(KERN_INFO "gpio_basic: Releasing GPIO\n");
    gpio_free(GPIO_LED_PIN);
	printk(KERN_INFO "Exiting module...\n");
}


module_init(init_function);
module_exit(exit_function);
MODULE_AUTHOR("Sunil Fernandes <sunil.fernandes@gmail.com>");
MODULE_DESCRIPTION("GPIO Basic Example");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
