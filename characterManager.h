#include "enemy.h"
#include "player.h"
#include "collisionStrategy.h"
#include "grid.h"
#include "projectile.h"
#include "explodingSprite.h"
#include <list>

class CharacterManager{
    public:
        static CharacterManager& getInstance();
        ~CharacterManager();

        void draw();
        void update(Uint32);

        //modifiers
        void registerPlayer(Player *p) 
            { player = p; }
        void newProjectile(const string &name, const Vector2f &pos, int dir)
            { projectiles.push_back(new Projectile(name, pos, dir)); }

        //getters
        Player* getPlayer() const
            { return player; }
        const Cell& getPlayerCell() const
            { return player->getGridCell(); }
    private:
        std::list<Enemy *> monsters;
        std::list<Enemy *> dieing;
        std::list<Enemy *> dead;
        std::list<Projectile *> projectiles;
        std::list<ExplodingSprite *> explosions;
        Player *player;
	    PerPixelCollisionStrategy collisionCheck;
        Grid &gameGrid;
        Cell playerCell;

	    void checkForCollisions();
        void loadXmlEnemy(const string &);
        void respawn();

        CharacterManager();
        CharacterManager(const CharacterManager&);
        CharacterManager& operator=(const CharacterManager&);
};
