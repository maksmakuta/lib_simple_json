#ifndef JSON_H
#define JSON_H

#include <vector>
#include <map>
#include <string>
#include <variant>

namespace simple_json {
    using uint = unsigned int;

    class json_value;

    class json_object : public std::map<std::string, json_value>{
    public:
        json_object() = default;
    };

    class json_array : public std::vector<json_value>{
    public:
        json_array() = default;

        json_array(const std::initializer_list<bool>& v);
        json_array(const std::initializer_list<double>& v);
        json_array(const std::initializer_list<std::string>& v);
        json_array(const std::initializer_list<json_object>& v);
        json_array(const std::initializer_list<json_array>& v);

    };

    class json_value{
    public:
        using json_type = std::variant<
            std::nullptr_t,
            bool,
            double,
            std::string,
            json_array,
            json_object
        >;

        json_value();
        explicit json_value(bool b);
        explicit json_value(int i);
        explicit json_value(double d);
        explicit json_value(const std::string& s);
        explicit json_value(const char* s);
        explicit json_value(const json_array& arr);
        explicit json_value(const json_object& obj);

        json_value(const json_value& obj);

        json_value& operator=(const std::nullptr_t& new_value);
        json_value& operator=(bool new_value);
        json_value& operator=(int new_value);
        json_value& operator=(double new_value);
        json_value& operator=(const std::string& new_value);
        json_value& operator=(const char* new_value);
        json_value& operator=(const json_array& new_value);
        json_value& operator=(const json_object& new_value);
        json_value& operator=(const std::initializer_list<bool>& v);
        json_value& operator=(const std::initializer_list<double>& v);
        json_value& operator=(const std::initializer_list<std::string>& v);
        json_value& operator=(const std::initializer_list<json_object>& v);
        json_value& operator=(const std::initializer_list<json_array>& v);

        bool operator==(const json_value& obj) const;

        json_type value;
    };

    class json_writer {
    public:
        explicit json_writer(json_object,int = 4);
        std::string pretty();
        std::string compact();

    private:
        std::string pretty(const json_value& obj);
        std::string pretty(const json_array& obj);
        std::string pretty(const json_object& obj);

        std::string compact(const json_value& obj);
        std::string compact(const json_array& obj);
        std::string compact(const json_object& obj);

        json_object json{};
        int padding{4};
        int level{0};
    };

    class json_reader {
    public:
        explicit json_reader(std::string input);
        json_object read();
    private:
        json_object parseObject();
        json_array  parseArray();
        json_value  parseValue();
        std::string parseKey();
        json_value parseNumber();

    private:
        std::string source;
        uint position{0};
    };

}

#endif //JSON_H
