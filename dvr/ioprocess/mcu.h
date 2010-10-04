
#ifndef __MCU_H__
#define __MCU_H__


#define MCU_CMD_RESET	        (0)
#define MCU_CMD_READRTC         (0x6)
#define MCU_CMD_WRITERTC        (0x7)
#define MCU_CMD_POWEROFFDELAY	(0x8)
#define MCU_CMD_IOTEMPERATURE   (0x0b)
#define MCU_CMD_HDTEMPERATURE   (0x0c)
#define MCU_CMD_BOOTUPREADY     (0x11)
#define MCU_CMD_KICKWATCHDOG    (0x18)
#define MCU_CMD_SETWATCHDOGTIMEOUT (0x19)
#define MCU_CMD_ENABLEWATCHDOG  (0x1a)
#define MCU_CMD_DISABLEWATCHDOG (0x1b)
#define MCU_CMD_DIGITALINPUT	(0x1d)
#define MCU_CMD_CAMERA_ZOOMIN   (0x1f)
#define MCU_CMD_CAMERA_ZOOMOUT  (0x20)
#define MCU_CMD_MICON	        (0x21)
#define MCU_CMD_MICOFF	        (0x22)
#define MCU_CMD_HDPOWERON       (0x28)
#define MCU_CMD_HDPOWEROFF      (0x29)
#define MCU_CMD_GETVERSION	    (0x2d)
#define MCU_CMD_DEVICEPOWER     (0x2e)
#define MCU_CMD_PANELLED        (0x2f)
#define MCU_CMD_DIGITALOUTPUT	(0x31)
#define MCU_CMD_GSENSORINIT	    (0x34)
#define MCU_CMD_READCODE	    (0x41)

// mcu input
#define MCU_INPUT_DIO           ('\x1c')
#define MCU_INPUT_IGNITIONOFF   ('\x08') 
#define MCU_INPUT_IGNITIONON    ('\x09')
#define MCU_INPUT_ACCEL         ('\x40')

#define MCU_CMD_DELAY       (500000)
#define MIN_SERIAL_DELAY	(10000)
#define DEFSERIALBAUD	    (115200)

#define MCU_INPUTNUM (6)
#define MCU_OUTPUTNUM (4)

#ifdef PWII_APP

#define PWII_CMD_BOOTUPREADY    (4)
#define PWII_CMD_VERSION        (0x11)
#define PWII_CMD_C1             (0x12)
#define PWII_CMD_C2             (0x13)
#define PWII_CMD_LEDMIC         (0xf)
#define PWII_CMD_LCD	        (0x16)
#define PWII_CMD_STANDBY        (0x15)
#define PWII_CMD_LEDPOWER       (0x14)
#define PWII_CMD_LEDERROR       (0x10)
#define PWII_CMD_POWER_GPSANT   (0x0e)
#define PWII_CMD_POWER_GPS      (0x0d)
#define PWII_CMD_POWER_RF900    (0x0c)
#define PWII_CMD_POWER_WIFI     (0x19)
#define PWII_CMD_OUTPUTSTATUS   (0x17)

// CDC inputs 
#define PWII_INPUT_REC ('\x05')
#define PWII_INPUT_C1 (PWII_INPUT_REC)
#define PWII_INPUT_C2 ('\x06')
#define PWII_INPUT_TM ('\x07')
#define PWII_INPUT_LP ('\x08')
#define PWII_INPUT_BO ('\x0b')
#define PWII_INPUT_MEDIA ('\x09')
#define PWII_INPUT_BOOTUP ('\x18')

#endif      // PWII_APP

inline int bcd(int v)
{
    return (((v/10)%10)*0x10 + v%10) ;
}

// open serial port
int serial_open(char * device, int buadrate) ;
int serial_dataready(int handle, int usdelay=MIN_SERIAL_DELAY, int * usremain=NULL);

extern int mcupowerdelaytime ;
extern int mcu_baud ;
extern unsigned int mcu_doutputmap ;
extern int mcu_inputmissed ;



// check if data from mcu is ready          
int mcu_dataready(int usdelay=MIN_SERIAL_DELAY, int * usremain=NULL) ;
// read one byte from mcu
int mcu_readbyte(char * b, int timeout=MIN_SERIAL_DELAY);
// read data from mcu
int mcu_read(char * sbuf, size_t bufsize, int wait=MIN_SERIAL_DELAY, int interval=MIN_SERIAL_DELAY);
// write data to mcu
int mcu_write(void * buf, int bufsize);
// clear receiving buffer
void mcu_clear(int delay=MIN_SERIAL_DELAY);
int mcu_input(int usdelay);
void mcu_response(char * msg, int datalen=0, ... );

void mcu_calchecksum( char * data );
int mcu_sendcmd(int cmd, int datalen=0, ...);
char * mcu_cmd(int cmd, int datalen=0, ...);

int mcu_reset();
int mcu_bootupready();
time_t mcu_r_rtc( struct tm * ptm = NULL );
int mcu_w_rtc(time_t tt);
void mcu_rtctosys();
void mcu_readrtc();
void mcu_led(int led, int flash);
void mcu_devicepower(int device, int poweron );
int mcu_version(char * version);
void mcu_poweroffdelay();
void mcu_watchdogenable();
void mcu_watchdogdisable();
int mcu_watchdogkick();
int mcu_iotemperature();
int mcu_hdtemperature();
void mcu_hdpoweron();
void mcu_hdpoweroff();
int mcu_doutput();
int mcu_checkinputbuf(char * ibuf);
void mcu_dinput_help(char * ibuf);
int mcu_dinput();
int mcu_update_firmware( char * firmwarefile) ;

#ifdef PWII_APP

char * mcu_pwii_cmd(int cmd, int datalen=0, ...);
int mcu_pwii_bootupready();
int mcu_pwii_version(char * version);
unsigned int mcu_pwii_ouputstatus();

#endif          // PWII_APP

void mcu_restart();
void mcu_init(config & dvrconfig) ;
void mcu_finish();

#endif      // __MCU_H__
