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

    /// block returns the coordinates of the block in which the point resides.
    pub fn block_pos(&self) -> (i64, u8) {
        let x = if (self.x() as i64) < 0 {
            (self.x() - 1.0) as i64
        } else {
            self.x() as i64
        };
        (x, self.y() as u8)
    }

    /// block offsets returns the percentage of the block in which it resides that it is offset
    /// from the top left of the block.
    pub fn block_offsets(&self) -> (f64, f64) {
        let x = if self.x() < 0.0 {
            1.0 - (self.x().abs() % 1.0)
        } else {
            self.x() % 1.0
        };
        (x, self.y() % 1.0)
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
