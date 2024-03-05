project('orm64', 'c')

add_project_arguments(['-std=c11'], language: 'c')

if host_machine.system() == 'windows'
  error('Orm64, Orm64Util, and Ormlib are for *NIX system only. I do not plan to add Windows support.')
endif



# User Data and Configuration
run_command('chmod', '+x', 'scripts/install.sh')

if get_option('debug_install') == true
  run_command('sh', 'scripts/install.sh')
  add_project_arguments(['-DDEBUG_MODE'], language: 'c')
endif

meson.add_install_script('scripts/install.sh')

# Ormlib
ormlib = library('ormlib', [
  'src/ormlib/ormlib.c'
], install: true)
install_headers('src/ormlib/ormlib.h')

# Orm64 and Orm64Util

deps = [
  dependency('libedit'),
  dependency('luajit'),
  dependency('raylib'),
]

run_command('sh', 'scripts/configure.sh')
executable('orm64', [
  'src/main.c',
  'src/lua.c',
  'src/user.c',
  'src/util.c',
  'src/apis/graphics.c',
  'src/apis/socket.c',
  'src/apis/multimedia.c',
  'src/apis/graphics/functions.c',
], dependencies: deps, link_with: ormlib, install: true)

executable('orm64util', [
  'src/orm64util/orm64util.c',
  'src/orm64util/ormutil.c'
], dependencies: deps, link_with: ormlib, install: true)
