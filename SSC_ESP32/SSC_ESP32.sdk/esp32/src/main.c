//AXI GPIO driver
#include "xgpio.h"
#include <string.h>
#include <stdio.h>

//send data over UART
#include "xil_printf.h"

//information about AXI peripherals
#include "xparameters.h"

#include "sleep.h"
#include "PmodESP32.h"

#ifdef __MICROBLAZE__
#define HOST_UART_DEVICE_ID XPAR_AXI_UARTLITE_0_BASEADDR
#define HostUart XUartLite
#define HostUart_Config XUartLite_Config
#define HostUart_CfgInitialize XUartLite_CfgInitialize
#define HostUart_LookupConfig XUartLite_LookupConfig
#define HostUart_Recv XUartLite_Recv
#define HostUartConfig_GetBaseAddr(CfgPtr) (CfgPtr->RegBaseAddr)
#include "xuartlite.h"
#include "xil_cache.h"
#else
#define HOST_UART_DEVICE_ID XPAR_PS7_UART_1_DEVICE_ID
#define HostUart XUartPs
#define HostUart_Config XUartPs_Config
#define HostUart_CfgInitialize XUartPs_CfgInitialize
#define HostUart_LookupConfig XUartPs_LookupConfig
#define HostUart_Recv XUartPs_Recv
#define HostUartConfig_GetBaseAddr(CfgPtr) (CfgPtr->BaseAddress)
#include "xuartps.h"
#endif

#define PMODESP32_UART_BASEADDR XPAR_PMODESP32_0_AXI_LITE_UART_BASEADDR
#define PMODESP32_GPIO_BASEADDR XPAR_PMODESP32_0_AXI_LITE_GPIO_BASEADDR

HostUart myHostUart;
PmodESP32 myESP32;

u8 recv_buffer;
u32 num_received;

u32 led;


#define RX_BUF_SIZE     512

char rx[RX_BUF_SIZE];
char * ip;

void EnableCaches();
void DisableCaches();
void DemoInitialize();
void checkAT();
void getDeviceInfo();
void getResponse();
void setWiFiMode(unsigned int mode);
int getIp();
void resetESP();
int establishTCPConnection(char * remoteIP, char * remotePort);
int getServerStatus();
void connectToTheRouter();
void queryDeviceIp();
int sendToServer(char  character);

void initialize () {
	HostUart_Config *CfgPtr;
	EnableCaches();
	ESP32_Initialize(&myESP32, PMODESP32_UART_BASEADDR, PMODESP32_GPIO_BASEADDR);
	CfgPtr = HostUart_LookupConfig(HOST_UART_DEVICE_ID);
	HostUart_CfgInitialize(&myHostUart, CfgPtr, HostUartConfig_GetBaseAddr(CfgPtr));
}


