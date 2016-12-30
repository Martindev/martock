//! Camera is responsible for keeping track of the current viewing window. This does not
//! necessarily mean that it is coupled to the player; the camera should be able to move
//! independently of the player.
//!
//! There should be one static camera instance (i.e., multiple cameras should not be created).
//!
//! The camera has a relative position in the world. This is a two-dimensional floating point value

use piston::input::Button;
use piston::input::Key;
use piston::input::Input;

use interactive;

// The amount of pixels by which the camera is nudged by input keys.
// TODO(jacob-zimmerman): Implement natural camera motion in response to input.
const NUDGE: f64 = 0.1;

#[derive(Copy, Clone)]
pub struct Position {
    pub x: f64,
    pub y: f64,
}

// TODO(jacob-zimmerman): Ensure the camera cannot enter illegal (negative height) positions. This
// may require giving it knowledge of the screen size in blocks.
pub struct Camera {
    position: Position,
}

impl Camera {
    pub fn new(initial_position: Position) -> Self {
        Camera { position: initial_position }
    }

    /// position returns the top left of the focal area.
    pub fn position(&self) -> Position {
        self.position
    }
}

impl interactive::Interactive for Camera {
    fn interact(&mut self, i: &Input) {
        if let Input::Press(b) = *i {
            if let Button::Keyboard(k) = b {
                match k {
                    Key::Left => self.position.x -= NUDGE,
                    Key::Right => self.position.x += NUDGE,
                    Key::Up => self.position.y -= NUDGE,
                    Key::Down => self.position.y += NUDGE,
                    _ => (),
                }
            }
        }
    }
}
