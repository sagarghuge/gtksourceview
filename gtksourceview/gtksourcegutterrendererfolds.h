/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8; coding: utf-8 -*- */
/* gtksourcegutterrendererfolds.h
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

#ifndef __GTK_SOURCE_GUTTER_RENDERER_FOLDS_H__
#define __GTK_SOURCE_GUTTER_RENDERER_FOLDS_H__

#include <gtksourceview/gtksourcetypes.h>
#include <gtksourceview/gtksourcegutterrenderer.h>

G_BEGIN_DECLS

#define GTK_SOURCE_TYPE_GUTTER_RENDERER_FOLDS             (gtk_source_gutter_renderer_folds_get_type ())
#define GTK_SOURCE_GUTTER_RENDERER_FOLDS(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_SOURCE_TYPE_GUTTER_RENDERER_FOLDS, GtkSourceGutterRendererFolds))
#define GTK_SOURCE_GUTTER_RENDERER_FOLDS_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_SOURCE_TYPE_GUTTER_RENDERER_FOLDS, GtkSourceGutterRendererFoldsClass))
#define GTK_SOURCE_IS_GUTTER_RENDERER_FOLDS(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_SOURCE_TYPE_GUTTER_RENDERER_FOLDS))
#define GTK_SOURCE_IS_GUTTER_RENDERER_FOLDS_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_SOURCE_TYPE_GUTTER_RENDERER_FOLDS))
#define GTK_SOURCE_GUTTER_RENDERER_FOLDS_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_SOURCE_TYPE_GUTTER_RENDERER_FOLDS, GtkSourceGutterRendererFoldsClass))

typedef struct _GtkSourceGutterRendererFoldsClass    GtkSourceGutterRendererFoldsClass;
typedef struct _GtkSourceGutterRendererFoldsPrivate  GtkSourceGutterRendererFoldsPrivate;

struct _GtkSourceGutterRendererFolds
{
	GtkSourceGutterRenderer parent;

	GtkSourceGutterRendererFoldsPrivate *priv;
};

struct _GtkSourceGutterRendererFoldsClass
{
	GtkSourceGutterRendererClass parent_class;

	gpointer padding[10];
};

GType gtk_source_gutter_renderer_folds_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* __GTK_SOURCE_GUTTER_RENDERER_FOLDS_H__ */
