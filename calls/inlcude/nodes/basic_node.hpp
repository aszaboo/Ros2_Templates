#pragma once

//std libraries
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

// ros2 libraries
#include <rclcpp/rclcpp.hpp>
#include <some_package/srv/SomeService.hpp>

namespace composition {
    class basic_node : public rclcpp::Node {
        public:
            //node
            basic_node(const rclcpp::NodeOptions &options);

        private:
            // client
            rclcpp::Client<some_package::srv::SpcificService>::Sharedptr client;
            // naming the nodes
            std::vector<std::string> nodes = {"node1", "node2", "etc"};
            // timer for scheduled callback
            rclcpp::TimerBase::SharedPtr timer_;
            // fxn to call service
            void someservice();
    }
} // namespace