int main()
{
	initialize ();
	ESP32_HardwareReset(&myESP32);
	sleep(1);
	checkAT();
	getDeviceInfo();
	setWiFiMode(3);
	connectToTheRouter();
	usleep(1000);
	queryDeviceIp();
	usleep(1000);
	establishTCPConnection("192.168.0.14", "9092");

	XGpio gpio;
	u32 btn;

	XGpio_Initialize(&gpio, 0);

	XGpio_SetDataDirection(&gpio, 2, 0x00000000); // set LED GPIO channel tristates to All Output
	XGpio_SetDataDirection(&gpio, 1, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input

	while (1)
	{

		btn = XGpio_DiscreteRead(&gpio, 1);

		if (btn == 1)
		{
			led = 0xFFFFFFFF;
			sendToServer('W');
		}
		else if (btn == 2)
		{
			led = 0xFFFFFFFF;
			sendToServer('A');
		}
		else if (btn == 8)
		{
			led = 0xFFFFFFFF;
			sendToServer('S');
		}
		else if (btn == 4)
		{
			led = 0xFFFFFFFF;
			sendToServer('D');
		}
		else
		{
			getServerStatus();
		}

		XGpio_DiscreteWrite(&gpio, 2, led);


	}
}

int establishTCPConnection(char * remoteIP, char * remotePort) {
	xil_printf("Attempting to establish TCP connection...\r\n");
    char tx[300] = "";
    strcat(tx, "AT+CIPSTART=\"TCP\",\"");
    strcat(tx, remoteIP);
    strcat(tx, "\",");
    strcat(tx, remotePort);
    strcat(tx, "\r\n");

    xil_printf("%s", tx);
    sendToESP(tx);


    usleep(1000);

    getResponse();


    char * connect;
    connect = strstr(rx, "CONNECT");
    if(NULL == connect) {
        return -1;
    }

    return 0;
}

void connectToTheRouter()
{
	xil_printf("Connect To The Router...\r\n");
	char tx[50] = "AT+CWJAP=\"UPC0065854\",\"QEWMCGGU\"\r\n";
	sendToESP(tx);

	usleep(50);

	getResponse();
}

void sendToESP(char * string) {
    u32 i = 0;
    u32 length = strlen(string);
    u32 num = 0;
    while (length > 0) {
        num = ESP32_Send(&myESP32, &string[i], 1);
        i += num;
        length -= num;
    }
}

void checkAT() {
	xil_printf("Getting AT Info...\r\n");
    char tx[] = "AT\r\n";
    sendToESP(tx);

    usleep(50);

    getResponse();
}

void  getResponse()
{
	    int i = 0 ;
	    int ok = 1;
	    while(ok)
	    {
	    	if(ESP32_Recv(&myESP32, &recv_buffer, 1) > 0)
	    	{
	    	   rx[i] = (char ) recv_buffer;
	    	   if(rx[i-2] == 'O' && rx[i-1] == 'K')
	    	   {
	    			ok=0;
	    	   }
	    	   i++;
	    	}
	    }

	    rx[i] = NULL;
	    xil_printf("%s\n", rx);
}



void queryDeviceIp()
{
	xil_printf("Query Device Ip...\r\n");
	    char tx[] = "AT+CIFSR\r\n";
	    sendToESP(tx);

	    usleep(50);

	    getResponse();
}

void getDeviceInfo() {
	xil_printf("Getting Device Info...\r\n");
    char tx[] = "AT+GMR\r\n";
    sendToESP(tx);

    usleep(50);

    getResponse();

}

void setWiFiMode(unsigned int mode) {
	xil_printf("Setting WiFi mode \r\n");
    char tx[50] = "AT+CWMODE=3\r\n";
    if(mode > 3) {
    	xil_printf("WiFi mode must be between 0 and 3\r\n");
    	xil_printf("Consult the AT command manual for information about modes\r\n");
        return;
    }
   // sprintf(tx, "AT+CWMODE=%d\r\n", mode);
    sendToESP(tx);
    usleep(20);

    getResponse();

}

int getIp() {
	xil_printf("get ip \r\n");
    char tx[50] = "AT+CWLIF\r\n";
    sendToESP(tx);
    usleep(20);

    getResponse();

    if(strlen(rx) > 20 )
    {
    	ip = strchr(rx,':');
    	ip = (ip+1);
    	ip[11] = NULL;
    	//xil_printf("%s",ip);
    	return 1;
    }
    else
    {
    	ip[0] = NULL;
    	return 0;
    }
}

void resetESP() {
	xil_printf("Resetting ESP32...\r\n");
    char tx[] = "AT+RST\r\n";
    sendToESP(tx);

    usleep(500);

    getResponse();
}

int sendToServer(char character)
{
	xil_printf("\nSend to Server ...\r\n");
	char tx[20]="AT+CIPSEND=1\r\n";

	sendToESP(tx);
	sleep(1);
	char str[2]="";
	str[0]=character;
	str[1]=NULL;
	sendToESP(str);

	getResponse();
}

int getServerStatus() {

	xil_printf("\nGet Server Status...\r\n");
    char request[200] = "cmd";

    char tx[20]="AT+CIPSEND=3\r\n";

    sendToESP(tx);
    sleep(1);
    sendToESP(request);

    getResponse();

    char tx2[20]="+IPD,7\r\n";
    sleep(1);
    sendToESP(tx2);
    sleep(1);

    int i=15;
    while(i)
    {
    	num_received = ESP32_Recv(&myESP32, &recv_buffer, 1);
    			if (num_received > 0) {
    				xil_printf("%c", recv_buffer);
    				i--;
    			}
    }
    //xil_printf("%c", recv_buffer);
    led = recv_buffer - 48;


}

void EnableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheEnable();
#endif
#endif
}

void DisableCaches() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheDisable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheDisable();
#endif
#endif
}
