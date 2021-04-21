//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//

// TO GET IT TO WORK:
// Copy the zm.hpp from https://github.com/zeromq/cppzmq into the include folder of zmq (3.2.4 at the time)
// VS needs to specify .lib files of platform! e.g.

#include <stdbool.h>
#include <zmq.hpp>
#include <string>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <unistd.h>
#include <exception>
#include <errno.h>

//#include "../wheelchair.h"
//#include "arduino_serial.h"

#define ADDR "tcp://129.21.118.106:4321"

bool g_running = true;
zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_PAIR);

void user_interrupt(){
    zmq::message_t msg;

    while(g_running){
        socket.recv(&msg, ZMQ_NOBLOCK);
        if(errno == EAGAIN){
            break;
        }
        else{
            std::string json_str =
        }
    }
}

//void Init_Headset(){
int main () {
    //  Prepare our context and socket
    int ret = zmq_bind((void *)socket, ADDR);

    if(ret < 0){
        std::cout << "Failed to bind socket\r\n";
    }


    while (g_running) {
       // zmq::message_t request;
        user_interrupt();
        //  Wait for next request from client
        //socket.recv (&request);
        //std::cout << "Received Hello" << std::endl;


        //  Send reply back to client
        //zmq::message_t reply (5);
        //memcpy ((void *) reply.data (), "World", 5);
        //socket.send(reply);
    }
    socket.close();
    return 0;
}
