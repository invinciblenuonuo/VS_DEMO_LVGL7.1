#include "../../lv_examples.h"
int i;

typedef struct
{
    lv_task_t* task_ReWave;//一个刷新波形的任务

}My_task;//任务集


typedef struct
{
    lv_obj_t* yaw;
    lv_obj_t* progess;
}My_obj;

My_obj  MY_OBJ;
My_task task_1;
static void event_test()
{

    printf("press\r\n");
}
static void slider_event_handler(lv_obj_t* obj, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED) 
    {
        printf("Value: %d\n", lv_slider_get_value(obj));
        //printf("%d\r\n", i);

    }
}

int process_init;
static void event_test_2(lv_task_t* task)
{
    i++;
    //lv_label_set_text_fmt(MY_OBJ.yaw, "Value: %d", i);
    //lv_obj_align(MY_OBJ.yaw, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_bar_set_value(MY_OBJ.progess,  i, LV_ANIM_ON);

}

void ReWave_task_etr(void)
{
    task_1.task_ReWave = lv_task_create(event_test_2, 100, LV_TASK_PRIO_MID, i);//设置时间为0，应该能立即执行
}

void CONTENER_Init()
{

}
/**
 * Using the outline style properties
 */
void Label_Init(void)
{

    static lv_style_t style;
    lv_style_init(&style);

    /*Set a background color and a radius*/
    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_SILVER);


    /*Create an object with the new style*/
    lv_obj_t* obj2 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj2, LV_OBJ_PART_MAIN, &style);
    lv_obj_set_size(obj2, 100, 30);
    lv_obj_align(obj2, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);



    MY_OBJ.yaw = lv_label_create(obj2, NULL);
    lv_label_set_text_fmt(MY_OBJ.yaw, "Value: %d", i);
    lv_obj_align(MY_OBJ.yaw, NULL, LV_ALIGN_CENTER, 0, 0);

}
void lv_obj_add_anim(lv_obj_t* obj, lv_anim_exec_xcb_t exec_cb, uint16_t time, lv_coord_t start, lv_coord_t end, lv_anim_path_cb_t path_cb)
{
    lv_anim_t a;

    lv_anim_init(&a);
    lv_anim_set_var(&a, obj); //动画对象

    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)exec_cb); //动画函数
    lv_anim_set_time(&a, time);

    a.start = start;		  //起始值
    a.end = end; //结束值
    a.path.cb = path_cb;	  //动画计算方法
    a.playback_time = 0;				  //回放时间设为0不执行动画回放

    lv_anim_start(&a); //开启动画
}

//开始动画
//开机初始化的动画初始化
void Animations_Init()
{
    static lv_style_t style;
    lv_style_init(&style);

    /*Set a background color and a radius*/
    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_SILVER);

    MY_OBJ.progess = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(MY_OBJ.progess, 100, 20);
    lv_obj_align(MY_OBJ.progess, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_anim(MY_OBJ.progess, lv_obj_set_y, 800, 0, 100, lv_anim_path_ease_out);

    lv_bar_set_anim_time(MY_OBJ.progess, 500);
    lv_bar_set_value(MY_OBJ.progess,0, LV_ANIM_ON );
    lv_obj_set_style_local_bg_color(MY_OBJ.progess, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_obj_set_style_local_bg_color(MY_OBJ.progess, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_PURPLE);

    ReWave_task_etr();


}








