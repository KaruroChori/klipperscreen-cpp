#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#include <lvgl.h>
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
    lv_init();

    /*Linux frame buffer device init*/
    lv_display_t * disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");

    /*Create a Demo*/
    lv_demo_widgets();
    lv_demo_widgets_start_slideshow();

    /*Handle LVGL tasks*/
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