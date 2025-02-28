# Simple JSON

Simple JSON library build on top of STL

This project was created to practice and learn something new. If you need a JSON library for C++, use something else, or you can use this project at your own risk

### Features
 - Construct JSON like std::map
 - Read JSON data from string
 - Write JSON into string (or variable/file/etc)
   - Pretty printer ```json_writer().pretty()```
   - Compact printer ```json_writer().compact()```
 - Operations with values
   - Check type
   - Get data
   - Rewrite value (using same type or another)

### Dependencies
 - C++20 with STL (std::vector, std::variant, std::string, std::map, std::optional)

### Example

```C++

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

    std::cout << json_writer(result,4).pretty() << std::endl;
    return 0;
}

```

Pretty output:

```JSON
{
    "author" : {
        "gender" : "male",
        "languages" : [
            "C++",
            "Java",
            "Kotlin"
        ],
        "name" : "Maks",
        "surname" : "Makuta"
    },
    "project" : {
        "lang" : "C++",
        "name" : "lib_simple_json",
        "tools" : [
            "CMake",
            "CLion"
        ]
    }
}

```

Compact output:

```JSON
{"author":{"gender":"male","languages":["C++","Java","Kotlin"],"name":"Maks","surname":"Makuta"},"project":{"lang":"C++","name":"lib_simple_json","tools":["CMake","CLion"]}}
```

### Author
Maks Makuta   
2025 (C) MIT Licence
