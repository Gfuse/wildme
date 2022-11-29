How would you build Netflix?
-------

For developing a web application, there are several options, but I usually prefer to develop it as a cluster of several 
microservices. This structure can provide an industrial level of security thanks to the docker. And also helps to develop
the microservices in parallel by predefining the APIs and SDKs as refrences. There are various options for the communication layer
that each one has advantage and disadvantages (likes protobuf, rest, and Gstreamer. And each one of this frame works has been desgin 
for one reason that a web application like Netflix can use all of them or some of them).


