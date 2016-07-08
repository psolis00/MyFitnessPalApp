#include <pebble.h>
#include "main.h"

static Window *window;

static TextLayer *title;
static TextLayer *remaining_calories;
static TextLayer *remaining;
static TextLayer *consumed;

static int s_radius = 20;
static int s_center;

static void update_proc(Layer *layer, GContext *ctx) {
	s_center = (60, 60); 
	graphics_draw_circle(ctx, s_center, s_radius)
}

static void window_load(Window *window) {
	GFont font = fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS);
  Layer *window_layer = window_get_root_layer(window);
	layer_set_update_proc(window_layer, update_proc);
  GRect bounds = layer_get_bounds(window_layer);

	layer_set_update_proc(window_layer, update_proc);
	
  title = text_layer_create((GRect) { .origin = { 10, 10 }, .size = { 100, 20 } });
  text_layer_set_text(title, "Calories");
  text_layer_set_text_alignment(title, GTextAlignmentLeft);
  text_layer_set_background_color(title, GColorBlack);
  text_layer_set_text_color(title, GColorWhite);
  layer_add_child(window_layer, text_layer_get_layer(title));
  
  remaining_calories = text_layer_create((GRect) { .origin = { 0, 60 }, .size = {bounds.size.w, bounds.size.h} });
  text_layer_set_text(remaining_calories, "1,100");
  text_layer_set_text_alignment(remaining_calories, GTextAlignmentCenter);
  text_layer_set_background_color(remaining_calories, GColorBlack);
  text_layer_set_text_color(remaining_calories, GColorKellyGreen);
	text_layer_set_font(remaining_calories, font);
  layer_add_child(window_layer, text_layer_get_layer(remaining_calories));
  
  remaining = text_layer_create((GRect) { .origin = { 0, 95 }, .size = {bounds.size.w, 20 } });
  text_layer_set_text(remaining, "remaining");
  text_layer_set_text_alignment(remaining, GTextAlignmentCenter);
  text_layer_set_background_color(remaining, GColorBlack);
  text_layer_set_text_color(remaining, GColorLightGray);
  layer_add_child(window_layer, text_layer_get_layer(remaining));
	
	consumed = text_layer_create((GRect) { .origin = { 0, 150 }, .size = {bounds.size.w, 20 } });
	text_layer_set_text(consumed, "400 consumed");
	text_layer_set_text_alignment(consumed, GTextAlignmentCenter);
	text_layer_set_background_color(consumed, GColorBlack);
	text_layer_set_text_color(consumed, GColorLightGray);
	layer_add_child(window_layer, text_layer_get_layer(consumed));
}

static void window_unload(Window *window) {
	text_layer_destroy(consumed);
	text_layer_destroy(remaining);
	text_layer_destroy(remaining_calories);
	text_layer_destroy(title);
}

static void init(void) {
  window = window_create();
  window_set_background_color(window, GColorBlack);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}