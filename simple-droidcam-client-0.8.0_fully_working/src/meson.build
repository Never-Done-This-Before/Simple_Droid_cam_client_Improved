sources = [
  'simple_droidcam_client_main.vala',
  'simple_droidcam_client_application_window.vala',
]

add_project_arguments('-DGETTEXT_PACKAGE="simple_droidcam_client"', language:'c')

executable(
  'simple_droidcam_client',
  sources,
  gresources_ui,
  gresources_db,
  config_data,
  vala_args: '--target-glib=2.50',
  dependencies: deps,
  include_directories : config_dir,
  install: true,
)