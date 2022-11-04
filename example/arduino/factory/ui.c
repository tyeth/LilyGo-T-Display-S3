// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: TFT_eSPI_TDisplayS3_lvgl833

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void ui_event_LogoScreen(lv_event_t * e);
lv_obj_t * ui_LogoScreen;
lv_obj_t * ui_LogoScreenImage;
lv_obj_t * ui_WifiScreen;
lv_obj_t * ui_WifiScreenPanelQRCode;
lv_obj_t * ui_WifiScreenImageQRCode;
lv_obj_t * ui_Screen2_Panel2;
lv_obj_t * ui_Screen2Label1Searching1;
lv_obj_t * ui_DeviceScanningScreen;
lv_obj_t * ui_Screen2_Panel1;
lv_obj_t * ui_Screen2Label1Searching;
lv_obj_t * ui_Screen2_Spinner1;
lv_obj_t * ui_Screen2_TextArea1;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_LogoScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        _ui_screen_change(ui_DeviceScanningScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 250, 500);
    }
}

///////////////////// SCREENS ////////////////////
void ui_LogoScreen_screen_init(void)
{
    ui_LogoScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_LogoScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LogoScreenImage = lv_img_create(ui_LogoScreen);
    lv_img_set_src(ui_LogoScreenImage, &ui_img_194160428);
    lv_obj_set_width(ui_LogoScreenImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LogoScreenImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LogoScreenImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_LogoScreenImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_LogoScreenImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_LogoScreen, ui_event_LogoScreen, LV_EVENT_ALL, NULL);
        

}
void ui_WifiScreen_screen_init(void)
{
    ui_WifiScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_WifiScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_WifiScreen, lv_color_hex(0x9CC641), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WifiScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_WifiScreen, &ui_img_194160428, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_WifiScreen, 100, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiScreenPanelQRCode = lv_obj_create(ui_WifiScreen);
    lv_obj_set_width(ui_WifiScreenPanelQRCode, 164);
    lv_obj_set_height(ui_WifiScreenPanelQRCode, 164);
    lv_obj_set_x(ui_WifiScreenPanelQRCode, -3);
    lv_obj_set_y(ui_WifiScreenPanelQRCode, 0);
    lv_obj_set_align(ui_WifiScreenPanelQRCode, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(ui_WifiScreenPanelQRCode, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_WifiScreenPanelQRCode, lv_color_hex(0x001C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WifiScreenPanelQRCode, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_WifiScreenPanelQRCode, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiScreenImageQRCode = lv_img_create(ui_WifiScreenPanelQRCode);
    lv_obj_set_width(ui_WifiScreenImageQRCode, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WifiScreenImageQRCode, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_WifiScreenImageQRCode, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiScreenImageQRCode, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WifiScreenImageQRCode, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen2_Panel2 = lv_obj_create(ui_WifiScreen);
    lv_obj_set_height(ui_Screen2_Panel2, lv_pct(100));
    lv_obj_set_width(ui_Screen2_Panel2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_Screen2_Panel2, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_Screen2_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen2_Panel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Screen2_Panel2, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen2_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen2_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen2_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen2_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2Label1Searching1 = lv_label_create(ui_Screen2_Panel2);
    lv_obj_set_width(ui_Screen2Label1Searching1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen2Label1Searching1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen2Label1Searching1, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen2Label1Searching1,
                      "Wifi Connected\nConnected AP:\nssid: espressif\nquality: -45db\nip: 192.168.4.1\n\nHelpful QRCode to\njoin wifi then visit\nhttp://192.168.4.1\nin web browser\n\n\n\n\nWifi Connected\nBroadcasting AP:\nssid: espressif\npw: password\nip: 192.168.4.1");
    lv_obj_set_style_text_color(ui_Screen2Label1Searching1, lv_color_hex(0x3C6A00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2Label1Searching1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_Screen2Label1Searching1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen2Label1Searching1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2Label1Searching1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen2Label1Searching1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen2Label1Searching1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen2Label1Searching1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen2Label1Searching1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_DeviceScanningScreen_screen_init(void)
{
    ui_DeviceScanningScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_DeviceScanningScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_DeviceScanningScreen, lv_color_hex(0x9CC641), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DeviceScanningScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_DeviceScanningScreen, &ui_img_194160428, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_DeviceScanningScreen, 100, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2_Panel1 = lv_obj_create(ui_DeviceScanningScreen);
    lv_obj_set_height(ui_Screen2_Panel1, lv_pct(100));
    lv_obj_set_width(ui_Screen2_Panel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_Screen2_Panel1, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_Screen2_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen2_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Screen2_Panel1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen2_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen2_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen2_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen2_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2Label1Searching = lv_label_create(ui_Screen2_Panel1);
    lv_obj_set_width(ui_Screen2Label1Searching, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen2Label1Searching, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen2Label1Searching, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen2Label1Searching, "Searching\nfor devices...\n\n( Sensors /\nControllers )");
    lv_obj_set_style_text_color(ui_Screen2Label1Searching, lv_color_hex(0x3C6A00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2Label1Searching, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_Screen2Label1Searching, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen2Label1Searching, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2Label1Searching, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen2Label1Searching, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen2Label1Searching, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen2Label1Searching, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen2Label1Searching, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen2_Spinner1 = lv_spinner_create(ui_Screen2_Panel1, 1000, 90);
    lv_obj_set_width(ui_Screen2_Spinner1, 60);
    lv_obj_set_height(ui_Screen2_Spinner1, 60);
    lv_obj_set_x(ui_Screen2_Spinner1, 0);
    lv_obj_set_y(ui_Screen2_Spinner1, -10);
    lv_obj_set_align(ui_Screen2_Spinner1, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Screen2_Spinner1, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_arc_width(ui_Screen2_Spinner1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_Screen2_Spinner1, lv_color_hex(0xE4FF85), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Screen2_Spinner1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Screen2_Spinner1, 14, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_Screen2_Spinner1, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_Screen2_TextArea1 = lv_textarea_create(ui_DeviceScanningScreen);
    lv_obj_set_width(ui_Screen2_TextArea1, lv_pct(67));
    lv_obj_set_height(ui_Screen2_TextArea1, lv_pct(100));
    lv_obj_set_align(ui_Screen2_TextArea1, LV_ALIGN_RIGHT_MID);
    lv_textarea_set_max_length(ui_Screen2_TextArea1, 30000);
    lv_textarea_set_text(ui_Screen2_TextArea1, "Status will appear here as things happen...");
    lv_obj_set_style_text_color(ui_Screen2_TextArea1, lv_color_hex(0xE4FF85), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2_TextArea1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen2_TextArea1, &ui_font_InterRegular13, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen2_TextArea1, lv_color_hex(0x001C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2_TextArea1, 200, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_Screen2_TextArea1, lv_color_hex(0xE4FF85),
                                LV_PART_TEXTAREA_PLACEHOLDER | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Screen2_TextArea1, 255, LV_PART_TEXTAREA_PLACEHOLDER | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_LogoScreen_screen_init();
    ui_WifiScreen_screen_init();
    ui_DeviceScanningScreen_screen_init();
    lv_disp_load_scr(ui_LogoScreen);
    
    //_ui_screen_change(ui_DeviceScanningScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 250, 500);
}
