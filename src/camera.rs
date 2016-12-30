//! Camera is responsible for keeping track of the current viewing window. This does not
//! necessarily mean that it is coupled to the player; the camera should be able to move
//! independently of the player.
//!
//! There should be one static camera instance (i.e., multiple cameras should not be created).
//!
//! The camera has a relative position in the world. This is a two-dimensional floating point value

use interactive;
use piston::input::Input;

#[derive(Copy, Clone)]
pub struct Position {
    pub x: f64,
    pub y: f64,
}

pub struct Camera {
    position: Position,
}

impl Camera {
    pub fn new(initial_position: Position) -> Self {
        Camera { position: initial_position }
    }

    fn getPosition(&self) -> Position {
        self.position
    }
}

impl interactive::Interactive for Camera {
    fn interact(&mut self, i: &Input) {}
}
