#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>


class CommandParser
{
public:
    typedef bool (*Callback) (const String& value);

    struct Item
    {
        const String identifier;
        const Callback callback;
    };
    using List = std::vector<Item>;

    CommandParser(const List& list);
    uint8_t parse(const String& line);
    static bool compare(const String& src, const String& ref);

private:
    List m_list;
};

#endif // COMMAND_PARSER_H
