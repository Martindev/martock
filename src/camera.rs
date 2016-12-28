//! camera views the world for the user.

use piston_window;
use piston_window::WindowSettings;
use sdl2_window;

use body;
use life;
use world;

pub struct Camera {
    window: sdl2_window::Sdl2Window,
}

impl Camera {
    /// new creates a Camera with a viewing size of width by height pixels.
    pub fn new(width: usize, height: usize) -> Result<Self, String> {
        let size = piston_window::Size {
            width: width as u32,
            height: height as u32,
        };
        match WindowSettings::new("martock", size).build() {
            Err(e) => Err(e),
            Ok(w) => Ok(Camera { window: w }),
        }
    }
}

impl life::Life for Camera {
    fn update(&mut self, _: &world::World, _: &[&body::Body]) {}
}
