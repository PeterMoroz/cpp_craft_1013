#include <iostream>
#include <exception>
#include "Task24.h"

using namespace std;

static const char* kInputFilename = "2.4_example.in";
static const char* kOutputFilename = "2.4_results.out";

int main() {

  Task24 task(kInputFilename, kOutputFilename);

  try {
    task.Initialize();
    task.Perform();
  } catch (exception& ex) {
    cout << "An exception has been caught. "
      << "Reason: " << ex.what() << endl;
    return -1;
  }

  return 0;
}