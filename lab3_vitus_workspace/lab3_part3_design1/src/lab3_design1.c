#include <stdio.h>
#include <xil_io.h>

// Set up variables for inputs.
short ar = NULL;
short ai = NULL;
short br = NULL;
short bi = NULL;
int pr = NULL;
int pi = NULL;

// Constants for the addresses of our output registers that we'll read from.
static const void* PR_ADDR = 0x43C00000;
static const void* PR_ADDR = 0x43C00004;

// Constants for the addresses of our input registers that we'll write to.
static void* AR_ADDR = 0x43C00008;
static void* AI_ADDR = 0x43C0000C;
static void* BR_ADDR = 0x43C00010;
static void* BI_ADDR = 0x43C00014;
// NOTE: could make these pointers to 32-bit unsigned integers, as we have 32-bit pointers;
// 			OR could make that pointer type a typedef to make it dynamic.

int main() {

	while(true) {

		printf("Enter ar: ");
		scanf("%hd", &ar);
		printf("Enter ai: ");
		scanf("%hd", &ai);
		printf("Enter br: ");
		scanf("%hd", &br);
		printf("Enter bi: ");
		scanf("%hd", &bi);

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

		// Write the 32 bit values to their respective registers.
		Xil_Out32(AR_ADDR, ar);
		Xil_Out32(AI_ADDR, ai);
		Xil_Out32(BR_ADDR, br);
		Xil_Out32(BI_ADDR, bi);

		// Read the output and print it.
		pr = Xil_In32(PR_ADDR);
		pi = Xil_In32(PI_ADDR);

		printf("pr: %d\npi: %d", pr, pi);

	}


	return 0;
}
