#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "authorization.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using auth::AuthService;
using auth::LoginRequest;
using auth::LoginResponse;

class AuthClient {
 public:
  AuthClient(std::shared_ptr<Channel> channel): stub_(AuthService::NewStub(channel)) {}

  std::string Login(const std::string& username, const std::string& password) {
    LoginRequest request; 
    request.set_username(username);
    request.set_password(password);
    LoginResponse response;
    ClientContext context;
    Status status = stub_->Login(&context, request, &response);

    if (status.ok()) {
      return response.token();
    } else {
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<AuthService::Stub> stub_;
};

int main() {
  std::shared_ptr<Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
  AuthClient client(channel);
  std::string name = "Alice";
  std::string pass = "1234";
  std::string response = client.Login(name,pass);
  std::cout << "Server response: " << response << std::endl;
  return 0;
}
