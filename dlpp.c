#include <stdarg.h>
#include <stdint.h>

#include "dlpp.h"

#define DLPP_MASK_SIZE 0x0F

uint8_t dlpp_get_size(uint8_t * buffer){
  return (buffer[1]&DLPP_MASK_SIZE)+2;
}

int8_t dlpp(uint8_t channel, uint8_t * buffer, char type, uint8_t number, ...){

  va_list ap;

  va_start(ap, number);

  uint8_t curseur = 2;
  uint8_t nb = number;
  uint8_t sb = 0;

  buffer[0]=channel;
  buffer[1]=0;

  switch(type){
    case 'b':
    case 'h':
    case 'i':
      buffer[1]=buffer[1]|0x80;
      break;
    case 'B':
    case 'H':
    case 'I':
      buffer[1]=buffer[1]&0x7F;
      break;
    default:
      return -1;
  }

  switch(type){
    case 'b':
    case 'B':
      sb=1;
      break;
    case 'h':
    case 'H':
      sb=2;
      break;
    case 'i':
    case 'I':
      sb=4;
      break;
    default:
      return -1;
  }

  buffer[1]=buffer[1]|(sb << 4);
  if(sb*nb>=16) return -1;
  buffer[1]=buffer[1]|((sb*nb)&0x0F);
  while (((curseur-2)/sb) < number)
  {
    int8_t val_sc;
    uint8_t val_c;
    int16_t val_ss;
    uint16_t val_s;
    int32_t val_si;
    uint32_t val_i;

    switch(type){
      case 'b':
        val_sc = va_arg(ap, int);
        buffer[curseur++]=val_sc;
        break;
      case 'B':
        val_c = va_arg(ap, unsigned int);
        buffer[curseur++]=val_c;
        break;
      case 'h':
        val_ss = va_arg(ap, int);
        buffer[curseur++]=val_ss >> 8;
        buffer[curseur++]=val_ss;
        break;
      case 'H':
        val_s = va_arg(ap, unsigned int);
        buffer[curseur++]=val_s >> 8;
        buffer[curseur++]=val_s;
        break;
      case 'i':
        val_si = va_arg(ap, int);
        buffer[curseur++]=val_si >> 24;
        buffer[curseur++]=val_si >> 16;
        buffer[curseur++]=val_si >> 8;
        buffer[curseur++]=val_si;
        break;
      case 'I':
        val_i = va_arg(ap, unsigned int);
        buffer[curseur++]=val_i >> 24;
        buffer[curseur++]=val_i >> 16;
        buffer[curseur++]=val_i >> 8;
        buffer[curseur++]=val_i;
        break;

      default:
        return -1;
    }
  }

  va_end(ap);
  return 0;
}
