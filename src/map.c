/* 'map.c' contains functions to draw parts of the game map & to load
   maps. */
#include <errno.h>
#include <stdlib.h>

#include <ncurses.h>

#include "error.h"
#include "win.h"
#include "entity/entity.h"
#include "map.h"

/* 'maptile_chars' is a 2-dimensional array that stores the character
   representations of map tile types & their different styles.
   
   The first dimension of the array is the tile type, and the second
   dimension is the style. */
chtype g_maptile_chars[MAP_TILE_NUM][MAP_STYLE_NUM];

/* Global map variable, a 2-dimensional array representing a grid of
   map spaces */
Mapspace g_map[MAPH][MAPW];

/* Initialize 'maptile_chars' */
void
init_maptile_chars (void)
{
  g_maptile_chars[0][0] = '.';
  g_maptile_chars[0][1] = '#';
  g_maptile_chars[1][0] = '-';
  g_maptile_chars[1][1] = '|';
}

/* Load map data from a text file; print errors & return nonzero on
   error */
int
load_map_txt (char *path)
{
  FILE *mapfile;
  if ((mapfile = fopen (path, "r")) == NULL)
    {
      endwin ();
      perror ("roguelike: error opening map file");
      refresh ();
      return 1;
    }

  /* Current character being read */
  int c;

  /* Current character being read (unsigned) */
  unsigned uc;

  /* Read the map file from the top, moving from left to right on rows
     of text */
  for (int y = 0; y < MAPH; y++)
    {
      for (int x = 0; x < MAPW; x++)
        {
          uc = fgetc (mapfile);
          Mapspace *ms = &g_map[y][x];
                        
          /* Get tile type & style */
          for (int tile = 0; tile < MAP_TILE_NUM; tile++)
            {
              for (int style = 0; style < MAP_STYLE_NUM; style++)
                {
                  if (g_maptile_chars[tile][style] == uc)
                    {
                      /* Tile & style found */
                      ms->tile = tile;
                      ms->style = style;
                      goto load_map_txt_set_vis;
                    }
                }
            }

          /* Tile & style not found; use default values & print a
             warning */
          PERR ();
          fprintf (stderr,
                   "map tile & style not found for space at "
                   "y%d x%d\n", y, x);
          ms->tile = MAPTILE_AIR;
          ms->style = 0;

          /* Set visibility */
        load_map_txt_set_vis:
          ms->vis = MAPVIS_SEE;
        }
      /* Skip newline character at the end of a row */
      fgetc (mapfile);
    }

  /* Find & execute map commands */
  while ((c = fgetc (mapfile)) != EOF)
    {
      switch (c)
        {
        case 'e':
          {
            /* Entity spawn command found; find the entity id &
               position */
            int id, y, x;
            fscanf (mapfile, "%d.%d.%d\n", &id, &y, &x);

            /* TODO: add better error checking after 'fscanf' calls
               here */

            /* Call the entity constructor */
            if ((*entity_id_list[id]) (y, x) == NULL)
              {
                PERR ();
                fprintf (stderr, "failed to create entity with id %d "
                         "at y%d x%d\n", id, y, x);
              }
            break;
          }
        case 'v':
          {
            /* Visibility modifier rectangle found; find its position
               & dimensions */
            int y, x, h, w;
            fscanf (mapfile, "%d.%d.%d.%d\n", &y, &x, &h, &w);

            int y1, x1, y2, x2;
            x1 = x;
            y1 = y;
            y2 = y + h;
            x2 = x + w;

            /* Make every map space in the rectangle unseen */
            for (y = y1; y < y2; y++)
              for (x = x1; x < x2; x++)
                g_map[y][x].vis = MAPVIS_UNSEEN;
            break;
          }
        default:
          {
            PERR ();
            fprintf (stderr, "unknown map command found \"%c\"; "
                     "aborting map command reading.\n", c);
            fclose (mapfile);
            return 1;
          }
        }
    }

  fclose (mapfile);
  return 0;
}

/* Draw the entire map */
void
draw_map (void)
{
  /* Draw map tiles */
  for (int y = 0; y < MAPH; y++)
    for (int x = 0; x < MAPW; x++)
      draw_map_tile (y, x);
        
  /* Draw all entities */
  ELNode *node = &elhead;
  while (node->e != NULL)
    {
      draw_entity (node->e);
      node = node->next;
    }
}

/* Draw the tile of a single map space */
void
draw_map_tile (int y, int x)
{
  Mapspace *ms = &g_map[y][x];
  if (ms->vis != MAPVIS_SEE)
    return;
  mvwaddch (g_mapwin, y, x, MAPTC (ms));
}

/* Draw an entity */
void
draw_entity (Entity *e)
{
  Mapspace *ms = &g_map[e->y][e->x];
  if (ms->vis != MAPVIS_SEE)
    return;
  mvwaddch (g_mapwin, e->y, e->x, e->c);
}

/* Draw an entire map space (tile & entity) */
void
draw_map_space (int y, int x)
{
  draw_map_tile (y, x);

  /* Check if any entities are at the map space coordinates & draw
     them if so */
  for (ELNode *node = &elhead; node->e != NULL; node = node->next)
    {
      if (node->e->y == y && node->e->x == x)
        {
          draw_entity (node->e);
                        
          /* 1 entity can be drawn at most, so the function call ends
             here */
          return;
        }
    }
}
