#include <cmath>
#include <rclcpp/node.hpp>
#include <rmcs_executor/component.hpp>

namespace rmcs_core::controller::task_components {

class SinCosGenerator
    : public rmcs_executor::Component
    , public rclcpp::Node {
public:
    SinCosGenerator()
        : Node(
              get_component_name(),
              rclcpp::NodeOptions{}.automatically_declare_parameters_from_overrides(true)) {
        
        // 从配置文件读取角频率ω
        omega_ = get_parameter("omega").as_double();
        
        // 注册输出接口
        register_output("/task/sin_output", sin_output_);
        register_output("/task/cos_output", cos_output_);
        
        // 初始化时间计数器
        time_counter_ = 0.0;
    }

    void update() override {
        // 更新时间计数器（考虑1000Hz更新频率）
        time_counter_ += 0.001;  // 1ms
        
        // 计算sin(ωt)和cos(ωt)
        double sin_value = std::sin(omega_ * time_counter_);
        double cos_value = std::cos(omega_ * time_counter_);
        
        // 更新输出接口值
        *sin_output_ = sin_value;
        *cos_output_ = cos_value;
    }

private:
    double omega_;
    double time_counter_;
    
    OutputInterface<double> sin_output_;
    OutputInterface<double> cos_output_;
};

} // namespace rmcs_core::controller::task_components

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(
    rmcs_core::controller::task_components::SinCosGenerator, rmcs_executor::Component)