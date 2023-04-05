#include "mbed.h"
#include "accelerometer.h"

static BufferedSerial serial_port(USBTX, USBRX);

InterruptIn btnRecord(BUTTON1);
EventQueue queue(128 * EVENTS_EVENT_SIZE);
Thread t;
Accelerometer acc;
double Accel[3]={0};
double data[128][3];

void record(void) {

    for (int i = 0; i < 128; i++){
        acc.GetAcceleromterSensor(Accel);
        acc.GetAcceleromterCalibratedData(Accel);
        data[i][0] = Accel[0];
        data[i][1] = Accel[1];
        data[i][2] = Accel[2];
        ThisThread::sleep_for(10ms);
    }
}

void printData()
{
    for (int i = 0; i < 128; i++){
        printf("%lf/%lf/%lf\n" ,data[i][0], data[i][1], data[i][2]);
    }
}

int main() {
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    char buf;
    while (true){
        if (serial_port.readable()){
            serial_port.read(&buf, 1);
            if (buf == '1'){
                record();
            }
            printData();
        }
    }
}