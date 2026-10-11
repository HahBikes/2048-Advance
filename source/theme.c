#include <global.h>

#include <graphics/bg0.h>
#include <graphics/sprites.h>
#include <graphics/titlebg0.h>

#define HEX( c ) \
    ((((c) >> 19) & 31) | ((((c) >> 11) & 31) << 5) | ((((c) >> 3) & 31) << 10))

typedef struct {
    COLOR page;
    COLOR board;
    COLOR cell;

    COLOR box;
    COLOR box_aa;
    COLOR box_text;
    COLOR score_text;

    COLOR button;
    COLOR button_edge;
    COLOR button_aa;
    COLOR button_text;
    COLOR dot;
    COLOR dot_aa;
    COLOR dot_down;
    COLOR dot_down_shade;

    COLOR win_wash;
    COLOR win_text;
    COLOR win_text_edge;
    COLOR lose_wash;
    COLOR lose_text;
    COLOR lose_text_aa;

    COLOR title_bg;
    COLOR title_shadow;
    COLOR title_aa_dark;
    COLOR title_aa_light;
    COLOR title_text;

    COLOR menu_text;
    COLOR menu_dim;
    COLOR menu_select;
    COLOR menu_select_text;

    COLOR tiles[TILE_MAX][2];
} Theme;

