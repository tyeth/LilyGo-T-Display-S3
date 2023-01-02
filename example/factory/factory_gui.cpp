#include "factory_gui.h"
#include "Arduino.h"
#include "esp_log.h"
#include "examples/lv_examples.h"
#include "lv_conf.h"
#include "lvgl.h"
#include "misc/lv_log.h"

LV_FONT_DECLARE(font_Alibaba);
LV_IMG_DECLARE(lilygo1_gif);
static lv_point_t line_points[] = {{-320, 0}, {320, 0}};

static int scroll_value = 0;

static void store_scroll_value_event_cb(lv_event_t *e);
static void update_text_subscriber_cb(lv_event_t *e);
static void update_touch_point_subscriber_cb(lv_event_t *e);
static void chart_event_cb(lv_event_t *e);
static void timer_task(lv_timer_t *t);
static lv_obj_t *dis;
static lv_obj_t *chart;
static lv_chart_series_t *ser1;
static lv_chart_series_t *ser2;
static lv_obj_t *tv1;
static lv_obj_t *tv2;
static lv_obj_t *tv3;
static lv_obj_t *tv4;
void *chartMsgSub;


void ui_switch_page(void) {
  static uint8_t n;
  n++;
  lv_obj_set_tile_id(dis, 0, n % UI_PAGE_COUNT, LV_ANIM_ON);
  if (n == 5) {
    lv_example_chart_3();
  }
}

