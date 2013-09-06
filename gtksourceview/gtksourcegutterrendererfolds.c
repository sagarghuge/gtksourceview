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

struct _GtkSourceGutterRendererFoldsPrivate
{
	gint something;
};

G_DEFINE_TYPE_WITH_PRIVATE (GtkSourceGutterRendererFolds,
			    gtk_source_gutter_renderer_folds,
			    GTK_SOURCE_TYPE_GUTTER_RENDERER)

static void
gtk_source_gutter_renderer_folds_finalize (GObject *object)
{

	G_OBJECT_CLASS (gtk_source_gutter_renderer_folds_parent_class)->finalize (object);
}

static void
gtk_source_gutter_renderer_folds_class_init (GtkSourceGutterRendererFoldsClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	object_class->finalize = gtk_source_gutter_renderer_folds_finalize;
}

static void
gtk_source_gutter_renderer_folds_init (GtkSourceGutterRendererFolds *self)
{
	self->priv = gtk_source_gutter_renderer_folds_get_instance_private (self);
}
