#include "CommandParser.h"

static const unsigned long consoleBaudrate = 115200;
static const unsigned char consoleConfig = SERIAL_8N1;

static unsigned long baudrate = 4800;
static unsigned char config = SERIAL_8N1;

static String commandBuffer;

bool baudrateCallback(const String& value)
{
    bool ok = false;
    int v = value.toInt();
    if(v != 0)
    {
        baudrate = v;
        ok = true;
        Serial3.print("Baudrate changed: ");
        Serial3.println(baudrate);
    }
    return ok;
}

CommandParser::List list = {
    {"BAUDRATE", baudrateCallback},
}

static CommandParser parser(list);

void start() {
    Serial1.begin(m_baudrate, m_config);
    Serial2.begin(m_baudrate, m_config);
}

void stop() {
    Serial1.end();
    Serial2.end();
}

void setup() {

    Serial3.begin(consoleBaudrate, consoleConfig);

    Serial3.println("");
    Serial3.println("Serial Port Forwarder (v0.1)");
    Serial3.println("====================================");
    Serial3.println("2019-11-01, Eric Zhang <Eric.ZH.Zhang@emerson.com>");
    Serial3.println("");
    Serial3.println("Bridges Serial1 and Serial2, and forward them to Serial3");
    Serial3.println("--------------------------------------------");
    Serial3.println("");

    start();
}

void serialEvent1()
{
    while(Serial1.available())
    {
        register char c = Serial1.read();
        Serial2.write(c);
        Serial3.write(c);
    }
}

void serialEvent2()
{
    while(Serial2.available())
    {
        register char c = Serial2.read();
        Serial1.write(c);
        Serial3.write(c);
    }
}

void loop() {
    if(Serial3.available())
    {
        register char c = Serial3.read();
        commandBuffer += c;
        if(c == '\n')
        {
            parser.parse(commandBuffer);
            commandBuffer = "";
        }
    }

}
