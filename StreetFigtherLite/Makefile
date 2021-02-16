CORE = core/Jeu.cpp core/Personnage.cpp core/Vec2.cpp core/Projectile.cpp

SRCS_TXT = $(CORE) txt/txtJeu.cpp txt/winTxt.cpp txt/main_txt.cpp

SRCS_SFML = $(CORE) sfml/sfmlJeu.cpp sfml/sfmlPersonnage.cpp \
			sfml/sfmlTerrain.cpp sfml/sfmlProjectile.cpp sfml/Ryu.cpp \
			sfml/Ken.cpp sfml/sfmlMenu.cpp sfml/sfml_main.cpp

FINAL_TARGET_TXT = executable_txt
FINAL_TARGET_SFML = executable_sfml


ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SFML = 	-Iextern/SFML-2.5.1/include \
						-DSFML_STATIC

	LIBS_SFML = -Lextern/SFML-2.5.1/lib \
				-lsfml-graphics-s -lsfml-window-s -lsfml-audio-s \
			 	-lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32\
			 	-lflac -lvorbisenc -lvorbisfile -lvorbis -logg -static

	LDFLAGS = -static 
			
else
	INCLUDE_DIR_SFML = -I/usr/include/SFML
	LIBS_SFML = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system 
endif

CC					= g++
LD 					= g++
CPPFLAGS 			= -Wall -ggdb
OBJ_DIR 			= obj
SRC_DIR 			= src
BIN_DIR 			= bin
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sfml -Isrc/txt

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SFML)

make_dir:
ifeq ($(OS),Windows_NT)
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	if not exist $(OBJ_DIR)\core mkdir $(OBJ_DIR)\core
	if not exist $(OBJ_DIR)\txt mkdir $(OBJ_DIR)\txt
	if not exist $(OBJ_DIR)\sfml mkdir $(OBJ_DIR)\sfml
	copy extern\SFML-2.5.1\bin\openal32.dll bin
else
	test -d $(BIN_DIR) || mkdir -p $(BIN_DIR)
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	test -d $(OBJ_DIR)/core || mkdir -p $(OBJ_DIR)/core
	test -d $(OBJ_DIR)/txt || mkdir -p $(OBJ_DIR)/txt
	test -d $(OBJ_DIR)/sfml || mkdir -p $(OBJ_DIR)/sfml
endif

$(BIN_DIR)/$(FINAL_TARGET_TXT): $(SRCS_TXT:%.cpp=$(OBJ_DIR)/%.o) $(CORE%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(BIN_DIR)/$(FINAL_TARGET_SFML): $(SRCS_SFML:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LIBS_SFML)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR_SFML) $(INCLUDE_DIR) $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q $(OBJ_DIR) $(BIN_DIR)
else
	rm -rf $(OBJ_DIR) $(BIN_DIR)
endif