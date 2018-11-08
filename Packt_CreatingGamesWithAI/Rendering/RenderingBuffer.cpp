//
//  RenderingBuffer.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 25/02/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "RenderingBuffer.hpp"

RenderingBuffer::RenderingBuffer()
{
    backGroundColor.r = 0xFF;
    backGroundColor.g = 0xFF;
    backGroundColor.b = 0xFF;
    backGroundColor.a = 0xFF;
}

RenderingBuffer::~RenderingBuffer()
{
    clear();
}

void RenderingBuffer::clear()
{
    textureList.clear();
}
