#include <rclcpp/node.hpp>
#include <rmcs_executor/component.hpp>

namespace rmcs_core::controller::task_components {

class SinCosAdder
    : public rmcs_executor::Component
    , public rclcpp::Node {
public:
    SinCosAdder()
        : Node(
              get_component_name(),
              rclcpp::NodeOptions{}.automatically_declare_parameters_from_overrides(true)) {
        
        // 注册输入接口
        register_input("/task/sin_output", sin_input_);
        register_input("/task/cos_output", cos_input_);
        
        // 注册输出接口
        register_output("/task/sum_output", sum_output_);
    }

    void update() override {
        // 读取两个输入值
        double sin_value = *sin_input_;
        double cos_value = *cos_input_;
        
        // 计算和
        double sum_value = sin_value + cos_value;
        
        // 更新输出接口值
        *sum_output_ = sum_value;
    }

private:
    InputInterface<double> sin_input_;
    InputInterface<double> cos_input_;
    
    OutputInterface<double> sum_output_;
};

} // namespace rmcs_core::controller::task_components

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(
    rmcs_core::controller::task_components::SinCosAdder, rmcs_executor::Component)