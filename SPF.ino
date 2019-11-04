static long m_baudrate = 4800;
static uint8_t m_config = SERIAL_8N1;

static long console_baudrate = 115200;
static uint8_t console_config = SERIAL_8N1;

void setup() {
    Serial3.begin(console_baudrate, console_config);

    Serial3.println("");
    Serial3.println("Serial Port Forwarder (v0.2)");
    Serial3.println("====================================");
    Serial3.println("2019-11-04, Eric Zhang <Eric.ZH.Zhang@emerson.com>");
    Serial3.println("");
    Serial3.println("Bridges Serial1 and Serial2, and forward them to Serial3");
    Serial3.println("--------------------------------------------");
    Serial3.println("");
    
    Serial1.begin(m_baudrate, m_config);
    Serial2.begin(m_baudrate, m_config);
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
  // put your main code here, to run repeatedly:

}
