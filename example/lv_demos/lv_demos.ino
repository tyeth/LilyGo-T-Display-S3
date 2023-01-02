#define MAX_SERIES_DATAPOINTS 126

#ifndef USEPLATFORMIO
#error "This example can only be run on platformIO"
#endif

#define TOUCH_MODULES_CST_MUTUAL
// #define TOUCH_MODULES_CST_SELF
#include "TouchLib.h"
// #define TOUCH_READ_FROM_INTERRNUPT

/* The product now has two screens, and the initialization code needs a small change in the new version. The LCD_MODULE_CMD_1 is used to define the
 * switch macro. */
//#define LCD_MODULE_CMD_1

/*
This example can only be run on platformIO.
Because Arduino cannot index into the demos directory.
*/

#include "demos/lv_demos.h"
#include "lv_conf.h"
#include "lvgl.h" /* https://github.com/lvgl/lvgl.git */

#include "Arduino.h"
#include "Wire.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "pin_config.h"


    lv_obj_t * chart;
esp_lcd_panel_io_handle_t io_handle = NULL;
static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv;      // contains callback functions
static lv_color_t *lv_disp_buf;
static bool is_initialized_lvgl = false;
#if defined(LCD_MODULE_CMD_1)
typedef struct {
  uint8_t cmd;
  uint8_t data[14];
  uint8_t len;
} lcd_cmd_t;

lcd_cmd_t lcd_st7789v[] = {
    {0x11, {0}, 0 | 0x80},
    // {0x3A, {0X06}, 1},
    {0xB2, {0X0B, 0X0B, 0X00, 0X33, 0X33}, 5},
    {0xB7, {0X75}, 1},
    {0xBB, {0X28}, 1},
    {0xC0, {0X2C}, 1},
    {0xC2, {0X01}, 1},
    {0xC3, {0X1F}, 1},
    {0xC6, {0X13}, 1},
    {0xD0, {0XA7}, 1},
    {0xD0, {0XA4, 0XA1}, 2},
    {0xD6, {0XA1}, 1},
    {0xE0, {0XF0, 0X05, 0X0A, 0X06, 0X06, 0X03, 0X2B, 0X32, 0X43, 0X36, 0X11, 0X10, 0X2B, 0X32}, 14},
    {0xE1, {0XF0, 0X08, 0X0C, 0X0B, 0X09, 0X24, 0X2B, 0X22, 0X43, 0X38, 0X15, 0X16, 0X2F, 0X37}, 14},

};
#endif

void my_log_cb(const char * buf);
#if defined(TOUCH_MODULES_CST_MUTUAL)
TouchLib touch(Wire, PIN_IIC_SDA, PIN_IIC_SCL, CTS328_SLAVE_ADDRESS, PIN_TOUCH_RES);
#elif defined(TOUCH_MODULES_CST_SELF)
TouchLib touch(Wire, PIN_IIC_SDA, PIN_IIC_SCL, CTS820_SLAVE_ADDRESS, PIN_TOUCH_RES);
#endif

bool inited_touch = false;
#if defined(TOUCH_READ_FROM_INTERRNUPT)
bool get_int_signal = false;
#endif


void my_log_cb(const char * buf)
{
  Serial.print(buf);
  Serial.flush();
}


static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
  if (is_initialized_lvgl) {
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
  }
  return false;
}

static void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map) {
  esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)drv->user_data;
  int offsetx1 = area->x1;
  int offsetx2 = area->x2;
  int offsety1 = area->y1;
  int offsety2 = area->y2;
  // copy a buffer's content to a specific area of the display
  esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

static void lv_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
#if defined(TOUCH_READ_FROM_INTERRNUPT)
  if (get_int_signal) {
    get_int_signal = false;
    touch.read();
#else
  if (touch.read()) {
#endif

    uint8_t touch_points_num = touch.getPointNum();
    TP_Point t = touch.getPoint(0);
    data->point.x = t.x;
    data->point.y = t.y;
    data->state = (touch_points_num > 0) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    // lv_msg_send(MSG_NEW_TOUCH_POINT, str_buf.c_str());
  } else
    data->state = LV_INDEV_STATE_REL;
}

