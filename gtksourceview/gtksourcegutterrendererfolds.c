/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8; coding: utf-8 -*- */
/* gtksourcegutterrendererfolds.c
 * This file is part of GtkSourceView
 *
 * Copyright (C) 2013 - Sébastien Wilmet <swilmet@gnome.org>
 *
 * GtkSourceView is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * GtkSourceView is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "gtksourcegutterrendererfolds.h"

#define LINE_WIDTH	1.0

/* The square size for drawing the box around the minus and plus signs. If the
 * line width is 1, the square size must be an odd number, to be able to draw
 * the sign in the middle of the square.
 */
#define SQUARE_SIZE	9

/* The folding state at a certain line in the text buffer.
 * Some states can be combined. For example, END and CONTINUE.
 */
typedef enum
{
	FOLDING_NONE		= 0,
	FOLDING_START_FOLDED	= 1 << 0,
	FOLDING_START_OPENED	= 1 << 1,
	FOLDING_CONTINUE	= 1 << 2,
	FOLDING_END		= 1 << 3
} FoldingState;

struct _GtkSourceGutterRendererFoldsPrivate
{
	gint something;
};

G_DEFINE_TYPE_WITH_PRIVATE (GtkSourceGutterRendererFolds,
			    gtk_source_gutter_renderer_folds,
			    GTK_SOURCE_TYPE_GUTTER_RENDERER)

/* Draw a minus or a plus surrounded by a square. */
static void
draw_sign (cairo_t      *cr,
	   GdkRectangle *cell_area,
	   gboolean      folded)
{
	gint sign_width = SQUARE_SIZE - 4;
	gint left_margin;
	gint top_margin;
	gint x;
	gint y;

	/* Integer division */
	left_margin = (cell_area->width - SQUARE_SIZE) / 2;
	top_margin = (cell_area->height - SQUARE_SIZE) / 2;

	x = cell_area->x + left_margin;
	y = cell_area->y + top_margin;

	cairo_rectangle (cr,
			 x + 0.5,
			 y + 0.5,
			 SQUARE_SIZE - 1.0,
			 SQUARE_SIZE - 1.0);

	cairo_move_to (cr,
		       x + 2.5,
		       y + SQUARE_SIZE / 2.0);

	cairo_rel_line_to (cr, sign_width - 1.0, 0);

	if (folded)
	{
		cairo_move_to (cr,
			       x + SQUARE_SIZE / 2.0,
			       y + 2.5);

		cairo_rel_line_to (cr, 0, sign_width - 1.0);
	}
}

static void
draw_vertical_line (cairo_t      *cr,
		    GdkRectangle *cell_area)
{
	/* Integer division */
	gint x = cell_area->x + cell_area->width / 2;

	cairo_move_to (cr,
		       x + 0.5,
		       cell_area->y + 0.5);

	cairo_rel_line_to (cr,
			   0,
			   cell_area->height - 1.0);
}

static void
draw_end (cairo_t      *cr,
	  GdkRectangle *cell_area)
{
	/* Integer division */
	gint x = cell_area->x + cell_area->width / 2;
	gint height = cell_area->height / 2 + 1;

	cairo_move_to (cr,
		       x + 0.5,
		       cell_area->y + 0.5);

	cairo_rel_line_to (cr,
			   0,
			   height - 1.0);

	cairo_line_to (cr,
		       cell_area->x + cell_area->width - 0.5,
		       cell_area->y + height - 0.5);
}

/* To draw the folding states (that can be combined), the cell_area is split in
 * three parts. The middle_area can contain the minus or plus sign, surrounded
 * by a square. It can also contain a vertical bar, or a small horizontal bar to
 * mark a fold end, etc. The top_area and bottom_area can just contain a
 * vertical bar.
 */
static void
split_cell_area (const GdkRectangle *cell_area,
		 GdkRectangle       *top_area,
		 GdkRectangle       *middle_area,
		 GdkRectangle       *bottom_area)
{
	g_assert (SQUARE_SIZE <= cell_area->height);

	top_area->x = cell_area->x;
	top_area->y = cell_area->y;
	top_area->width = cell_area->width;
	top_area->height = (cell_area->height - SQUARE_SIZE) / 2;

	middle_area->x = cell_area->x;
	middle_area->y = top_area->y + top_area->height;
	middle_area->width = cell_area->width;
	middle_area->height = SQUARE_SIZE;

	bottom_area->x = cell_area->x;
	bottom_area->y = middle_area->y + middle_area->height;
	bottom_area->width = cell_area->width;
	bottom_area->height = cell_area->height - top_area->height - middle_area->height;
}

