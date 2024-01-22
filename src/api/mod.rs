pub mod graphics;

macro_rules! set_global_table_value {
    ($lua:expr, $table:expr, $key:expr, $value:expr) => {
        $lua.globals().get::<&str, LuaTable>($table).unwrap().set($key, $value).unwrap(); 
    };
}
macro_rules! create_global_table {
    ($lua:expr, $name:expr) => {    
        let t = $lua.create_table().unwrap();
        $lua.globals().set($name, t).unwrap();
    };
}

pub(crate) use {set_global_table_value, create_global_table};
