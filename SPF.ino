static long m_baudrate = 115000;
static uint8_t m_config = SERIAL_8N1;

static long console_baudrate = 115200;
static uint8_t console_config = SERIAL_8N1;

static HardwareSerial& serialPort = Serial;

void setup() {
    serialPort.begin(console_baudrate, console_config);

    serialPort.println("");
    serialPort.println("Serial Port Forwarder (v0.2)");
    serialPort.println("====================================");
    serialPort.println("Eric Zhang <Eric.ZH.Zhang@emerson.com>");
    serialPort.println("2019-11-05");
    serialPort.println("");
    serialPort.println("Bridges Serial1 and Serial2, and forward them to Serial or Serial3");
    serialPort.println("--------------------------------------------");
    serialPort.println("");
    
    Serial1.begin(m_baudrate, m_config);
    Serial2.begin(m_baudrate, m_config);
}

void serialEvent1()
{
    while(Serial1.available())
    {
        register char c = Serial1.read();
        Serial2.write(c);
        serialPort.write(c);
    }
}

void serialEvent2()
{
    while(Serial2.available())
    {
        register char c = Serial2.read();
        Serial1.write(c);
        serialPort.write(c);
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
