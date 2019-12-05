# UpdateRandom
Libraries for sampling from a time-changing discrete distribution

This is the software package for the thesis work: An Empirical Study of Random Sampling Methods for Changing Discrete Distributions

We implemented ten random sampling methods under the scenario of time-changing discrete distritbuions. To use a method we implemented in your project, you need to copy and include the related files. For example, here are the steps required to use the Alias Method:\
(1). Copy the method files and virtual class file in your folder(copy aliasMethod.cpp, aliasMethod.h, and baseDiscrete.h into your project repo)\
(2). Include the method header in your file(write “#include "aliasMethod.h"” in your file)\
(3). Create a method object(e.g. “aliasMethod alm(n,p)” will construct an Alias Method object with size n and weight array p)\
(4). Generate a random variable(e.g. “alm.ransample()” will generate a random sample)\
(5). Update weight(e.g. “alm.change(index,new_weight)” will update the weight with a given index to new_weight)\
(6). Compile your file with the method file using c++11(e.g. “g++ -std=c++11 <your file name>.cpp aliasMethod.cpp”)

You may refer to our test file "testmain.cpp" as an example. The test platform can be built with “make“ command.
