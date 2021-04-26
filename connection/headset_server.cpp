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


//Does not currently work.
//Something that could be fixed in the future
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

void send_reached_destination(){
    //TODO Create Message of State : STOPPED, Reason: Destination Reached
    /*Json::Value root;
    Json::Reader reader;
    reader.parse(stopped.c_str(), root);
    Json::FastWriter fastwriter;
    std::string message = fastwriter.write(root);
    zmq::message_t rq (message.size());
    memcpy(rq.data(), message.c_str(), message.size());
    socket.send(rq);*/
}

//int Init_Headset(int start_node){
int main () {
    int node = 0;
    int start_node = 5;
    zmq::message_t msg;
    //  Prepare our context and socket
    int ret = zmq_bind((void *)socket, ADDR);

    if(ret < 0){
        std::cout << "Failed to bind socket\r\n";
    }

    //Receive Connection Confirmation
    socket.recv(&msg);
    std::string rpl = std::string(static_cast<char*>(msg.data()), msg.size());

    Json::Value parsedFromString;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(rpl, parsedFromString);

    std::cout << parsedFromString["State"];
    if(parsedFromString["State"] != "CONNECTED"){
        std::cout << "Invalid State Received\r\n";
        return -1;
    }

    socket.recv(&msg);
    rpl = std::string(static_cast<char*>(msg.data()), msg.size());
    parsingSuccessful = reader.parse(rpl, parsedFromString);
    if(parsedFromString["MoveTo"] != NULL){
        //TODO Get int from Json::Value
        node = parsedFromString["MoveTo"];
        if(node == start_node){
            send_reached_destination();
            return -2;
        }
    }
    else{
        std::cout << "Invalid check\r\n";
        return -1;
    }

    return node;
}
