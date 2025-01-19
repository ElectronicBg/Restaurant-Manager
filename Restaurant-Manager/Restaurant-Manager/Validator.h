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
* Header: Input validation functions
*
*/

#pragma once

#include "Constants.h"

void validatePositiveInt(int& value, const char* prompt);

void validatePositiveDouble(double& value, const char* prompt);

void validateMenuOption(int& option);

void validateStringInput(char* input, int maxLength, const char* prompt);
