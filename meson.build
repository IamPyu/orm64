project('orm64', 'c')

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
  'src/apis/graphics/functions.c'
]

executable('orm64', src, dependencies: deps, link_with: ormlib)
