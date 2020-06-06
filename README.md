# image_recog_cpp
A project for teaching, checking and preparing image examples for neural network in C++ with openCV.

Made as project for course "Systems based on algorithms of artificial intelligence" lectured by Prof. Andrzej Kos on AGH in Kraków.

It consists of two C++ programs:
-Drawing - which allows us to create our own base of handwritten symbols(i.e. letters) and store in built-in folder database as jpeg, as example to learn, or as example just for checking efficiency of network.
-AlphaDetect - which is main part of the project, it contains Neural Network class that can construct an object with given dimensions by user. Methods of this class are among others ones responsible for learning, statistics and displaying wages of neurons. It uses database created by Drawing program, so you don't have to create special files cotaining examples.

Both programs require OpenCV external library for image processing, which needs to be included in project settings in our case in Visual Studio.

Our interpretation of network efficiency is case of examples correctly guessed(highest output) on independent example set.
AlphaDetect allows for creating time statistics of transfering and learning examples.
It allows also for mass statistics of efficiency while network is learning by iteration.
Here is graph of two sessions of learning(for learning coeff. equal 0.2 and 0.05 for best result):
![mass statistics of network learning](https://img.techpowerup.org/200606/chart8.png)
It shows efficiency for independent examples against iterations of 1000 examples. 

With use of AlphaDetect we can also print wages of first hidden layer as jpeg pictures.
Here are some of above, trained network:
![wages](https://img.techpowerup.org/200606/trzy.png)

We also included NN class versions for 1 and 2 layer networks, you just need to swap the .cpp files.
Keep in mind that our class uses only one core for transferring and learning!
Here is comparison of times(in ms) of learning each type of network:
![average times](https://img.techpowerup.org/200606/chart7.png)
The networks are as follows: one ,two and three layer, where three layer is shown for number of 98x64 and 64x48 neurons in hidden layers. The 7500 is number of pixels in input picture.
