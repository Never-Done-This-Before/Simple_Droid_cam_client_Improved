project(
  'simple_droidcam_client',
  ['c', 'vala'],
  version: '0.8.0',
  meson_version: '>= 0.40.0',
)

i18n = import('i18n')
gnome = import('gnome')

gio = dependency('gio-2.0', version: '>= 2.50')
gtk4 = dependency('gtk4', version: '>= 4.0')

deps = [
  gio,
  gtk4,
]

subdir('data')
subdir('config')
subdir('db')
subdir('icon')
subdir('ui')
subdir('src')
subdir('po')

