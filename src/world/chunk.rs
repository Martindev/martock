use std;

use block;
use world;

const HEIGHT: usize = world::HEIGHT;
const WIDTH: usize = std::u8::MAX as usize;

pub struct Chunk {
    pub blocks: [[block::Block; HEIGHT]; WIDTH],
}

impl Chunk {
    pub fn new() -> Self {
        Chunk { blocks: [[block::Block::Void; HEIGHT]; WIDTH] }
    }
}

// Coords is the internal representation of a block's position in the world.
pub struct Coords {
    pub chunk: i64,
    pub x: usize,
    pub y: usize,
}

impl Coords {
    pub fn from(x: i64, y: u8) -> Self {
        let chunk_x = if x < 0 {
            x as usize % WIDTH + (WIDTH - 1)
        } else {
            x as usize % WIDTH
        };
        Coords {
            chunk: x / WIDTH as i64,
            x: chunk_x,
            y: y as usize,
        }
    }
}
