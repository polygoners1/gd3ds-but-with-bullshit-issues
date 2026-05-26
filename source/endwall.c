#include "main.h"
#include "state.h"
#include "math_helpers.h"
#include "mp3_player.h"
#include "utils/gfx.h"
#include "wav_player.h"

#include "endwall.h"
#include "particles/rays.h"

int circles_spawned = 0;
int circunferences_spawned = 0;
float completion_timer = 0.0f;

// TODO: implement all the gfx stuff of the end wall
bool handle_wall_cutscene(float delta) {
    // Init wall variables
    if (completion_timer == 0) {
        state.completion_shake = true;
        circles_spawned = 0;
        circunferences_spawned = 0;
        
        //particle_templates[END_WALL_COLL_CIRCLE].end_scale = 400;
        //particle_templates[END_WALL_COLL_CIRCLE].life = 0.5f;
        //spawn_particle(END_WALL_COLL_CIRCLE, level_info.wall_x, level_info.wall_y, NULL);
        //spawn_particle(END_WALL_COLL_CIRCUNFERENCE, level_info.wall_x, level_info.wall_y, NULL);
        circunferences_spawned++;
        
        play_sfx(&end_sound, 1);

        rays_start();
    } else if (completion_timer <= 0.2 && circunferences_spawned < 5) {
        //spawn_particle(END_WALL_COLL_CIRCUNFERENCE, level_info.wall_x, level_info.wall_y, NULL);
        circunferences_spawned++;
    }

    // Spawn circles
    if (completion_timer > CIRCLE_SPAWN_TIME) {
        // Init circles
        if (circles_spawned == 0) {
            rays_start_fade();

            //float screen_middle_x = state.camera_x_middle;
            //float screen_middle_y = state.camera_y_middle;

            //particle_templates[END_WALL_COLL_CIRCLE].end_scale = 400;
            //particle_templates[END_WALL_COLL_CIRCLE].life = 0.5f;

            //spawn_particle(END_WALL_COLL_CIRCUNFERENCE, level_info.wall_x, level_info.wall_y, NULL); // Comes from wall
            circunferences_spawned++;

            //spawn_particle(END_WALL_COLL_CIRCLE, level_info.wall_x, level_info.wall_y, NULL); // Comes from wall
            //spawn_particle(END_WALL_COLL_CIRCLE, screen_middle_x, screen_middle_y, NULL); // Comes from complete text

            // TODO: use a particle system
            for (s32 i = 0; i < END_EFFECT_COUNT; i++) {
                //float x = random_float(screen_middle_x - 120, screen_middle_x + 120);
                //float y = random_float(screen_middle_y - 10, screen_middle_y + 10);
                //int color = random_int(0,1);
                //if (color) {
                //    set_particle_color(END_WALL_TEXT_EFFECT, p1.r, p1.g, p1.b);
                //} else {
                //    set_particle_color(END_WALL_TEXT_EFFECT, p2.r, p2.g, p2.b);
                //}

                //spawn_particle(END_WALL_TEXT_EFFECT, x, y, NULL);
            }

            circles_spawned++;
        } else {
            if (circunferences_spawned < CIRCUNFERENCE_COUNT) {
                //spawn_particle(END_WALL_COLL_CIRCUNFERENCE, level_info.wall_x, level_info.wall_y, NULL);
                circunferences_spawned++;
            }

            // Fireworks
            if (completion_timer > CIRCLE_SPAWN_TIME + (circles_spawned * CIRCLE_SPAWN_DELAY)) {
                //float x = random_float(state.camera_x, state.camera_x + WIDTH_ADJUST_AREA + SCREEN_WIDTH_AREA);
                //float y = random_float(state.camera_y, state.camera_y + SCREEN_HEIGHT_AREA);
                //spawn_particle(END_WALL_COMPLETE_CIRCLES, x, y, NULL);
                
                // TODO: use a particle system
                for (int i = 0; i < FIREWORK_COUNT; i++) {
                    //particle_templates[END_WALL_FIREWORK].angle = random_float(0, 360);
                    //spawn_particle(END_WALL_FIREWORK, x, y, NULL);
                    //spawn_particle(END_WALL_FIREWORK, x, y, NULL);
                }
                
                circles_spawned++;
            }
        }
        state.completion_shake = false;
    }

    // End the level!
    if (completion_timer > END_TIME) {
        completion_timer = 0.0f;
        stop_mp3();
        
        set_fade_status(FADE_STATUS_OUT);
        //erase_rays();
        return true;
    }

    completion_timer += delta;
    return false;
}