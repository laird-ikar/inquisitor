#pragma once

#include <iostream>
#include <regex>
#include <thread>

#include "arping.hpp"
#include "capture_and_forward.hpp"

using namespace std;

void signalHandler(int signum);
