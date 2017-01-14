//! world manages the object world state.

mod chunk;
mod iter;
mod iter_test;

use std;
use std::collections::HashMap;

use block;

/// The world is WORLD_HEIGHT blocks tall and starts counting at FLOOR.
pub const HEIGHT: usize = std::u8::MAX as usize;
pub const FLOOR: usize = 0;

/// CHUNK_WIDTH is the width of allocated blocks of world. Use this as a hint if making many
/// modifications to the world to reduce allocations.
pub const CHUNK_WIDTH: usize = chunk::WIDTH;


/// World manages changing and accessing the state of the world, which is a three dimensional array
/// of blocks which can vary in state and behavior. World is explicitly not responsible for
/// determining the content of the world by itself; World should not modify the state of the world
/// except in fulfillment of a user's request.
///
/// From the user's perspective there is no concept of world boundaries; initialization is a
/// per-block property and blocks are not allocated contiguously.
pub struct World {
    grid: HashMap<i64, chunk::Chunk>,
}

impl World {
    /// new creates a new world.
    pub fn new() -> Self {
        World { grid: HashMap::new() }
    }

    /// Returns a block if it is initialized. If the block is Block::Void, it will return None.
    pub fn block(&self, x: i64, y: u8) -> Option<block::Block> {
        let c = chunk::Coords::from(x, y);
        if self.grid.contains_key(&c.chunk) {
            match self.grid[&c.chunk].blocks[c.x][c.y] {
                block::Block::Void => None,
                v => Some(v),
            }
        } else {
            None
        }
    }

    /// Sets a block state to the passed next_state. To deinitialize a Block, set the block state
    /// to Block::Void.
    pub fn set_block(&mut self, x: i64, y: u8, next_state: block::Block) {
        let c = chunk::Coords::from(x, y);
        if !self.grid.contains_key(&c.chunk) {
            self.grid.insert(c.chunk, chunk::Chunk::new());
        }
        self.grid.get_mut(&c.chunk).unwrap().blocks[c.x][c.y] = next_state;
    }

    /// iter returns an iterator over blocks starting at (x,y) moving to the right and down using a
    /// window defined by width and height.
    pub fn iter(&self, x: i64, y: u8, width: usize, height: usize) -> iter::BlockIter {
        iter::BlockIter::new(x, y, width, height, &self)
    }
}
