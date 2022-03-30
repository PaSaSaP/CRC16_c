#pragma once

#include "Arduino.h"

#include "CRC_polynomes.h"

  // set parameters to default
void CRC16_reset();    // set all to constructor defaults
void CRC16_restart();  // reset crc with same parameters

// set parameters
void  CRC16_setPolynome(uint16_t polynome);
void  CRC16_setStartXOR(uint16_t start);
void  CRC16_setEndXOR(uint16_t end);
void  CRC16_setReverseIn(bool reverseIn);
void  CRC16_setReverseOut(bool reverseOut);

// get parameters
uint16_t CRC16_getPolynome();
uint16_t CRC16_getStartXOR();
uint16_t CRC16_getEndXOR();
bool CRC16_getReverseIn();
bool CRC16_getReverseOut();

void CRC16_add(uint8_t value);
void CRC16_add_array(const uint8_t * array, uint16_t length);

uint16_t CRC16_getCRC();  // returns CRC
uint32_t CRC16_count();
