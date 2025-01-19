/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Emil Neshkov
* @idnumber 0MI0600506
* @compiler VC
*
* Header: Handles date tracking and incrementation
*
*/

#pragma once

#include "Constants.h"

void loadCurrentDate(char* date, const char* filename);

void saveCurrentDate(const char* date, const char* filename);

void incrementDate(char* date);