void ui_begin() {

  dis = lv_tileview_create(lv_scr_act());
  lv_obj_align(dis, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_set_size(dis, LV_PCT(100), LV_PCT(100));
  tv1 = lv_tileview_add_tile(dis, 0, 0, LV_DIR_HOR);
  tv2 = lv_tileview_add_tile(dis, 0, 1, LV_DIR_HOR);
  tv3 = lv_tileview_add_tile(dis, 0, 2, LV_DIR_HOR);
  tv4 = lv_tileview_add_tile(dis, 0, 3, LV_DIR_HOR);

  /* page 1 */
  lv_obj_t *main_cout = lv_obj_create(tv1);
  lv_obj_set_size(main_cout, LV_PCT(100), LV_PCT(100));
  // lv_obj_clear_flag(main_cout, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_border_width(main_cout, 0, 0);
  lv_obj_set_style_bg_color(main_cout, UI_BG_COLOR, 0);

  lv_obj_t *hour_cout = lv_obj_create(main_cout);
  lv_obj_set_size(hour_cout, 140, 140);
  lv_obj_align(hour_cout, LV_ALIGN_CENTER, -85, 0);
  lv_obj_set_style_bg_color(hour_cout, UI_FRAME_COLOR, 0);
  // lv_obj_clear_flag(hour_cout, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *min_cout = lv_obj_create(main_cout);
  lv_obj_set_size(min_cout, 140, 140);
  lv_obj_align(min_cout, LV_ALIGN_CENTER, 85, 0);
  lv_obj_set_style_bg_color(min_cout, UI_FRAME_COLOR, 0);
  // lv_obj_clear_flag(min_cout, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *seg_text = lv_label_create(main_cout);
  lv_obj_align(seg_text, LV_ALIGN_CENTER, 0, -10);
  lv_obj_set_style_text_font(seg_text, &font_Alibaba, 0);
  lv_label_set_text(seg_text, ":");
  lv_obj_set_style_text_color(seg_text, UI_FONT_COLOR, 0);

  lv_obj_t *hour_text = lv_label_create(hour_cout);
  lv_obj_center(hour_text);
  lv_obj_set_style_text_font(hour_text, &font_Alibaba, 0);
  lv_label_set_text(hour_text, "12");
  lv_obj_set_style_text_color(hour_text, UI_FONT_COLOR, 0);
  lv_obj_add_event_cb(hour_text, update_text_subscriber_cb, LV_EVENT_MSG_RECEIVED, NULL);
  lv_msg_subsribe_obj(MSG_NEW_HOUR, hour_text, (void *)"%02d");

  lv_obj_t *min_text = lv_label_create(min_cout);
  lv_obj_center(min_text);
  lv_obj_set_style_text_font(min_text, &font_Alibaba, 0);
  lv_label_set_text(min_text, "34");
  lv_obj_set_style_text_color(min_text, UI_FONT_COLOR, 0);
  lv_obj_add_event_cb(min_text, update_text_subscriber_cb, LV_EVENT_MSG_RECEIVED, NULL);
  lv_msg_subsribe_obj(MSG_NEW_MIN, min_text, (void *)"%02d");

  static lv_style_t style_line;
  lv_style_init(&style_line);
  lv_style_set_line_width(&style_line, 4);
  lv_style_set_line_color(&style_line, UI_BG_COLOR);
  lv_style_set_line_rounded(&style_line, true);
  // lv_style_set_pad_all(&style_line, 5);

  lv_obj_t *line;
  line = lv_line_create(main_cout);
  lv_line_set_points(line, line_points, 2);
  lv_obj_add_style(line, &style_line, 0);
  lv_obj_center(line);

  /* page 2 */
  lv_obj_t *logo_img = lv_gif_create(tv2);
  lv_obj_center(logo_img);
  lv_gif_set_src(logo_img, &lilygo1_gif);

  /* page 3 */
  lv_obj_t *debug_label = lv_label_create(tv3);
  String text;
  esp_chip_info_t t;
  esp_chip_info(&t);
  text = "onboard chip : ";
  text += ESP.getChipModel();
  text += "\t temp : ";
  text += temperatureRead();
  text += "\n";
  text += "psram size : ";
  text += ESP.getPsramSize() / 1024;
  text += " KB\n";
  text += "flash size : ";
  text += ESP.getFlashChipSize() / 1024;
  text += " KB\n";
  lv_label_set_text(debug_label, text.c_str());
  lv_obj_align(debug_label, LV_ALIGN_TOP_LEFT, 0, 0);

  lv_obj_t *bat_label = lv_label_create(tv3);
  lv_obj_align_to(bat_label, debug_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_obj_add_event_cb(bat_label, update_text_subscriber_cb, LV_EVENT_MSG_RECEIVED, NULL);
  lv_msg_subsribe_obj(MSG_NEW_VOLT, bat_label, (void *)"VOLT : %d mV");

  lv_obj_t *touch_label = lv_label_create(tv3);
  lv_label_set_text(touch_label, "Data would appear here if touch enabled...");
  lv_obj_align_to(touch_label, bat_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_obj_add_event_cb(touch_label, update_touch_point_subscriber_cb, LV_EVENT_MSG_RECEIVED, NULL);
  lv_msg_subsribe_obj(MSG_NEW_TOUCH_POINT, touch_label, (void *)"%s");

  // /* page 4
  //  * based on chart4 example:
  //  * https://github.com/lvgl/lvgl/blob/master/examples/widgets/chart/lv_example_chart_4.c
  // */

  /*Create a chart*/

  lv_obj_t *chart_panel_obj = lv_obj_create(tv4);
  lv_obj_set_size(chart_panel_obj, LV_PCT(100), LV_PCT(100));
  // lv_obj_clear_flag(chart_panel_obj, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_border_width(chart_panel_obj, 0, 0);
  lv_obj_set_style_bg_color(chart_panel_obj, UI_BG_COLOR, 0);

  chart = lv_chart_create(chart_panel_obj);
  lv_obj_set_size(chart, LV_PCT(100), LV_PCT(100));
  lv_obj_center(chart);

  lv_obj_add_event_cb(chart, chart_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_refresh_ext_draw_size(chart);

  /*Zoom in a little in X (255 default, 800 previous)*/
  lv_chart_set_zoom_x(chart, 800);

  /*Add two data series*/
  lv_chart_series_t *ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_series_t *ser2 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
  uint32_t i;
  for (i = 0; i < 10; i++) {
    lv_chart_set_next_value(chart, ser1, lv_rand(2860, 2990));
    lv_chart_set_next_value(chart, ser2, lv_rand(3010, 3440));
  }
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 2700, 5200);
  lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
  

  // timer: clock "second" denoting blinking segments
  lv_timer_t *timer = lv_timer_create(timer_task, 500, seg_text);
}

static void timer_task(lv_timer_t *t) {
  lv_obj_t *seg = (lv_obj_t *)t->user_data;
  static bool j;
  if (j)
    lv_obj_add_flag(seg, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_clear_flag(seg, LV_OBJ_FLAG_HIDDEN);
  j = !j;
}

static void update_text_subscriber_cb(lv_event_t *e) {
  lv_obj_t *label = lv_event_get_target(e);
  lv_msg_t *m = lv_event_get_msg(e);

  const char *fmt = (const char *)lv_msg_get_user_data(m);
  const int32_t *v = (const int32_t *)lv_msg_get_payload(m);

  lv_label_set_text_fmt(label, fmt, *v);
}

static void update_touch_point_subscriber_cb(lv_event_t *e) {
  lv_obj_t *label = lv_event_get_target(e);
  lv_msg_t *m = lv_event_get_msg(e);

  const char *fmt = (const char *)lv_msg_get_user_data(m);
  const char *t = (const char *)lv_msg_get_payload(m);

  lv_label_set_text_fmt(label, fmt, t);
}

static void chart_event_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *chart = lv_event_get_target(e);

  if (code == LV_EVENT_VALUE_CHANGED) {
    ESP_LOGI("LV_EVENT_VALUE_CHANGED", "lv_obj_invalidate(chart)");
    lv_obj_invalidate(chart);
  }
  if (code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
    ESP_LOGI("LV_EVENT_REFR_EXT_DRAW_SIZE", "get param max 20");

    lv_coord_t *s = (lv_coord_t *)lv_event_get_param(e);
    *s = LV_MAX(*s, 20);
  } else if (code == LV_EVENT_DRAW_POST_END) {
    // ESP_LOGI("LV_EVENT_DRAW_POST_END","long one drawing points and logging");
    int32_t id = lv_chart_get_pressed_point(chart);
    if (id == LV_CHART_POINT_NONE)
      return;

    LV_LOG_USER("Selected point %d", (int)id);

    lv_chart_series_t *ser = lv_chart_get_series_next(chart, NULL);
    while (ser) {
      lv_point_t p;
      lv_chart_get_point_pos_by_id(chart, ser, id, &p);

      lv_coord_t *y_array = lv_chart_get_y_array(chart, ser);
      lv_coord_t value = y_array[id];

      char buf[16];
      lv_snprintf(buf, sizeof(buf), LV_SYMBOL_DUMMY "$%d", value);

      lv_draw_rect_dsc_t draw_rect_dsc;
      lv_draw_rect_dsc_init(&draw_rect_dsc);
      draw_rect_dsc.bg_color = lv_color_black();
      draw_rect_dsc.bg_opa = LV_OPA_50;
      draw_rect_dsc.radius = 3;
      draw_rect_dsc.bg_img_src = buf;
      draw_rect_dsc.bg_img_recolor = lv_color_white();

      lv_area_t a;
      a.x1 = chart->coords.x1 + p.x - 20;
      a.x2 = chart->coords.x1 + p.x + 20;
      a.y1 = chart->coords.y1 + p.y - 30;
      a.y2 = chart->coords.y1 + p.y - 10;

      lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);
      lv_draw_rect(draw_ctx, &draw_rect_dsc, &a);

      ser = lv_chart_get_series_next(chart, ser);
    }
  } else if (code == LV_EVENT_RELEASED) {
    ESP_LOGI("LV_EVENT_RELEASED", "lv_obj_invalidate(chart)");

    // store_scroll_value_event_cb(e);
    // lv_chart_refresh(chart);
    lv_obj_invalidate(chart);
    // lv_obj_scroll_to_x(obj, x, LV_ANIM_ON/OFF)

  } else if (code == LV_EVENT_MSG_RECEIVED) {
    lv_msg_t *m = lv_event_get_msg(e);
    if (m->id == MSG_NEW_VOLT) {
      if (lv_tileview_get_tile_act(dis) == tv4) {
        ESP_LOGI("msg-received", "msg-volt processing started");
        lv_coord_t v = *(lv_coord_t *)lv_msg_get_payload(m);
        char output[5];
        sprintf(output,"%ld",v);
        ESP_LOGI("msg-received", "msg-volt processing started on %s", output);
        lv_chart_set_next_value(chart, ser1, lv_rand(v,v+2)); //(unsigned long)m->payload);
        
        lv_chart_refresh(chart);
        ESP_LOGI("msg-received", "msg-volt processed");
      } else {
        ESP_LOGI("msg-received", "tile not active, ignoring msg");
      }
    } else {
      ESP_LOGI("msg-received", "untrapped msg processed %d", m->id);
    }
  } else if (code == LV_EVENT_SCROLL_END) {
    ESP_LOGI("LV_EVENT_SCROLL_END", "storing position");
    // store_scroll_value_event_cb(e);
    ESP_LOGI("LV_EVENT_SCROLL_END", "stored position");
  } else if (code == LV_EVENT_SCROLL) {
    ESP_LOGI("LV_EVENT_SCROLL", "LV_EVENT_SCROLL happened");
  } else if (code == LV_EVENT_CLICKED) {
    ESP_LOGI("LV_EVENT_CLICKED", "LV_EVENT_CLICKED happened");
  } else if (code == LV_EVENT_LONG_PRESSED) {
    ESP_LOGI("LV_EVENT_LONG_PRESSED", "LV_EVENT_LONG_PRESSED happened");
  } else if (code == LV_EVENT_SCREEN_LOADED) {
    chartMsgSub = lv_msg_subsribe_obj(MSG_NEW_VOLT, chart, NULL); // for tooltip
    ESP_LOGI("LV_EVENT_LOADED", "LV_EVENT_LOADED happened");
  } else if (code == LV_EVENT_SCREEN_UNLOAD_START) {
    lv_msg_unsubscribe(chartMsgSub);
    ESP_LOGI("LV_EVENT_SCREEN_UNLOAD_START", "LV_EVENT_SCREEN_UNLOAD_START happened");
  } else if (code == LV_EVENT_SCROLL_BEGIN) {
    ESP_LOGI("LV_EVENT_SCROLL_START", "storing position");
    // store_scroll_value_event_cb(e);
    ESP_LOGI("LV_EVENT_SCROLL_START", "stored position");
  }
}

static void store_scroll_value_event_cb(lv_event_t *e) {
  lv_obj_t *screen = lv_event_get_target(e);
  scroll_value = lv_obj_get_scroll_x(screen);
  printf("%d pixels are scrolled out on the x\n", scroll_value);

  scroll_value = lv_obj_get_scroll_y(screen);
  printf("%d pixels are scrolled out on the y\n", scroll_value);

  scroll_value = lv_obj_get_scroll_left(screen);
  printf("%d pixels are scrolled out on the left\n", scroll_value);

  scroll_value = lv_obj_get_scroll_right(screen);
  printf("%d pixels are scrolled out on the right\n", scroll_value);
}