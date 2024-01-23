// #![allow(unused)]
#![allow(unused_imports)]

pub mod core;
pub mod lua;
pub mod api;

pub mod util {
    use std::{fs::{read_to_string, create_dir, File}, path::Path, io::Write};
     
    /// Returns the Orm64 directory, also creates it if it does not exist.
    pub fn orm64_directory() -> String {
        let p = format!("{}/.orm64.d/", std::env::var("HOME").unwrap());
        if !Path::new(&p).exists() {
            create_dir(&p).unwrap();
            File::create(p.clone() + "config.lua")
                .unwrap()
                .write_all(DEFAULT_CONFIG.as_bytes())
                .unwrap();

            for dir in ORM64_DIRECTORIES {
                create_dir(p.clone() + dir).unwrap();
            }
        }
        p
    }

    /// Returns the contents of a configuration file or any file in $HOME/.orm64.d
    /// 
    /// If the file does not exist it will create the file and an empty string is returned.
    pub fn get_config_file_contents(file: &str) -> String {
        let mut value = "".to_string();

        if !Path::new(&orm64_directory()).exists() {
            create_dir(orm64_directory()).unwrap();
        }

        if !Path::new(&(orm64_directory()+file)).exists() {
            File::create(orm64_directory()+file).unwrap();   
        }

        let path = orm64_directory() + file;
        let res = read_to_string(path);

        match res {
            Ok(contents) => value = contents,
            Err(_) => {}
        }
        
        value
    }

    pub const ORM64_DIRECTORIES: [&str;3] = ["software", "data", "home"];

    /*
    Application structure:
    Apps and Libraries live in the `software` directory. An app is just another directory.

    A directory app would look like: hi/init.lua

    As you saw above by the file extensions "*.lua" apps are written in Lua.
    */

    /// Default Orm64 configuration
    /// 
    /// This gets loaded before the user configuration so anything unset in the user configuration
    /// gets its default values
    pub const DEFAULT_CONFIG: &str = include_str!("res/default.lua");

    /// Orm64 manual
    pub const HELP_MESSAGE: &str = include_str!("res/doc/help.md");
    /// Orm64 API manual
    pub const API_MESSAGE: &str = include_str!("res/doc/api.md");
}
