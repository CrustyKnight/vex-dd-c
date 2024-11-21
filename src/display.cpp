#include "main.h"
#include "pros/apix.h"

#include "liblvgl/lvgl.h"

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


static void test_button(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * button = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
      static uint8_t cnt = 0;
      cnt++;


      lv_obj_t * label = lv_obj_get_child(button,0);
      lv_label_set_text_fmt(label, "Pressed %d times", cnt);
    }
}

static lv_color_t darken(const lv_color_filter_dsc_t * dsc, lv_color_t color, lv_opa_t opa)
{
    LV_UNUSED(dsc);
    return lv_color_darken(color, opa);
}

LV_IMG_DECLARE(catplush);
static lv_obj_t * catplush_img;

static lv_obj_t * maint;

lv_obj_t * motortemps;

void draw_catplush(){
  catplush_img = lv_img_create(maint);
  lv_img_set_src(catplush_img, &catplush);
  lv_obj_align(catplush_img, LV_ALIGN_CENTER, 0, -30);
  lv_img_set_zoom(catplush_img, 512);
}

static void style_init(void){

  //BUTTON
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 10);
    lv_style_set_border_color(&style_btn, lv_color_hex(cat_lavender));
    lv_style_set_bg_opa(&style_btn, 255);
    lv_style_set_bg_color(&style_btn, lv_color_hex(cat_lavender));
    lv_style_set_border_width(&style_btn, 2);
    lv_style_set_text_color(&style_btn, lv_color_hex(cat_crust));

  //BUTTON PRESSED
    static lv_color_filter_dsc_t color_filter;
    lv_color_filter_dsc_init(&color_filter, darken);
    lv_style_init(&style_button_pressed);
    lv_style_set_color_filter_dsc(&style_button_pressed, &color_filter);
    lv_style_set_color_filter_opa(&style_button_pressed, LV_OPA_20);

}

void display_init(void){

  style_init();

  lv_obj_t * tabview;
  tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 30);

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);

  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(cat_crust), LV_PART_MAIN);

    maint = lv_tabview_add_tab(tabview, "MAIN");
    lv_obj_t * diag = lv_tabview_add_tab(tabview, "INFO");
 
    lv_obj_t * title = lv_label_create(maint);
    lv_label_set_text(title, "~~DONUT DYNAMICS~~");
    lv_obj_set_style_text_color(maint, lv_color_hex(TEXTCLR), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -90);
   
    /*
    LV_IMG_DECLARE(img_donut_argb);
    lv_obj_t * donut = lv_img_create(main);
    lv_img_set_src(donut, &img_donut_argb);
    lv_obj_align(donut, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(donut, 200, 200);
    */
    
    draw_catplush();

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

    motortemps = lv_label_create(diag);
    lv_obj_align(motortemps, LV_DIR_LEFT, 0, 0);
    std::vector<double> mtemps = get_motor_temps();
    lv_label_set_text_fmt(motortemps, "MOTOR 1: %d\nMOTOR 2: %d\nMOTOR 3: %d\nMOTOR 4: %d\nMOTOR 5: %d\nMOTOR 6: %d", &mtemps[0], &mtemps[1], &mtemps[2], &mtemps[3], &mtemps[4], &mtemps[5]);

}

