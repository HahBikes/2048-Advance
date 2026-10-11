#include <global.h>

/*----------------------------------------------------------------
                        BG2 is a 240x160 4bpp canvas: every map |
                        entry points at its own tile in CBB 2,  |
                        so text and panels can be drawn to any  |
                        pixel. Colours come from BG palette     |
                        bank 3 (see Ui_Colors / theme.c)       */
#define UI_CBB      (2)
#define UI_SBB      (29)
#define UI_COLS     (30)
#define UI_ROWS     (20)

#define BOARD_CX    (118)
#define BOARD_CY    (80)

static u32 *const canvas = (u32 *)&tile_mem[UI_CBB][0];

typedef struct {
    char ch;
    const char *rows;
} Glyph;

typedef struct {
    const Glyph *glyphs;
    int count;
    int height;
} Font;

static const Glyph small_glyphs[] = {
    { ' ', "..|..|..|..|.." },
    { '0', "###|#.#|#.#|#.#|###" }, { '1', ".#.|##.|.#.|.#.|.#." },
    { '2', "###|..#|###|#..|###" }, { '3', "###|..#|###|..#|###" },
    { '4', "#.#|#.#|###|..#|..#" }, { '5', "###|#..|###|..#|###" },
    { '6', "###|#..|###|#.#|###" }, { '7', "###|..#|.#.|.#.|.#." },
    { '8', "###|#.#|###|#.#|###" }, { '9', "###|#.#|###|..#|###" },
    { ':', ".|#|.|#|." },           { '/', "..#|..#|.#.|#..|#.." },
    { '-', "...|...|###|...|..." }, { '+', "...|.#.|###|.#.|..." },
    { 'A', "###|#.#|###|#.#|#.#" }, { 'B', "###|#.#|##.|#.#|###" },
    { 'C', "###|#..|#..|#..|###" }, { 'D', "##.|#.#|#.#|#.#|##." },
    { 'E', "###|#..|###|#..|###" }, { 'F', "###|#..|###|#..|#.." },
    { 'G', "###|#..|#.#|#.#|###" }, { 'H', "#.#|#.#|###|#.#|#.#" },
    { 'I', "###|.#.|.#.|.#.|###" }, { 'J', "..#|..#|..#|#.#|###" },
    { 'K', "#.#|#.#|##.|#.#|#.#" }, { 'L', "#..|#..|#..|#..|###" },
    { 'M', "#.#|###|###|#.#|#.#" }, { 'N', "###|#.#|#.#|#.#|#.#" },
    { 'O', "###|#.#|#.#|#.#|###" }, { 'P', "###|#.#|###|#..|#.." },
    { 'Q', "###|#.#|#.#|###|..#" }, { 'R', "###|#.#|##.|#.#|#.#" },
    { 'S', "###|#..|###|..#|###" }, { 'T', "###|.#.|.#.|.#.|.#." },
    { 'U', "#.#|#.#|#.#|#.#|###" }, { 'V', "#.#|#.#|#.#|#.#|.#." },
    { 'W', "#.#|#.#|###|###|#.#" }, { 'X', "#.#|#.#|.#.|#.#|#.#" },
    { 'Y', "#.#|#.#|###|.#.|.#." }, { 'Z', "###|..#|.#.|#..|###" },
};

