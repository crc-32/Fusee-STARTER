#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include "mtp.h"

int down = 1;


void openPayload(char* payloadPath) // Single open payload function to avoid repeating code
{
	FILE *f = fopen(payloadPath, "rb");
	if (f == NULL) {
		printf("Failed to open payload!\n");
	} else {
		fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
		fclose(f);
		reboot_to_payload();
	}
}

int main(int argc, char* argv[])
{
	consoleInit(NULL);
	while (appletMainLoop())
	{
		romfsInit();
		hidScanInput();

		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) break;
		
		consoleClear();
		printf("Welcome to Fusee-STARTER!\nSelect your payload and press A.\n");
		printf("%s1. Launch hekate payload\n%s2. Launch fusee payload\n%s3. Lanch ArgonNX \n", 
			(down==1) ? "--> " : "    ", // If condition in brackets is true, the left side of : is used, otherwise the right side of : is used
			(down==2) ? "--> " : "    ",
			(down==3) ? "--> " : "    ");
		
		if (kDown & KEY_A)
		{
			Result rc = splInitialize();
			if(R_FAILED(rc))
				fatalSimple(rc);
			
			if (down == 1) // Shorthand if statements are better when we just want to do one thing (no need for curly brackets {})
				openPayload("romfs:/payload/hekate.bin");
			else if (down == 2)
				openPayload("romfs:/payload/fusee.bin");
			else if (down == 3)
				openPayload("romfs:/payload/argon.bin");
		}

		if (down == 0) down = 3;
		if (kDown & KEY_DUP)
		{
			if(down < 4)
				down--;
			else
				down = 3;
		}
		if (kDown & KEY_DDOWN)
		{
			if(down < 3)
				down++;
			else
				down = 1;
		}
		consoleUpdate(NULL);
	}
	
	consoleExit(NULL);
	return 0;
}