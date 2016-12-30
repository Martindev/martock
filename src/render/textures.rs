//! textures provides textures for elements of the world.

use graphics::color::hex;
use graphics::Rectangle;

use block::Block;

/// block returns a texture for the given block.
fn block(b: Block) -> Rectangle {
    match b {
        Block::Void => Rectangle::new_border(hex("#ffffff"), 0.25),
        Block::Ether => Rectangle::new(hex("#aaaaaa")),
    }
}
