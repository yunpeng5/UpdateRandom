# UpdateRandom
Libraries for sampling from a time-changing discrete distribution

This is the software package for the thesis work: An Empirical Study of Random Sampling Methods for Changing Discrete Distributions

We implemented following random sampling methods under the scenario of time-changing discrete distritbuions: Alias Method, Linear search, Binary Search, Two-level Search, Three-level Search, Binary Tree Search, Rejection Sampling, Flat Method, Log* Mehtod. All the methods were implemented based on a virtual class baseDiscrete in the file “baseDiscrete.h”. All these methods have a ransample() function for random sampling and a change(index,new_weight) function for weight updating.

To use a method we implemented in your project, you need to copy and include the related files. For example, here are the steps required to use the Alias Method:\
(1). Copy the method files and virtual class file in your folder(copy aliasMethod.cpp, aliasMethod.h, and baseDiscrete.h into your project repo)\
(2). Include the method header in your file(write “#include "aliasMethod.h"” in your file)\
(3). Create a method object(e.g. “aliasMethod alm(n,p)” will construct an Alias Method object with size n and weight array p)\
(4). Generate a random variable(e.g. “alm.ransample()” will generate a random sample)\
(5). Update weight(e.g. “alm.change(index,new_weight)” will update the weight with a given index to new_weight)\
(6). Compile your file with the method file using c++11(e.g. “g++ -std=c++11 yourFileName.cpp aliasMethod.cpp”)

To use these methods, you may want to further refer to our test file "testmain.cpp" as an example. The test platform can be built with “make“ command.
