project('orm64', 'c')

if host_machine.system() == 'windows'
  error('Orm64 and Ormlib are for *NIX system only. I do not plan to add Windows support.')
endif

ormlib = library('ormlib', [
  'src/ormlib/ormlib.c'
], install: true)

install_subdir('default', install_dir: '~/.config/orm64')
install_headers('src/ormlib/ormlib.h')

run_command('sh', 'configure.sh')

executable('orm64', [
  'src/main.c',
  'src/lua.c',
  'src/user.c',
  'src/util.c',
  'src/apis/graphics.c',
  'src/apis/socket.c',
  'src/apis/graphics/functions.c',
], dependencies: [
  dependency('libedit'),
  dependency('luajit'),
  dependency('raylib'),
  dependency('ncurses'),
], link_with: ormlib, install: true)