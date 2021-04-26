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

#define ADDR "tcp://129.21.118.204:4321"

bool g_running = true;
zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_PAIR);


void user_interrupt(){
    zmq::message_t msg;
    std::string stopped ="{\"State\": \"STOPPED\", \
                           \"Reason\": \"User Request\"}";
    std::string start = "{\"State\": \"MOVING\", \
                           \"Reason\": \"User Request\"}";

    while(g_running){
        bool ret = socket.recv(&msg, ZMQ_NOBLOCK);
        //msg = socket.recv(flags = ZMQ_NOBLOCK);
        if(errno == EAGAIN){
            break;
        }
        else if(!ret){
            std::cout << "Bad\r\n";
        }
        else{
            std::string rpl = std::string(static_cast<char*>(msg.data()), msg.size());

            std::cout << rpl << std::endl;

            Json::Value root;
            Json::Reader reader;
            reader.parse(stopped.c_str(), root);
            Json::FastWriter fastwriter;
            std::string message = fastwriter.write(root);
            zmq::message_t rq (message.size());
            memcpy(rq.data(), message.c_str(), message.size());
            socket.send(rq);
            break;
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
