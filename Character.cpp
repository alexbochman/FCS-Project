#include <iostream>
#include "Character.hpp"

Character::Character(int n) {this->nValue = n;}

Character::~Character() {}

void Character::set_nValue(int n) { this->nValue = n; }
int Character::get_nValue() {return nValue;}