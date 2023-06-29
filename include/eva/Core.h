/**
 * @file    :   Core.h
 * @date    :   2023/06/27 14:06:31
 * @author  :   yaojie
 * @version :   1.0
 * 核心头文件
 */

#pragma once

#include "eva.h"

#define BIT(x) (1 << x)

#define EVA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
