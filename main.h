#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <raylib.h>

#include "configs/consts.c"

#include "src/utils/env.c"

#include "src/globals/game-state.c"

#include "src/addons/sprite.c"

#include "src/screens/screen-states.c"
#include "src/screens/title-screen.c"
#include "src/screens/playing-screen.c"

// functions functions
void update(HGEnv *);
void render(HGEnv *);