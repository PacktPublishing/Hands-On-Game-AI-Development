//
//  BattleCityCommons.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 17/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef BattleCityCommons_hpp
#define BattleCityCommons_hpp

#include "vec2.hpp"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int CELL_SIZE = 64;
const glm::ivec2 PLAYER_SPAWN_POINT( WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT - CELL_SIZE);

const float FIRE_COOL_DOWN_TIME = 0.33f;
const float MAX_TANK_SPEED = 50.f;

const float MISSILE_RESILIENCE = 5.f;
const int MISSILE_TEXTURE_WIDTH = 32;
const int MISSILE_TEXTURE_HEIGHT = 32;
const float MAX_MISSILE_SPEED = MAX_TANK_SPEED * 4.f;

const int WALL_TEXTURE_WIDTH = 32;
const int WALL_TEXTURE_HEIGHT = 32;

enum eTankColliderTypes
{
    eCT_Tank,
    eCT_Bullet,
    eCT_Wall
};

#endif /* BattleCityCommons_hpp */
