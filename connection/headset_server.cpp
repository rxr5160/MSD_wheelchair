//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//

// TO GET IT TO WORK:
// Copy the zm.hpp from https://github.com/zeromq/cppzmq into the include folder of zmq (3.2.4 at the time)
// VS needs to specify .lib files of platform! e.g.

#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

#define ADDR "tcp://129.21.118.106:4321"

int main () {
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t socket (context, ZMQ_REP);

    int ret = zmq_bind((void *)socket, ADDR);
    if(ret < 0){
        std::cout << "Failed to bind socket\r\n";
    }


    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        std::cout << "Received Hello" << std::endl;


        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy ((void *) reply.data (), "World", 5);
        socket.send (reply);
    }
    return 0;
}
