#pragma once
#include<cstdint>

//プレイヤー陣営
const uint32_t kCollitionAttributePlayer = 0b1;
//敵陣営
const uint32_t kCollitionAttributeEnemy = 0b1 << 1;
//壁
const uint32_t kCollitionAttributeWall = 0b1 << 2;
//ボム
const uint32_t kCollitionAttributeBomb = 0b1 << 3;
//Switch
const uint32_t kCollitionAttributeSwitch = 0b1 << 4;