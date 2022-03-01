#include "Entrypoint.hpp"

int main(int argc, char **argv)
{
  auto app = CreateApplication();
  app->Run();
  delete app;
  app = nullptr;
  return 0;
}