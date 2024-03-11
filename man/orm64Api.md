# The Orm64 Core Api

## Plugins

Orm64 has a feature called "Plugins", unlike packages written in Lua, plugins are written and compiled in C.

Orm64 has to built in functions for loading and building plugins.

"orm64.buildPlugins()" builds or rebuilds all plugins in ~/.config/orm64/plugins.

"orm64.loadPlugin(PLUGIN_NAME)" tries to find PLUGIN_NAME.so in ~/.config/orm64/plugins if it does, 
it will load the plugin and run the C function orm64SetupPLUGIN_NAME where PLUGIN_NAME is replaced with the argument you specified.
