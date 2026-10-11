#include <global.h>

#define MENU_W       (128)
#define MENU_H       (106)
#define MENU_X       (118 - (MENU_W >> 1))
#define MENU_Y       (80 - (MENU_H >> 1))
#define MENU_ITEM_Y  (MENU_Y + 28)
#define MENU_ITEM_H  (14)

typedef enum {
    ITEM_RESUME,
    ITEM_NEW_GAME,
    ITEM_THEME,
    ITEM_SOUND,
    ITEM_RESET_BEST,
    ITEM__MAX__,
} Menu_Items;

static const char *item_labels[ITEM__MAX__] = {
    [ITEM_RESUME]     = "RESUME",
    [ITEM_NEW_GAME]   = "NEW GAME",
    [ITEM_THEME]      = "THEME",
    [ITEM_SOUND]      = "SOUND",
    [ITEM_RESET_BEST] = "RESET BEST",
};

static int cursor = 0;
static bool confirm_reset = false;

static
void draw_item( int item )
{
    int y = MENU_ITEM_Y + item * MENU_ITEM_H;
    bool selected = item == cursor;
    int text_clr = selected ? UI_SELECT_TEXT : UI_TEXT;

    ui_fill( MENU_X + 4, y - 3, MENU_W - 8, MENU_ITEM_H, UI_PANEL );

    if (selected) {
        ui_fill( MENU_X + 7, y - 3, MENU_W - 14, MENU_ITEM_H, UI_SELECT );
        ui_fill( MENU_X + 6, y - 2, MENU_W - 12, MENU_ITEM_H - 2, UI_SELECT );
    }

    const char *label = item_labels[item];

    if (item == ITEM_RESET_BEST && confirm_reset)
        label = "SURE? PRESS A";

    ui_text( MENU_X + 12, y, label, FONT_BOLD, text_clr );

    const char *value = NULL;

    if (item == ITEM_THEME) value = theme_name( state.theme );
    if (item == ITEM_SOUND) value = state.sound ? "ON" : "OFF";

    if (!value)
        return;

    int right = MENU_X + MENU_W - 12;
    int width = ui_text_width( value, FONT_BOLD );
    int value_clr = selected ? UI_SELECT_TEXT : UI_DIM;

    if (selected) {
        ui_text( right - 5, y, ">", FONT_BOLD, value_clr );
        right -= 9;
    }

    ui_text( right - width, y, value, FONT_BOLD, value_clr );

    if (selected)
        ui_text( right - width - 9, y, "<", FONT_BOLD, value_clr );
}

static
void draw_menu( void )
{
    ui_panel( MENU_X, MENU_Y, MENU_W, MENU_H );
    ui_text_centered( MENU_X + (MENU_W >> 1), MENU_Y + 8, "PAUSED", FONT_BOLD, UI_TEXT );
    ui_fill( MENU_X + 8, MENU_Y + 20, MENU_W - 16, 1, UI_DIM );

    for (int i = 0; i < ITEM__MAX__; ++i)
        draw_item( i );
}

static
void move_cursor( int delta )
{
    int previous = cursor;

    cursor = (cursor + delta + ITEM__MAX__) % ITEM__MAX__;
    confirm_reset = false;

    draw_item( previous );
    draw_item( cursor );

    mmEffectEx( &sfx.slide );
}

static
void change_value( int delta )
{
    if (cursor == ITEM_THEME)
    {
        state.theme = (state.theme + delta + THEME__MAX__) % THEME__MAX__;
        apply_theme();
    }
    else if (cursor == ITEM_SOUND)
    {
        state.sound = !state.sound;
        apply_sound_setting();
    }
    else return;

    save_state();
    draw_item( cursor );

    mmEffectEx( &sfx.spawn );
}

static
void close_menu( void )
{
    ui_fill( MENU_X, MENU_Y, MENU_W, MENU_H, UI_CLEAR );
    ui_undim();
}

void open_menu( void )
{
    cursor = ITEM_RESUME;
    confirm_reset = false;

    hide_toast();
    draw_menu();
    ui_dim_outside( MENU_X, MENU_Y, MENU_W, MENU_H );

    mmEffectEx( &sfx.save );
}

Menu_Result update_menu( void )
{
    if (key_hit( KEY_B | KEY_START ))
    {
        close_menu();
        return MENU_RESUME;
    }

    if (key_hit( KEY_UP ))   move_cursor( -1 );
    if (key_hit( KEY_DOWN )) move_cursor(  1 );

    if (key_hit( KEY_LEFT ))  change_value( -1 );
    if (key_hit( KEY_RIGHT )) change_value(  1 );

    if (!key_hit( KEY_A ))
        return MENU_OPEN;

    switch (cursor) {
        case ITEM_RESUME: {
            close_menu();
            return MENU_RESUME;
        }
        case ITEM_NEW_GAME: {
            close_menu();
            return MENU_NEW_GAME;
        }
        case ITEM_THEME:
        case ITEM_SOUND: {
            change_value( 1 );
        } break;

        case ITEM_RESET_BEST: {
            if (confirm_reset) {
                state.hiscore = 0;
                save_state();
                mmEffectEx( &sfx.lose );
            }
            confirm_reset = !confirm_reset;
            draw_item( cursor );
        } break;
    }

    return MENU_OPEN;
}
