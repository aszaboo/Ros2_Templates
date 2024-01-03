// std libs
#include iostream

// message hpp file
#include <../include/basic_message.hpp>

// using chrono_literals namespace for easier time conventions
using namespace std::chrono_literals;

namespace composition {

    basic_message::basic_message(const rclcpp::NodeOptions & options) : Node("basic_message", options) {

        // creating a callback for each node (getting data for calc)
        auto callback_1 = [this] (const some_package::msg::MsgType::SharedPtr msg) -> void {
            this->callback_1.string_var = msg->string_var;
            this->callback_1.int_var = msg->int_var;
        };

        auto callback_2 = [this] (const some_package::msg::MsgType::SharedPtr msg) -> void {
            this->callback_2.string_var = msg->string_var;
            this->callback_1.int_var = msg->int_var;
        };

        // creating a publish callback

        auto publish_callback = [this] (void) -> void {
            // creating a variable foo of type node_data
            node_data foo;

            foo.name = {this->callback_1.string_var};
            foo.diff = {abs(this->callback_2 - this->callback_1)};

            // constructing the message
            auto msg = std::make_unique<basic_message::msg::Message>();

            // filling the message with data
            msg->node_name1 = foo.name;
            msg->node_distance = foo.diff;
            msg->diff_x_2 = (2 * diff);

            // displaying the msg to screen
            std::cout<<"name is "<<msg->name<<"\n";
            std::cout<<"diff is "<<msg->diff<<"\n";
            std::cout<<"diff times 2 is "<<msg->diff_x_2<<"\n";

            // publishing the message
            this->publisher->publish(std::move(msg));
        };

        // creating a callback grouping that is mutually exclusive
        callbacks = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

        // adding callback options

        //declaring the callback options container var
        auto callback_option = rclcpp::SubscriptionOptions();
        // assigning the callback options to the callback group
        callback_option.callback_group = callbacks;
        // enabling the option topic statistics
        callback_option.topic_stats_options.state = rclcpp::TopicStatisticsState::Enable;

        // creating a topic called statistics
        std::string s_name{"/statistics"}
        // getting the node name
        std::string node_name{this->get_name()};

        // adding the names together to be published
        std::string stat_name = s_name + node_name;
        // sets topic name for publishing stats to the value of stat_name
        callback_option.topic_stats_options.publish_topic = stat_name.c_str();

        // creating subscribers for each node
        sub1 = this->create_subscription<basic_message::msg::MsgType>(
            "/node1/msg_type", 10, callback_1, callback_option); //qos depth of 10?
        
        sub2 = his->create_subscription<basic_message::msg::MsgType>(
            "/node2/msg_type", 10, callback_2, callback_option); //qos depth of 10?

        // defining a publisher
        publisher = this->create_subscription<messages::msg::Message>(
            "/difference, 10"
        );

        // publishing the callbacks every 0.25s
        timer = this->create_wall_timer(0.25s, publish_callback, callbacks)
        )

    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(composition::basic_message)

