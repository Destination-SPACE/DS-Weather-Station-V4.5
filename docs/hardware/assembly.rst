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

.. _assembly:

Destination Weather Station v4.5 Assembly
=========================================

The Destination Weather Station v4.5 is preassembled with the majority of the circuit components.

Before using the weather station, you will need to :ref:`solder<soldering>` the :ref:`XIAO RP2040 microcontroller<xiao-RP2040>`, :ref:`OLED display<oled-display>`, and :ref:`power switch<switch>`. Follow the instructions below to solder your weather station. You can then :ref:`connect the batteries<batteries>` and insert the microSD card.

Soldering
---------

.. _soldering:

To solder the weather station, follow the instructions below. Tools required to complete these steps are:

* Soldering iron
* Solder wire

Power Switch
~~~~~~~~~~~~

.. _switch:

.. image:: ../assets/switchOnly.png
      :target: assembly.html

To solder the power switch to the weather station, insert it into the front side of the board. Flip the board over and solder the pins, starting with the two outer ones.

XIAO RP2040
~~~~~~~~~~~

.. _xiao-RP2040:

To solder the XIAO RP2040 to the weather station, begin by inserting the long side of the 1x7 header pins into the weather station board as shown below.

.. image:: ../assets/xiaoPinsOnly.png
      :target: assembly.html

Next, flip the weather station over and solder all 14 pins to the weather station.

Finally, flip the weather station back over and solder the XIAO to the short side of the header pins. After you are done, it should look like the image below.

.. image:: ../assets/xiaoOnly.png
      :target: assembly.html

OLED Display
~~~~~~~~~~~~

.. _oled-display:

To solder the OLED display to the weather station, you will follow similar procedures to the steps above to solder the XIAO.

Begin by inserting the long side of the 1x4 header into the weather station board as shown below.

.. image:: ../assets/oledPinsOnly.png
      :target: assembly.html

Next, flip the board over and solder the pins to the back.

Similarly, flip the board back over and solder the display to the front.

.. image:: ../assets/front.png
      :target: assembly.html

Final Assembly
--------------
.. image:: ../assets/iso.png
      :target: assembly.html

Batteries
~~~~~~~~~

.. _batteries:

Insert three (3) AAA batteries into the battery pack. Connect the JST-PH connector to the matching connector on the weather station.