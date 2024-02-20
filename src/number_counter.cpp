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
        timer_ = this->create_wall_timer(std::chrono::milliseconds(1000),
                                         std::bind(&NumberCounterNode::publishNumberCount, 
                                         this));

        RCLCPP_INFO(this->get_logger(), "NumberCounter has been started.");
    }

private:
    void callbackNumberReceived(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        received_number_ = msg->data;

        if (received_number_ != counting_number_)
        {
            // publishing_number_ = received_number_;
            pcount_->data = received_number_;
            counting_number_ = received_number_;
        }
    }

    void publishNumberCount()
    {
        pcount_->data += 2;
        publisher_->publish(*pcount_);
    }

    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subsriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::int64_t received_number_;
    // std::int64_t publishing_number_;
    std::shared_ptr<example_interfaces::msg::Int64> pcount_;
    std::int64_t counting_number_ = 0;
    std::int64_t increasement = 2;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}