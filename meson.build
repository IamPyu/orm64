project('orm64', 'c')
add_project_arguments(['-std=c11'], language: 'c')

# Windows support notice

if host_machine.system() == 'windows'
  error('Orm64, Orm64Util, and Orm64lib are for *NIX system only. I do not plan to add Windows support.')
endif

# Build options

if get_option('debug_install') == true
  add_project_arguments(['-DDEBUG_MODE'], language: 'c')
endif

if get_option('enable_bloat') == true
  add_project_arguments(['-DENABLE_BLOAT'], language: 'c')
endif

luajit_dep = dependency('luajit')
prefix = luajit_dep.get_variable('prefix')

add_project_arguments(['-DLUAJIT_PREFIX="'+prefix+'"'], language: 'c')

# User Data and Configuration

## Default Configuration
install_subdir('default', install_dir: 'etc/orm64/')

## Manpages
meson.add_install_script('scripts/man.py')

# Orm64lib
orm64lib = library('orm64lib', [
  'src/orm64lib/orm64lib.c'
], install: true)
install_headers('src/orm64lib/orm64lib.h')

# Orm64 and Orm64Util

deps = [
  luajit_dep,
  dependency('libedit'),
  dependency('raylib'),
  dependency('sdl2'),
  dependency('sdl2_net')
]



run_command('sh', 'scripts/configure.sh')
executable('orm64', [
  'src/main.c',
  'src/lua.c',
  'src/user.c',
  'src/util.c',
  'src/server/server.c',
  'src/apis/socket.c',
  'src/apis/graphics.c',
  'src/apis/multimedia.c',
  'src/apis/graphics/functions.c',
], dependencies: deps, link_with: [
  orm64lib, 
], install: true)

executable('orm64util', [
  'src/orm64util/orm64util.c',
  'src/orm64util/ormutil.c'
], dependencies: deps, link_with: [
  orm64lib,
], install: true)
