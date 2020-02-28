# CaffeBean
## A deep learning framework in cpp
The implementation of this code is heavily borrowed from [Caffe](https://github.com/BVLC/caffe), runs only on cpu and the efficiency should be extremely low(when it's completed), help me with it if you're interested 😉 
***
### 🗒This repo include:  
[CaffeBean](https://github.com/SiriusKY/CaffeBean)  
[Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) -- A C++ template library for linear algebra  
[googletest](https://github.com/google/googletest/tree/master/googletest) -- for unit test  
[jsoncpp](https://github.com/open-source-parsers/jsoncpp) -- A C++ library for interacting with JSON  
Note that you *don't* need to install these libraries, just clone the repo by  
```Shell
git clone https://github.com/SiriusKY/CaffeBean.git
```
then use cmake tool like
```
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" /path/to/CaffeBean
cmake --build /path/to/CaffeBean/cmake-build-debug --target CaffeBean -- -j 4
```
Now you are ready to go!
```
/path/to/CaffeBean/cmake-build-debug/CaffeBean
```
***
### 🗓Progress
* Fully Connected Layer  
* L1 Loss Layer