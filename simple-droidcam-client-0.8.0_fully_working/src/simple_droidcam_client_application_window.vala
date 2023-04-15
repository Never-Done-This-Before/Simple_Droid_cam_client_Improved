/* -*- Mode: Vala; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/* simple_droidcam_client_application_window.vala
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

namespace SimpleDroidCamClient {
  [GtkTemplate ( ui = "/ar/com/softwareperonista/simple_droidcam_client/ui/simple_droidcam_client_application_window.ui" )]
  public class ApplicationWindow : Gtk.ApplicationWindow {
    [GtkChild]
    private unowned Gtk.Button button_new_devices;
    [GtkChild]
    private unowned Gtk.Button button_connect_camera;
    [GtkChild]
    private unowned Gtk.Entry entry_v4ld;
    [GtkChild]
    private unowned Gtk.Entry entry_ip;
    [GtkChild]
    private unowned Gtk.Entry entry_newdevices;
    [GtkChild]
    private unowned Gtk.Entry entry_port;
    [GtkChild]
    private unowned Gtk.Entry entry_resolution;
    [GtkChild]
    private unowned Gtk.Image image_state;
    [GtkChild]
    private unowned Gtk.MenuButton menubutton;
    [GtkChild]
    private unowned Gtk.Switch switch_vertical_flip;
    [GtkChild]
    private unowned Gtk.Spinner spinner_connecting;

    private Settings settings;
    private Subprocess ffmpeg;
    private const string device_name = "DroidCam";


    public ApplicationWindow ( Gtk.Application app ) {
      Object ( application: app );

      this.application.window_removed.connect ( this.kill_ffmpeg );

      this.settings = new Settings ( "ar.com.softwareperonista.SimpleDroidCamClient" );

      this.entry_ip.set_text ( this.settings.get_string ( "ip" ) );
      this.entry_v4ld.set_text ( this.settings.get_string ( "v4ld" ) );
      this.entry_newdevices.set_text ( this.settings.get_string ( "newdevices" ) );
      this.entry_port.set_text ( this.settings.get_string ( "port" ) );
      this.entry_resolution.set_text ( this.settings.get_string ( "resolution" ) );
      this.switch_vertical_flip.set_active ( this.settings.get_boolean ( "vertical-flip" ) );

      this.ffmpeg = null;

      this.create_menu ();
    }

    [GtkCallback]
    private void button_connect_camera_clicked () {
      if ( !this.module_loaded () ) {
        this.load_module ();
      }

      if ( this.ffmpeg  == null ) {
        this.connect_camera ();
      } else {
        this.kill_ffmpeg ( this );
      }
    }

    [GtkCallback]
    private void button_new_devices_clicked () {


      string standard_outputs = "";
      string command6 = "pkexec rmmod v4l2loopback ";

      string command7 = "sleep 1";

      string command8 = "pkexec  modprobe v4l2loopback devices=" + this.entry_newdevices.get_text();

        try {
        Process.spawn_command_line_sync ( command6, out standard_outputs, null, null );
        standard_outputs = standard_outputs.slice ( 0, standard_outputs.length-1 );
      } catch ( SpawnError spawnCaughtError ) {
        stderr.printf ( "There was an error spawining the process. Details: %s", spawnCaughtError.message );
      }

        try {
        Process.spawn_command_line_sync ( command7, out standard_outputs, null, null );
        standard_outputs = standard_outputs.slice ( 0, standard_outputs.length-1 );
      } catch ( SpawnError spawnCaughtError ) {
        stderr.printf ( "There was an error spawining the process. Details: %s", spawnCaughtError.message );
      }

      try {
        Process.spawn_command_line_sync ( command8, out standard_outputs, null, null );
        standard_outputs = standard_outputs.slice ( 0, standard_outputs.length-1 );
      } catch ( SpawnError spawnCaughtError ) {
        stderr.printf ( "There was an error spawining the process. Details: %s", spawnCaughtError.message );
      }




    }

    private bool module_loaded () {
      string command = "cat /sys/devices/virtual/video4linux/video" + this.entry_v4ld.get_text() + "/name";
      string standard_output = "";

      bool ret = false;

      try {
        Process.spawn_command_line_sync ( command, out standard_output, null, null );
        standard_output = standard_output.slice ( 0, standard_output.length-1 );
      } catch ( SpawnError spawnCaughtError ) {
        stderr.printf ( "There was an error spawining the process. Details: %s", spawnCaughtError.message );
      }

      if ( standard_output == SimpleDroidCamClient.ApplicationWindow.device_name ) {
        ret = true;
      }
      debug ( ret.to_string () );
      return ret;
    }

    private void load_module () {
      string command = "pkexec modprobe v4l2loopback exclusive_caps=1 video_nr=" + this.entry_v4ld.get_text() + " " +  "card_label="+ SimpleDroidCamClient.ApplicationWindow.device_name + "";

      try {
        Process.spawn_command_line_sync ( command, null, null, null );
      } catch ( SpawnError spawnCaughtError ) {
        stderr.printf ( "There was an error spawining the process. Details: %s", spawnCaughtError.message );
      }
    }

    private void connect_camera () {
      string socket = this.entry_ip.get_text () + ":" + this.entry_port.get_text ();

      var args = new Array<string> ();
      args.append_val ( "ffmpeg" );
      args.append_val ( "-i" );
      args.append_val ( "http://" + socket + "/mjpegfeed?" + this.entry_resolution.get_text () );
      args.append_val ( "-vcodec" );
      args.append_val ( "rawvideo" );
      args.append_val ( "-pix_fmt" );
      args.append_val ( "yuv420p" );
      args.append_val ( "-f" );
      args.append_val ( "v4l2" );
      if ( this.switch_vertical_flip.active ) {
        args.append_val ( "-vf" );
        args.append_val ( "vflip" );
      }
      args.append_val ( "/dev/video" + this.entry_v4ld.get_text() );

      string[] spawn_args = args.steal ();

      string command = spawn_args[0];
      for ( int i = 1; i < spawn_args.length; i++ ) {
        command += " " + spawn_args[i];
      }

      debug ( command );

      try {
        this.ffmpeg = new Subprocess.newv ( spawn_args, SubprocessFlags.NONE );
        this.ffmpeg.wait_async.begin ( (null), () => {
          this.ffmpeg = null;
          this.button_connect_camera.set_label ( "Connect" );
          this.image_state.set_from_icon_name ( "window-close-symbolic" );
          this.hide_spinner ();
        } );

        this.button_connect_camera.set_label ( "Connecting..." );
        this.show_spinner ();

        Timeout.add_seconds ( 1, () => {
          if ( this.ffmpeg != null ) {
            this.settings.set_string ( "ip", this.entry_ip.get_text () );
            this.settings.set_string ( "port", this.entry_port.get_text () );
            this.settings.set_string ( "resolution", this.entry_resolution.get_text () );
            this.settings.set_boolean ( "vertical-flip", this.switch_vertical_flip.active );
            this.button_connect_camera.set_label ( "Disconnect" );
            this.image_state.set_from_icon_name ( "emblem-ok-symbolic" );
            this.hide_spinner();
          }

          return Source.REMOVE;
        } );
      } catch ( Error e ) {
        stderr.printf ( "There was an error spawining the process. Details: %s", e.message );
      }
    }

    private void kill_ffmpeg ( Gtk.Window window ) {
      if ( this.ffmpeg != null ) {
        this.ffmpeg.force_exit ();
      }
    }

    private void create_menu () {
      var builder = new Gtk.Builder ();
      try {
        builder.add_from_resource ( "/ar/com/softwareperonista/simple_droidcam_client/ui/simple_droidcam_client_main_menu.ui" );
        this.menubutton.set_menu_model ( builder.get_object ( "main-menu" ) as  Menu );
      } catch (  Error e ) {
        error ( "loading ui file: %s", e.message );
      }
      var action = new SimpleAction ( "quit", null );
      action.set_enabled ( true );
      action.activate.connect ( () => { this.close (); } );
      this.application.add_action ( action );

      action = new SimpleAction ( "about", null );
      action.set_enabled ( true );
      action.activate.connect ( () => { this.about (); } );
      this.application.add_action ( action );
    }

    private void about () {
      string[] authors = {
        "Fernando Fernandez <fernando@softwareperonista.com.ar>",
      };
      Gtk.show_about_dialog ( this,
                              "authors", authors,
                              "program-name", "Simple Droidcam Client",
                              "title", _("About" ) + " Simple DroidCam Client",
                              "comments", _("A simple DroidCam client" ),
                              "copyright", "Copyright 2020-2021 Fernando Fernández",
                              "license-type", Gtk.License.GPL_3_0,
                              "logo-icon-name", "ar.com.softwareperonista.SimpleDroidCamClient",
                              "version", Config.VERSION,
                              "website", "https://gitlab.com/tarmaciltur/simple-droidcam-client",
                              "wrap-license", true );
    }

    private void show_spinner () {
      this.image_state.set_visible (false);
      this.spinner_connecting.set_visible (true);
      this.spinner_connecting.start();
      this.button_connect_camera.set_sensitive ( false );
    }

    private void hide_spinner () {
      this.image_state.set_visible (true);
      this.spinner_connecting.set_visible (false);
      this.spinner_connecting.stop();
      this.button_connect_camera.set_sensitive ( true );
    }
  }
}
