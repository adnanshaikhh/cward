#include "timer.h"

#include "log.h"
#include "mathops.h"

#include <SDL.h>

#include <time.h>

timer timer_start(int id, const char* tag)
{
	timer t;
	t.id = id;
	t.start = SDL_GetTicks();
	t.split = SDL_GetTicks();
	t.end = 0;

	debug("Timer %d '%s' Start: %f", id, tag, 0.0f);

	return t;
}

timer timer_split(timer t, const char* tag)
{
	long curr = SDL_GetTicks();

	double difference = (double)(curr - t.split) / 1000.0;
	debug("Timer %d '%s' Split: %f", t.id, tag, difference);

	t.split = curr;
	return t;
}

timer timer_stop(timer t, const char* tag)
{
	long curr = SDL_GetTicks();

	double difference = (double)(curr - t.start) / 1000.0f;
	debug("Timer %d '%s' End: %f", t.id, tag, difference);

	t.end = SDL_GetTicks();
	return t;
}

static int timestamp_counter = 0;

void timestamp(char* out)
{
	time_t ltime;
	struct tm *time_val;

	ltime = time(NULL);
	time_val = localtime(&ltime);

	sprintf(out, "%d%d%d%d%d%d%d",
		time_val->tm_mday,
		time_val->tm_mon,
		time_val->tm_year,
		time_val->tm_hour,
		time_val->tm_min,
		time_val->tm_sec,
		timestamp_counter);

	timestamp_counter++;
}

static char frame_rate_string_var[12];

static int frame_rate_var = 0;
static double frame_time_var = 0.0;

static unsigned long frame_start_time = 0.0;
static unsigned long frame_end_time = 0.0;

static const double frame_update_rate = 0.5;

static int frame_counter = 0;
static double frame_acc_time = 0.0;

void frame_begin()
{
	frame_start_time = SDL_GetTicks();
}

void frame_end()
{
	frame_end_time = SDL_GetTicks();

	frame_time_var = ((double)(frame_end_time - frame_start_time) / 1000.0f);
	frame_acc_time += frame_time_var;
	frame_counter++;

	if (frame_acc_time > frame_update_rate) {
		frame_rate_var = round((double)frame_counter / frame_acc_time);
		frame_counter = 0;
		frame_acc_time = 0.0;
	}

	sprintf(frame_rate_string_var, "%i", frame_rate_var);
}

void frame_end_at_rate(double fps)
{
	unsigned long end_ticks = SDL_GetTicks();
	double active_frame_time = ((double)(end_ticks - frame_start_time) / 1000.0f);

	double wait = (1.0f / fps) - active_frame_time;
	int milliseconds = max(wait, 0) * 1000;

	SDL_Delay(milliseconds);

	frame_end();
}

double frame_rate()
{
	return frame_rate_var;
}

double frame_time()
{
	return frame_time_var;
}

char* frame_rate_string()
{
	return frame_rate_string_var;
}
