// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: TFT_eSPI_TDisplayS3_lvgl833

#ifndef _TFT_ESPI_TDISPLAYS3_LVGL833_UI_H
#define _TFT_ESPI_TDISPLAYS3_LVGL833_UI_H

#ifdef __cplusplus
extern "C" {
#endif

// #if defined __has_include
// #if __has_include("lvgl.h")
// #include "lvgl.h"
// #elif __has_include("lvgl/lvgl.h")
// #include "lvgl/lvgl.h"
// #else
// #include "lvgl.h"
// #endif
// #else
#ifdef ARDUINO
#include "lvgl.h"
#else
#include "../../../../lib/lvgl/lvgl.h"
#endif
// #endif

void ui_event_LogoScreen(lv_event_t * e);
extern lv_obj_t * ui_LogoScreen;
extern lv_obj_t * ui_LogoScreenImage;
extern lv_obj_t * ui_WifiScreen;
extern lv_obj_t * ui_WifiScreenPanelQRCode;
extern lv_obj_t * ui_WifiScreenImageQRCode;
extern lv_obj_t * ui_Screen2_Panel2;
extern lv_obj_t * ui_Screen2Label1Searching1;
extern lv_obj_t * ui_DeviceScanningScreen;
extern lv_obj_t * ui_Screen2_Panel1;
extern lv_obj_t * ui_Screen2Label1Searching;
extern lv_obj_t * ui_Screen2_Spinner1;
extern lv_obj_t * ui_Screen2_TextArea1;


LV_IMG_DECLARE(ui_img_194160428);    // assets\20221011-Good-Enough-technology-1280 x 720.png


LV_FONT_DECLARE(ui_font_Font1);
LV_FONT_DECLARE(ui_font_InterRegular13);
LV_FONT_DECLARE(ui_font_InterRegular16);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
