#include <iostream>

#include "json.h"

#include <utility>
#include <sstream>

namespace simple_json {

    std::string spaces(int count) {
        std::stringstream ss;
        for (int i = 0; i < count; i++) {
            ss << ' ';
        }
        return ss.str();
    }

    json_writer::json_writer(json_object o, int t) : json{std::move(o)}, padding{t} {}

    std::string json_writer::pretty() {
        return pretty(json);
    }

    std::string json_writer::pretty(const json_value& obj){
        std::stringstream ss;
        if (std::get_if<std::nullptr_t>(&obj)) {
            ss << "null";
        }else if (const auto& type_bool = std::get_if<bool>(&obj)) {
            ss << std::string(*type_bool ? "true" : "false");
        }else if (const auto& type_num = std::get_if<double>(&obj)) {
            ss << *type_num ;
        }else if (const auto& type_str = std::get_if<std::string>(&obj)) {
            ss << "\"" << *type_str << "\"";
        }else if (const auto& type_arr = std::get_if<json_array>(&obj)) {
            ss << pretty(*type_arr);
        }else if (const auto& type_obj = std::get_if<json_object>(&obj)) {
            ss << pretty(*type_obj);
        }
        return ss.str();
    }

    bool is_composite(const json_value& obj) {
        return std::holds_alternative<json_array>(obj) || std::holds_alternative<json_object>(obj);
    }

    std::string json_writer::pretty(const json_array& obj){
        std::stringstream ss;
        ss << '[' << std::endl;
        ++level;
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            ss << spaces(padding * level) << pretty(*it);
            if (it != obj.end() - 1) {
                ss << "," << std::endl;
            }
        }
        --level;
        ss << std::endl << spaces(padding * level) <<']';
        return ss.str();
    }

    std::string json_writer::pretty(const json_object& obj){
        std::stringstream ss;
        ss << "{" << std::endl;
        ++level;
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            ss << spaces(padding * level) << "\"" << it->first << "\"" << " : " << pretty(it->second);
            if (it != --obj.end()) {
                ss << ",";
            }
            ss << std::endl;
        }
        --level;
        ss << spaces(padding * level) << "}";
        return ss.str();
    }

    std::string json_writer::compact() {
        return compact(json);
    }

    std::string json_writer::compact(const json_value& obj){
        std::stringstream ss;
        if (std::get_if<std::nullptr_t>(&obj)) {
            ss << "null";
        }else if (const auto& type_bool = std::get_if<bool>(&obj)) {
            ss << std::string(*type_bool ? "true" : "false");
        }else if (const auto& type_num = std::get_if<double>(&obj)) {
            ss << *type_num ;
        }else if (const auto& type_str = std::get_if<std::string>(&obj)) {
            ss << "\"" << *type_str << "\"";
        }else if (const auto& type_arr = std::get_if<json_array>(&obj)) {
            ss << compact(*type_arr);
        }else if (const auto& type_obj = std::get_if<json_object>(&obj)) {
            ss << compact(*type_obj);
        }
        return ss.str();
    }

    std::string json_writer::compact(const json_array& obj){
        std::stringstream ss;
        ss << '[';
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            ss << compact(*it);
            if (it != obj.end() - 1) {
                ss << ",";
            }
        }
        ss  << ']';
        return ss.str();
    }

    std::string json_writer::compact(const json_object& obj){
        std::stringstream ss;
        ss << "{";
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            ss << "\"" << it->first << "\"" << ":" << compact(it->second);
            if (it != --obj.end()) {
                ss << ",";
            }
        }
        ss << "}";
        return ss.str();
    }



}