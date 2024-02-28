cmake_minimum_required(VERSION 3.8)
project(yolo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(interfaces REQUIRED)
find_package(OpenVINO REQUIRED)

add_executable(
  node
  src/node.cpp
)
ament_target_dependencies(node rclcpp cv_bridge sensor_msgs OpenCV interfaces)

include_directories(node
  /opt/intel/openvino_2023/runtime/include
  /opt/intel/openvino_2023/runtime/include/ie
  /opt/intel/openvino_2023/runtime/include/ngraph
)

target_link_libraries(node
  /opt/intel/openvino_2023/runtime/lib/intel64/libopenvino.so
)

install(TARGETS
  node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
