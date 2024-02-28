// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for interfaces/Object
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)
#pragma warning(disable : 4265)
#pragma warning(disable : 4456)
#pragma warning(disable : 4458)
#pragma warning(disable : 4946)
#pragma warning(disable : 4244)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif //_MSC_VER
#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/object.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class INTERFACES_EXPORT ros2_interfaces_msg_Object_common : public MATLABROS2MsgInterface<interfaces::msg::Object> {
  public:
    virtual ~ros2_interfaces_msg_Object_common(){}
    virtual void copy_from_struct(interfaces::msg::Object* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const interfaces::msg::Object* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_interfaces_msg_Object_common::copy_from_struct(interfaces::msg::Object* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //color
        const matlab::data::TypedArray<uint8_t> color_arr = arr["color"];
        msg->color = color_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'color' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'color' is wrong type; expected a uint8.");
    }
    try {
        //x
        const matlab::data::TypedArray<int32_t> x_arr = arr["x"];
        msg->x = x_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a int32.");
    }
    try {
        //y
        const matlab::data::TypedArray<int32_t> y_arr = arr["y"];
        msg->y = y_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a int32.");
    }
    try {
        //angle
        const matlab::data::TypedArray<int32_t> angle_arr = arr["angle"];
        msg->angle = angle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angle' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'angle' is wrong type; expected a int32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_interfaces_msg_Object_common::get_arr(MDFactory_T& factory, const interfaces::msg::Object* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","RED","YELLOW","BLUE","color","x","y","angle"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("interfaces/Object");
    // RED
    auto currentElement_RED = (msg + ctr)->RED;
    outArray[ctr]["RED"] = factory.createScalar(currentElement_RED);
    // YELLOW
    auto currentElement_YELLOW = (msg + ctr)->YELLOW;
    outArray[ctr]["YELLOW"] = factory.createScalar(currentElement_YELLOW);
    // BLUE
    auto currentElement_BLUE = (msg + ctr)->BLUE;
    outArray[ctr]["BLUE"] = factory.createScalar(currentElement_BLUE);
    // color
    auto currentElement_color = (msg + ctr)->color;
    outArray[ctr]["color"] = factory.createScalar(currentElement_color);
    // x
    auto currentElement_x = (msg + ctr)->x;
    outArray[ctr]["x"] = factory.createScalar(currentElement_x);
    // y
    auto currentElement_y = (msg + ctr)->y;
    outArray[ctr]["y"] = factory.createScalar(currentElement_y);
    // angle
    auto currentElement_angle = (msg + ctr)->angle;
    outArray[ctr]["angle"] = factory.createScalar(currentElement_angle);
    }
    return std::move(outArray);
  } 
class INTERFACES_EXPORT ros2_interfaces_Object_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_interfaces_Object_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_interfaces_Object_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<interfaces::msg::Object,ros2_interfaces_msg_Object_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_interfaces_Object_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<interfaces::msg::Object,ros2_interfaces_msg_Object_common>>();
  }
  std::shared_ptr<void> ros2_interfaces_Object_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<interfaces::msg::Object>();
    ros2_interfaces_msg_Object_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_interfaces_Object_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_interfaces_msg_Object_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (interfaces::msg::Object*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_interfaces_msg_Object_common, MATLABROS2MsgInterface<interfaces::msg::Object>)
CLASS_LOADER_REGISTER_CLASS(ros2_interfaces_Object_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER