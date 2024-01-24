use orm64::core::Orm64;

fn main() {
    env_logger::init();
    let mut orm64 = Orm64::new();
    orm64.start();
}

