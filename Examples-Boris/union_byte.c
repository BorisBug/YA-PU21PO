/**
 * @file byte.c
 * @author Boris Snäll (boris.snall@yaelev.se)
 * @brief Example of bitfield access combined with unions to simulate the creation of types: uchar, uint, ulong
 * @version 0.1
 * @date 2021-10-08
 */
#include <stdio.h>
#include <stdint.h>

// acsess each bit inside of a char
// sizeof = 1
typedef struct byte_t
{
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
} byte_t;

// build an "unsigned char" using bits
// sizeof = 1
typedef union uchar_t
{
    uint8_t value; // normal unsigned char (sizeof 1)
    byte_t bits;   // bitfield access (sizeof 1)
} uchar_t;

// build a word using two bytes
// sizeof = 2
typedef struct word_t
{
    byte_t lo; // low byte
    byte_t hi; // high byte
} word_t;

// build an "unsigned short"
// sizeof = 2
typedef union ushort_t
{
    uint16_t value; // normal unsigned short (sizeof 2)
    word_t word;    // expressed as a word (HI & LO bytes) // (sizeof 2)
    byte_t byte[2]; // expressed as byte array (sizeof 1*2)
    uchar_t uc[2];  // expressed as uchar array (sizeof 1x2)
} ushort_t;

// build a dword (double word) using two words
// sizeof = 4
typedef struct dword_t
{
    word_t low; // low word (sizeof 2)
    word_t hiw; // high word (sizeof 2)
} dword_t;

// build an "unsigned long"
// sizeof = 4
typedef union ulong_t
{
    uint32_t value; // normal uint32 (sizeof 4)
    dword_t dword;  // expressed as dword (using HI & LO words) // (sizeof 4)
    word_t word[2]; // expressed as word array (sizeof 2*2)
    ushort_t us[2]; // expressed as unsigned short array (sizeof 2*2)
    byte_t byte[4]; // expressed as byte array (sizeof 1*4)
} ulong_t;


// print bits for each type

void print_uint8(uint8_t b)
{
    // shift left & print most significant bit (first left)
    for (int i=0; i<8; i++, b<<=1)
        printf("%c", (b & 0x80) ? '1' : '0'); 
}

void print_uint16(uint16_t b)
{
    // shift left & print most significant bit (first left)
    for (int i = 0; i < 16; i++, b <<= 1)
        printf("%c", (b & 0x8000) ? '1' : '0');
}

void print_uint32(uint32_t b)
{
    // shift left & print most significant bit (first left)
    for (int i = 0; i < 32; i++, b <<= 1)
        printf("%c", (b & 0x80000000) ? '1' : '0');
}

void print_byte(byte_t byte)
{
    print_uint8(*((uint8_t*)&byte));
}

