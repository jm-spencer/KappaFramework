# KappaFramework
C++ framework for Vex robots inspired by on [Okapilib](https://github.com/OkapiLib/OkapiLib), but designed for use only as a framework to be built upon by users.

This project was created with the intent of providing a modular interface for users to work with. All kappaframework objects are organized into Inputs, Outputs, and Controllers. Inputs get values from sensors and the like, Outputs send values to motors and the like, and Controllers act as a bridge between the two. Using polymorphism, Inputs and Outputs can wrap other Inputs and Outputs, creating a modular chain of control signals. This lets users create and implement their own modules with ease. Additionally, many utilities, such as loggers, are already availble within kappaframework.

Installing
==========
* Go over to [releases](https://github.com/SpencerJ21/KappaFramework/releases) and download the latest version (or download the above zip file)
* Open a terminal wherever you downloaded it(try shift + right click in file explorer)
* run `prosv5 c fetch kappaframework@VERSION.zip`, replacing VERSION with the version
* run `prosv5 c apply kappaframework` in your project directory to install

License
=======
This software uses the MPL-2 License. See [LICENSE](LICENSE) for more information.


Example
-------
This directory (specifically [main.cpp](./main/opcontrol.cpp)) is a usage example. Feel free to dm me on discord @sufficient#0331 with any questions.
