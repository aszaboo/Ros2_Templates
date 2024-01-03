#include "../basic_node.hpp"

namespace composition {

    basic_node::basic_node(const rclcpp::NodeOptions & options): Node("basic_node", options) {

        // creating a client to call the server
        client = this->create_cleient<some_package::srv::SpcificService>("name for call");

        // send a message for all nodes
        for (auto node : nodes) {

            //spcific message for each node
            auto message = std::make_unique<some_pakcage::srv::SpcificService::Request>();
            // components of message
            message->priv_data_member.string_var;
            message->priv_data_member.int_var;
            // ...

            // creating a server callback
            auto server_callback = [this](rclcpp::Client<some_package::srv::SpcificService::SharedFuture responce) ->
            void {
                // shutdown server
                rclcpp::shutdown();
            };

            // get the result
            auto result = client->async_send_request(std::move(message), server_callback);
        } // for
    } // node
} // namespace

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(composition::basic_node)

