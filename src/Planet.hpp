#ifndef PLANET_H_DEFINED
#define PLANET_H_DEFINED

#include "SDL.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "DamageableObject.hpp"


class Planet: public GameObject,
              public DamageableObject
{
public:
    Planet(Sprite* sprite, float hp, float x, float y, int w, int h);
    virtual ~Planet() {};

	/// Shows planet onscreen according to it's #x and #y
	void render(float cameraX, float cameraY);

    virtual void update(uint32_t dt) = 0;

protected:
	Sprite* sprite;	 ///< Appearance.
};

#endif /* PLANET_H_DEFINED */
