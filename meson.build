project('orm64', 'c')

if host_machine.system() == 'windows'
  error('Orm64 and Ormlib are for *NIX system only. I do not plan to add Windows support.')
endif

ormlib = library('ormlib', 'src/ormlib/ormlib.c')

deps = [
  dependency('libedit'),
  dependency('luajit'),
  dependency('raylib'),
  dependency('ncurses'),
]

src = [
  'src/main.c',
  'src/lua.c',
  'src/user.c',
  'src/util.c',
  'src/apis/graphics.c',
  'src/apis/socket.c',
  'src/apis/graphics/functions.c',
]

run_command('configure.sh')
executable('orm64', src, dependencies: deps, link_with: ormlib)