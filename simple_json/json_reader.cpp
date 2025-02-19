#include <iostream>

#include "json.h"
#include <utility>

namespace simple_json {

    json_reader::json_reader(std::string input) : source(std::move(input)){
        std::erase_if(source, isspace);
    }

    json_object json_reader::read() {
        json_object result;
        if (!source.empty()) {
            if (*source.begin() == '[') {
                result["arr"] = parseArray();
            }else{
                result = parseObject();
            }
        }
        return result;
    }

    json_object json_reader::parseObject(){
        json_object obj;
        position++;
        while (source[position] != '}') {
            std::string key = parseKey();
            if (source[position] != ':') {
                throw std::runtime_error("Invalid JSON: Expected ':' after key.");
            }
            position++;
            obj[key] = parseValue();
            if (source[position] == ',') {
                position++;
            } else if (source[position] != '}') {
                throw std::runtime_error("Invalid JSON: Expected ',' or '}' after value.");
            }
        }
        position++;
        return obj;
    }

    json_array  json_reader::parseArray(){
        json_array arr;
        position++;
        while (source[position] != ']') {
            json_value value = parseValue();
            arr.push_back(value);
            if (source[position] == ',') {
                position++;
            } else if (source[position] != ']') {
                throw std::runtime_error("Invalid JSON: Expected ',' or ']' after value in array.");
            }
        }
        position++;
        return arr;
    }

    json_value  json_reader::parseValue(){
        if (std::isdigit(source[position]) || source[position] == '-') {
            return parseNumber();
        } else if (source[position] == '\"') {
            return json_value(parseKey());
        } else if (source[position] == 't' || source[position] == 'f' || source[position] == 'n') {
            std::string key;
            while (std::isalpha(source[position])) {
                key += source[position++];
            }
            if (key == "true") {
                return json_value(true);
            }else if (key == "false") {
                return json_value(false);
            }else if (key == "null") {
                return {};
            }else {
                throw std::runtime_error("Invalid JSON: Invalid JSON word.");
            }
        } else if (source[position] == '{') {
            return json_value(parseObject());
        } else if (source[position] == '[') {
            return json_value(parseArray());
        } else {
            throw std::runtime_error("Invalid JSON: Unexpected character for value.");
        }
    }

    std::string json_reader::parseKey(){
        if (source[position] != '\"') {
            throw std::runtime_error("Invalid JSON: Expected '\"' at the beginning of a key.");
        }
        position++;
        std::string key;
        while (source[position] != '\"') {
            key += source[position++];
        }
        position++;
        return key;
    }


    json_value json_reader::parseNumber() {
        std::string numberStr;
        bool isFloatingPoint = false;
        if (source[position] == '-') {
            numberStr += source[position++];
        }
        while (std::isdigit(source[position])) {
            numberStr += source[position++];
        }
        if (source[position] == '.') {
            isFloatingPoint = true;
            numberStr += source[position++];
            while (std::isdigit(source[position])) {
                numberStr += source[position++];
            }
        }
        if (source[position] == 'e' || source[position] == 'E') {
            isFloatingPoint = true;
            numberStr += source[position++];
            if (source[position] == '-' || source[position] == '+') {
                numberStr += source[position++];
            }
            while (std::isdigit(source[position])) {
                numberStr += source[position++];
            }
        }

        json_value value;
        if (isFloatingPoint) {
            value = std::stod(numberStr); // Convert to double
        } else {
            value = std::stoi(numberStr); // Convert to int
        }
        return value;
    }


}