
#include "pebble.h"

static Window *window;
static MenuLayer *menu_layer;

static char *thursday_events[7];
static char *thursday_times[7];
static int thursday_hours[7] = {8, 10, 12, 13, 18, 19, 22};

static char *friday_events[8];
static char *friday_times[8];
static int friday_hours[8] = {9, 10, 10, 12, 13, 18, 19, 22};

static char *saturday_events[8];
static char *saturday_times[8];
static int saturday_hours[8] = {9, 10, 10, 12, 13, 18, 20, 22};

static char *sunday_events[6];
static char *sunday_times[6];
static int sunday_hours[6] = {9, 10, 11, 12, 14, 15};

static void create_data () {
    // Thursday
    thursday_events[0] = "Registration/Breakfast/Swag";
    thursday_events[1] = "Introduction and overview of talks";
    thursday_events[2] = "Lunch!";
    thursday_events[3] = "Advanced Techniques, Tools, and APIs";
    thursday_events[4] = "First ever Pebble Meetup in SF with lightning talks and the community!";
    thursday_events[5] = "Food trucks for dinner!";
    thursday_events[6] = "Leave SF -> Mountain View to sleep or explore";
    
    thursday_times[0] = "9:30";
    thursday_times[1] = "10:30";
    thursday_times[2] = "12:00";
    thursday_times[3] = "13:00";
    thursday_times[4] = "18:00";
    thursday_times[5] = "19:00";
    thursday_times[6] = "22:00";

    // Friday
    friday_events[0] = "Welcome/Breakfast";
    friday_events[1] = "Let the hacking commence all afternoon!";
    friday_events[2] = "Optional battery workshop";
    friday_events[3] = "Lunch!";
    friday_events[4] = "Optional individual code reviews and mystery workshop";
    friday_events[5] = "Private tours/exploration of the Computer History Museum (CHM) in Mountain View";
    friday_events[6] = "Dinner at the CHM next to the Babbage Engine!";
    friday_events[7] = "Leave CHM -> Mountain View to sleep or explore";
    
    friday_times[0] = "9:30";
    friday_times[1] = "10:00";
    friday_times[2] = "10:30";
    friday_times[3] = "12:00";
    friday_times[4] = "13:00";
    friday_times[5] = "18:00";
    friday_times[6] = "19:00";
    friday_times[7] = "22:00";
    
    // Saturday
    saturday_events[0] = "Welcome/Breakfast";
    saturday_events[1] = "Let the hacking commence all afternoon!";
    saturday_events[2] = "Optional robotics competition!";
    saturday_events[3] = "Lunch!";
    saturday_events[4] = "Optional app demos/design reviews/code reviews";
    saturday_events[5] = "Dinner!";
    saturday_events[6] = "Custom ice cream sandwich making bar provided by Cream!";
    saturday_events[7] = "Leave retreat and go sleep or explore";
    
    saturday_times[0] = "9:30";
    saturday_times[1] = "10:00";
    saturday_times[2] = "10:30";
    saturday_times[3] = "12:00";
    saturday_times[4] = "13:00";
    saturday_times[5] = "18:00";
    saturday_times[6] = "20:00";
    saturday_times[7] = "22:00";
    
    // Sunday
    sunday_events[0] = "Welcome/Small breakfast";
    sunday_events[1] = "Last minute hacking!";
    sunday_events[2] = "Brunch! Everyone loves brunch!";
    sunday_events[3] = "Developer showcase";
    sunday_events[4] = "Awards (TBD) and closing talk";
    sunday_events[5] = "You're probably tired of us and want to leave!";
    
    sunday_times[0] = "9:30";
    sunday_times[1] = "10:00";
    sunday_times[2] = "11:00";
    sunday_times[3] = "12:00";
    sunday_times[4] = "14:00";
    sunday_times[5] = "15:30";

}

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
    return 4;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    if (section_index == 0) {
        return 7;
    } else if (section_index == 1) {
        return 8;
    } else if (section_index == 2) {
        return 8;
    } else {
        return 6;
    }
}

static int16_t menu_layer_get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
    return 44;
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    if (section_index == 0) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Thursday 2");
    } else if (section_index == 1) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Friday 3");
    } else if (section_index == 2) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Saturday 4");
    } else if (section_index == 3) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Sunday 5");
    }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    
    graphics_context_set_text_color(ctx, GColorBlack);
  
    if (cell_index->section == 0) {
        float text_height = graphics_text_layout_get_content_size(thursday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, thursday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, thursday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    } else if (cell_index->section == 1) {
        float text_height = graphics_text_layout_get_content_size(friday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, friday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, friday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    } else if (cell_index->section == 2) {
        float text_height = graphics_text_layout_get_content_size(saturday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, saturday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, saturday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    } else if (cell_index->section == 3) {
        float text_height = graphics_text_layout_get_content_size(sunday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, sunday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, sunday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    }
}

void window_load(Window *window) {
  
    create_data();

    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_frame(window_layer);

    menu_layer = menu_layer_create(bounds);

    menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
        .get_num_sections = menu_get_num_sections_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .get_header_height = menu_get_header_height_callback,
        .draw_header = menu_draw_header_callback,
        .draw_row = menu_draw_row_callback,
        .get_cell_height = menu_layer_get_cell_height_callback,
    });

    menu_layer_set_click_config_onto_window(menu_layer, window);

    layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
    
    time_t now = time(NULL);
    struct tm *tick_time = localtime(&now);
    
    int hour = tick_time->tm_hour;
    int day = tick_time->tm_mday;
    
    if (day == 17 || day == 2 || day == 3 || day == 4) {
        MenuIndex selected;
        selected.section = /*day - */2;

        if (day == 17) {
            for (int i = 0; i < 7; i++) {
                int event_hour = thursday_hours[i];
                if (event_hour <= hour) {
                    selected.row = i;
                }
            }
        } else if (day == 2) {
            for (int i = 0; i < 8; i++) {
                int event_hour = friday_hours[i];
                if (event_hour <= hour) {
                    selected.row = i;
                }
            }
        } else if (day == 3) {
            for (int i = 0; i < 8; i++) {
                int event_hour = saturday_hours[i];
                if (event_hour <= hour) {
                    selected.row = i;
                }
            }
        } else if (day == 4) {
            for (int i = 0; i < 8; i++) {
                int event_hour = sunday_hours[i];
                if (event_hour <= hour) {
                    selected.row = i;
                }
            }
        }
        
        menu_layer_set_selected_index(menu_layer, selected, MenuRowAlignCenter, false);
    }
}

void window_unload(Window *window) {
    menu_layer_destroy(menu_layer);
}

int main(void) {
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    window_stack_push(window, true);
    app_event_loop();
    window_destroy(window);
}