int main()
{
    //uchar_t b = {0xCA};
    uchar_t uc = {202};

    printf("\n***** char\n\n");
    printf("sizeof: %lu\n\n", sizeof(uc));

    printf("Print the value as a char\n");
    printf("value: %u (0x%02X)", uc.value, uc.value);
    printf("\n\n");

    printf("Print all bits using bitwise operators\n");
    printf("bits 7-0: ");
    print_uint8(uc.value);
    printf("\n\n");

    printf("Print all bits individually using union & structure combination\n");
    printf("b7: %u ", uc.bits.b7);
    printf("b6: %u ", uc.bits.b6);
    printf("b5: %u ", uc.bits.b5);
    printf("b4: %u ", uc.bits.b4);
    printf("b3: %u ", uc.bits.b3);
    printf("b2: %u ", uc.bits.b2);
    printf("b1: %u ", uc.bits.b1);
    printf("b0: %u ", uc.bits.b0);
    printf("\n\n");

    //short_t us = {0x80F1};
    ushort_t us = {33009};

    printf("\n***** unsigned short\n\n");
    printf("sizeof: %lu\n\n", sizeof(us));

    printf("Print the value as a unsigned short\n");
    printf("value: %u (0x%04X)", us.value, us.value);
    printf("\n\n");

    printf("Print all bits using bitwise operators\n");
    printf("bits 15-0: ");
    print_uint16(us.value);
    printf("\n\n");

    printf("Print all bits using HI & LO word struct\n");
    printf("HI 15-8: ");
    print_byte(us.word.hi); // equivalent to us.uc[1].value
    printf(" + ");
    printf("LO 7-0: ");
    print_byte(us.word.lo); // equivalent to us.uc[0].value
    printf("\n\n");

    printf("Print all bits using byte[] array\n");
    printf("bits 15-8: ");
    print_byte(us.byte[1]);
    printf(" + ");
    printf("bits 7-0: ");
    print_byte(us.byte[0]);
    printf("\n\n");

    printf("Print all bits individually using union & structure combination\n");
    printf("b15: %u ", us.byte[1].b7); // hi...
    printf("b14: %u ", us.byte[1].b6); // equivalent to us.word.hi.b6;
    printf("b13: %u ", us.byte[1].b5); // equivalent to us.uc[1].bits.b5
    printf("b12: %u ", us.byte[1].b4);
    printf("b11: %u ", us.byte[1].b3);
    printf("b10: %u ", us.byte[1].b2);
    printf("b09: %u ", us.byte[1].b1);
    printf("b08: %u ", us.byte[1].b0);
    printf("b07: %u ", us.byte[0].b7); // lo...
    printf("b06: %u ", us.byte[0].b6); // equivalent to us.word.lo.b6;
    printf("b05: %u ", us.byte[0].b5); // equivalent to us.uc[0].bits.b5
    printf("b04: %u ", us.byte[0].b4);
    printf("b03: %u ", us.byte[0].b3);
    printf("b02: %u ", us.byte[0].b2);
    printf("b01: %u ", us.byte[0].b1);
    printf("b00: %u ", us.byte[0].b0);
    printf("\n\n");

    ulong_t ul = {0x7006E00E};
    //ulong_t ul = {1879498766};

    printf("\n***** unsigned long\n\n");
    printf("sizeof: %lu\n\n", sizeof(ul));

    printf("Print the value as a unsigned long\n");
    printf("value: %d (0x%08X)", ul.value, ul.value);
    printf("\n\n");

    printf("Print all bits using bitwise operators\n");
    printf("bits 31-0: ");
    print_uint32(ul.value);
    printf("\n\n");

    printf("Print all bits using HI & LO word unions\n");
    printf("HIWh 31-24: ");
    print_byte(ul.dword.hiw.hi);
    printf(" + ");
    printf("HIWl 23-16: ");
    print_byte(ul.dword.hiw.lo);
    printf(" + ");
    printf("LOWh 15-8: ");
    print_byte(ul.dword.low.hi);
    printf(" + ");
    printf("LOWl 7-0: ");
    print_byte(ul.dword.low.lo);
    printf("\n\n");

    printf("Print all bits using byte[] array\n");
    printf("bits 31-24: ");
    print_byte(ul.us[1].byte[1]);
    printf(" + ");
    printf("bits 23-16: ");
    print_byte(ul.us[1].byte[0]);
    printf(" + ");
    printf("bits 15-8: ");
    print_byte(ul.us[0].byte[1]);
    printf(" + ");
    printf("bits 7-0: ");
    print_byte(ul.us[0].byte[0]);
    printf("\n\n");

    printf("Print all bits individually using union & structure combination\n");
    printf("b31: %u ", ul.us[1].byte[1].b7); // equivalent to ul.dword.hiw.hi.b7
    printf("b30: %u ", ul.us[1].byte[1].b6); // equivalent to ul.word[1].hi.b6;
    printf("b29: %u ", ul.us[1].byte[1].b5); // equivalent to ul.byte[3].b5
    printf("b28: %u ", ul.us[1].byte[1].b4);
    printf("b27: %u ", ul.us[1].byte[1].b3);
    printf("b26: %u ", ul.us[1].byte[1].b2);
    printf("b25: %u ", ul.us[1].byte[1].b1);
    printf("b24: %u ", ul.us[1].byte[1].b0);
    printf("b23: %u ", ul.us[1].byte[0].b7); 
    printf("b22: %u ", ul.us[1].byte[0].b6);
    printf("b21: %u ", ul.us[1].byte[0].b5);
    printf("b20: %u ", ul.us[1].byte[0].b4);
    printf("b19: %u ", ul.us[1].byte[0].b3);
    printf("b18: %u ", ul.us[1].byte[0].b2);
    printf("b17: %u ", ul.us[1].byte[0].b1);
    printf("b16: %u ", ul.us[1].byte[0].b0);
    printf("\n");
    printf("b15: %u ", ul.us[0].byte[1].b7); 
    printf("b14: %u ", ul.us[0].byte[1].b6);
    printf("b13: %u ", ul.us[0].byte[1].b5);
    printf("b12: %u ", ul.us[0].byte[1].b4);
    printf("b11: %u ", ul.us[0].byte[1].b3);
    printf("b10: %u ", ul.us[0].byte[1].b2);
    printf("b09: %u ", ul.us[0].byte[1].b1);
    printf("b08: %u ", ul.us[0].byte[1].b0);
    printf("b07: %u ", ul.us[0].byte[0].b7); 
    printf("b06: %u ", ul.us[0].byte[0].b6);
    printf("b05: %u ", ul.us[0].byte[0].b5);
    printf("b04: %u ", ul.us[0].byte[0].b4);
    printf("b03: %u ", ul.us[0].byte[0].b3);
    printf("b02: %u ", ul.us[0].byte[0].b2);
    printf("b01: %u ", ul.us[0].byte[0].b1);
    printf("b00: %u ", ul.us[0].byte[0].b0);
    printf("\n\n");

    return 0;
}