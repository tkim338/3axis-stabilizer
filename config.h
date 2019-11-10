/*
 * config.h
 *
 *  Created on: Nov 10, 2019
 *      Author: tkim
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define multi_LED GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2
#define red_LED GPIO_PIN0
#define green_LED GPIO_PIN1
#define blue_LED GPIO_PIN2

void initLEDs(void) {
    // multi-colored LED (P2.0, P2.1, P2.2)
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, red_LED);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, green_LED);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, blue_LED);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, multi_LED);
}

volatile eUSCI_I2C_MasterConfig i2cConfig =
{
 EUSCI_B_I2C_CLOCKSOURCE_SMCLK,
 3E6, // 3MHz
 EUSCI_B_I2C_SET_DATA_RATE_400KBPS, // I2C clock 400kHz
 0, // no byte counter threshold
 EUSCI_B_I2C_NO_AUTO_STOP
};

void initI2C(void) {
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION); // SCL
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); // SDA

    MAP_I2C_initMaster(EUSCI_B1_BASE, (const eUSCI_I2C_MasterConfig *)&i2cConfig)

    MAP_I2C_enableModule(EUSCI_B1_BASE);
}

void initAll() {
    initLEDs();
}

void ledControl(char color, bool state) {
    if (color == 'r') {
        if (state == true) MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, red_LED);
        else MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, red_LED);
    }
    else if (color == 'g') {
        if (state == true) MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, green_LED);
        else MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, green_LED);
    }
    else {
        if (state == true) MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, blue_LED);
        else MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, blue_LED);
    }
}


void pause(int n) {
    int c;
    for (c = 0; c < n; c++) {
        // wait here for n clock cycles
    }
}

#endif /* CONFIG_H_ */
