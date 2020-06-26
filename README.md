WVZ minitree analysis
==============================

1. Basic information

----------------------------------------------------

This code can:
 - generate cutflow
 - geenrate histograms of some variable

----------------------------------------------------

2. Code structure

----------------------------------------------------
 - /source: source code, including cpp and header files
 - /build: Makefile, can generate exe
 - /run: contain 
   1. `run: main exe`
   2. `file.list: include root file names`
   3. `output.root: include histograms`
   4. `cutflowinfo.txt: include cutflow information`
----------------------------------------------------

3. How to run this code

-----------------------------------------------------
 - `cd build/`
 - `make`
 - `cd ../run`
 - `./run`
if you are not working in UMATLAS server, you might need to change `file.list` first!!!
