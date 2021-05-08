#include "../../include/utils.h"

void utils::string::lower(std::string& in) {
     transform(in.begin(), in.end(), in.begin(), ::tolower);
}