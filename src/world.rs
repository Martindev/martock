//! world is the objective world manager for martock.

use std;
use std::collections::HashMap;

use block;

const CHUNK_HEIGHT: usize = std::u8::MAX as usize;
const CHUNK_WIDTH: usize = std::u8::MAX as usize;
struct Chunk {
    blocks: [[block::Block; CHUNK_HEIGHT]; CHUNK_WIDTH],
}

impl Chunk {
    fn new() -> Self {
        Chunk { blocks: [[block::Block::Void; CHUNK_HEIGHT]; CHUNK_WIDTH] }
    }
}

struct Coords {
    chunk: i64,
    x: usize,
    y: usize,
}

impl Coords {
    fn from(x: i64, y: u8) -> Self {
        let chunk_x = if x < 0 {
            x as usize % CHUNK_WIDTH + (CHUNK_WIDTH - 1)
        } else {
            x as usize % CHUNK_WIDTH
        };
        Coords {
            chunk: x / CHUNK_WIDTH as i64,
            x: chunk_x,
            y: y as usize,
        }
    }
}

/// World manages changing and accessing the state of the world, which is a three dimensional array
/// of blocks which can vary in state and behavior. World is explicitly not responsible for
/// determining the content of the world by itself; World should not modify the state of the world
/// except in fulfillment of a user's request.
pub struct World {
    grid: HashMap<i64, Chunk>,
}

impl World {
    /// new creates a new world
    pub fn new() -> Self {
        World { grid: HashMap::new() }
    }

    pub fn block(&self, x: i64, y: u8) -> Option<block::Block> {
        let c = Coords::from(x, y);
        if self.grid.contains_key(&c.chunk) {
            match self.grid[&c.chunk].blocks[c.x][c.y] {
                block::Block::Void => None,
                v => Some(v),
            }
        } else {
            None
        }
    }

    pub fn set_block(&mut self, x: i64, y: u8, next_state: block::Block) {
        let c = Coords::from(x, y);
        if !self.grid.contains_key(&c.chunk) {
            self.grid.insert(c.chunk, Chunk::new());
        }
        self.grid.get_mut(&c.chunk).unwrap().blocks[c.x][c.y] = next_state;
    }
}
