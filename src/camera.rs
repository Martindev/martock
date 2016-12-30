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

/// View represents a focal area of the world.
#[derive(Copy, Clone, Debug)]
pub struct View {
    x: f64,
    y: f64,

    /// width of window in blocks.
    pub width: usize,
    /// height of window in blocks.
    pub height: usize,

    /// x-index of the top left block in the view.
    pub block_x: i64,
    /// y-index of the top left block in the view.
    pub block_y: u8,

    /// x-translation of view to represent in-block position (multiply by block size in pixels).
    pub translate_x: f64,
    /// y-translation of view to represent in-block position (multiply by block size in pixels).
    pub translate_y: f64,
}

impl View {
    fn new(x: f64, y: f64, width: usize, height: usize) -> Self {
        let mut view = View {
            x: x,
            y: y,
            width: width,
            height: height,
            block_x: x as i64,
            block_y: y as u8,
            translate_x: (x % 1.0) * -1.0,
            translate_y: (y % 1.0) * -1.0,
        };
        if x < 0.0 {
            view.block_x -= 1;
            view.translate_x = (1.0 - (x % 1.0).abs()) * -1.0;
        }
        view
    }

    fn renew(&mut self, xdiff: f64, ydiff: f64) {
        *self = View::new(self.x + xdiff, self.y + ydiff, self.width, self.height)
    }

    fn move_up(&mut self) {
        if self.y - NUDGE >= 0.0 {
            self.renew(0.0, -NUDGE)
        }
    }

    fn move_down(&mut self) {
        if self.y + NUDGE + self.height as f64 <= world::HEIGHT as f64 {
            self.renew(0.0, NUDGE)
        }
    }

    fn move_right(&mut self) {
        self.renew(NUDGE, 0.0)
    }

    fn move_left(&mut self) {
        self.renew(-NUDGE, 0.0)
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
