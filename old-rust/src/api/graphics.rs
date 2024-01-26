// graphics.rs

use mlua::prelude::*;
use super::{set_global_table_value, create_global_table};

pub fn setup_graphics(lua: &Lua) {
    create_global_table!(lua, "orm64_graphics");


    set_global_table_value!(lua, "orm64_graphics", "init", lua.create_function(|_l, _args: ()| {

        Ok(())
    }).unwrap());
}
