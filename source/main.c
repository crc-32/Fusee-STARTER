#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include "mtp.h"

int down = 1;


int main(int argc, char* argv[])
{

	consoleInit(NULL);
	while (appletMainLoop()){
	romfsInit();
	  
		hidScanInput();

		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) break;

		
		if (down == 1) 
		{
			consoleClear();
			printf("Welcome to Fusee-STARTER!\nSelect your payload and press A.\n--> 1. Launch hekate payload\n    2. Launch fusee payload\n    3. Lanch ArgonNX \n");
		}
		else if (down == 2) 
		{
			consoleClear();
			printf("Welcome to Fusee-STARTER!\nSelect your payload and press A.\n    1. Launch hekate payload\n--> 2. Launch fusee payload\n    3. Lanch ArgonNX \n");
		}
		else if (down == 3) 
		{
			consoleClear();
			printf("Welcome to Fusee-STARTER!\nSelect your payload and press A.\n    1. Launch hekate payload\n    2. Launch fusee payload\n--> 3. Lanch ArgonNX \n");
		}
		if (kDown & KEY_A)
		{
			if (down == 1)
			{
			Result rc = splInitialize();
			FILE *f = fopen("romfs:/payload/hekate.bin", "rb");
			if (f == NULL) {
			printf("Failed to open hekate!\n");
			} else {
			fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
			fclose(f);
			reboot_to_payload();
		}
		}
		else if (down == 2)
			{
		Result rc = splInitialize();
		FILE *f = fopen("romfs:/payload/fusee.bin", "rb");
		if (f == NULL) {
			printf("Failed to open fusee!\n");
		} else {
			fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
			fclose(f);
			reboot_to_payload();
		}
		}
		else if (down == 3)
			{
		Result rc = splInitialize();
		FILE *f = fopen("romfs:/payload/argon.bin", "rb");
		if (f == NULL) {
			printf("Failed to open argon!\n");
		} else {
			fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
			fclose(f);
			reboot_to_payload();
		}
		}
		}
		if (down == 0)
		{
			down = 3;
		}
		if (kDown & KEY_DUP)
		{
			consoleClear();
			if(down < 4) {
				down--;
			}
			else
			{
				down = 3;
		        }
		}
		if (kDown & KEY_DDOWN)
		{
			consoleClear();
			if(down < 3) {
				down++;
			}
			else
			{
				down = 1;
		        }
		}
		consoleUpdate(NULL);
	}
	
	consoleExit(NULL);
	return 0;
}
