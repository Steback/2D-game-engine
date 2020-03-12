#ifndef CONSTANS_H
#define CONSTANS_H

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int WINDOW_WIDTH_BORDER = WINDOW_WIDTH - 30;
const unsigned int WINDOW_HEIGHT_BORDER = WINDOW_HEIGHT - 30;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

const unsigned int NUM_LAYERS = 7;

enum LayerType {
        TILEMAP_LAYER= 0,
        VEGETATION_LAYER = 1,
        ENEMY_LAYER = 2,
        PLAYER_LAYER = 3,
        PROJECTILE_LAYER = 4,
        UI_LAYER = 5,
        OBSTACLE_LAYER = 6
};

enum CollisionType {
    NO_COLLISION,
    PLAYER_ENEMY_COLLISION,
    PLAYER_PROJECTILE_COLLISION,
    ENEMY_PROJECTILE_COLLISION,
    PLAYER_VEGETATION_COLLIDER,
    PLAYER_LEVEL_COMPLETE_COLLISION
};

#endif