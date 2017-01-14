//! block is the atomic unit of the world.

#[derive(Copy, Clone, PartialEq, Debug)]
pub enum Block {
    Void,
    Ether,
    Ground,
}

impl Default for Block {
    fn default() -> Self {
        Block::Void
    }
}
