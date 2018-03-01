#pragma once

typedef struct
{
	int id;
	unsigned long start;
	unsigned long end;
	unsigned long split;
} timer;

timer timer_start(int id, const char* tag);
timer timer_split(timer t, const char* tag);
timer timer_stop(timer t, const char* tag);

void timestamp(char* out);


void frame_begin();
void frame_end();
void frame_end_at_rate(double fps);

double frame_rate();
double frame_time();
char* frame_rate_string();
