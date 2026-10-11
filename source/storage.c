#include <global.h>

#define SAVE_VERSION (3)

#define SCORE_ADDR   (4)
#define HISCORE_ADDR (8)
#define MOVES_ADDR   (12)
#define FRAMES_ADDR  (16)
#define SAVED_ADDR   (20)
#define WON_ADDR     (21)
#define UNDOS_ADDR   (22)
#define THEME_ADDR   (23)
#define SOUND_ADDR   (24)
#define SQUARES_ADDR (32)
#define VERSION_ADDR (64)

static
u8 read_byte( u16 addr )
{
    return sram_mem[addr];
}

static inline
u32 read_4_bytes( u16 addr )
{
    return read_byte( addr )
         | read_byte( addr + 1 ) << 8
         | read_byte( addr + 2 ) << 16
         | read_byte( addr + 3 ) << 24;
}

static inline
void write_byte( u16 addr, u8 byte )
{
    sram_mem[addr] = byte;
}

static inline
void write_4_bytes( u16 addr, u32 bytes )
{
    write_byte( addr, bytes );
    write_byte( addr + 1, bytes >> 8 );
    write_byte( addr + 2, bytes >> 16 );
    write_byte( addr + 3, bytes >> 24 );
}

static inline
bool has_game_code( void )
{
    /* ------------------------------------------
       verify that game code "2048" is present */
    return read_byte( 0 ) == '2' &&
           read_byte( 1 ) == '0' &&
           read_byte( 2 ) == '4' &&
           read_byte( 3 ) == '8';
}

void load_state( void )
{
    state.undos = UNDO_MAX;
    state.sound = true;

    if (!has_game_code())
        return;

    /*-----------------------------------------
         older save formats only keep their   |
         hi-score (same address in all       |
         versions); everything else resets  */
    state.hiscore = read_4_bytes( HISCORE_ADDR );

    if (read_byte( VERSION_ADDR ) != SAVE_VERSION)
        return;

    state.score       = read_4_bytes( SCORE_ADDR );
    state.moves       = read_4_bytes( MOVES_ADDR );
    state.play_frames = read_4_bytes( FRAMES_ADDR );
    state.saved       = read_byte( SAVED_ADDR );
    state.won         = read_byte( WON_ADDR );
    state.undos       = read_byte( UNDOS_ADDR );
    state.theme       = read_byte( THEME_ADDR );
    state.sound       = read_byte( SOUND_ADDR );

    if (state.theme >= THEME__MAX__) state.theme = THEME_CLASSIC;
    if (state.undos > UNDO_MAX)      state.undos = UNDO_MAX;

    for (u8 i = 0; i < 16; ++i)
        state.squares[i].data = read_byte( SQUARES_ADDR + i );
}

void save_state( void )
{
    /* ------------------------------------------
                            game code - "2048" */
    write_byte( 0, '2' );
    write_byte( 1, '0' );
    write_byte( 2, '4' );
    write_byte( 3, '8' );

    write_byte( VERSION_ADDR, SAVE_VERSION );

    write_4_bytes( SCORE_ADDR,   state.score );
    write_4_bytes( HISCORE_ADDR, state.hiscore );
    write_4_bytes( MOVES_ADDR,   state.moves );
    write_4_bytes( FRAMES_ADDR,  state.play_frames );

    write_byte( SAVED_ADDR, state.saved );
    write_byte( WON_ADDR,   state.won );
    write_byte( UNDOS_ADDR, state.undos );
    write_byte( THEME_ADDR, state.theme );
    write_byte( SOUND_ADDR, state.sound );
}

void save_state_including_squares( void )
{
    save_state();

    for (u8 i = 0; i < 16; ++i)
        write_byte( SQUARES_ADDR + i, state.squares[i].data );
}
