
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
  CXX = g++
endif
CXX_LINK = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0 

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS =
else
  ifeq ("$(shell uname)", "Linux")
  LDFLAGS = `sdl-config --libs` -lSDL_ttf -lexpat -lSDL_image -lSDL_mixer
  endif
endif

OBJS = \
	main.o \
	manager.o \
	gamedata.o \
	parseXML.o \
	clock.o \
	vector2f.o \
	sprite.o \
	frame.o \
	spriteFactory.o \
	multiSpriteFactory.o \
	ioManager.o \
	world.o \
	viewport.o \
	multiSprite.o \
	gui.o \
	startMenu.o \
	deadMenu.o \
	charMenu.o \
    character.o \
    player.o \
    enemy.o \
	aaline.o \
	collisionStrategy.o \
    characterManager.o \
	hud.o \
	sound.o \
    grid.o \
    cell.o \
    explodingSprite.o \
	explosion.o \
	explosionFactory.o \
	projectile.o

EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX_LINK) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp
manager.o: manager.cpp manager.h ioManager.h sprite.h clock.h viewport.h world.h player.h enemy.h characterManager.h sound.h
ioManager.o: ioManager.cpp ioManager.h
parseXML.o: parseXML.cpp parseXML.h
gamedata.o: gamedata.cpp gamedata.h parseXML.h
spriteFactory.o: spriteFactory.cpp spriteFactory.h factory.h frame.h
multiSpriteFactory.o: multiSpriteFactory.cpp multiSpriteFactory.h \
	factory.h frame.h
clock.o: clock.cpp clock.h
vector2f.o: vector2f.cpp vector2f.h
frame.o: frame.cpp frame.h
sprite.o: sprite.cpp sprite.h drawable.h frame.h
multiSprite.o: multiSprite.cpp multiSprite.h sprite.h
gui.o: gui.cpp gui.h
startMenu.o: startMenu.cpp startMenu.h gui.h
deadMenu.o: deadMenu.cpp deadMenu.h
charMenu.o: charMenu.cpp charMenu.h gui.h
frame.o: frame.cpp frame.h ioManager.h
SpriteCollection.o: SpriteCollection.cpp SpriteCollection.h frame.h sprite.h gamedata.h vector2f.h ioManager.h multiSprite.h
viewport.o: viewport.cpp viewport.h sprite.h gamedata.h ioManager.h
world.o: world.cpp world.h frame.h gamedata.h viewport.h
pokemon.o: pokemon.cpp pokemon.h multiSprite.h explodingSprite.h vector2f.h CollisionDetector.h projectile.h viewport.h
hud.o: hud.cpp hud.h clock.h gamedata.h ioManager.h aaline.h
explodingSprite.o: explodingSprite.cpp explodingSprite.h sprite.h \
	ioManager.h explosion.h
explosion.o: explosion.cpp explosion.h sprite.h gamedata.h
explosionFactory.o: explosionFactory.cpp explosionFactory.h \
	factory.h frame.h
character.o: character.cpp character.h multiSprite.h gamedata.h
player.o: player.cpp player.h character.h multiSprite.h clock.h projectile.h
enemy.o: enemy.cpp enemy.h character.h multiSprite.h vector2f.h
aaline.o: aaline.cpp aaline.h
collisionStrategy.o: collisionStrategy.cpp collisionStrategy.h sprite.h ioManager.h multiSprite.h
characterManager.o: characterManager.cpp characterManager.h enemy.h player.h vector2f.h projectile.h explodingSprite.h
hud.o: hud.cpp hud.h ioManager.h clock.h spriteFactory.h characterManager.h player.h viewport.h
path.o: path.cpp path.h vector2f.h
sound.o: sound.cpp sound.h
grid.o: grid.cpp grid.h gamedata.h cell.h
cell.o: cell.cpp cell.h
explodingSprite.o: explodingSprite.cpp explodingSprite.h sprite.h \
	ioManager.h explosion.h
explosion.o: explosion.cpp explosion.h sprite.h gamedata.h
explosionFactory.o: explosionFactory.cpp explosionFactory.h \
	factory.h frame.h
projectile.o: projectile.cpp projectile.h multiSprite.h vector2f.h gamedata.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
	rm -rf *~
