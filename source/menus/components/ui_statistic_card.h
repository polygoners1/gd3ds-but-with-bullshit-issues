#pragma once
#include "ui_element.h"
#include <stdbool.h>

UIElement ui_create_statistic_card(int x, int y, bool swap_color, char *name, int value, char (*tag)[TAG_LENGTH]);