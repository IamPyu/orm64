use std::process::Command;

// use std::collections::HashMap;
use rustyline::DefaultEditor;
use crate::lua::Orm64Lua;

pub struct Orm64<> {
    pub lua: Orm64Lua   
}

impl Default for Orm64 {
    fn default() -> Self {
        Self::new()
    }
}

impl Orm64 {
    pub fn new() -> Self {
        Self {
            lua: Orm64Lua::new()
        }
    }

    pub fn start(&mut self) {
        let mut reader = DefaultEditor::new().unwrap();
        println!("{}", self.lua.get_configuration_value::<String>("startup_message").unwrap());

        'orm64_loop: loop {
            match reader.readline(self.lua.get_configuration_value::<String>("prompt").unwrap().to_string().as_str()) {
                Ok(cmd) => {
                    reader.add_history_entry(&cmd).unwrap_or(false);

                    match cmd.as_str() {
                        "exit" => break 'orm64_loop,
                        "help" => println!("{}", super::util::HELP_MESSAGE),
                        "srtupmsg" => println!("{}", self.lua.get_configuration_value::<String>("startup_message").unwrap()),
                        "api" => println!("{}", super::util::API_MESSAGE),
                        _ => self.lua.load(cmd)
                    }
                }
                Err(e) => {
                    println!("Failed to read input! {e}");
                }
            }
        }
    }
}