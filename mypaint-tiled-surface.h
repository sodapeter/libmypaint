#ifndef MYPAINTTILEDSURFACE_H
#define MYPAINTTILEDSURFACE_H

#include <stdint.h>
#include <glib.h>

#include <mypaint-surface.h>

G_BEGIN_DECLS

struct _MyPaintTiledSurface;

typedef uint16_t *(*MyPaintTiledSurfaceGetTileFunction) (struct _MyPaintTiledSurface *self, int tx, int ty, gboolean readonly);
typedef void (*MyPaintTiledSurfaceUpdateTileFunction) (struct _MyPaintTiledSurface *self, int tx, int ty, uint16_t * tile_buffer);
typedef void (*MyPaintTiledSurfaceAtomicChangeFunction) (struct _MyPaintTiledSurface *self);
typedef void (*MyPaintTiledSurfaceAreaChanged) (struct _MyPaintTiledSurface *self, int bb_x, int bb_y, int bb_w, int bb_h);

/**
  * MyPaintTiledSurface:
  *
  * MyPaintSurface backed by a tile store. The size of the surface is infinite.
  */
struct _MyPaintTiledSurface {
    MyPaintSurface parent;
    MyPaintTiledSurfaceGetTileFunction get_tile;
    MyPaintTiledSurfaceUpdateTileFunction update_tile;
    MyPaintTiledSurfaceAtomicChangeFunction begin_atomic;
    MyPaintTiledSurfaceAtomicChangeFunction end_atomic;
    MyPaintTiledSurfaceAreaChanged area_changed;

    /* private: */
    gboolean surface_do_symmetry;
    float surface_center_x;
};

typedef struct _MyPaintTiledSurface MyPaintTiledSurface;

/**
  * mypaint_tiled_surface_new:
  *
  * Create a new MyPaintTiledSurface.
  */
void
mypaint_tiled_surface_init(MyPaintTiledSurface *);

void
mypaint_tiled_surface_destroy(MyPaintTiledSurface *self);

void
mypaint_tiled_surface_set_symmetry_state(MyPaintTiledSurface *self, gboolean active, float center_x);
float
mypaint_tiled_surface_get_alpha (MyPaintTiledSurface *self, float x, float y, float radius);

void mypaint_tiled_surface_begin_atomic(MyPaintTiledSurface *self);
void mypaint_tiled_surface_end_atomic(MyPaintTiledSurface *self);
uint16_t * mypaint_tiled_surface_get_tile(MyPaintTiledSurface *self, int tx, int ty, gboolean readonly);
void mypaint_tiled_surface_update_tile(MyPaintTiledSurface *self, int tx, int ty, uint16_t * tile_buffer);
void mypaint_tiled_surface_area_changed(MyPaintTiledSurface *self, int bb_x, int bb_y, int bb_w, int bb_h);

G_END_DECLS

#endif // MYPAINTTILEDSURFACE_H
