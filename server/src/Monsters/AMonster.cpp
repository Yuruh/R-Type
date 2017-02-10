//
// Created by wasta-geek on 06/12/16.
//

#include "AMonster.hpp"

AMonster::AMonster() : IMonster() {
}

AMonster::~AMonster() {
}

void AMonster::takeDamage(const int &i) {
    this->_hp -= i;
}

void AMonster::kill() {
    delete (this->_pattern);
}