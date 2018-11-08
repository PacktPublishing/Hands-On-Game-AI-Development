//
//  PLG_Commons.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 21/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_Commons_hpp
#define PLG_Commons_hpp

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 1024;
const int CELL_SIZE = 128;

const int WALL_TEXTURE_WIDTH = 64;
const int WALL_TEXTURE_HEIGHT = 64;
const int CIRCLE_TEXTURE_WIDTH = 64;
const int CIRCLE_TEXTURE_HEIGHT = 64;
const int KEY_TEXTURE_WIDTH = 64;
const int KEY_TEXTURE_HEIGHT = 64;
const int ALARM_TEXTURE_WIDTH = 64;
const int ALARM_TEXTURE_HEIGHT = 64;

enum ePLG_COLLIDER_TYPES{ WALL, PLAYER, ENEMY, KEY, ALARM };

const float CIRCLE_CHARACTER_SPEED = 40.f;

const float ALARM_POS_X = 896.f;
const float ALARM_POS_Y = 512.f;
const float KEY_POS_X = 480.f;
const float KEY_POS_Y = 544.f;
const float PLAYER_POS_X = 64.f;
const float PLAYER_POS_Y = 448.f;

#endif /* PLG_Commons_hpp */
