/* -*- Mode: Vala; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/* simple_droidcam_client_main.vala
 *
 * Copyright 2020 Fernando Fernandez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

int main ( string[] args ) {
  Intl.bind_textdomain_codeset ( Config.GETTEXT_PACKAGE, "UTF-8" );
  Intl.textdomain ( Config.GETTEXT_PACKAGE );

  var app = new Gtk.Application ( "ar.com.softwareperonista.SimpleDroidCamClient", ApplicationFlags.FLAGS_NONE );
  app.activate.connect ( () => {
    var win = app.active_window;
    /*if ( win == null ) {*/
      win = new SimpleDroidCamClient.ApplicationWindow ( app );
    /*}*/
    win.show ();
  } );

  return app.run ( args );
}
