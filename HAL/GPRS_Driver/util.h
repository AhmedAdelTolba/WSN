#ifndef _file1_H_
#define _file1_H_

#define GetBit(Reg,Bit) (Reg&(1<<Bit))>>Bit
#define ClrBit(Reg,Bit) Reg&=~(1<<Bit)
#define SetBit(Reg,Bit) Reg|=(1<<Bit)
#define ToggleBit(Reg,Bit) Reg^=(1<<Bit)

#define SetReg(Reg) Reg=0xFF
#define ClrReg(Reg) Reg=0x00
#define ToggleReg(Reg) Reg^=0xFF

#define GetLowNibble(Reg) Reg&0x0F
#define ClrLowNibble(Reg) Reg&=0xF0
#define SetLowNibble(Reg) Reg|=0x0F
#define ToggleLowNibble(Reg) Reg^=0x0F

#define GetHighNibble(Reg) Reg&0xF0
#define ClrHighNibble(Reg) Reg&=0x0F
#define SetHighNibble(Reg) Reg|=0xF0
#define ToggleHighNibble(Reg) Reg^=0xF0

#define AssignReg(Reg,Value) Reg=Value
#define AssignLowNibble(Reg,Value) Reg=((Reg&0xF0)|(Value&0x0F))

#endif
