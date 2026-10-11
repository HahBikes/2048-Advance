#pragma once
#include <stdlib.h>
#include <string.h>

#include <tonc.h>
#include <tonc_memmap.h>
#include <tonc_types.h>
#include <tonc_video.h>
#include <tonc_oam.h>
#include <tonc_irq.h>

#include <maxmod.h>
#include <mm_types.h>

#define SCENE_LIST \
  x(FIRST, first)  \
  x(TITLE, title)  \
  x(GAME,  game)   \
  x(LOSE,  lose)   \
  x(WIN,   win)    \

#define SFX_LIST              \
  x(START,       start)       \
  x(SPAWN,       spawn)       \
  x(SLIDE,       slide)       \
  x(SMALL_MERGE, small_merge) \
  x(MERGE,       merge)       \
  x(BIG_MERGE,   big_merge)   \
  x(HUGE_MERGE,  huge_merge)  \
  x(SAVE,        save)        \
  x(LOSE,        lose)        \
  x(WIN,         win)         \

#define THEME_LIST                 \
  x(CLASSIC, classic, "CLASSIC")   \
  x(DARK,    dark,    "DARK")      \
  x(OCEAN,   ocean,   "OCEAN")     \
  x(RETRO,   retro,   "RETRO")     \

#define FIRST_FADE_DURATION (20)
#define TITLE_FADE_DURATION (15)
#define GAME_FADE_DURATION  (20)

#define ANIM_SLIDE_DURATION (5)
#define ANIM_SPAWN_DURATION (9)
#define ANIM_MERGE_DURATION (9)
#define ANIM_SCORE_DURATION (32)

#define TILE_2048     (11)
#define TILE_MAX      (15)
#define UNDO_MAX      (3)
#define UNDO_EARN_AT  (9)

#define OBJECT_IS_HIDDEN( o ) \
    (((o).attr0 & ATTR0_MODE_MASK) == ATTR0_HIDE)

typedef enum {
    SCENE_NULL = 0,
    #define x(ENUM, FUNC) SCENE_##ENUM,
    SCENE_LIST
    #undef x
    SCENE__MAX__
} Scenes;

#define x(ENUM, FUNC) void init_scene_##FUNC( void );
SCENE_LIST
#undef x

#define x(ENUM, FUNC) void update_scene_##FUNC( void );
SCENE_LIST
#undef x

typedef enum {
    #define x(ENUM, NAME, LABEL) THEME_##ENUM,
    THEME_LIST
    #undef x
    THEME__MAX__
} Themes;

typedef enum {
    BUTTON_START,
    BUTTON_SELECT,
    BUTTON_B,
    BUTTON_LR,
} Buttons;

typedef enum {
    FONT_SMALL,
    FONT_BOLD,
} Fonts;

/*---------------------------------------
                   BG palette bank 3 is |
                   reserved for the UI  |
                   layer drawn by ui.c */
typedef enum {
    UI_CLEAR = 0,
    UI_PANEL,
    UI_EDGE,
    UI_TEXT,
    UI_DIM,
    UI_SELECT,
    UI_SELECT_TEXT,
    UI_STAT,
    UI_BUTTON_TEXT,
} Ui_Colors;

typedef struct {
    int x : 16;
    int y : 16;
} Vector2_int;

typedef union {
    struct {
        u8 shift : 2;
        u8 merge : 1;
        u8 fresh : 1;
        u8 value : 4;
    };
    u8 data;
} Square;

typedef struct {
    int seed;

    Scenes scene;
    Scenes next_scene;
    Scenes last_scene;

    u32 score;
    u32 hiscore;
    u32 moves;
    u32 play_frames;

    u8 saved;
    u8 won;
    u8 undos;
    u8 theme;
    u8 sound;
    Square squares[16];
} Global_State;

typedef struct {
#define x( generated, member ) mm_sound_effect member;
    SFX_LIST
#undef x
} Global_Sfx;


extern Global_State state;
extern Global_Sfx sfx;

/*------------------------------------
                             main.c */
void set_scene( Scenes scene );
void update_scene( void );
void apply_sound_setting( void );

/*------------------------------------
                          storage.c */
void load_state( void );
void save_state( void );
void save_state_including_squares( void );

/*------------------------------------
                            score.c */
void init_score( void );
void reset_score( void );
void update_score( void );

bool score_starts_with_1( bool is_hiscore );
int get_digit_count( void );
int get_bg1_offset( void );

void hide_tally_particle( void );
void spawn_tally_particle( void );
void update_tally_particle( void );
void reset_tally( void );
void add_to_tally( u32 amount );
void add_tally_to_score( void );

/*------------------------------------
                            theme.c */
const char *theme_name( int theme );
COLOR theme_page( void );
COLOR theme_win_wash( void );
COLOR theme_lose_wash( void );
void theme_game_palettes( COLOR *bg, COLOR *obj );
void theme_title_palette( COLOR *bg );
void apply_theme( void );
void press_button( Buttons button, bool down );

/*------------------------------------
                               ui.c */
void ui_init( void );
void ui_clear( void );
void ui_fill( int x, int y, int w, int h, int clr );
void ui_panel( int x, int y, int w, int h );
void ui_text( int x, int y, const char *str, Fonts font, int clr );
void ui_text_on( int x, int y, const char *str, Fonts font, int clr, int bg );
void ui_text_centered( int cx, int y, const char *str, Fonts font, int clr );
int ui_text_width( const char *str, Fonts font );
void ui_dim_outside( int x, int y, int w, int h );
void ui_undim( void );

void show_toast( const char *line1, const char *line2, int frames );
void show_toast_at( int cy, const char *line1, const char *line2, int frames );
void hide_toast( void );
void update_toast( void );
bool toast_visible( void );

void draw_hud( void );
void update_hud( void );

/*------------------------------------
                             menu.c */
typedef enum {
    MENU_OPEN,
    MENU_RESUME,
    MENU_NEW_GAME,
} Menu_Result;

void open_menu( void );
Menu_Result update_menu( void );