static const Glyph bold_glyphs[] = {
    { ' ', "...|...|...|...|...|...|...|..." },
    { '0', ".###.|#####|##.##|##.##|##.##|##.##|#####|.###." },
    { '1', "...##|..###|.####|...##|...##|...##|...##|...##" },
    { '2', ".###.|#####|##.##|..###|.###.|###..|#####|#####" },
    { '3', "####.|#####|...##|.###.|.####|...##|#####|####." },
    { '4', "##.##|##.##|##.##|#####|#####|...##|...##|...##" },
    { '5', "#####|#####|##...|####.|#####|...##|#####|####." },
    { '6', ".####|#####|##...|####.|#####|##.##|#####|.###." },
    { '7', "#####|#####|...##|..##.|..##.|.##..|.##..|.##.." },
    { '8', ".###.|#####|##.##|.###.|#####|##.##|#####|.###." },
    { '9', ".###.|#####|##.##|#####|.####|...##|#####|####." },
    { ':', "..|##|##|..|..|##|##|.." },
    { '.', "..|..|..|..|..|..|##|##" },
    { '!', "##|##|##|##|##|..|##|##" },
    { '?', ".###.|#####|##.##|..###|.###.|.##..|.....|.##.." },
    { '-', "....|....|....|####|####|....|....|...." },
    { '+', "......|..##..|..##..|######|######|..##..|..##..|......" },
    { '/', "...##|...##|..##.|..##.|.##..|.##..|##...|##..." },
    { '<', "...##|..###|.###.|###..|###..|.###.|..###|...##" },
    { '>', "##...|###..|.###.|..###|..###|.###.|###..|##..." },
    { 'A', ".###.|#####|##.##|#####|#####|##.##|##.##|##.##" },
    { 'B', "####.|#####|##.##|####.|#####|##.##|#####|####." },
    { 'C', ".####|#####|##...|##...|##...|##...|#####|.####" },
    { 'D', "####.|#####|##.##|##.##|##.##|##.##|#####|####." },
    { 'E', "#####|#####|##...|####.|####.|##...|#####|#####" },
    { 'F', "#####|#####|##...|####.|####.|##...|##...|##..." },
    { 'G', ".####|#####|##...|##.##|##.##|##.##|#####|.###." },
    { 'H', "##.##|##.##|##.##|#####|#####|##.##|##.##|##.##" },
    { 'I', "####|####|.##.|.##.|.##.|.##.|####|####" },
    { 'J', "...##|...##|...##|...##|...##|##.##|#####|.###." },
    { 'K', "##.##|##.##|####.|###..|####.|##.##|##.##|##.##" },
    { 'L', "##...|##...|##...|##...|##...|##...|#####|#####" },
    { 'M', "###..###|########|########|##.##.##|##.##.##|##.##.##|##....##|##....##" },
    { 'N', "##..##|###.##|###.##|######|######|##.###|##.###|##..##" },
    { 'O', ".###.|#####|##.##|##.##|##.##|##.##|#####|.###." },
    { 'P', "####.|#####|##.##|#####|####.|##...|##...|##..." },
    { 'Q', ".###.|#####|##.##|##.##|##.##|#####|.####|...##" },
    { 'R', "####.|#####|##.##|####.|#####|##.##|##.##|##.##" },
    { 'S', ".####.|######|###.##|.###..|..###.|##.###|######|.####." },
    { 'T', "######|######|..##..|..##..|..##..|..##..|..##..|..##.." },
    { 'U', "##.##|##.##|##.##|##.##|##.##|##.##|#####|.###." },
    { 'V', "##.##|##.##|##.##|##.##|##.##|#####|.###.|..#.." },
    { 'W', "##....##|##....##|##.##.##|##.##.##|##.##.##|########|########|.##..##." },
    { 'X', "##.##|##.##|#####|.###.|.###.|#####|##.##|##.##" },
    { 'Y', "###.##|###.##|###.##|######|.####.|..##..|..##..|..##.." },
    { 'Z', "#####|#####|...##|..###|.###.|###..|#####|#####" },
};

static const Font fonts[] = {
    [FONT_SMALL] = { small_glyphs, sizeof( small_glyphs ) / sizeof( Glyph ), 5 },
    [FONT_BOLD]  = { bold_glyphs,  sizeof( bold_glyphs )  / sizeof( Glyph ), 8 },
};

static struct {
    bool visible;
    int timer;
    int x, y, w, h;
} toast;

static struct {
    u32 moves;
    u32 seconds;
    int undos;
} hud;

static inline
void plot( int x, int y, int clr )
{
    if ((unsigned)x >= SCREEN_WIDTH || (unsigned)y >= SCREEN_HEIGHT)
        return;

    u32 *row = &canvas[((y >> 3) * UI_COLS + (x >> 3)) * 8 + (y & 7)];
    int shift = (x & 7) << 2;

    *row = (*row & ~(0xFu << shift)) | ((u32)clr << shift);
}

static
const Glyph *find_glyph( const Font *font, char ch )
{
    if (ch >= 'a' && ch <= 'z')
        ch -= 'a' - 'A';

    for (int i = 0; i < font->count; ++i)
        if (font->glyphs[i].ch == ch)
            return &font->glyphs[i];

    return &font->glyphs[0];
}

