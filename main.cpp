#include <iostream>
#include "json.h"

using namespace simple_json;

int main() {

    json_object author;
    author["name"] = "Maks";
    author["surname"] = "Makuta";
    author["gender"] = "male";
    author["languages"] = std::initializer_list<std::string>{"C++", "Java", "Kotlin"};

    json_object project;
    project["name"] = "lib_simple_json";
    project["lang"] = "C++";
    project["tools"] = std::initializer_list<std::string>{"CMake", "CLion"};

    json_object result;
    result["author"] = author;
    result["project"] = project;

    std::cout << json_writer(result,4).compact() << std::endl;
    return 0;
}