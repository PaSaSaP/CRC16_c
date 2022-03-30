#include "CRC16_c.h"

struct CRC16 {
  uint16_t _polynome;
  uint16_t _startMask;
  uint16_t _endMask;
  uint16_t _crc;
  bool     _reverseIn;
  bool     _reverseOut;
  bool     _started;
  uint32_t _count;
} crc;


uint16_t CRC16_reverse(uint16_t value);
uint8_t CRC16_reverse8(uint8_t value);
void CRC16_update(uint8_t value);


void CRC16_reset()
{
  crc._polynome   = 0x1021;
  crc._startMask  = 0x1D0F;
  crc._endMask    = 0;
  crc._crc        = 0;
  crc._reverseIn  = false;
  crc._reverseOut = false;
  crc._started    = false;
  crc._count      = 0;
}


void CRC16_restart()
{
  crc._started = true;
  crc._crc     = crc._startMask;
  crc._count   = 0;
}


void CRC16_add(uint8_t value)
{
  crc._count++;
  CRC16_update(value);
}

#if 0
void CRC16_add_array(const uint8_t * array, uint16_t length)
{
  while (length--)
  {
    CRC16_add(*array++);
  }
}
#endif

uint16_t CRC16_getCRC()
{
  uint16_t rv = crc._crc;
  // if (crc._reverseOut) rv = CRC16_reverse(rv);
  rv ^= crc._endMask;
  return rv;
}

#if 0
uint32_t CRC16_count()
{
   return crc._count; 
}
#endif

#if 0
void  CRC16_setPolynome(uint16_t polynome) { crc._polynome = polynome; }
void  CRC16_setStartXOR(uint16_t start)    { crc._startMask = start; }
void  CRC16_setEndXOR(uint16_t end)        { crc._endMask = end; }
void  CRC16_setReverseIn(bool reverseIn)   { crc._reverseIn = reverseIn; }
void  CRC16_setReverseOut(bool reverseOut) { crc._reverseOut = reverseOut; }
#endif

#if 0
uint16_t CRC16_getPolynome()   { return crc._polynome; }
uint16_t CRC16_getStartXOR()   { return crc._startMask; }
uint16_t CRC16_getEndXOR()     { return crc._endMask; }
bool     CRC16_getReverseIn()  { return crc._reverseIn; }
bool     CRC16_getReverseOut() { return crc._reverseOut; }
#endif

void CRC16_update(uint8_t value)
{
  if (!crc._started) CRC16_restart();
  // if (crc._reverseIn) value = CRC16_reverse8(value);
  crc._crc ^= ((uint16_t)value) << 8;
  for (uint8_t i = 8; i; i--) 
  {
    if (crc._crc & (1UL << 15))
    {
      crc._crc <<= 1;
      crc._crc ^= crc._polynome;
    }
    else
    {
      crc._crc <<= 1;
    }
  }
}

#if 0
uint16_t CRC16_reverse(uint16_t in)
{
  uint16_t x = in;
  x = (((x & 0XAAAA) >> 1) | ((x & 0X5555) << 1));
  x = (((x & 0xCCCC) >> 2) | ((x & 0X3333) << 2));
  x = (((x & 0xF0F0) >> 4) | ((x & 0X0F0F) << 4));
  x = (( x >> 8) | (x << 8));
  return x;
}


uint8_t CRC16_reverse8(uint8_t in)
{
  uint8_t x = in;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  return x;
}
#endif