static void
gutter_renderer_folds_draw (GtkSourceGutterRenderer      *renderer,
			    cairo_t                      *cr,
			    GdkRectangle                 *background_area,
			    GdkRectangle                 *cell_area,
			    GtkTextIter                  *start,
			    GtkTextIter                  *end,
			    GtkSourceGutterRendererState  state)
{
	gint line_num;
	FoldingState folding_state;
	GdkRectangle top_area;
	GdkRectangle middle_area;
	GdkRectangle bottom_area;

	/* Chain up to draw background */
	GTK_SOURCE_GUTTER_RENDERER_CLASS (
		gtk_source_gutter_renderer_folds_parent_class)->draw (renderer,
								      cr,
								      background_area,
								      cell_area,
								      start,
								      end,
								      state);

	line_num = gtk_text_iter_get_line (start);

	if (line_num == 0)
	{
		folding_state = FOLDING_START_FOLDED;
	}
	else if (line_num == 1)
	{
		folding_state = FOLDING_START_OPENED;
	}
	else if (line_num < 5)
	{
		folding_state = FOLDING_CONTINUE;
	}
	else if (line_num == 5)
	{
		folding_state = FOLDING_END;
	}
	else if (line_num == 6)
	{
		folding_state = FOLDING_NONE;
	}
	else if (line_num == 7)
	{
		folding_state = FOLDING_START_OPENED;
	}
	else if (line_num == 8)
	{
		folding_state = FOLDING_CONTINUE;
	}
	else if (line_num == 9)
	{
		folding_state = FOLDING_CONTINUE | FOLDING_START_OPENED;
	}
	else if (line_num < 12)
	{
		folding_state = FOLDING_CONTINUE;
	}
	else if (line_num == 12)
	{
		folding_state = FOLDING_CONTINUE | FOLDING_END;
	}
	else if (line_num == 13)
	{
		folding_state = FOLDING_CONTINUE;
	}
	else if (line_num == 14)
	{
		folding_state = FOLDING_CONTINUE | FOLDING_START_FOLDED;
	}
	else if (line_num == 15)
	{
		folding_state = FOLDING_CONTINUE;
	}
	else if (line_num == 16)
	{
		folding_state = FOLDING_END;
	}
	else
	{
		folding_state = FOLDING_NONE;
	}

	split_cell_area (cell_area,
			 &top_area,
			 &middle_area,
			 &bottom_area);

	cairo_save (cr);

	cairo_set_line_cap (cr, CAIRO_LINE_CAP_SQUARE);
	cairo_set_line_width (cr, LINE_WIDTH);

	/* Top area */

	if (folding_state & FOLDING_CONTINUE ||
	    folding_state & FOLDING_END)
	{
		draw_vertical_line (cr, &top_area);
	}

	/* Middle area */

	if (folding_state & FOLDING_START_FOLDED)
	{
		draw_sign (cr, &middle_area, TRUE);
	}
	else if (folding_state & FOLDING_START_OPENED)
	{
		draw_sign (cr, &middle_area, FALSE);
	}
	else
	{
		if (folding_state & FOLDING_CONTINUE)
		{
			draw_vertical_line (cr, &middle_area);
		}

		if (folding_state & FOLDING_END)
		{
			draw_end (cr, &middle_area);
		}
	}

	/* Bottom area */

	if (folding_state & FOLDING_START_OPENED ||
	    folding_state & FOLDING_CONTINUE)
	{
		draw_vertical_line (cr, &bottom_area);
	}

	cairo_stroke (cr);

	cairo_restore (cr);
}

static void
gtk_source_gutter_renderer_folds_finalize (GObject *object)
{

	G_OBJECT_CLASS (gtk_source_gutter_renderer_folds_parent_class)->finalize (object);
}

static void
gtk_source_gutter_renderer_folds_class_init (GtkSourceGutterRendererFoldsClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	GtkSourceGutterRendererClass *renderer_class = GTK_SOURCE_GUTTER_RENDERER_CLASS (klass);

	object_class->finalize = gtk_source_gutter_renderer_folds_finalize;

	renderer_class->draw = gutter_renderer_folds_draw;
}

static void
gtk_source_gutter_renderer_folds_init (GtkSourceGutterRendererFolds *self)
{
	self->priv = gtk_source_gutter_renderer_folds_get_instance_private (self);
}

GtkSourceGutterRenderer *
gtk_source_gutter_renderer_folds_new (void)
{
	return g_object_new (GTK_SOURCE_TYPE_GUTTER_RENDERER_FOLDS,
			     "size", SQUARE_SIZE,
			     "xpad", 2,
			     NULL);
}