static
int glyph_width( const Glyph *glyph )
{
    int width = 0;

    while (glyph->rows[width] && glyph->rows[width] != '|')
        ++width;

    return width;
}

void ui_init( void )
{
    for (int y = 0; y < 32; ++y)
    for (int x = 0; x < 32; ++x)
    {
        int tile = (y < UI_ROWS && x < UI_COLS) ? y * UI_COLS + x : 0;
        se_mem[UI_SBB][(y << 5) + x] = SE_PALBANK( 3 ) | tile;
    }

    ui_clear();

    REG_BG2HOFS = 0;
    REG_BG2VOFS = 0;
    REG_BG2CNT  = BG_CBB( UI_CBB ) | BG_SBB( UI_SBB ) | BG_4BPP | BG_REG_32x32 | BG_PRIO( 0 );

    ui_undim();

    toast.visible = false;
}

void ui_clear( void )
{
    memset32( canvas, 0, UI_COLS * UI_ROWS * 8 );
}

void ui_fill( int x, int y, int w, int h, int clr )
{
    int x1 = x + w;
    int y1 = y + h;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x1 > SCREEN_WIDTH)  x1 = SCREEN_WIDTH;
    if (y1 > SCREEN_HEIGHT) y1 = SCREEN_HEIGHT;

    u32 pattern = (u32)clr * 0x11111111;

    for (int py = y; py < y1; ++py)
    {
        int px = x;

        while (px < x1)
        {
            int start = px & 7;
            int count = 8 - start;

            if (count > x1 - px)
                count = x1 - px;

            u32 mask = count == 8 ? 0xFFFFFFFF : ((1u << (count << 2)) - 1) << (start << 2);
            u32 *row = &canvas[((py >> 3) * UI_COLS + (px >> 3)) * 8 + (py & 7)];

            *row = (*row & ~mask) | (pattern & mask);
            px += count;
        }
    }
}

void ui_panel( int x, int y, int w, int h )
{
    ui_fill( x + 1, y,     w - 2, h,     UI_EDGE );
    ui_fill( x,     y + 1, w,     h - 2, UI_EDGE );
    ui_fill( x + 2, y + 1, w - 4, h - 2, UI_PANEL );
    ui_fill( x + 1, y + 2, w - 2, h - 4, UI_PANEL );
}

int ui_text_width( const char *str, Fonts font )
{
    int width = 0;

    for (; *str; ++str)
    {
        const Glyph *glyph = find_glyph( &fonts[font], *str );
        width += glyph_width( glyph ) + 1;
    }

    return width > 0 ? width - 1 : 0;
}

void ui_text( int x, int y, const char *str, Fonts font, int clr )
{
    for (; *str; ++str)
    {
        const Glyph *glyph = find_glyph( &fonts[font], *str );
        int col = 0;
        int row = 0;

        for (const char *p = glyph->rows; *p; ++p)
        {
            if (*p == '|') {
                ++row;
                col = 0;
                continue;
            }

            if (*p == '#')
                plot( x + col, y + row, clr );

            ++col;
        }

        x += glyph_width( glyph ) + 1;
    }
}

void ui_text_centered( int cx, int y, const char *str, Fonts font, int clr )
{
    int width = ui_text_width( str, font );
    ui_text( cx - (width >> 1), y, str, font, clr );
}

/*----------------------------------------------------
                    darken everything except a box |
                    using window 0 and brightness  |
                    blending                      */
void ui_dim_outside( int x, int y, int w, int h )
{
    REG_WIN0H   = (x << 8) | (x + w);
    REG_WIN0V   = (y << 8) | (y + h);
    REG_WININ   = WIN_ALL;
    REG_WINOUT  = WIN_ALL | WIN_BLD;
    REG_BLDCNT  = BLD_ALL | BLD_BACKDROP | BLD_BLACK;
    REG_BLDY    = 9;
    REG_DISPCNT |= DCNT_WIN0;
}

void ui_undim( void )
{
    REG_DISPCNT &= ~DCNT_WIN0;
    REG_BLDCNT = 0;
    REG_BLDY   = 0;
}

void show_toast( const char *line1, const char *line2, int frames )
{
    show_toast_at( BOARD_CY, line1, line2, frames );
}

