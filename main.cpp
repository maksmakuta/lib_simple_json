#include <iostream>
#include "json.h"

using namespace simple_json;

const auto test = R"(
[
    {
        "id": 1,
        "name": "Player1",
        "score": 100
    },
    {
        "id": 2,
        "name": "Player2",
        "score": 200
    }
]
)";

int main() {
    json_reader reader(test);
    json_object json = reader.read();
    std::cout << json_writer(json,4).pretty() << std::endl;
    return 0;
}