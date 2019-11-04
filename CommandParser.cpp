#include "CommandParser.h"

#include <string.h>
#include <ctype.h>

static char* _strtok_r (char *str, const char *delim, char **stash)
{
    char *end;
    if(str == NULL)
        str = *stash;

    if(*str == '\0')
    {
        *stash = str;
        return NULL;
    }

    str += strspn(str, delim);
    if(*str == '\0')
    {
        *stash = str;
        return NULL;
    }

    end = str + strcspn(str, delim);
    if(*end == '\0')
    {
        *stash = end;
        return str;
    }

    *end = '\0';
    *stash = end + 1;
    return str;
}

CommandParser::CommandParser(const CommandList& list) : m_list(list)
{}

uint8_t CommandParser::parse(const String& line)
{
    uint8_t count = 0;

    const uint8_t length (200);
    char buffer[length];
    line.getBytes((unsigned char*)buffer, length);

    const char delimiter[] = ",; \f\n\r\t\v";

    char* stash;
    char* token = _strtok_r(buffer, delimiter, &stash);

    while(token != NULL)
    {
        // Extract parameters from token
        const char mark[] = ":=";
        char* param = strtok(token, mark);
        char* value = strtok(NULL, mark);

        if(param != NULL && value != NULL)
        {
            String p (param);
            String v (value);

            for(CommandList::const_iterator i = m_list.begin(); i != m_list.end(); ++i)
            {
                if(i->identifier.equalsIgnoreCase(p))
                {
                    if(i->callback(v))
                        count++;
                }
            }
        }

        token = _strtok_r(NULL, delimiter, &stash);
    }

    return count;
}

bool CommandParser::compare(const String& src, const String& ref)
{
    return (src.compareTo(ref) == 0);
}
