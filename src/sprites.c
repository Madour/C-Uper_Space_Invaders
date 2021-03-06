/*_____________________________________________________
 /                                                     \
| Modar NASSER - Groupe TP2                            |
| TP5 - 22/10/2019                                     |
| Création d'un space invader                          |
|------------------------------------------------------|
| Fichier : sprites.c                                  |
|   -> contient la description des sprites non texte   |
|      utilisés dans le jeu                            |
|------------------------------------------------------|
| Compilation :                                        |
|   - generation du .o :                               |
|   	  $ gcc -c sprites.c                           |
|                                                      |
\______________________________________________________/
*/


#include "sprites.h"


t_sprite missile_sprite = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

t_spritesheet shields_spritesheet = {
    {
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    }

};


t_sprite impact_sprite = {
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
};

t_sprite heart_sprite = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
};

t_spritesheet player_spritesheet = {
    {
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
    }
};

t_spritesheet player_reactor = {
    {
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }
};

t_spritesheet player_glow_spritesheet = {
    {
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
    },
};

t_spritesheet alien0_spritesheet = {
    {
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 1 ,1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0 ,0, 0, 0, 1, 0, 0},
    },
    {
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1 ,1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0 ,0, 0, 0, 0, 1, 0},
    }
};
t_spritesheet alien0_glow_spritesheet = {
    {
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 1 ,1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0 ,0, 0, 0, 1, 0, 0},
    },
    {
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 1 ,1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0 ,0, 0, 0, 0, 1, 0},
    }
};

t_spritesheet alien1_spritesheet = {
    {
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1 ,1, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 1, 1, 1 ,0, 1, 1, 1, 0, 0},
    },
    {
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1 ,1, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 0 ,0, 0, 1, 1, 0, 1},
    }
};

t_spritesheet alien1_glow_spritesheet = {
    {
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 1 ,1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 1, 1, 1 ,0, 1, 1, 1, 0, 0},
    },
    {
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 1 ,1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 0 ,0, 0, 1, 1, 0, 1},
    }
};

t_spritesheet alien2_spritesheet = {
    {
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 0, 1, 1 ,1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0 ,1, 0, 1, 1, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 0, 1, 1 ,1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0 ,1, 0, 1, 1, 1, 0},
    }
};

t_spritesheet alien2_glow_spritesheet = {
    {
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 0 ,0, 1, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0 ,1, 0, 1, 1, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 0 ,0, 1, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0 ,1, 0, 1, 1, 1, 0},
    }
};

t_spritesheet alien3_spritesheet = {
    {
        {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1 ,1, 1, 1, 1},
        {0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 0 ,0, 0, 0, 0, 1},
    },
    {
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0 ,0, 0, 0, 0, 1, 0, 0},
    }
};

t_spritesheet alien3_glow_spritesheet = {
    {
        {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 0, 0 ,0, 0, 0, 1},
        {0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 0 ,0, 0, 0, 0, 1},
    },
    {
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0 ,0, 0, 0, 1, 0, 0},
        {1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0 ,0, 0, 0, 0, 1, 0, 0},
    },
};

t_spritesheet* aliens_spritesheets_list[5] = {&alien0_spritesheet, &alien1_spritesheet, &alien2_spritesheet, &alien3_spritesheet};
t_spritesheet* aliens_glow_spritesheets_list[5] = {&alien0_glow_spritesheet, &alien1_glow_spritesheet, &alien2_glow_spritesheet, &alien3_glow_spritesheet};
int aliens_animspeed[5] = {10, 2, 6, 3};


