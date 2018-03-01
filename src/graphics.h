#pragma once

void graphics_init();
void graphics_swap();
void graphics_viewport_set_title(const char* title);
const char* graphics_viewport_title();
void graphics_finish();
void graphics_viewport_start();