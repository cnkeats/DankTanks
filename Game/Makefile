#LIBS=-lsfml-graphics -lsfml-window -lsfml-system
LIBS=~/Workspace/sfml-pi/build/lib/libsfml-graphics.so ~/Workspace/sfml-pi/build/lib/libsfml-window.so ~/Workspace/sfml-pi/build/lib/libsfml-system.so
CXX := g++

all: Tanks

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.h
	$(CXX) -c $< -o $@

Tanks: main.o Globals.o Application.o MainMenu.o TileMap.o Player.o Projectile.o Projectile_AirSplitBomb.o Projectile_BinaryTree.o Projectile_Bridge.o Projectile_ImpactSplitBomb.o Projectile_Teleport.o Projectile_Tunnel.o
	$(CXX) -o Tanks main.o Globals.o Application.o MainMenu.o TileMap.o Player.o Projectile.o Projectile_AirSplitBomb.o Projectile_BinaryTree.o Projectile_Bridge.o Projectile_ImpactSplitBomb.o Projectile_Teleport.o Projectile_Tunnel.o $(LIBS)

clean:
	$(RM) Tanks *.o

install:
	cp Tanks /usr/local/bin

uninstall:
	$(RM) /usr/local/bin/Tanks

