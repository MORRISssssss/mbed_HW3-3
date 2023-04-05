#include "mbed.h"
#include "accelerometer.h"

static BufferedSerial serial_port(USBTX, USBRX);
DigitalOut led(LED1);

Accelerometer acc;
double data[128][3] = {{0}};

int main() {
    char buf;
    led = 0;
    while (true){
        if (serial_port.readable()){
            serial_port.read(&buf, 1);
            if (buf == '1'){
                led = 1;
                for (int i = 0; i < 128; i++){
                    acc.GetAcceleromterSensor(data[i]);
                    acc.GetAcceleromterCalibratedData(data[i]);
                    ThisThread::sleep_for(10ms);
                }
                led = 0;
                for (int i = 0; i < 128; i++){
                    printf("%lf/%lf/%lf\n", data[i][0], data[i][1], data[i][2]);
                }
            }
            
        }
    }
}