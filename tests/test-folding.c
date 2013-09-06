/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8; coding: utf-8 -*- */
/* test-folding.c
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

#include <gtksourceview/gtksource.h>

static void
add_folds_gutter (GtkSourceView *view)
{
	GtkSourceGutter *gutter;
	GtkSourceGutterRenderer *renderer;

	gutter = gtk_source_view_get_gutter (view, GTK_TEXT_WINDOW_LEFT);
	renderer = gtk_source_gutter_renderer_folds_new ();
	gtk_source_gutter_insert (gutter, renderer, 0);
}

int
main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *sw;
	GtkWidget *source_view;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
	g_signal_connect (window, "destroy", gtk_main_quit, NULL);

	sw = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER (window), sw);

	source_view = gtk_source_view_new ();
	gtk_container_add (GTK_CONTAINER (sw), source_view);

	add_folds_gutter (GTK_SOURCE_VIEW (source_view));

	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}
