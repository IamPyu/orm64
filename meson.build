project('orm64', 'cpp')

add_project_arguments(['-std=c++11'], language: 'cpp')

if host_machine.system() == 'windows'
  error('Orm64, Orm64Util, and Ormlib are for *NIX system only. I do not plan to add Windows support.')
endif

# Ormlib
ormlib = library('ormlib', [
  'src/ormlib/ormlib.cpp'
], install: true)
install_headers('src/ormlib/ormlib.h')

# User Data and Configuration
run_command('chmod', '+x', 'scripts/install.sh')

if get_option('debug_install') == true
  run_command('sh', 'scripts/install.sh')
endif

meson.add_install_script('scripts/install.sh')

# Orm64 and Orm64Util

deps = [
  dependency('libedit'),
  dependency('luajit'),
  dependency('raylib'),
]

run_command('sh', 'scripts/configure.sh')
executable('orm64', [
  'src/main.cpp',
  'src/lua.cpp',
  'src/user.cpp',
  'src/util.cpp',
  'src/apis/graphics.cpp',
  'src/apis/socket.cpp',
  'src/apis/multimedia.cpp',
  'src/apis/graphics/functions.cpp',
], dependencies: deps, link_with: ormlib, install: true)

executable('orm64util', [
  'src/orm64util/orm64util.cpp',
  'src/orm64util/ormutil.cpp'
], dependencies: deps, link_with: ormlib, install: true)
