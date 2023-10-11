#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "authorization.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using auth::AuthService;
using auth::LoginRequest;
using auth::LoginResponse;

class AuthServiceImpl final : public AuthService::Service {
  
  Status Login(ServerContext* context, const LoginRequest* request, LoginResponse* response) override {
    std::string user_name = request->username();
    std::string password = request->password();
    std::string token;
    if(user_name == password)
      token = "Success";
    else 
      token = "Fail";
    response->set_token(token);
    return Status::OK;
  }

  // next functions ..
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  AuthServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main() {
  RunServer();
  return 0;
}