void setup() {
  pinMode(PIN_POWER_ON, OUTPUT);
  digitalWrite(PIN_POWER_ON, HIGH);
  Serial.begin(115200);

  pinMode(PIN_LCD_RD, OUTPUT);
  digitalWrite(PIN_LCD_RD, HIGH);
  esp_lcd_i80_bus_handle_t i80_bus = NULL;
  esp_lcd_i80_bus_config_t bus_config = {
      .dc_gpio_num = PIN_LCD_DC,
      .wr_gpio_num = PIN_LCD_WR,
      .clk_src = LCD_CLK_SRC_PLL160M,
      .data_gpio_nums =
          {
              PIN_LCD_D0,
              PIN_LCD_D1,
              PIN_LCD_D2,
              PIN_LCD_D3,
              PIN_LCD_D4,
              PIN_LCD_D5,
              PIN_LCD_D6,
              PIN_LCD_D7,
          },
      .bus_width = 8,
      .max_transfer_bytes = LVGL_LCD_BUF_SIZE * sizeof(uint16_t),
  };
  esp_lcd_new_i80_bus(&bus_config, &i80_bus);

  esp_lcd_panel_io_i80_config_t io_config = {
      .cs_gpio_num = PIN_LCD_CS,
      .pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
      .trans_queue_depth = 20,
      .on_color_trans_done = example_notify_lvgl_flush_ready,
      .user_ctx = &disp_drv,
      .lcd_cmd_bits = 8,
      .lcd_param_bits = 8,
      .dc_levels =
          {
              .dc_idle_level = 0,
              .dc_cmd_level = 0,
              .dc_dummy_level = 0,
              .dc_data_level = 1,
          },
  };
  ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));
  esp_lcd_panel_handle_t panel_handle = NULL;
  esp_lcd_panel_dev_config_t panel_config = {
      .reset_gpio_num = PIN_LCD_RES,
      .color_space = ESP_LCD_COLOR_SPACE_RGB,
      .bits_per_pixel = 16,
  };
  esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle);
  esp_lcd_panel_reset(panel_handle);
  esp_lcd_panel_init(panel_handle);
  esp_lcd_panel_invert_color(panel_handle, true);

  esp_lcd_panel_swap_xy(panel_handle, true);
  esp_lcd_panel_mirror(panel_handle, false, true);
  // the gap is LCD panel specific, even panels with the same driver IC, can
  // have different gap value
  esp_lcd_panel_set_gap(panel_handle, 0, 35);
#if defined(LCD_MODULE_CMD_1)
  for (uint8_t i = 0; i < (sizeof(lcd_st7789v) / sizeof(lcd_cmd_t)); i++) {
    esp_lcd_panel_io_tx_param(io_handle, lcd_st7789v[i].cmd, lcd_st7789v[i].data, lcd_st7789v[i].len & 0x7f);
    if (lcd_st7789v[i].len & 0x80)
      delay(120);
  }
#endif
  /* Lighten the screen with gradient */
  ledcSetup(0, 10000, 8);
  ledcAttachPin(PIN_LCD_BL, 0);
  for (uint8_t i = 0; i < 0xFF; i++) {
    ledcWrite(0, i);
    delay(2);
  }

  lv_init();
  #if LV_USE_LOG != 0
  lv_log_register_print_cb(my_log_cb);
  LV_LOG_ERROR("logging on error message");
  lv_log("test");
  #else
  ESP_LOGI("LV","LVGL logging off");
  LV_LOG_ERROR("logging off error message");
  #endif
  
  lv_disp_buf = (lv_color_t *)heap_caps_malloc(LVGL_LCD_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);

  lv_disp_draw_buf_init(&disp_buf, lv_disp_buf, NULL, LVGL_LCD_BUF_SIZE);
  /*Initialize the display*/
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = EXAMPLE_LCD_H_RES;
  disp_drv.ver_res = EXAMPLE_LCD_V_RES;
  disp_drv.flush_cb = example_lvgl_flush_cb;
  disp_drv.draw_buf = &disp_buf;
  disp_drv.user_data = panel_handle;
  lv_disp_drv_register(&disp_drv);

  /* Register touch brush with LVGL */
  Wire.begin(PIN_IIC_SDA, PIN_IIC_SCL, 800000);
  inited_touch = touch.init();
  if (inited_touch) {
    touch.setRotation(1);
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lv_touchpad_read;
    lv_indev_drv_register(&indev_drv);
  }
  is_initialized_lvgl = true;
#if defined(TOUCH_READ_FROM_INTERRNUPT)
  attachInterrupt(
      PIN_TOUCH_INT, [] { get_int_signal = true; }, FALLING);
#endif

#if LV_USE_DEMO_WIDGETS
  // lv_demo_widgets();
  lv_example_chart_4_on_tile();


#elif LV_USE_DEMO_BENCHMARK
  lv_demo_benchmark();
#elif LV_USE_DEMO_STRESS
  lv_demo_stress();
#elif LV_USE_DEMO_KEYPAD_AND_ENCODER
  lv_demo_keypad_encoder();
