project('orm64', 'c')


orm64lib = library('orm64lib', 'src/util.c')

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
  'src/apis/graphics.c',
  'src/apis/socket.c',
  'src/apis/graphics/functions.c',
]

executable('orm64', src, dependencies: deps, link_with: orm64lib)
