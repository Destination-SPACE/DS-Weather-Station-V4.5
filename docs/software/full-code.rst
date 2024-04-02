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

.. _blink:

Full Code Sketch
================

The `Full Code <https://gitlab.com/Destination-SPACE/ds-weather-station-v4.5/-/blob/main/software/Full_Code/Full_Code.ino>`_ sketch incorporates all of the components of the weather station, including data recording. This has all the menus of the `Demo <https://gitlab.com/Destination-SPACE/ds-weather-station-v4.5/-/blob/main/software/Demo/Demo.ino>`_ sketch as well as a menu used to start and stop data recording.

Program Overview
----------------

Button Menu
-----------

On the weather station there are 4 buttons, ↑, ↓, ←, →.

The ← and → buttons are used to scroll between the weather menu, air quality menu, and the light menu.

The ↑ arrow is used to navigate to the data recording menu. Here you can choose to either start recording data or pause data recording. **data recording is paused by default**. Press the → button to confirm your selection.

The ↓ is used to navigate the data recording menu above. When in either the air quality or light menu, pressing it will return you to the weather menu.