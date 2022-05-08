#include <stdio.h>

int	main()
{
	int		num = 16777216 + 65536 + 256 + 1; // 2^24 + 2^16 + 2^8 + 2^0
	// 00000001 00000001 00000001 00000001
	// 		  ^		   ^		^		 ^
    // bit	 24       16        8        0
    //
    // byte 4   byte 3   byte 2   byte 1

	int		*num_pointer = &num;
	char	*num_byte = (char *)num_pointer; // byte now points to the first byte 0 of num


	*num_byte = 32; // change first byte to 2^5
	// 00000001 00000001 00000001 00100000
	// 		  ^		   ^		^	^	  
    // bit	 24       16        8   5     
    //
    // byte 4   byte 3   byte 2   *byte 1
    
    num_byte++; // byte now points to the second byte of num

	*num_byte = 20; // change second byte to 2^4 + 2^2
	// 00000001 00000001 00010100 00100000
	// 		  ^		   ^    ^ ^     ^     	  
    // bit	 24       16   12 10    5     
    //
    // byte 4   byte 3   *byte 2   byte 1

    num_byte++; // byte now points to the third byte of num
	
	*num_byte = 2; // change third byte to 2^1
	// 00000001 00000010 00010100 00100000
	// 		  ^		  ^     ^ ^     ^     	  
    // bit	 24      17    12 10    5     
    //
    // byte 4   *byte 3   byte 2   byte 1
    
    num_byte++; // byte now points to the fourth byte of num

	*num_byte = 8; // change fourth byte to 2^3
	// 00001000 00000010 00010100 00100000
	// 	   ^		  ^     ^ ^     ^     	  
    // bit 27        17    12 10    5     
    //
    // *byte 4   byte 3   byte 2   byte 1
    
    // return to the first byte of num
    num_byte = num_byte - 3;
	printf("Value of num is now = 2^27 + 2^17 + 2^12 + 2^10 + 2^5 or %d\n", num);
	printf("Value of 1st byte of p is now = 2^5 or %d\n", *num_byte);
	printf("Value of 2nd byte of p is now = 2^4 + 2^2 or %d\n", *(num_byte + 1));
	printf("Value of 3rd byte of p is now = 2^1 or %d\n", *(num_byte + 2));
	printf("Value of 4th byte of p is now = 2^3 or %d\n", *(num_byte + 3));
}