void show_toast_at( int cy, const char *line1, const char *line2, int frames )
{
    hide_toast();

    int width = ui_text_width( line1, FONT_BOLD );

    if (line2) {
        int width2 = ui_text_width( line2, FONT_BOLD );

        if (width2 > width)
            width = width2;
    }

    toast.w = width + 16;
    toast.h = line2 ? 32 : 18;
    toast.x = BOARD_CX - (toast.w >> 1);
    toast.y = cy - (toast.h >> 1);

    ui_panel( toast.x, toast.y, toast.w, toast.h );
    ui_text_centered( BOARD_CX, toast.y + 5, line1, FONT_BOLD, UI_TEXT );

    if (line2)
        ui_text_centered( BOARD_CX, toast.y + 19, line2, FONT_BOLD, UI_DIM );

    toast.timer = frames;
    toast.visible = true;
}

void hide_toast( void )
{
    if (!toast.visible)
        return;

    ui_fill( toast.x, toast.y, toast.w, toast.h, UI_CLEAR );
    toast.visible = false;
}

void update_toast( void )
{
    if (!toast.visible || toast.timer <= 0)
        return;

    if (--toast.timer == 0)
        hide_toast();
}

bool toast_visible( void )
{
    return toast.visible;
}

/*----------------------------------------------------
                                 left column stats |
                                 (art in bg0.png) */
#define HUD_X        (4)
#define HUD_W        (32)
#define HUD_MOVES_Y  (20)
#define HUD_TIME_Y   (52)
#define HUD_UNDO_X   (28)
#define HUD_UNDO_Y   (112)

static
char *format_u32( char *end, u32 value )
{
    *end = '\0';

    do {
        *--end = '0' + value % 10;
        value /= 10;
    } while (value);

    return end;
}

static
char *format_2_digits( char *end, u32 value )
{
    *--end = '0' + value % 10;
    *--end = '0' + value / 10 % 10;
    return end;
}

static
void draw_stat( int y, const char *text )
{
    ui_fill( HUD_X + 2, y, HUD_W - 4, 8, UI_CLEAR );

    Fonts font = ui_text_width( text, FONT_BOLD ) <= HUD_W - 4 ? FONT_BOLD : FONT_SMALL;
    int text_y = font == FONT_BOLD ? y : y + 2;

    ui_text_centered( HUD_X + (HUD_W >> 1), text_y, text, font, UI_STAT );
}

static
void draw_moves( void )
{
    char buffer[12];
    char *text = format_u32( &buffer[11], state.moves );

    draw_stat( HUD_MOVES_Y, text );
}

static
void draw_time( void )
{
    char buffer[16];
    char *end = &buffer[15];
    u32 seconds = hud.seconds;

    *end = '\0';
    end = format_2_digits( end, seconds % 60 );
    *--end = ':';

    if (seconds < 3600) {
        char minutes[4];
        char *text = format_u32( &minutes[3], seconds / 60 );
        int length = &minutes[3] - text;

        end -= length;
        memcpy( end, text, length );
    }
    else {
        end = format_2_digits( end, seconds / 60 % 60 );
        *--end = ':';

        char hours[8];
        char *text = format_u32( &hours[7], seconds / 3600 );
        int length = &hours[7] - text;

        end -= length;
        memcpy( end, text, length );
    }

    draw_stat( HUD_TIME_Y, end );
}

static
void draw_undos( void )
{
    char buffer[4];
    char *text = format_u32( &buffer[3], state.undos );

    ui_fill( HUD_UNDO_X, HUD_UNDO_Y, 4, 5, UI_CLEAR );
    ui_text( HUD_UNDO_X, HUD_UNDO_Y, text, FONT_SMALL, UI_BUTTON_TEXT );
}

void draw_hud( void )
{
    hud.moves   = state.moves;
    hud.seconds = state.play_frames / 60;
    hud.undos   = state.undos;

    draw_moves();
    draw_time();
    draw_undos();
}

void update_hud( void )
{
    u32 seconds = state.play_frames / 60;

    if (hud.moves != state.moves) {
        hud.moves = state.moves;
        draw_moves();
    }

    if (hud.seconds != seconds) {
        hud.seconds = seconds;
        draw_time();
    }

    if (hud.undos != state.undos) {
        hud.undos = state.undos;
        draw_undos();
    }
}
