#pragma once

// std libs
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <cmath>

// std ros2 lib
#include <rclcpp/rclcpp.hpp>

// including the message hpp
#include <message/msg/message.hpp>

namespace composition {
    
    class basic_message : public rclcpp:Node {
        public:
            // creating basic_node constructor
            basic_node(const rclcpp::NodeOptions &options);
        private:
            // creating subscribers
            rclcpp::Subscription<some_package::msg::MsgType>::SharedPtr sub1;
            rclcpp::Subscription<some_package::msg::MsgType>::SharedPtr sub2;
            // creating publisher
            rclcpp::Subscription<message::msg::Message>::SharedPtr publisher;
            // creating a time for publisher
            rclcpp:TimerBase::SharedPtr timer;
            // creating a callback group called callbacks
            rclcpp:: CallbackGroup::SharedPtr callbacks;
            
            // creating a struct to hold the node data
            struct node_data {
                string string_var;
                int int_var;
            };

            //defining two container vars for data of node1 and node2
            node_data node1;
            node_data node2;

            // defining a container var for diff
            float diff;
    }
} // namespace