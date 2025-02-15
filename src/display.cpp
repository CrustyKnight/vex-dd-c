#include <string>

#include "liblvgl/lvgl.h"
#include "main.h"
#include "pros/apix.h"




std::vector<double> get_motor_temps() {
  std::vector<double> temps;

  for (int i = 1; i < 7; i++) {
    temps.push_back(pros::c::motor_get_temperature(i));
  }

  return temps;
}

std::vector<double> get_motor_torques() {
  std::vector<double> torques;

  for (int i = 1; i < 7; i++) {
    torques.push_back(pros::c::motor_get_torque(i));
  }

  return torques;
}

std::vector<double> get_motor_rpms() {
  std::vector<double> rpms;

  for (int i = 1; i < 7; i++) {
    rpms.push_back(pros::c::motor_get_actual_velocity(i));
  }

  return rpms;
}









// catpuccin mocha B)
#define cat_blue 0x89b4fa
#define cat_red 0xf38ba8
#define cat_green 0xa65e3a1
#define cat_yellow 0xf9e2af
#define cat_orange 0xfab387
#define cat_pink 0xf5c2e7
#define cat_purple 0xcba6f7
#define cat_crust 0x11111b
#define cat_lavender 0xb4befe

#define TEXTCLR 0xcdd6f4

static lv_style_t style_btn;
static lv_style_t style_button_pressed;

lv_obj_t* diag;
lv_obj_t* table;

static void test_button(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* button = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    static uint8_t cnt = 0;
    cnt++;

    lv_obj_t* label = lv_obj_get_child(button, 0);
    lv_label_set_text_fmt(label, "Pressed %d times", cnt);
  }
}

static lv_color_t darken(const lv_color_filter_dsc_t* dsc, lv_color_t color, lv_opa_t opa) {
  LV_UNUSED(dsc);
  return lv_color_darken(color, opa);
}

LV_IMG_DECLARE(strawb);
static lv_obj_t* strawb_img;
static lv_obj_t* maint;

lv_obj_t* motortemps;

void draw_strawb() {
  strawb_img = lv_img_create(maint);
  lv_img_set_src(strawb_img, &strawb);
  lv_obj_align(strawb_img, LV_ALIGN_CENTER, 0, -30);
  lv_img_set_zoom(strawb_img, 512);
}

static void style_init(void) {
  // BUTTON
  lv_style_init(&style_btn);
  lv_style_set_radius(&style_btn, 10);
  lv_style_set_border_color(&style_btn, lv_color_hex(cat_lavender));
  lv_style_set_bg_opa(&style_btn, 255);
  lv_style_set_bg_color(&style_btn, lv_color_hex(cat_lavender));
  lv_style_set_border_width(&style_btn, 2);
  lv_style_set_text_color(&style_btn, lv_color_hex(cat_crust));

  // BUTTON PRESSED
  static lv_color_filter_dsc_t color_filter;
  lv_color_filter_dsc_init(&color_filter, darken);
  lv_style_init(&style_button_pressed);
  lv_style_set_color_filter_dsc(&style_button_pressed, &color_filter);
  lv_style_set_color_filter_opa(&style_button_pressed, LV_OPA_20);
}

void telemetry_table(lv_obj_t* tab) {
  table = lv_table_create(tab);

  lv_table_set_col_width(table, 0, 90);
  lv_obj_set_style_pad_ver(table, 10, LV_PART_ITEMS);

  lv_table_set_cell_value(table, 0, 0, "motor");
  lv_table_set_cell_value(table, 0, 1, "temp");

  // scuffed
  std::vector<double> mt = get_motor_temps();
  std::vector<int> mtemps;

  std::vector<double> tqs = get_motor_torques();
  std::vector<int> torques;

  std::vector<double> rs = get_motor_rpms();
  std::vector<int> rpms;
  for (int i = 0; i < 6; i++) {
    mtemps.push_back((int)mt[i]);
    torques.push_back((int)tqs[i]);
    rpms.push_back((int)rs[i]);
  }

  for (int i = 1; i < 7; i++) {
    lv_table_set_cell_value_fmt(table, i, 0, "%i", i);
    lv_table_set_cell_value_fmt(table, i, 1, "%f", mtemps[i - 1]);
    lv_table_set_cell_value_fmt(table, i, 2, "%f", torques[i - 1]);
    lv_table_set_cell_value_fmt(table, i, 3, "%f", rpms[i - 1]);
  }

  lv_obj_align(table, LV_DIR_LEFT, -25, -25);
}

lv_obj_t* title;

void display_init(void) {
  style_init();

  lv_obj_t* tabview;
  tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 30);

  lv_obj_t* tab_btns = lv_tabview_get_tab_btns(tabview);
  lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
  lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
  lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);

  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(cat_crust), LV_PART_MAIN);

  maint = lv_tabview_add_tab(tabview, "MAIN");
  diag = lv_tabview_add_tab(tabview, "INFO");

  title = lv_label_create(maint);
  lv_label_set_text(title, "~~DONUT DYNAMICS~~");
  lv_obj_set_style_text_color(maint, lv_color_hex(TEXTCLR), LV_PART_MAIN);

  draw_strawb();

  // lv_obj_t * autonbutton = lv_btn_create(maint);
  // lv_obj_remove_style_all(autonbutton);
  // lv_obj_add_style(autonbutton, &style_btn, 0);
  // lv_obj_set_pos(autonbutton, 175, 50);
  // lv_obj_set_size(autonbutton, 120, 50);
  // lv_obj_add_event_cb(autonbutton, auton, LV_EVENT_ALL, NULL);
  // lv_obj_add_style(autonbutton, &style_button_pressed, LV_STATE_PRESSED);

  /*
      lv_obj_t * testbutton = lv_btn_create(maint); //create a button as a child of the main display (screen)
      lv_obj_remove_style_all(testbutton);
      lv_obj_add_style(testbutton, &style_btn, 0);
      lv_obj_set_pos(testbutton, 175, 50); //0,0 is in the topleft corner
      lv_obj_set_size(testbutton, 120, 50);
      lv_obj_add_event_cb(testbutton, test_button, LV_EVENT_ALL, NULL);           //Assign a callback to the button
      lv_obj_add_style(testbutton, &style_button_pressed, LV_STATE_PRESSED);

      lv_obj_t * testbtnlabel = lv_label_create(testbutton); //label for the button
      lv_label_set_text(testbtnlabel, "press me?");
      lv_obj_center(testbtnlabel);
  */

  telemetry_table(diag);
}

void display_tick(void) {
  telemetry_table(diag);
}
