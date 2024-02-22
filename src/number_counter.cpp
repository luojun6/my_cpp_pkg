#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberCounterNode : public rclcpp::Node 
{
public:
    NumberCounterNode() : Node("number_counter")
    {   
        subsriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(&NumberCounterNode::callbackNumberReceived,
                      this, std::placeholders::_1));
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_counter", 10);

        RCLCPP_INFO(this->get_logger(), "Number Counter has been started.");
    }

private:
    void callbackNumberReceived(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        if (counter_ == 0)
        {
            counter_ = msg->data;
        }
        else
        {
            counter_ += 2;
        }
        auto number_counter = example_interfaces::msg::Int64();
        number_counter.data = counter_;
        publisher_->publish(number_counter);
    }

    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subsriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::int64_t counter_ = 0;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}