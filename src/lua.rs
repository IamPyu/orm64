use std::{path::Path, process::Command};

use mlua::prelude::*;

pub struct Orm64Lua {
    pub lua: Lua, // Why didn't i define it like: pub struct Orm64Lua(pub Lua)? Too late now i guess
                  // I am not recfactoring this stuff..
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
    lua.load(format!("package.path = package.path .. ';{}software/?/init.lua'",
        super::util::orm64_directory()))
    .exec().unwrap();

    let t = lua.create_table().unwrap();
    lua.globals().set("orm64_options", t).unwrap();
    
    let t = lua.create_table().unwrap();
    lua.globals().set("orm64", t).unwrap();

    #[allow(unused)]
    /// Sets a key in the orm64 variable to a value
    macro_rules! set_orm64_value {
        ($lua:expr, $key:expr, $value:expr) => {
            $lua.globals().get::<&str, LuaTable>("orm64").unwrap().set($key, $value).unwrap(); 
        };
    }

    // Small function to get the directory of a program, its like the get_modpath function for minetest
    //
    // This function *will* return nil if the specified program does NOT exist.
    set_orm64_value!(lua, "get_software_path", lua.create_function(|_, name: String|{
        let mut path_str = None;
        let orm64_dir = super::util::orm64_directory();
        let tmp = orm64_dir + "software/" + name.as_str(); 
        let path = Path::new(&(tmp));

        if path.exists() && path.is_dir() {
            path_str = Some(tmp);
        } 

        return Ok(path_str);
    }).unwrap());

    set_orm64_value!(lua, "install_packages", lua.create_function(|l, _:()|{
        let packages = l.globals().get::<&str, LuaTable>("orm64_options").unwrap().get::<&str, LuaTable>("packages").unwrap();

        for pair in packages.pairs::<String, String>() {
            let (name, url) = pair.unwrap_or(("orm64_no_git_repo_found".to_string(), "https://gitlab.com/pyudev/orm64_no_git_repo_found".to_string()));
            let path = super::util::orm64_directory()+"software/"+&name;

        }

        return Ok(());
    }).unwrap());
}
