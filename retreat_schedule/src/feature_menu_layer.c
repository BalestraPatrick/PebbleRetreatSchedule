
#include "pebble.h"

static Window *window;
static MenuLayer *menu_layer;

static char *thursday_events[12];
static char *thursday_times[12];
static int thursday_hours[12] = {9, 10, 11, 12, 13, 16, 18, 18, 19, 19, 20, 21};

static char *friday_events[14];
static char *friday_times[14];
static int friday_hours[14] = {9, 10, 11, 12, 14, 14, 15, 15, 15, 16, 17, 18, 19, 22};

static char *saturday_events[9];
static char *saturday_times[9];
static int saturday_hours[9] = {9, 10, 10, 12, 14, 16, 18, 20, 22};

static char *sunday_events[6];
static char *sunday_times[6];
static int sunday_hours[6] = {9, 11, 12, 14, 14, 15};

static void create_data () {
    // Thursday
    thursday_events[0] = "Start of the Retreat";
    thursday_events[1] = "Opening Presentation";
    thursday_events[2] = "Mingling";
    thursday_events[3] = "Lunch";
    thursday_events[4] = "Technical Presentations";
    thursday_events[5] = "Leave via Caltrain for Meetup in SF";
    thursday_events[6] = "Meeting and Mingling";
    thursday_events[7] = "Introduction";
    thursday_events[8] = "Technical talks";
    thursday_events[9] = "Lightning talks";
    thursday_events[10] = "Raffle 3 Pebble Steels";
    thursday_events[11] = "Meetup Ends";
    
    thursday_times[0] = "9:30";
    thursday_times[1] = "10:30";
    thursday_times[2] = "11:30";
    thursday_times[3] = "12:00";
    thursday_times[4] = "13:00";
    thursday_times[5] = "16:00";
    thursday_times[6] = "18:00";
    thursday_times[7] = "18:40";
    thursday_times[8] = "19:00";
    thursday_times[9] = "19:30";
    thursday_times[10] = "20:30";
    thursday_times[11] = "21:30";

    // Friday
    friday_events[0] = "Start of Day 2";
    friday_events[1] = "Battery Talk by Stuart Harrell";
    friday_events[2] = "BLE Presentation by Martijn Thé";
    friday_events[3] = "Lunch";
    friday_events[4] = "Code Reviews in the Workshop Room";
    friday_events[5] = "Workshop on CloudPebble";
    friday_events[6] = "Guest Presentation by Strap";
    friday_events[7] = "Guest Presentation on Overlay";
    friday_events[8] = "Panintelligent demo w/ Pebble and Crepes";
    friday_events[9] = "Workshop on Pebble TM";
    friday_events[10] = "Travel to Computer History Museum";
    friday_events[11] = "Self-Guided Tours of the CHM";
    friday_events[12] = "Dinner at the CHM";
    friday_events[13] = "Leave the CHM";
    
    friday_times[0] = "9:30";
    friday_times[1] = "10:30";
    friday_times[2] = "11:00";
    friday_times[3] = "12:00";
    friday_times[4] = "14:00";
    friday_times[5] = "14:30";
    friday_times[6] = "15:00";
    friday_times[7] = "15:30";
    friday_times[8] = "15:30";
    friday_times[9] = "16:00";
    friday_times[10] = "17:30";
    friday_times[11] = "18:00";
    friday_times[12] = "19:00";
    friday_times[13] = "22:00";
    
    // Saturday
    saturday_events[0] = "Start of Day 3";
    saturday_events[1] = "Code Reviews in the Workshop Room";
    saturday_events[2] = "Robot Competition Introduction";
    saturday_events[3] = "Lunch";
    saturday_events[4] = "Code Reviews in the Workshop Room";
    saturday_events[5] = "Robot Competition Matches";
    saturday_events[6] = "Dinner";
    saturday_events[7] = "Ice Cream Sandwhich Bar by Cream";
    saturday_events[8] = "End of Day 3";
    
    saturday_times[0] = "9:30";
    saturday_times[1] = "10:00";
    saturday_times[2] = "10:30";
    saturday_times[3] = "12:00";
    saturday_times[4] = "14:00";
    saturday_times[5] = "16:00";
    saturday_times[6] = "18:00";
    saturday_times[7] = "20:00";
    saturday_times[8] = "22:00";
    
    // Sunday
    sunday_events[0] = "Start of Day 4";
    sunday_events[1] = "Brunch";
    sunday_events[2] = "Developer Showcase";
    sunday_events[3] = "Awards Ceremony";
    sunday_events[4] = "Final Words";
    sunday_events[5] = "Official End of Retreat";
    
    sunday_times[0] = "9:30";
    sunday_times[1] = "11:30";
    sunday_times[2] = "12:30";
    sunday_times[3] = "14:00";
    sunday_times[4] = "14:30";
    sunday_times[5] = "15:30";

}

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
    return 5;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    if (section_index == 0) {
        return 1;
    } else if (section_index == 1) {
        return 12;
    } else if (section_index == 2) {
        return 14;
    } else if (section_index == 3) {
        return 9;
    } else {
        return 6;
    }
}

