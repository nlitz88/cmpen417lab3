#include <stdio.h>
#include <xil_io.h>
#include <stdbool.h>

// Set up variables for inputs.
short ar = 0;
short ai = 0;
short br = 0;
short bi = 0;
int pr = 0;
int pi = 0;

// Constants for the addresses of our output registers that we'll read from.
static const UINTPTR PR_ADDR = (UINTPTR)0x43C00000;
static const UINTPTR PI_ADDR = (UINTPTR)0x43C00004;

// Constants for the addresses of our input registers that we'll write to.
static const UINTPTR AR_ADDR = (UINTPTR)0x43C00008;
static const UINTPTR AI_ADDR = (UINTPTR)0x43C0000C;
static const UINTPTR BR_ADDR = (UINTPTR)0x43C00010;
static const UINTPTR BI_ADDR = (UINTPTR)0x43C00014;
// NOTE: could make these pointers to 32-bit unsigned integers, as we have 32-bit pointers;
// 			OR could make that pointer type a typedef to make it dynamic.

int main() {

	while(true) {

		printf("Enter ar: ");
		scanf("%hd", &ar);
		printf("\nYou entered ar=%d", ar);

		printf("\nEnter ai: ");
		scanf("%hd", &ai);
		printf("\nYou entered ai=%d", ai);

		printf("\nEnter br: ");
		scanf("%hd", &br);
		printf("\nYou entered br=%d", br);

		printf("\nEnter bi: ");
		scanf("%hd", &bi);

//		printf("Why do i not make it here?");
		printf("\nYou entered bi=%d", bi);

		// THE BELOW REGISTER-PACKING IDEA COULD BE WRONG.
		// Based on the lab handout, it's sounding like we're just writing
		// each of the 16-bit values to a 32 bit register, and passing that
		// 32-bit value to the registers of our multiplier.
		// EVEN THOUGH THE MULTIPLIER GIVES US A 32-BIT REGISTER TO WRITE TO
		// FOR EACH INPUT, the multiplier inside is ONLY looking at the FIRST
		// 16-BITS of those 32-bit fields.
		// THEREFORE, we're kind of just inefficiently using these 32-bit registers
		// as a "vehicle" for the actual 16-bit input values.

		// ar gets placed in the first half of slave_reg2 @ 0x43c0_0008
		// ai gets placed in the 2nd half of slave_reg2 @ 0x43c0_000a
		// br at c
		// bi at e

		// ar gets placed in the FIRST byte, ai gets placed in the second byte
		// at a later address (so the next byte at the next byte address).

		//[  ar    |   ai    ]

		// Pack ar and ai into a 32 bit unsigned field.
//		a = ar << 16 | ai;
		// Pack br and bi into a 32 bit unsigned field.
//		b = br << 16 | bi;

		// Write the 16 bit values to their respective registers
		// NOTE: the values are really only 16-bit--the other remaining 16-bits will just
		// be zeroed out.
		Xil_Out32(AR_ADDR, (u32)ar);
		Xil_Out32(AI_ADDR, (u32)ai);
		Xil_Out32(BR_ADDR, (u32)br);
		Xil_Out32(BI_ADDR, (u32)bi);

//		// Read the output and print it.
		pr = Xil_In32(PR_ADDR);
		pi = Xil_In32(PI_ADDR);

		printf("\npr: %d\npi: %d\n", pr, pi);


	}


	return 0;
}
