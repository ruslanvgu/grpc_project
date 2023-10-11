cmake_minimum_required(VERSION 3.8)

project(grpc C CXX)

#include(common/common.cmake)

include_directories(
  "/home/ruslanvgu/.local/include"
)

link_directories(
 "/home/ruslanvgu/.local/lib"
)

find_package(Protobuf CONFIG REQUIRED)
  message(STATUS "Using protobuf ${Protobuf_VERSION}")
  set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)

find_program(_PROTOBUF_PROTOC protoc)
  if(_PROTOBUF_PROTOC)
    message("Program found at: ${_PROTOBUF_PROTOC}")
  else()
    message("Program not found.")
  endif()

find_package(gRPC CONFIG REQUIRED)
  message(STATUS "Using gRPC ${gRPC_VERSION}")
  set(_GRPC_GRPCPP gRPC::grpc++)
  set(_REFLECTION grpc++_reflection)

find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
  if(_GRPC_CPP_PLUGIN_EXECUTABLE)
    message("Program found at: ${_GRPC_CPP_PLUGIN_EXECUTABLE}")
  else()
    message("Program not found.")
  endif()

#find_package(jsoncpp CONFIG REQUIRED)
#find_package(openssl CONFIG REQUIRED)
#find_package(absl CONFIG REQUIRED)


# Proto file
#get_filename_component(hw_proto "proto/service.proto" ABSOLUTE)
#get_filename_component(hw_proto_path "${hw_proto}" PATH)


# Установка переменных
#set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
#set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
#set(_REFLECTION grpc++_reflection)
#set(_GRPC_GRPCPP grpc++)
#set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)

# message("${_PROTOBUF_PROTOC}")
# message("${_GRPC_CPP_PLUGIN_EXECUTABLE}")
# message("${_REFLECTION}")
# message("${_GRPC_GRPCPP}")
# message("${_PROTOBUF_LIBPROTOBUF}")

message(STATUS "Using protobuf ${Protobuf_VERSION}")
message(STATUS "Protobuf include directory: ${Protobuf_INCLUDE_DIRS}")
message(STATUS "Protobuf libraries: ${Protobuf_LIBRARIES}")

message(STATUS "Using gRPC ${gRPC_VERSION}")
message(STATUS "gRPC include directory: ${gRPC_INCLUDE_DIR}")
message(STATUS "gRPC libraries: ${_GRPC_GRPCPP}")

message(STATUS "Using absl version: ${absl_VERSION}")
message(STATUS "absl include directory: ${absl_INCLUDE_DIRS}")
message(STATUS "absl library: ${absl_LIBRARIES}")

# Generated sources
# set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/service.pb.cc")
# set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/service.pb.h")
# set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/service.grpc.pb.cc")
# set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/service.grpc.pb.h")
# add_custom_command(
#      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
#      COMMAND ${_PROTOBUF_PROTOC}
#      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
#        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
#        -I "${hw_proto_path}"
#        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
#        "${hw_proto}"
#      DEPENDS "${hw_proto}")

# Include generated *.pb.h files
#include_directories("${CMAKE_CURRENT_BINARY_DIR}")
# hw_grpc_proto
#add_library(hw_grpc_proto
#  ${hw_grpc_srcs}
#  ${hw_grpc_hdrs}
#  ${hw_proto_srcs}
#  ${hw_proto_hdrs})
# Targets greeter_[async_](client|server)

add_executable(grpc_server grpc_server.cpp authorization.grpc.pb.h authorization.grpc.pb.cc authorization.pb.h authorization.pb.cc)
target_link_libraries(grpc_server 
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF}
)
add_executable(grpc_client  grpc_client.cpp authorization.grpc.pb.h authorization.grpc.pb.cc authorization.pb.h authorization.pb.cc)
target_link_libraries(grpc_client 
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF}
)
#foreach(_target grpc_server)
 # add_executable(${_target} "${_target}.cpp")
 # target_link_libraries(${_target}
 #   hw_grpc_proto
 #   absl::flags
 #   absl::flags_parse
 #   ${_REFLECTION}
 #   ${_GRPC_GRPCPP}
 #   ${_PROTOBUF_LIBPROTOBUF}
    #${JSONCPP_LIBRARY}
 #   jsoncpp_lib
    #${OPENSSL_LIBRARIES}
 #   )
#endforeach()

