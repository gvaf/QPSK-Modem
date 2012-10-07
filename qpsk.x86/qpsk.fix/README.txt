   QPSK Modem
   
   Copyright 2012 George Vafiadis

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

Description
-------------
Implementation of QPSK Algorithm

Contents
---------
- QPSK C floating point

Howto Compile:
----------------
in Linux:
make

in Windows:
in folder qpsk.win there are solution files for Microsoft Visual Studio 2005


Configuration:
---------------
Running the gen_qpsk.m script from matlab generates a qpsk.h header file with the appropriate configuration.
The gen_qpsk.m  depends on matlab module located at toQ15_interface.c in order to use it
you have to compile it, inside matlab run
>> mex toQ15_interface.c

Notes:
--------
Running the program creates a random message and modulates and demodulates it using QPSK.
The program creates a "plot.txt" file which is the scatter plot of the output.
Inside matlab you can run the graph.m script, this scripts reads the plot.txt and produces the scatter plot.



