//! world is the objective world manager for martock.

use block;

#[derive(Copy, Clone)]
pub struct BlockID;

/// World manages changing and accessing the state of the world, which is a three dimensional array
/// of blocks which can vary in state and behavior. World is explicitly not responsible for
/// determining the content of the world by itself; World should not modify the state of the world
/// except in fulfillment of a user's request.
pub struct World {    
}

impl World {
    /// new creates a new world
    pub fn new() -> Self {
        World {}
    }

    pub fn set_block(&mut self, _: BlockID, _: block::Block) {}
}
