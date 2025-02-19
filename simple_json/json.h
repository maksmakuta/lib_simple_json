#ifndef JSON_H
#define JSON_H

#include <vector>
#include <map>
#include <optional>
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

    using json_variant = std::variant<
        std::nullptr_t, bool, double, std::string, json_array, json_object
    >;

    class json_value : public json_variant{
    public:
        json_value() = default;

        explicit json_value(bool);
        explicit json_value(double v);
        explicit json_value(long v);
        explicit json_value(const std::string& v);
        explicit json_value(const json_array& v);
        explicit json_value(const json_object& v);

        json_value& operator=(std::nullptr_t);
        json_value& operator=(bool);
        json_value& operator=(double v);
        json_value& operator=(long v);
        json_value& operator=(const char* v);
        json_value& operator=(const std::string& v);
        json_value& operator=(const json_array& v);
        json_value& operator=(const json_object& v);

        [[nodiscard]] bool isBool() const;
        [[nodiscard]] bool isNumber() const;
        [[nodiscard]] bool isString() const;
        [[nodiscard]] bool isObject() const;
        [[nodiscard]] bool isArray() const;
        [[nodiscard]] bool isNull() const;

        [[nodiscard]] bool getBoolOr(bool def = false) const;
        [[nodiscard]] double getNumberOr(double def = 0.0) const;
        [[nodiscard]] std::string getStringOr(const std::string& def = "") const;
        [[nodiscard]] json_object getObjectOr(const json_object& def = {}) const;
        [[nodiscard]] json_array getArrayOr(const json_array& def = {}) const;

        [[nodiscard]] std::optional<bool> getBool() const;
        [[nodiscard]] std::optional<double> getNumber() const;
        [[nodiscard]] std::optional<std::string> getString() const;
        [[nodiscard]] std::optional<json_object> getObject() const;
        [[nodiscard]] std::optional<json_array> getArray() const;
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
        json_object readObject();
        json_array readArray();
    private:
        json_object parseObject();
        json_array  parseArray();
        json_value  parseValue();
        std::string parseKey();
        json_value parseNumber();

        std::string source;
        uint position{0};
    };

}

#endif //JSON_H
