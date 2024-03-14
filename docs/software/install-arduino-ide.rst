.. Copyright 2024 Destination SPACE Inc.
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

.. _install-arduino-ide:

Installing Arduino IDE
======================

To program the Destination Weather Station, you will need to download and install Arduino IDE.

Download
~~~~~~~~

To begin, navigate to https://www.arduino.cc/en/software.

Click ``Windows Win 10 and newer, 64 bits`` under the most recent version of IDE. This may be different than the screenshot below

.. image:: ../assets/arduino-ide-download-page.png
      :target: install-arduino-ide.html

When the page loads, click next

.. image:: ../assets/arduino-ide-just-download-1.png
      :target: install-arduino-ide.html

.. image:: ../assets/arduino-ide-just-download-2.png
      :target: install-arduino-ide.html

Installation
~~~~~~~~~~~~

To install Arduino IDE, navigate to where you saved your ``arduino-ide_2.x.x_Windows_64bit.exe`` file and follow the instructions in the install.

Software Configuration
======================

Board Manager
~~~~~~~~~~~~~

To properly configure IDE, the board manager for the XIAO RP2040 needs to be installed.

In Arduino IDE, navigate to **File > Preferences**. In the window, enter ``https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json`` into the **Additional boards manager URLs:** text box.

.. image:: ../assets/arduino-ide-preferences.png
      :target: install-arduino-ide.html

Click **OK**

Next, navigate to **Tools > Board: > Boards Manager...**. Search for ``Raspberry Pi Pico/RP2040`` and click **INSTALL** on the option published by Earle F. Philhower, III.

.. image:: ../assets/arduino-ide-boards-manager.png
      :target: install-arduino-ide.html

Code Libraries
~~~~~~~~~~~~~~

Several libraries are needed  to upload code to the weather station.

To install these libraries, navigate to **Tools > Manage Libraries...**

In the search box enter the following library names and install each including any required dependancies.

* ``Adafruit BME280 Library``
* ``Adafruit LTR390 Library``
* ``Adafruit SSD1306``
* ``Adafruit VEML7700 Library``
* ``ENS160 - Adafruit Fork``
* ``Sensirion I2C SCD4x``
