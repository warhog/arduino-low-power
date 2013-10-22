#arduino-low-power

This is a simple and easy to use library that has the following features:

Supports all sleeping mode of ATmega328P:

* Idle.
* ADC reduction mode.
* Power save.
* Power down.
* Standby.
* Extended standby.

Selectable sleep duration:

* 15 ms, 30 ms, 60 ms, 120 ms, 250 ms, 500 ms, 1 s, 2 s, 4 s, 8 s, and forever (wake up using other resources) through on chip 125 kHz Watchdog timer. Using sleeping forever duration, the Watchdog timer module is not in use and will further reduce the current consumption by approximately 4 µA.

More:
* Option to shutdown Analog to Digital Converter (ADC) module to further reduce current consumption.
* Option to disable Brownout Detector (BOD) module to further reduce current consumption by approximately 17 µA. BOD module cannot be disabled through software in idle and ADC noise reduction mode. It can only be disabled through fuse setting in these 2 modes. 
* Option to shutdown Timer 2 module in idle, ADC noise reduction, power save, and extended standby mode. Timer 2 is used by the core of Arduino for PWM operation. 
* Option to shutdown Timer 0, Timer 1, USART0, TWI, and SPI module in idle mode.

We didn’t add any wake up functionality except using the Watchdog timer module to allow certain amount of sleep duration as we think other wake up resources (interrupt on pins, TWI address match, ADC conversion complete, SPI serial transfer complete, EEPROM ready) are closely bind to the external peripheral or interface it is connected to. For example, an external RTC chip with it’s clock output pin connected to pin 2 of the Arduino board. In this case, the library should not know what this external interrupt signal means to the system (timer or counter for time stamping or other usage). Therefore, we omit them out (at least for now). But, rest assured examples are included (more will be added from time to time) to demonstrate the usage of the library with external peripheral and interface.

Please bear in mind that, most of the Arduino boards (official and also compatible) that is currently available in market (except some brilliant design from JeeLabs and Wiblocks, but there might be more out there that we are not aware of) are not low power by design. Low power design requires both hardware and software implementation. Our Mini Ultra 8 MHz (Arduino compatible) board is designed to be low power and is basically the testing platform for this library. Using the library on any Arduino boards (official or compatible) may and may not yield the best result.

Using our Mini Ultra 8 MHz (we are assembling an army of them right now using our reflow oven controller shield) and revision 1.0 of the library yields the following current consumption measurement result. The board is being powered by a Li-Ion 3.7 V battery running at 8 MHz with 3.3 V. The on board regulator of the Mini Ultra 8 MHz consumes about 1.6 µA of quiescent current.

<table>
<thead>
<tr>
<th scope="col">Mode</th>
<th scope="col">WDT</th>
<th scope="col">ADC</th>
<th scope="col">BOD</th>
<th scope="col">T2</th>
<th scope="col">T1</th>
<th scope="col">T0</th>
<th scope="col">SPI</th>
<th scope="col">USART0</th>
<th scope="col">TWI</th>
<th scope="col">Current</th>
</tr>
</thead>
<tfoot>
<tr>
<td colspan="11">
<p style="text-align: left;"><span style="color: #008000;">Timer 1 &amp; Timer 2 not in use</span></p>
<p style="text-align: left;"><span style="color: #3366ff;">Timer 2 not clock asynchronously from an external 32.768 kHz crystal &nbsp;(lower consumption can be further achieved)</span></p>
</td>
</tr>
</tfoot>
<tbody>
<tr>
<td>Idle</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>3648.0 µA</td>
</tr>
<tr>
<td>Idle</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>3643.0 µA</td>
</tr>
<tr>
<td>Idle</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td><span style="color: #008000;">*</span></td>
</tr>
<tr>
<td>Idle</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td><span style="color: #008000;">*</span></td>
</tr>
<tr>
<td>Idle</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>3618.0 µA</td>
</tr>
<tr>
<td>Idle</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>927.0 µA</td>
</tr>
<tr>
<td>Idle</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>832.0 µA</td>
</tr>
<tr>
<td>Idle</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>789.0 µA</td>
</tr>
<tr>
<td>Idle</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>687.0 µA</td>
</tr>
<tr>
<td>ADC Noise Reduction</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>651.0 µA</td>
</tr>
<tr>
<td>ADC Noise Reduction</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>646.0 µA</td>
</tr>
<tr>
<td>ADC Noise Reduction</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td><span style="color: #008000;">*</span></td>
</tr>
<tr>
<td>ADC Noise Reduction</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>Off</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>584.0 µA</td>
</tr>
<tr>
<td>Power Down</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>1.7 µA</td>
</tr>
<tr>
<td>Power Down</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>18.6 µA</td>
</tr>
<tr>
<td>Power Down</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>110.0 µA</td>
</tr>
<tr>
<td>Power Down</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>113.9 µA</td>
</tr>
<tr>
<td>Power Save</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>1.7 µA</td>
</tr>
<tr>
<td>Power Save</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td><span style="color: #3366ff;">416.0 µA</span></td>
</tr>
<tr>
<td>Power Save</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td><span style="color: #3366ff;">435.0 µA</span></td>
</tr>
<tr>
<td>Power Save</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td><span style="color: #3366ff;">527.0 µA</span></td>
</tr>
<tr>
<td>Power Save</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td><span style="color: #3366ff;">531.0 µA</span></td>
</tr>
<tr>
<td>Standby</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>201.7 µA</td>
</tr>
<tr>
<td>Standby</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>218.5 µA</td>
</tr>
<tr>
<td>Standby</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>309.9 µA</td>
</tr>
<tr>
<td>Standby</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>313.9 µA</td>
</tr>
<tr>
<td>Extended Standby</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>202.2 µA</td>
</tr>
<tr>
<td>Extended Standby</td>
<td>Off</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>416.0 µA</td>
</tr>
<tr>
<td>Extended Standby</td>
<td>Off</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>436.0 µA</td>
</tr>
<tr>
<td>Extended Standby</td>
<td>Off</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>527.0 µA</td>
</tr>
<tr>
<td>Extended Standby</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>On</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>-</td>
<td>531.0 µA</td>
</tr>
</tbody>
</table>

In idle mode, the IO clock is available for general IO modules usage. Therefore, you need to pull any unused pins low in output mode to reduce the overall current consumption.

In power save mode, Timer 2 can be clocked asynchronously from an external 32.768 kHz crystal to achieve very low current consumption. However, this will require the removal of the external 8 MHz resonator (or crystal in other board variants) to facilitate the low frequency crystal. This will require the ATmega328 to run on its internal 8 MHz on chip RC oscillator in normal operation. But, this will affect time critical modules such as millis, PWM and higher baud rate USART communication as the accuracy of the on chip RC oscillator is limited and is affected pretty much by the operating voltage and temperature. We have some prototype work on running a 32.768 kHz crystal asynchronously which can be seen here.

Here’s a sample code snapshot on how to use the library.

```
#include "LowPower.h"
 
void setup()
{
    // No setup is required for this library
}
 
void loop()
{
    // Sleep for 8 s with ADC module and BOD module off
    LowPower.powerDown(SLEEP_8S, ADC_CONTROL_OFF, BOD_OFF);
    // Do something here
    // Example: read sensor, log data, transmit data
}
```
