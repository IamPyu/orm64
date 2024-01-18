use std::collections::HashMap;
use rustyline::DefaultEditor;
use crate::lua::Orm64Lua;

/// An application for Orm64
pub trait Application {
    fn start(&mut self);
    fn update(&mut self);
}

pub struct Orm64<> {
    pub lua: Orm64Lua   
}

impl Orm64 {
    pub fn new() -> Self {
        return Self {
            lua: Orm64Lua::new()
        }
    }

    pub fn start(&mut self) {
        let mut reader = DefaultEditor::new().unwrap();
        println!("{}", self.lua.get_configuration_value::<String>("startup_message").unwrap());

        'orm64_loop: loop {
            let cmd = reader.readline(format!("{}", self.lua
                .get_configuration_value::<String>("prompt").unwrap())
                .as_str())
            .unwrap();
            reader.add_history_entry(&cmd).unwrap();


            match cmd.as_str() {
                "exit" => break 'orm64_loop,
                "help" => println!("{}", super::util::HELP_MESSAGE),
                "srtupmsg" => println!("{}", self.lua.get_configuration_value::<String>("startup_message").unwrap()),
                _ => self.lua.load(cmd)
            }
        }
    }
}