#else LV_USE_DEMO_MUSIC
  lv_demo_music();
#endif


}

void loop() {
  lv_timer_handler();
  delay(2);
  static uint32_t last_tick;
  if (millis() - last_tick > 500) {
    int16_t volt = (analogRead(PIN_BAT_VOLT) * 2 * 3.3 * 1000) / 4096;
  //   lv_msg_send(MSG_NEW_VOLT, &volt);
  Serial.printf("%u ",volt);
  lv_chart_series_t* ser1 = lv_chart_get_series_next(chart, NULL);
  lv_chart_set_next_value(chart,ser1, (lv_coord_t) ( lv_rand(volt,volt+1) ));
  lv_chart_series_t* ser2 = lv_chart_get_series_next(chart, ser1);
  lv_chart_set_next_value(chart,ser2,  lv_rand(2700,4900) );

    last_tick = millis();
  }
}



static void event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * chart = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_obj_invalidate(chart);
    }
    if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_coord_t * s = (lv_coord_t*)lv_event_get_param(e);
        *s = LV_MAX(*s, 20);
    }
    else if(code == LV_EVENT_DRAW_POST_END) {
        int32_t id = lv_chart_get_pressed_point(chart);
        if(id == LV_CHART_POINT_NONE) return;

        LV_LOG_USER("Selected: %d", (int)id);
        u_int16_t seriesCounter = 0;
        lv_chart_series_t * ser = lv_chart_get_series_next(chart, NULL);
        

        while(ser) {
            u_int16_t startX = lv_chart_get_x_start_point(chart,ser);
            LV_LOG_USER("x-axis start point: %d", startX);
            //if(startX<12){}
            seriesCounter++;
            lv_point_t p;
            lv_chart_get_point_pos_by_id(chart, ser, id, &p);
            LV_LOG_USER("Series %d \tx: %d\ty: %d", seriesCounter, (int)p.x, (int)p.y);

            lv_coord_t * y_array = lv_chart_get_y_array(chart, ser);
            lv_coord_t value = y_array[id];

            char buf[16];
            lv_snprintf(buf, sizeof(buf), LV_SYMBOL_DUMMY"$%d", value);

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

            lv_draw_ctx_t * draw_ctx = lv_event_get_draw_ctx(e);
            lv_draw_rect(draw_ctx, &draw_rect_dsc, &a);

            ser = lv_chart_get_series_next(chart, ser);
        }
    }
    else if(code == LV_EVENT_RELEASED) {
        lv_obj_invalidate(chart);
    }
}

/**
 * Show the value of the pressed points
 */
void lv_example_chart_4_on_tile(void)
{
    /*Create tile*/
    lv_obj_t *dis = lv_tileview_create(lv_scr_act());
    lv_obj_align(dis, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_size(dis, LV_PCT(100), LV_PCT(100));
    lv_obj_t *tv4 = lv_tileview_add_tile(dis, 0, 0, LV_DIR_HOR);
  // lv_obj_t *tv2 = lv_tileview_add_tile(dis, 0, 1, LV_DIR_HOR);
  // lv_obj_t *tv3 = lv_tileview_add_tile(dis, 0, 2, LV_DIR_HOR);
  // lv_obj_t *tv4 = lv_tileview_add_tile(dis, 0, 3, LV_DIR_HOR);


    /*Create a chart*/
    chart = lv_chart_create(tv4);
    //lv_obj_set_size(chart, 200, 150);
    lv_obj_set_size(chart, LV_PCT(100), LV_PCT(100));
    lv_obj_center(chart);

    lv_obj_add_event_cb(chart, event_cb, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(chart);

    /*Zoom in a little in X*/
    //lv_chart_set_zoom_x(chart, 200);
    
    // set chart range
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 2700, 5200);
    lv_chart_set_point_count(chart, MAX_SERIES_DATAPOINTS);
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_CIRCULAR); //When SHIFTED instead of CIRCULAR then points and tooltips break, look at x_start

    /*Add two data series*/
    lv_chart_series_t * ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * ser2 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    // lv_chart_set_all_value(chart,ser1,LV_CHART_POINT_NONE);
    // lv_chart_set_all_value(chart,ser2,LV_CHART_POINT_NONE);

    uint32_t i;
    for(i = 0; i < 10; i++) {
        lv_chart_set_next_value(chart, ser1, lv_rand(4400, 4900));
        lv_chart_set_next_value(chart, ser2, lv_rand(2700, 4900));
    }
    
    LV_LOG_USER("Point count: %d\n", lv_chart_get_point_count(chart));

}