static const Theme themes[THEME__MAX__] = {
    [THEME_CLASSIC] = {
        .page  = HEX( 0xfbf8f0 ),
        .board = HEX( 0xb9aca2 ),
        .cell  = HEX( 0xcac0b6 ),

        .box        = HEX( 0xb9aca2 ),
        .box_aa     = HEX( 0xcac0b6 ),
        .box_text   = HEX( 0xece3d9 ),
        .score_text = HEX( 0xfbf8f0 ),

        .button         = HEX( 0x8c7b68 ),
        .button_edge    = HEX( 0xb9aca2 ),
        .button_aa      = HEX( 0xcac0b6 ),
        .button_text    = HEX( 0xece3d9 ),
        .dot            = HEX( 0xfbf8f0 ),
        .dot_aa         = HEX( 0xcac0b6 ),
        .dot_down       = HEX( 0xcac0b6 ),
        .dot_down_shade = HEX( 0x5e5642 ),

        .win_wash      = HEX( 0xe0c068 ),
        .win_text      = HEX( 0xfaf2ef ),
        .win_text_edge = HEX( 0xece3d9 ),
        .lose_wash     = HEX( 0xffffff ),
        .lose_text     = HEX( 0x756866 ),
        .lose_text_aa  = HEX( 0xa0948f ),

        .title_bg       = HEX( 0xe1c26e ),
        .title_shadow   = HEX( 0xdebd65 ),
        .title_aa_dark  = HEX( 0xddcfad ),
        .title_aa_light = HEX( 0xeae1c9 ),
        .title_text     = HEX( 0xfbf8f0 ),

        .menu_text        = HEX( 0x776e65 ),
        .menu_dim         = HEX( 0x9c8f80 ),
        .menu_select      = HEX( 0x8c7b68 ),
        .menu_select_text = HEX( 0xfbf8f0 ),

        .tiles = {
            { HEX( 0xece3da ), HEX( 0x746b63 ) },
            { HEX( 0xe7dfc6 ), HEX( 0x746b63 ) },
            { HEX( 0xefad7c ), HEX( 0xf7efe7 ) },
            { HEX( 0xef9563 ), HEX( 0xf7efe7 ) },
            { HEX( 0xef7c63 ), HEX( 0xf7efe7 ) },
            { HEX( 0xef5b42 ), HEX( 0xf7efe7 ) },
            { HEX( 0xe7ce74 ), HEX( 0xf7efe7 ) },
            { HEX( 0xe7c663 ), HEX( 0xf7efe7 ) },
            { HEX( 0xe7c653 ), HEX( 0xf7efe7 ) },
            { HEX( 0xe7be53 ), HEX( 0xf7efe7 ) },
            { HEX( 0xe7be4b ), HEX( 0xf7efe7 ) },
            { HEX( 0x3c3a32 ), HEX( 0xf9f6f2 ) },
            { HEX( 0x33312b ), HEX( 0xf9f6f2 ) },
            { HEX( 0x2a2924 ), HEX( 0xf9f6f2 ) },
            { HEX( 0x1f1e1a ), HEX( 0xf9f6f2 ) },
        },
    },

    [THEME_DARK] = {
        .page  = HEX( 0x1e1d1b ),
        .board = HEX( 0x3a3732 ),
        .cell  = HEX( 0x2b2926 ),

        .box        = HEX( 0x3b3833 ),
        .box_aa     = HEX( 0x32302c ),
        .box_text   = HEX( 0xa59d91 ),
        .score_text = HEX( 0xf3eee6 ),

        .button         = HEX( 0x57524a ),
        .button_edge    = HEX( 0x6f695f ),
        .button_aa      = HEX( 0x857e73 ),
        .button_text    = HEX( 0xe6dfd3 ),
        .dot            = HEX( 0xe9c46a ),
        .dot_aa         = HEX( 0x857e73 ),
        .dot_down       = HEX( 0x3b3833 ),
        .dot_down_shade = HEX( 0x1e1d1b ),

        .win_wash      = HEX( 0xc9a227 ),
        .win_text      = HEX( 0xfff6e0 ),
        .win_text_edge = HEX( 0xc9a540 ),
        .lose_wash     = HEX( 0x000000 ),
        .lose_text     = HEX( 0xf3eee6 ),
        .lose_text_aa  = HEX( 0x8a8379 ),

        .title_bg       = HEX( 0x1e1d1b ),
        .title_shadow   = HEX( 0x121110 ),
        .title_aa_dark  = HEX( 0x615435 ),
        .title_aa_light = HEX( 0xa48b4f ),
        .title_text     = HEX( 0xe9c46a ),

        .menu_text        = HEX( 0xe6dfd3 ),
        .menu_dim         = HEX( 0x958d81 ),
        .menu_select      = HEX( 0xe9c46a ),
        .menu_select_text = HEX( 0x1e1d1b ),

        .tiles = {
            { HEX( 0x625b51 ), HEX( 0xf3eee6 ) },
            { HEX( 0x7a6c57 ), HEX( 0xf3eee6 ) },
            { HEX( 0xc4743f ), HEX( 0xfff4e8 ) },
            { HEX( 0xcd643a ), HEX( 0xfff4e8 ) },
            { HEX( 0xd25236 ), HEX( 0xfff4e8 ) },
            { HEX( 0xc93b28 ), HEX( 0xfff4e8 ) },
            { HEX( 0xc7a23e ), HEX( 0xfff8e8 ) },
            { HEX( 0xcd9d31 ), HEX( 0xfff8e8 ) },
            { HEX( 0xd29626 ), HEX( 0xfff8e8 ) },
            { HEX( 0xd88e1c ), HEX( 0xfff8e8 ) },
            { HEX( 0xe5b82a ), HEX( 0xfffaf0 ) },
            { HEX( 0x7b5fc4 ), HEX( 0xffffff ) },
            { HEX( 0x6152b5 ), HEX( 0xffffff ) },
            { HEX( 0x4659c2 ), HEX( 0xffffff ) },
            { HEX( 0x2f86c9 ), HEX( 0xffffff ) },
        },
    },

    [THEME_OCEAN] = {
        .page  = HEX( 0xeef5f9 ),
        .board = HEX( 0x8fb2c9 ),
        .cell  = HEX( 0xb4cddd ),

        .box        = HEX( 0x8fb2c9 ),
        .box_aa     = HEX( 0xa8c3d5 ),
        .box_text   = HEX( 0xe3eef5 ),
        .score_text = HEX( 0xffffff ),

        .button         = HEX( 0x4d7491 ),
        .button_edge    = HEX( 0x8fa9bc ),
        .button_aa      = HEX( 0xa7bccb ),
        .button_text    = HEX( 0xe3eef5 ),
        .dot            = HEX( 0xffffff ),
        .dot_aa         = HEX( 0xa7bccb ),
        .dot_down       = HEX( 0xb4cddd ),
        .dot_down_shade = HEX( 0x2b475c ),

        .win_wash      = HEX( 0xf6a04d ),
        .win_text      = HEX( 0xffffff ),
        .win_text_edge = HEX( 0xd8e9f3 ),
        .lose_wash     = HEX( 0xffffff ),
        .lose_text     = HEX( 0x2b475c ),
        .lose_text_aa  = HEX( 0x6d8ea6 ),

        .title_bg       = HEX( 0x4f9cc6 ),
        .title_shadow   = HEX( 0x3f88b2 ),
        .title_aa_dark  = HEX( 0x89bdd9 ),
        .title_aa_light = HEX( 0xc3ddec ),
        .title_text     = HEX( 0xffffff ),

        .menu_text        = HEX( 0x2b475c ),
        .menu_dim         = HEX( 0x6d8ea6 ),
        .menu_select      = HEX( 0x4d7491 ),
        .menu_select_text = HEX( 0xffffff ),

        .tiles = {
            { HEX( 0xe1eef6 ), HEX( 0x3d5a6e ) },
            { HEX( 0xcfe3ef ), HEX( 0x3d5a6e ) },
            { HEX( 0x8fd3e0 ), HEX( 0xffffff ) },
            { HEX( 0x5cbfd6 ), HEX( 0xffffff ) },
            { HEX( 0x3aa5c9 ), HEX( 0xffffff ) },
            { HEX( 0x2a85c0 ), HEX( 0xffffff ) },
            { HEX( 0x7fc8a9 ), HEX( 0xffffff ) },
            { HEX( 0x5bb89a ), HEX( 0xffffff ) },
            { HEX( 0x3ea58a ), HEX( 0xffffff ) },
            { HEX( 0x2b8f7a ), HEX( 0xffffff ) },
            { HEX( 0xf6a04d ), HEX( 0xffffff ) },
            { HEX( 0x3b4a8c ), HEX( 0xffffff ) },
            { HEX( 0x2f3a75 ), HEX( 0xffffff ) },
            { HEX( 0x26305f ), HEX( 0xffffff ) },
            { HEX( 0x1b2349 ), HEX( 0xffffff ) },
        },
    },

    [THEME_RETRO] = {
        .page  = HEX( 0xe0f8d0 ),
        .board = HEX( 0x346856 ),
        .cell  = HEX( 0x88c070 ),

        .box        = HEX( 0x346856 ),
        .box_aa     = HEX( 0x88c070 ),
        .box_text   = HEX( 0xe0f8d0 ),
        .score_text = HEX( 0xe0f8d0 ),

        .button         = HEX( 0x081820 ),
        .button_edge    = HEX( 0x346856 ),
        .button_aa      = HEX( 0x88c070 ),
        .button_text    = HEX( 0xe0f8d0 ),
        .dot            = HEX( 0xe0f8d0 ),
        .dot_aa         = HEX( 0x346856 ),
        .dot_down       = HEX( 0x88c070 ),
        .dot_down_shade = HEX( 0x081820 ),

        .win_wash      = HEX( 0x88c070 ),
        .win_text      = HEX( 0xe0f8d0 ),
        .win_text_edge = HEX( 0x346856 ),
        .lose_wash     = HEX( 0xe0f8d0 ),
        .lose_text     = HEX( 0x081820 ),
        .lose_text_aa  = HEX( 0x346856 ),

        .title_bg       = HEX( 0x88c070 ),
        .title_shadow   = HEX( 0x346856 ),
        .title_aa_dark  = HEX( 0x88c070 ),
        .title_aa_light = HEX( 0xe0f8d0 ),
        .title_text     = HEX( 0xe0f8d0 ),

        .menu_text        = HEX( 0x081820 ),
        .menu_dim         = HEX( 0x346856 ),
        .menu_select      = HEX( 0x346856 ),
        .menu_select_text = HEX( 0xe0f8d0 ),

        .tiles = {
            { HEX( 0xe0f8d0 ), HEX( 0x346856 ) },
            { HEX( 0xe0f8d0 ), HEX( 0x081820 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
            { HEX( 0x081820 ), HEX( 0x88c070 ) },
            { HEX( 0x081820 ), HEX( 0x88c070 ) },
            { HEX( 0x081820 ), HEX( 0x88c070 ) },
            { HEX( 0x081820 ), HEX( 0x88c070 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
            { HEX( 0x081820 ), HEX( 0xe0f8d0 ) },
        },
    },
};

static const char *theme_names[THEME__MAX__] = {
    #define x(ENUM, NAME, LABEL) [THEME_##ENUM] = LABEL,
    THEME_LIST
    #undef x
};

/*----------------------------------------------------
                    palette slots for the indicator |
                    dot of each on-screen button:   |
                    { body, top edge }             */
static const u8 button_dots[4][2] = {
    [BUTTON_START]  = { 38, 39 },
    [BUTTON_SELECT] = { 22, 23 },
    [BUTTON_B]      = { 42, 43 },
    [BUTTON_LR]     = { 26, 27 },
};

static inline
const Theme *current( void )
{
    return &themes[state.theme < THEME__MAX__ ? state.theme : THEME_CLASSIC];
}

const char *theme_name( int theme )
{
    return theme_names[theme];
}

COLOR theme_page( void )
{
    return current()->page;
}

COLOR theme_win_wash( void )
{
    return current()->win_wash;
}

COLOR theme_lose_wash( void )
{
    return current()->lose_wash;
}

void theme_game_palettes( COLOR *bg, COLOR *obj )
{
    const Theme *t = current();

    memcpy16( bg, bg0Pal, 256 );

    bg[0]  = t->page;
    bg[1]  = t->button;
    bg[2]  = t->board;
    bg[3]  = t->cell;
    bg[4]  = t->cell;
    bg[5]  = t->page;
    bg[8]  = t->box;
    bg[9]  = t->box_aa;
    bg[10] = t->box_text;
    bg[11] = t->lose_wash;
    bg[15] = t->score_text;

    /*-----------------------------------------
                 banks 1 and 2 hold the same |
                 button colours; only their  |
                 indicator dots differ      */
    for (int bank = 16; bank <= 32; bank += 16)
    {
        bg[bank + 1]  = t->button;
        bg[bank + 2]  = t->button_edge;
        bg[bank + 3]  = t->button_aa;
        bg[bank + 4]  = t->button_text;
        bg[bank + 5]  = t->page;
        bg[bank + 6]  = t->dot;
        bg[bank + 7]  = t->dot;
        bg[bank + 8]  = t->dot_aa;
        bg[bank + 10] = t->dot;
        bg[bank + 11] = t->dot;
    }

    bg[48 + UI_PANEL]       = t->page;
    bg[48 + UI_EDGE]        = t->board;
    bg[48 + UI_TEXT]        = t->menu_text;
    bg[48 + UI_DIM]         = t->menu_dim;
    bg[48 + UI_SELECT]      = t->menu_select;
    bg[48 + UI_SELECT_TEXT] = t->menu_select_text;
    bg[48 + UI_STAT]        = t->score_text;
    bg[48 + UI_BUTTON_TEXT] = t->button_text;

    memcpy16( obj, spritesPal, 256 );

    /*-----------------------------------------
                tile faces: 2..128 in bank 0 |
                256..2048 in bank 1, 4096+   |
                in bank 3 (see game.c)      */
    for (int value = 1; value <= TILE_MAX; ++value)
    {
        int slot = value <= 7  ? (value << 1) - 1
                 : value <= 11 ? 16 + 7 + ((value - 8) << 1)
                 : 48 + 1 + ((value - 12) << 1);

        obj[slot]     = t->tiles[value - 1][0];
        obj[slot + 1] = t->tiles[value - 1][1];
    }

    /*-----------------------------------------
                  bank 1 entries 1..4 are the |
                  spawn fade, blended from    |
                  the empty cell colour in    |
                  bank 2 entries 1..4        */
    for (int i = 1; i <= 4; ++i)
    {
        obj[16 + i] = t->cell;
        obj[32 + i] = t->cell;
    }

    obj[42] = t->page;
    obj[43] = t->win_text_edge;
    obj[44] = t->win_text;
    obj[45] = t->lose_text;
    obj[46] = t->lose_text_aa;
    obj[47] = t->lose_text;
}

void theme_title_palette( COLOR *bg )
{
    const Theme *t = current();

    memcpy16( bg, titlebg0Pal, 256 );

    bg[0] = t->title_bg;
    bg[1] = t->title_shadow;
    bg[2] = t->title_bg;
    bg[3] = t->title_aa_dark;
    bg[4] = t->title_aa_light;
    bg[5] = t->title_text;
}

void apply_theme( void )
{
    theme_game_palettes( pal_bg_mem, pal_obj_mem );
}

void press_button( Buttons button, bool down )
{
    const Theme *t = current();

    pal_bg_mem[button_dots[button][0]] = down ? t->dot_down       : t->dot;
    pal_bg_mem[button_dots[button][1]] = down ? t->dot_down_shade : t->dot;
}
