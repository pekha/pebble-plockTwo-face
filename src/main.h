#pragma once
 
void update_time();
static void main_window_load(Window *window) ;
static void main_window_unload(Window *window);
static void tick_handler(struct tm *tick_time, TimeUnits units_changed);
static void init();
static void deinit();
