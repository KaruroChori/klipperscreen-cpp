#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#include <lvgl.h>
#include <lv_drivers/display/fbdev.h>
#include <lv_drivers/indev/evdev.h>
#include <demos/lv_demos.h>
#include <unistd.h>
#include <pthread.h>
#include <ctime>

using json = nlohmann::json;

void test_json(){
    json data = json::parse("{}");
    std::cout<<data;
}

void test_cpr(){
    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                    cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                    cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    std::cout<<r.status_code;                  // 200
    std::cout<<r.header["content-type"];       // application/json; charset=utf-8
    std::cout<<r.text;                         // JSON text string
}

void test_lvgl(){
     /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb = evdev_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);


    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon)
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/


    /*Create a Demo*/
    lv_demo_widgets();

    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        lv_timer_handler();
        usleep(5000);
    }
    return;
}


int main(){
    test_json();
    test_cpr();
    return 0;
}