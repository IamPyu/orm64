use mlua::prelude::*;
use std::collections::HashMap;

pub struct Orm64Lua {
    pub lua: Lua,
}

impl Orm64Lua {
    pub fn new() -> Self {
        let mut lua = Lua::new();
        setup_lua(&mut lua);

        // load configuration (default and user config combined.)
        lua.load(super::util::DEFAULT_CONFIG).exec().unwrap();
        let config = super::util::get_config_file_contents("config.lua");
        match lua.load(&config).exec() {
            Ok(_) => eprintln!("Loaded configuration"),
            Err(e) => eprintln!("Error in configuration: {}", e)
        }
        
        return Self {
            lua
        };
    }
    
    pub fn get_configuration_value<'a, T: FromLua<'a>>(&'a mut self, name: &str) -> Option<T> {
        let options: LuaTable = self.lua.globals().get("orm64_options").unwrap();
        let value: mlua::Result<T> = options.get(name);

        match value {
            Ok(v) => Some(v),
            Err(_) => None
        }
    }

    pub fn load<'a, 'b, T: mlua::AsChunk<'a, 'b>>(&'a mut self, chunk: T) {
        match self.lua.load(chunk).exec() {
            Err(e) => println!("Uh oh! Your code ran into an error: {}", e),
            Ok(_) => {}
        }
    }
}

fn setup_lua(lua: &mut Lua) {
    let t = lua.create_table().unwrap();
    lua.globals().set("orm64_options", t);
    
    let t = lua.create_table().unwrap();
    lua.globals().set("orm64_data", t); 
    
    
    macro_rules! set_orm64_data_value {
        ($lua:expr, $key:expr, $value:expr) => {
            $lua.globals().get::<&str, LuaTable>("orm64_data").unwrap().set($key, $value); 
        };
    }
}