t_spritesheet boss1_spritesheets[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X] = {
    {
        // premiers 3 sprites de la premiere ligne du boss
        {
            {
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,1,1,1,1,1},
                {0,0,0,0,0,0,1,1,1,1,1},
                {0,0,0,0,1,1,1,1,1,1,1},
                {0,0,0,0,1,1,1,1,1,1,1},
                {0,0,1,1,1,1,0,0,1,1,1},
                {1,1,1,1,1,1,0,0,1,1,1},
            },
            {
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,1,1,1,1,1},
                {0,0,0,0,0,0,1,1,1,1,1},
                {0,0,0,0,1,1,1,0,0,1,1},
                {0,0,0,0,1,1,1,1,1,1,1},
                {0,0,1,1,1,1,0,0,1,1,1},
                {1,1,1,1,1,1,0,0,1,1,1},
            },
        },
        {
            {
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,0,0,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,1,1,1,1,0,0,1,1},
                {1,0,0,1,1,1,1,0,0,1,1},
            },
            {
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,1,1,1,1,0,0,1,1},
                {1,0,0,1,1,1,1,0,0,1,1},
            },
        },
        {
            {
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,0,0,0,0,0,0,0},
                {1,1,1,1,0,0,0,0,0,0,0},
                {1,1,1,1,1,1,0,0,0,0,0},
                {1,1,1,1,1,1,0,0,0,0,0},
                {1,1,0,0,1,1,1,1,0,0,0},
                {1,1,0,0,1,1,1,1,1,1,0},
            },
            {
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,0,0,0,0,0,0,0},
                {1,1,1,1,0,0,0,0,0,0,0},
                {1,0,0,1,1,1,0,0,0,0,0},
                {1,1,1,1,1,1,0,0,0,0,0},
                {1,1,0,0,1,1,1,1,0,0,0},
                {1,1,0,0,1,1,1,1,1,1,0},
            },
        },

    },

    {
        // premiers 3 sprites de la deuxieme ligne du boss
        {
            {
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {0,0,0,0,1,1,1,1,1,1,0},
                {0,0,0,0,1,1,1,1,1,1,0},
                {0,0,0,0,0,0,1,1,0,0,0},
                {0,0,0,0,0,0,1,1,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },
            {
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {0,0,0,0,1,1,1,1,1,1,0},
                {0,0,0,0,1,1,1,1,1,1,0},
                {0,0,0,0,0,0,1,1,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },

        },
        {
            {
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {0,0,0,1,1,1,1,0,0,0,0},
                {0,0,0,1,1,1,1,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },
            {
                {1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1},
                {0,0,0,1,1,1,1,0,0,0,0},
                {0,0,0,1,1,1,1,0,0,0,0},
                {0,0,0,0,1,1,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },

        },
        {
            {
                {1,1,1,1,1,1,1,1,1,1,0},
                {1,1,1,1,1,1,1,1,1,1,0},
                {1,1,1,1,1,1,0,0,0,0,0},
                {1,1,1,1,1,1,0,0,0,0,0},
                {0,0,1,1,0,0,0,0,0,0,0},
                {0,0,1,1,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },
            {
                {1,1,1,1,1,1,1,1,1,1,0},
                {1,1,1,1,1,1,1,1,1,1,0},
                {1,1,1,1,1,1,0,0,0,0,0},
                {1,1,1,1,1,1,0,0,0,0,0},
                {0,0,1,1,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },

        },
    }
};

t_spritesheet boss1_glow_spritesheets[BOSS_SPRITES_COUNT_Y][BOSS_SPRITES_COUNT_X] = {
    {
        // premiers 3 sprites de la premiere ligne du boss
        {
            {
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,1,1,1,1,0},
                {0,0,0,0,0,0,1,0,0,0,0},
                {0,0,0,0,1,1,0,0,0,0,0},
                {0,0,0,0,1,0,0,0,0,0,0},
                {0,0,1,1,0,0,1,1,0,0,0},
                {1,1,1,0,0,0,1,1,0,0,0},
            },
            {
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,1,1,1,1,0},
                {0,0,0,0,0,0,1,0,0,0,0},
                {0,0,0,0,1,1,0,1,1,0,0},
                {0,0,0,0,1,0,0,0,0,0,0},
                {0,0,1,1,0,0,1,1,0,0,0},
                {1,1,1,0,0,0,1,1,0,0,0},
            },
        },
        {
            {
                {1,1,1,1,1,1,1,1,1,1,1},
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,1,1,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,1,1,0,0,0,0,1,1,0,0},
                {0,1,1,0,0,0,0,1,1,0,0},
            },
            {
                {1,1,1,1,1,1,1,1,1,1,1},
                {0,0,0,0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,1,1,0,0,0,0,1,1,0,0},
                {0,1,1,0,0,0,0,1,1,0,0},
            },
        },
        {
            {
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0,0,0,0},
                {0,0,0,0,1,1,0,0,0,0,0},
                {0,0,0,0,0,1,0,0,0,0,0},
                {0,0,1,1,0,0,1,1,0,0,0},
                {0,0,1,1,0,0,0,1,1,1,0},
            },
            {
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0,0,0,0},
                {0,1,1,0,1,1,0,0,0,0,0},
                {0,0,0,0,0,1,0,0,0,0,0},
                {0,0,1,1,0,0,1,1,0,0,0},
                {0,0,1,1,0,0,0,1,1,1,0},
            },
        },

    },

    {
        // premiers 3 sprites de la deuxieme ligne du boss
        {
            {
                {1,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,0,0,0,0,0,0,1},
                {0,0,0,0,1,0,0,0,0,1,0},
                {0,0,0,0,1,1,0,0,1,1,0},
                {0,0,0,0,0,0,1,1,0,0,0},
                {0,0,0,0,0,0,1,1,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },
            {
                {1,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,0,0,0,0,0,0,1},
                {0,0,0,0,1,0,0,0,0,1,0},
                {0,0,0,0,1,1,0,0,1,1,0},
                {0,0,0,0,0,0,1,1,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },

        },
        {
            {
                {0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,0,0,0,0,1,1,1,1},
                {0,0,0,1,0,0,1,0,0,0,0},
                {0,0,0,1,1,1,1,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },
            {
                {0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,0,0,0,0,1,1,1,1},
                {0,0,0,1,0,0,1,0,0,0,0},
                {0,0,0,1,0,0,1,0,0,0,0},
                {0,0,0,0,1,1,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },

        },
        {
            {
                {0,0,0,0,0,0,0,0,0,1,0},
                {0,0,0,0,0,0,1,1,1,1,0},
                {0,0,0,0,0,1,0,0,0,0,0},
                {1,1,0,0,1,1,0,0,0,0,0},
                {0,0,1,1,0,0,0,0,0,0,0},
                {0,0,1,1,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },
            {
                {0,0,0,0,0,0,0,0,0,1,0},
                {0,0,0,0,0,0,1,1,1,1,0},
                {0,0,0,0,0,1,0,0,0,0,0},
                {1,1,0,0,1,1,0,0,0,0,0},
                {0,0,1,1,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0},
            },

        },
    }
};