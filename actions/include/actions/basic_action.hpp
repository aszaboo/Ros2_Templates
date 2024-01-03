#pragma once

// std c libraries
#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <iostream>

// ros2 libraries
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

// non std ros2 libs
#include </actions/action/waypoint.hpp>

namespace composition {

    class basic_action : public rclcpp::Node{ 
       
        public:
            basic_action(const rclcpp::NodeOptions &options);

            // declaring an action server to handle a goal defined in some_action
            using GoalHandleActionServer = rclcpp_action::ServerGoalHandle<actions::action::some_action>;
        
        private:

            // declaring a goal handler of type UUID
            rclcpp_action::GoalResponce handle_goal(
                const rclcpp_action::GoalUUID &uuid,
                std::shared_ptr<const actions::action::some_action::Goal> goal
            );
            
            rclcpp_action::CancelResponce handle_cancel(
                const std::shared_ptr<GoalHandleActionServer> goal_handle
            );
            
            void handle_accepted(
                const std::shared_ptr<GoalHandleActionServer> goal_handle
            );

            void execute(const std::shared_ptr<GoalHandleActionServer> goal_handle);
    }
}