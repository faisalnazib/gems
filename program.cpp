#include "splashkit.h"
#include "power_up.h"
#include "player.h"

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
    load_bitmap("fuel","fuel.png");
    load_bitmap("level","level.png");
    load_bitmap("pluto","pluto.png");
    load_bitmap("nos","nos.png");
    load_bitmap("coin","coin.png");
    load_bitmap("full","full.png");
}

drawing_options opts(){
    drawing_options ops =  option_to_screen();
    ops =  option_scale_bmp(0.5, 0.5, ops);
    ops = option_rotate_bmp(0, ops);
    return ops;
}

/*drawing_options draw_part(double pct){
    drawing_options ops = option_to_screen();
    ops = option_part_bmp(0, 0, 0.25, 1, ops);
    return ops;
}
*/
/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 800, 800);
    load_resources();

    int score = 0;
    bitmap fuel = bitmap_named("fuel");
    bitmap level = bitmap_named("level");
    bitmap nos = bitmap_named("nos");
    bitmap pluto = bitmap_named("pluto");
    bitmap coin = bitmap_named("coin");
    bitmap full = bitmap_named("full");

    player_data player;
    player = new_player();

    power_up_data power_up;
    power_up = new_power_up(200, 300);


    while ( not quit_requested() )
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(player);

        // Perform movement and update the camera
        update_player(player);

        // Redraw everything
        clear_screen(COLOR_BLACK);

        fill_rectangle(COLOR_BROWN, 0, 0, screen_width(), 220, option_to_screen());

        score++;
        draw_text("SCORE: " + to_string(score), COLOR_WHITE, 92, 60, option_to_screen());
        draw_text("LOCATION: " + point_to_string(center_point(player.player_sprite)), COLOR_WHITE, 92, 120, option_to_screen());
        draw_bitmap(level, 12, 12, opts());
        draw_bitmap(nos, 360, 72, opts());
        draw_bitmap(coin, 12, 72, opts());
        draw_bitmap(pluto, 12, 132, opts());
        draw_bitmap(fuel, 360, 12, opts());
        draw_bitmap(full, 460, 12, option_part_bmp(0, 0, 1.0, 1.0));

        update_power_up(power_up);
        draw_power_up(power_up);

        // as well as the player who can move
        draw_player(player);

        refresh_screen(60);
    }

    return 0;
}