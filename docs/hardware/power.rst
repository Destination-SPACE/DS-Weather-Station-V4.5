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

.. _power:

Power
=====

The power subsystem of the weather station was designed with reverse voltage protection in mind. Typically, if a battery is connected to a circuit backwards, it will not work, or worse, fry the entire system. This is why reverse current protection is often added to circuits to prevent such user error. This allows the user to not have to worry about the polarity of their LiPo battery. On the Destination Weather Station v4.5 we have taken this one step further, by not only having reverse voltage/polarity protection, but also correcting this polarity. This works using the same principal as an `AC rectifier <https://en.wikipedia.org/wiki/Rectifier>`_ circuit. This DC rectifier consists of two `N-Channel MOSFETs <https://en.wikipedia.org/wiki/NMOS_logic>`_ and two `P-Channel MOSFETs <https://en.wikipedia.org/wiki/PMOS_logic>`_. These MOSFETs combine to essentially create a rectifier circuit, which will only allow the correct polarity to pass through the FETs. A schematic of this circuit can be found below.

.. image:: ../assets/dcRectifier.png
   :target: power.html

**Note:** There is no over-current protection, so make sure to not exceed 5V in.