static int16_t menu_layer_get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
    if (cell_index->section == 0) {
        return 98;
    } else {
        return 44;
    }
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    if (section_index == 0) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Location/Contact");
    } else if (section_index == 1) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Thursday 2");
    } else if (section_index == 2) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Friday 3");
    } else if (section_index == 3) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Saturday 4");
    } else if (section_index == 4) {
        menu_cell_basic_header_draw(ctx, cell_layer, "Sunday 5");
    }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    
    graphics_context_set_text_color(ctx, GColorBlack);
  
    if (cell_index->section == 0) {
        graphics_draw_text(ctx, "Y Combinator", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(5, -4, 139, 98), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, "320 Pioneer Way\nMountain View\nCA 94041", fonts_get_system_font(FONT_KEY_GOTHIC_18), GRect(5, 20, 139, 78), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, "events@getpebble.com", fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(5, 76, 139, 22), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
    } else if (cell_index->section == 1) {
        float text_height = graphics_text_layout_get_content_size(thursday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, thursday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, thursday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    } else if (cell_index->section == 2) {
        float text_height = graphics_text_layout_get_content_size(friday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, friday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, friday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    } else if (cell_index->section == 3) {
        float text_height = graphics_text_layout_get_content_size(saturday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, 0, 100, 44), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft).h;
        graphics_draw_text(ctx, saturday_events[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_14), GRect(3, (44 / 2) - (text_height / 2) - 3, 100, text_height), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        graphics_draw_text(ctx, saturday_times[cell_index->row], fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(100, 10, 41, 20), GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
    } else if (cell_index->section == 4) {
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
    
    if (day == 2 || day == 3 || day == 4 || day == 5) {
        MenuIndex selected;
        selected.section = day - 1;

        if (day == 2) {
            for (int i = 0; i < 11; i++) {
                int event_hour = thursday_hours[i];
                if (event_hour < hour) {
                    selected.row = i;
                } else if (event_hour == hour) {
                    selected.row = i;
                    break;
                }
            }
        } else if (day == 3) {
            for (int i = 0; i < 13; i++) {
                int event_hour = friday_hours[i];
                if (event_hour < hour) {
                    selected.row = i;
                } else if (event_hour == hour) {
                    selected.row = i;
                    break;
                }
            }
        } else if (day == 4) {
            for (int i = 0; i < 8; i++) {
                int event_hour = saturday_hours[i];
                if (event_hour < hour) {
                    selected.row = i;
                } else if (event_hour == hour) {
                    selected.row = i;
                    break;
                }
            }
        } else if (day == 5) {
            for (int i = 0; i < 5; i++) {
                int event_hour = sunday_hours[i];
                if (event_hour < hour) {
                    selected.row = i;
                } else if (event_hour == hour) {
                    selected.row = i;
                    break;
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