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

#include "../wheelchair.h"
#include "headset_server.h"

#define ADDR "tcp://*:4321"

zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_PAIR);

std::string finished ="{\"State\": \"STOPPED\", \
                           \"Reason\": \"Destination Reached\"}";
std::string stopped ="{\"State\": \"STOPPED\", \
                           \"Reason\": \"User Request\"}";
std::string start = "{\"State\": \"MOVING\", \
                           \"Reason\": \"User Request\"}";
std::string invalid = "{\"State\": \"NULL\", \
                           \"Reason\": \"Invalid Request\"}";
/*
 * TODO This option does not currently work
 *      issue comes from no blocking recv
 *      to be fixed at a later date.
 */
void user_interrupt(){
    zmq::message_t msg;
    Json::Value root;
    Json::Value parsedFromString;
    Json::Reader reader;
    Json::FastWriter fastwriter;

    while(g_running){
        socket.recv(&msg, ZMQ_NOBLOCK);
        if(errno == EAGAIN){
            break;
        }
        else{
            std::string rpl = std::string(static_cast<char*>(msg.data()), msg.size());
            reader.parse(rpl, parsedFromString);
            if(parsedFromString["Command"] == "STOP"){
                reader.parse(stopped.c_str(), root);
                std::string message = fastwriter.write(root);
                zmq::message_t rq (message.size());
                memcpy(rq.data(), message.c_str(), message.size());
                socket.send(rq);
                //this should stay in while loop here
                // until start message is received
            }
            else if(parsedFromString["Command"] == "START"){
                reader.parse(start.c_str(), root);
                std::string message = fastwriter.write(root);
                zmq::message_t rq (message.size());
                memcpy(rq.data(), message.c_str(), message.size());
                socket.send(rq);
                break;
            }
        }
    }
}

void send_reached_destination(){
    Json::Value root;
    Json::Reader reader;
    reader.parse(finished.c_str(), root);
    Json::FastWriter fastwriter;
    std::string message = fastwriter.write(root);
    zmq::message_t rq (message.size());
    memcpy(rq.data(), message.c_str(), message.size());
    socket.send(rq);
}

int Init_Headset(int start_node){
    int node = 0;
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
    reader.parse(rpl, parsedFromString);

    //Parse for connected message
    std::cout << parsedFromString["State"];
    if(parsedFromString["State"] != "CONNECTED"){
        std::cout << "Invalid State Received\r\n";
        return -1;
    }

    //Receive destination node
    socket.recv(&msg);
    rpl = std::string(static_cast<char*>(msg.data()), msg.size());
    reader.parse(rpl, parsedFromString);
    if(parsedFromString["MoveTo"].asBool()){
        node = parsedFromString["MoveTo"].asInt();
        if(node == start_node){
            send_reached_destination();
            return -2;
        }
    }
    else{
        std::cout << "Invalid Json Message\r\n";
        return -1;
    }
    return node;
}
