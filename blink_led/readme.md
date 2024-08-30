This LKM works on the Beaglebone Black board. The code will
switch on the LED connected to Pin 12 on P9 connector of the
BBB board. This is GPIO 28 as per the pinout description
available at this location: https://docs.beagleboard.org/latest/boards/beaglebone/black/ch07.html
Connect the LED anode through a 470ohm resistor to pin 12 on P9
and connect the cathode to pin 2 of P9 (which is the GND).
Call the makescript file to build the LKM. When the LKM
is installed, the LED will glow. When the LKM is uninstalled
the LED may continue to glow faintly. This could be because
the Pin state is released and is possibly floating.

Driving a logic 0 on the pin without releasing it will cause
the LED to stop glowing completely.
