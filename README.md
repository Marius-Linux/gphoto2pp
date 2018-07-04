gphoto2pp
=========

gphoto2pp is a C++11 wrapper for libgphoto2.

Table Of Contents
-----------------
* [Prerequisites](#prerequisites)
* [2 Minute Tutorial](#2-minute-tutorial)
* [Building and Installing](#building-and-installing)
* [Examples](#examples)
  * [Example 1](EXAMPLES.md#example-1)
  * [Example 2](EXAMPLES.md#example-2)
  * [Example 3](EXAMPLES.md#example-3)
  * [Example 4](EXAMPLES.md#example-4)
  * [Example 5](EXAMPLES.md#example-5)
  * [Example 6](EXAMPLES.md#example-6)
  * [Example 7](EXAMPLES.md#example-7)
  * [Example 8](EXAMPLES.md#example-8)
  * [Example 9](EXAMPLES.md#example-9)
  * [Example 10](EXAMPLES.md#example-10)
  * [Example 11](EXAMPLES.md#example-11)
* [Dev/Test/Contributor](#devtest)
* [FAQ](#faq)
* [Doxygen Documentation](#doxygen-documentation)
* [Other Useful Links](#other-useful-links)

Prerequisites
------------
* A C++11 compiler
* libgphoto2 (2.5.0 or greater)
* cmake (3.1 or greater) *(build)*
* cxxtest *(optional, for running tests)*
* doxygen and graphviz *(optional, for generating documentation)*
  
2 Minute Tutorial
-----------------
The following snip will show you a quick demo of how easy it is to interact with your camera using gphoto2pp. Don't forget you will need to follow the [installation instructions](#installation) before you can compile this 2 minute tutorial on your computer.
Make a source file eg. ``touch testgphoto2pp.cpp``
Now put this in the source file
```cpp
#include <gphoto2pp/camera_wrapper.hpp> 		// Header for CameraWrapper
#include <gphoto2pp/camera_file_wrapper.hpp>	// Header for CameraFileWrapper
#include <gphoto2pp/helper_camera_wrapper.hpp>	// Used for helper::capture(...) method

#include <iostream>

int main()
{
	// Connects to the first camera found and initializes
	gphoto2pp::CameraWrapper camera;
	
	// Prints out the summary of your camera's abilities
	std::cout << camera.getSummary() << std::endl;
	
	// Creates empty instance of a cameraFile, which will be populated in our helper method
	gphoto2pp::CameraFileWrapper cameraFile;
	
	// Takes a picture with the camera and does all of the behind the scenes fetching
	gphoto2pp::helper::capture(camera, cameraFile);
	
	// Lastly saves the picture to your hard drive
	// Your camera might take files in different formats (bmp, raw)
	// so this extension might be wrong and you should rename your file appropriately
	cameraFile.save("my-gphoto2pp-test.jpg");
	
	return 1;
}
```

Now compile with the command:
```sh
g++ -std=c++11 testgphoto2pp.cpp -lgphoto2 -lgphoto2pp
```
and then execute it
```sh
./a.out
```

That's it! The library is certainly capable of more, which you can view at [examples](EXAMPLES.md).

Building and Installing
------------
```
git clone 'https://github.com/Marius-Linux/gphoto2pp'
cd gphotopp
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
make examples //Optional, for building examples
make docs //Optional, for building documentation with doxygen
sudo make install
```

Examples
--------
Please see the [Examples document](EXAMPLES.md) for details about all examples provided.

Dev/Test
--------
If you would like to contribute/develop/test gphoto2pp, please see the [Dev-Test doc](DEV-TEST.md).

FAQ
---
Please see the [FAQ document](FAQ.md)

Doxygen Documentation
-----------------------
Please see this [projects github pages](http://maldworth.github.io/gphoto2pp/) for the auto generated Doxygen Page.

Other Useful Links
---------------
If you are new to gphoto2pp (and perhaps gphoto), then please view some of these resources:
* This library wraps [gphoto](http://www.gphoto.org/)
