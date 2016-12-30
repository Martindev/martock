//! Camera is responsible for keeping track of the current viewing window. It is not coupled to the
//! player and may move independently.

use piston::input::Button;
use piston::input::Key;
use piston::input::Input;

use interactive;
use world;

// The amount of pixels by which the camera is nudged by input keys.
// TODO(jacob-zimmerman): Implement natural camera motion in response to input.
const NUDGE: f64 = 0.1;

#[derive(Copy, Clone)]
pub struct View {
    pub x: f64,
    pub y: f64,
    pub width: usize,
    pub height: usize,
}

impl View {
    fn new(x: f64, y: f64, width: usize, height: usize) -> Self {
        View {
            x: x,
            y: y,
            width: width,
            height: height,
        }
    }

    fn move_up(&mut self) {
        if self.y - NUDGE >= 0.0 {
            self.y -= NUDGE
        }
    }

    fn move_down(&mut self) {
        if self.y + NUDGE + self.height as f64 <= world::WORLD_HEIGHT as f64 {
            self.y += NUDGE
        }
    }

    fn move_right(&mut self) {
        self.x += NUDGE
    }

    fn move_left(&mut self) {
        self.x -= NUDGE
    }
}

// TODO(jacob-zimmerman): Ensure the camera cannot enter illegal (negative height) positions. This
// may require giving it knowledge of the screen size in blocks.
/// Camera represents a viewing window with a position which is the top left of the viewing window,
/// and dimensions in blocks.
pub struct Camera {
    view: View,
}

impl Camera {
    pub fn new(x: f64, y: f64, width: usize, height: usize) -> Self {
        Camera { view: View::new(x, y, width, height) }
    }

    /// view returns the focal area.
    pub fn view(&self) -> View {
        self.view
    }
}

impl interactive::Interactive for Camera {
    fn interact(&mut self, i: &Input) {
        if let Input::Press(b) = *i {
            if let Button::Keyboard(k) = b {
                match k {
                    Key::Left => self.view.move_left(),
                    Key::Right => self.view.move_right(),
                    Key::Up => self.view.move_up(),
                    Key::Down => self.view.move_down(),
                    _ => (),
                }
            }
        }
    }
}
