//! interactive is anything influenced by user input.

use piston::input::Input;

pub trait Interactive {
    fn interact(&mut self, i: &Input);
}
