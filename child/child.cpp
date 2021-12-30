#include <fstream>
#include <iostream>
#include <string>

#include "tools/cpp/runfiles/runfiles.h"

int main(int argc, const char** argv) {
  std::cout << "Child started with argv[0]=" << argv[0] << std::endl;

  using ::bazel::tools::cpp::runfiles::Runfiles;
  std::string error;
  Runfiles* runfiles = Runfiles::Create(argv[0], &error);
  if (runfiles == nullptr) {
    std::cout << "Failed to initialize runfiles: " << error << std::endl;
    return 1;
  }

  std::cout << "Runfiles variables in child:" << std::endl;
  for (const auto& var : runfiles->EnvVars()) {
    std::cout << var.first << "=" << var.second << std::endl;
  }

  std::string data_path = runfiles->Rlocation("__main__/data/foo.txt");
  std::ifstream foo(data_path);
  if (foo.good()) {
    std::cout << "Found runfile at: " << data_path << std::endl;
    return 0;
  } else {
    std::cout << "Failed to find runfile at: " << data_path << std::endl;
    return 1;
  }
}