#include <global.h>

#include <graphics/youwin.h>

static int fade_timer = 0;
static int fade_ended = false;

static OBJ_ATTR obj_buffer[18];

static OBJ_ATTR *obj_you = &obj_buffer[0];
static OBJ_ATTR *obj_win = &obj_buffer[1];

void init_scene_win( void )
{
    fade_ended = false;
    fade_timer = 30;

    REG_BG1VOFS = get_digit_count() < 5 ? -3 : -4;
    REG_BG1HOFS = get_bg1_offset() + score_starts_with_1( false );

    memcpy( &tile_mem[4][256], youwinTiles, youwinTilesLen );

    /*------------------------------------------------------
                          prioritize OAM slots 0 and 1 for |
                          you win text so it's drawn in    |
                          front of the number tiles       */
    obj_copy( obj_buffer + 2, obj_mem, 16 );
    obj_you = &obj_buffer[0];
    obj_win = &obj_buffer[1];

    obj_hide( obj_you );
    obj_hide( obj_win );

    hide_toast();

    mmEffectEx( &sfx.win );

    /*------------------------------------------------------
                         the win only counts once: mark it |
                         and keep the board so the player  |
                         can carry on towards 4096 and up  */
    state.won = true;
    save_state_including_squares();
}

static
void leave_scene( void )
{
    srand( state.seed );
    obj_hide( obj_you );
    obj_hide( obj_win );
    hide_toast();

    set_scene( SCENE_GAME );
}

void update_scene_win( void )
{
    update_tally_particle();

    state.seed += rand() << 1;

    REG_BG1VOFS = get_digit_count() < 5 ? -3 : -4;
    REG_BG1HOFS = get_bg1_offset() + score_starts_with_1( false );

    if (fade_timer > 0)
    {
        int alpha = (16 - fade_timer);

        if (alpha < 0)
            alpha = 0;

        COLOR wash = theme_win_wash();

        clr_fade_fast( pal_bg_mem,       wash, pal_bg_mem,       5,  alpha );
        clr_fade_fast( pal_obj_mem,      wash, pal_obj_mem,      32, alpha );
        clr_fade_fast( &pal_obj_mem[48], wash, &pal_obj_mem[48], 16, alpha );

        --fade_timer;

        if (fade_timer == 0)
        {
            fade_ended = true;
            obj_set_attr( obj_you, ATTR0_WIDE, ATTR1_SIZE_64x32, ATTR2_PALBANK(2) | 256 );
            obj_set_attr( obj_win, ATTR0_WIDE, ATTR1_SIZE_64x32, ATTR2_PALBANK(2) | (256 + 32) );
            obj_set_pos( obj_you, 54, 69 );
            obj_set_pos( obj_win, 54 + 64, 69 );

            show_toast_at( 124, "{A} KEEP PLAYING", "{SELECT} NEW GAME", 0 );
        }
    }

    if (fade_ended)
    {
        if (key_hit( KEY_A | KEY_START ))
        {
            leave_scene();
        }
        else if (key_hit( KEY_SELECT ))
        {
            state.saved = false;
            save_state();

            memset16( pal_bg_mem,  theme_page(), 256 );
            memset16( pal_obj_mem, theme_page(), 256 );

            leave_scene();
        }
    }

    obj_copy( obj_mem, obj_buffer, 18 );
}
