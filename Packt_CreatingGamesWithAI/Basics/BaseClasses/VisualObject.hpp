//
//  VisualObject.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 14/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef VisualObject_hpp
#define VisualObject_hpp

#include "GameObject.hpp"
#include "Texture.hpp"

#include "Collider.hpp"

class VisualObject : public GameObject
{
public:
    
    VisualObject();
    VisualObject(const std::string& pPath);
    VisualObject(const int pZOrder, const std::string& pPath);
    VisualObject(const int pScreenX, const int pScreenY, const std::string& pPath);
    VisualObject(const int pScreenX, const int pScreenY, const int pZOrder, const std::string& pPath);
    virtual ~VisualObject();
    
    void init(
                  const int pScreenX, const int pScreenY,
                  const int pZOrder, const float pRotationDegree,
                  const std::string& pPath
              );
    
    Texture* getTexture();

    void setPosition(const glm::vec2& pos);
    glm::vec2 getPosition() const;
    
    float getWidth() const;
    float getHeight() const;
    
    virtual void OnCollision(const LegacyCollider* obj )
    {

    }
    
    
protected:

    glm::vec2 mPosition;
    std::unique_ptr<Texture> mTexture;
    
};

#endif /* VisualObject_hpp */
