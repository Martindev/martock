//! point manages absolute world locations.

use world;

/// Point represents an absolute world location safely; it will never represent an invalid world
/// location.
#[derive(PartialEq, Debug, Copy, Clone)]
pub struct Point {
    x: f64,
    y: YCoord,
}

impl Point {
    pub fn from(x: f64, y: f64) -> Self {
        Point {
            x: x,
            y: YCoord::from(y),
        }
    }

    pub fn x(&self) -> f64 {
        self.x
    }

    pub fn y(&self) -> f64 {
        self.y.val()
    }
}

#[derive(PartialEq, Debug, Copy, Clone)]
struct YCoord {
    y: f64,
}

impl YCoord {
    fn from(y: f64) -> Self {
        let mut coord = YCoord { y: y };
        if coord.y < world::FLOOR as f64 {
            coord.y = world::FLOOR as f64
        } else if coord.y > world::HEIGHT as f64 {
            coord.y = world::HEIGHT as f64
        }
        coord
    }

    fn val(&self) -> f64 {
        self.y
    }
}
