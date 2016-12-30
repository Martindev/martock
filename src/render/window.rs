//! window represents a rendered portion of the world.

#[derive(Debug, PartialEq)]
pub struct Window {
    pub x: i64,
    pub y: u8,
    pub translate_x: f64,
    pub translate_y: f64,
}

impl Window {
    pub fn new(x: f64, y: f64) -> Self {
        let mut window = Window {
            x: x as i64,
            y: y as u8,
            translate_x: (x % 1.0) * -1.0,
            translate_y: (y % 1.0) * -1.0,
        };
        if x < 0.0 {
            window.x -= 1;
            window.translate_x = (1.0 - (x % 1.0).abs()) * -1.0;
        }
        window
    }
}
