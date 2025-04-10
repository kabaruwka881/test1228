**Before demonstration:**

1. Check $LD_LIBRARY_PATH.

`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/geom`

2. If scripts did not work:

 `g++ t.cpp -L/usr/local/lib/geom -lgeom`

**Demonstration (For Linux only):**

 1. Build library _geom_ and install to /usr/local: 
 
 `cd library && sudo bash ./install.sh`

 2. Build application with shared library _geom_ and run it:

 `cd app && bash ./run.sh && cd build && ./app`