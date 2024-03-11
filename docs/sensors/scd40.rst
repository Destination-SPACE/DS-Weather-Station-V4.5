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

.. _scd40:

SCD40
=====

.. image:: ../assets/MFG_SCD40.jpg
   :target: scd40.html

THe SCD40 CO2 sensor uses photoacoustic nondispersive infrared (NDIR) technology to measure actual CO2 concentration, unlike the eCO2 measurement on the :ref:`ENS160<ens160>`. This works by measuring the attenuation of an infrared light shining through the gas onto an accoustic transducer. Along with the sample chamber there is a reference nitrogen sample used to compare the CO2 measurement to the known gas. This process works according to Beer-Lambert law which is this attenuation of the gas.

.. image:: ../assets/scd40_blockDiagram.jpg
   :target: scd40.html

CO2 Sensing Preformance
~~~~~~~~~~~~~~~~~~~~~~~

.. list-table::
   :header-rows: 1

   * - Parameter
     - Conditions
     - Value
   
   * - Output range
     - -
     - 0 - 40,000ppm
   
   * - Accuracy
     - 400ppm - 2,000ppm
     - ±(50ppm + 5% of reading)
   
   * - Repeatability
     - Typical
     - ±10ppm

Humidty Sensing Preformance
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. list-table::
   :header-rows: 1

   * - Parameter
     - Conditions
     - Value
   
   * - Range
     - -
     - 0 %RH - 100 %RH

   * - Accuracy
     - 15°C - 35°C, 20 %RH - 65 %RH
     - ±6 %RH

   * - Accuracy
     - -10°C - 60°C, 0 %RH - 100 %RH
     - ±9 %RH

   * - Repeatability
     - Typical
     - ±0.4 %RH

Temperature Sensing Preformance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. list-table::
   :header-rows: 1

   * - Parameter
     - Conditions
     - Value
   
   * - Range
     - -
     - -10°C - 60°C
   
   * - Accuracy
     - 15°C - 35°C
     - ±0.8°C
   
   * - Accuracy
     - -10°C - 60°C
     - ±1.5°C

   * - Repeatability
     - Typical
     - ±0.1°C

Measuring CO2
~~~~~~~~~~~~~

Measuring CO2 is another important parameter for indoor and outdoor air quality. Health Canada reccomends not exceeding 1000ppm of CO2 in a 24 hour period. A high concentration of CO2 can increase the risk of respiratory symptoms, decreased cognitive function, and neurophysiological symptoms such as headaches, tiredness, and dizzyness. The graph below shows different concentrations and what effects one may encounter at that concentration.

.. image:: ../assets/co2Limits.jpg
   :target: scd40.html

