#![allow(unused)]

pub mod core;
pub mod lua;

pub mod util {
    use std::{fs::{read_to_string, create_dir, File}, path::Path, io::Write};
    
    /// Returns the Orm64 directory, also creates it if it does not exist.
    pub fn orm64_directory() -> String {
        let p = format!("{}/.orm64.d/", std::env::var("HOME").unwrap());
        if !Path::new(&p).exists() {
            create_dir(&p);
            File::create(p.clone() + "config.lua")
                .unwrap()
                .write_all(DEFAULT_CONFIG.as_bytes())
                .unwrap();

            for dir in ORM64_DIRECTORIES {
                create_dir(p.clone() + dir);
            }
        }
        return p;
    }

    /// Returns the contents of a configuration file or any file in $HOME/.orm64.d
    /// If the file does not exist or failed to be read it will create the file and an empty string is returned.
    pub fn get_config_file_contents(file: &str) -> String {
        let mut value = "".to_string();

        if !Path::new(&orm64_directory()).exists() {
            create_dir(orm64_directory());
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
        
        return value;
    }

    pub const ORM64_DIRECTORIES: [&str;2] = ["apps", ""];

    /*
    Application structure:
    Apps live in the `apps` directory. An app is just another file or directory.

    A file app would look like: hi.lua
    A directory app would look like: hi/init.lua

    As you saw above by the file extensions "*.lua" apps are written in Lua.
    */
    
pub const DEFAULT_CONFIG: &str = r#"--Orm64 config

-- Startup Message!
orm64_options.startup_message = "welcome to orm64, edit your configuration in $HOME/.orm64.d/config.lua"

-- Prompt
orm64_options.prompt = "> " -- The prompt! Its like the PS1 variable in GNU Bash.
    -- It is that text that is printed before your cursor in a normal terminal shell.
    -- Pretty cool right?
"#;

pub const HELP_MESSAGE: &str = r#"Welcome to Orm64!

### SHELL ###
It seems like you need help! You might be questioning why is this shell not working?
Thats because its not a shell for your system. Its a Lua REPL to control Orm64!

Anything that is not a reserved command Orm64 uses (like this help command) will be passed to Lua to evaluate and execute.

Here is a list of reserved commands: [
    exit
    help
    srtupmsg
]

### CONFIGURATION ###

If you are running Orm64 for the first time, a directory would've been created at: $HOME/.orm64.d

There are a few files in there

"#;
}
