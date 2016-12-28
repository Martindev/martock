#[derive(Copy, Clone, PartialEq, Debug)]
pub enum Block {
    Void,
    Ether,
}

impl Default for Block {
    fn default() -> Self {
        Block::Void
    }
}
